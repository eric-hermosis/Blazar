#include <cassert> 
#include <stack>
#include <vector>
#include <deque>
#include <iostream>
#include <blazar/trace.hpp>

namespace blazar {  
 
Node::Node() {
    sources_.reserve(4);
}

void Node::set(Symbol const& symbol, Type const& type, Layout const& layout) { 
    shape_t shape;
    strides_t strides;

    for (auto dimension = 0; dimension < layout.rank(); dimension++) {
        shape.sizes[dimension] = layout.size(dimension);
        strides.sizes[dimension] = layout.stride(dimension);
    }

    body_ = node_t {
        .name = symbol.name().data(),
        .type = type,
        .layout {
            .rank = layout.rank(),
            .size = layout.size(), 
            .shape   = std::move(shape),
            .strides = std::move(strides)
        }
    };
} 

static thread_local struct {
    std::stack<Node> arena;
    std::stack<Node*, std::vector<Node*>> free; 
} nodes;

auto Node::allocate(Symbol const& symbol, Type const& type, Layout const& layout) -> Node* { 
    if (nodes.free.empty()) {
        nodes.arena.emplace();
        nodes.free.push(&nodes.arena.top());
    }
    auto node = nodes.free.top();
    node->acquire();
    node->set(symbol, type, layout);
    nodes.free.pop();
    return node; 
}

void Node::acquire() {
    ++references_; 
}

void Node::release() { 
    assert(references_ > 0 && "Assertion error: releasing empty resource");
    if (--references_ == 0) { 
        prune();
        nodes.free.push(this);
    }
}

auto Node::arity() const noexcept -> std::uint8_t {
    return sources_.size();
}

void Node::link(Node* source) { 
    assert(source);
    source -> acquire();
    sources_.push_back(source); 
}

void Node::prune() {   
    for (auto node : sources_) {
        node->release();
    }
    sources_.clear();
}

Task::Task() {
    sources_.reserve(4);
}

void Task::set() { 
} 

static thread_local struct {
    std::stack<Task> arena;
    std::stack<Task*, std::vector<Task*>> free; 
} tasks;

auto Task::allocate() -> Task* { 
    if (tasks.free.empty()) {
        tasks.arena.emplace();
        tasks.free.push(&tasks.arena.top());
    }
    auto task = tasks.free.top();
    task->acquire();
    task->set();
    tasks.free.pop();
    return task; 
} 

void Task::acquire() {
    ++references_; 
}

void Task::release() { 
    assert(references_ > 0 && "Assertion error: releasing empty resource");
    if (--references_ == 0) { 
        prune();
        tasks.free.push(this);
    }
}

auto Task::arity() const noexcept -> std::uint8_t {
    return sources_.size();
}

void Task::link(Task* source) { 
    assert(source);
    source -> acquire();
    sources_.push_back(source); 
}

void Task::prune() {   
    for (auto task : sources_) {
        task->release();
    }
    sources_.clear();
} 

}