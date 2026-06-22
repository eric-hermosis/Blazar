#include <cassert> 
#include <stack>
#include <vector>
#include <deque> 
#include <blazar/trace.hpp>

namespace blazar {   

Node::Node() {
    sources_.reserve(4);
}

Node::~Node() {}

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

void Node::set(Storage const& storage) {
    memory_ = storage.get();
    if (memory_) {
        memory_-> acquire();
    }
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
        if (memory_) {
            memory_-> release();
            memory_ = nullptr;
        }
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

} namespace blazar::execution { 
    
Task::Task() {
    sources_.reserve(4); 
}

auto Task::arity() const noexcept -> std::size_t {
    return sources_.size();
}

void Task::link(Task* source) {
    assert(source);
    sources_.push_back(source); 
}
  
void Task::prune() {
    sources_.clear();
}

static thread_local struct {
    std::stack<Task> arena;
    std::stack<Task*, std::vector<Task*>> free; 
} tasks;

Tasks::Tasks(std::size_t count) {
    checklist_.resize(count);
    std::fill(checklist_.begin(), checklist_.end(), nullptr); 
} 

auto Tasks::allocate(std::size_t index) -> Task* { 
    assert(checklist_[index] == nullptr);
    if (tasks.free.empty()) {
        tasks.arena.emplace();
        tasks.free.push(&tasks.arena.top());
    }
    auto task = tasks.free.top(); 
    checklist_[index] = task;
    tasks.free.pop(); 
    return task; 
} 

void Tasks::resize(std::size_t count) {
    checklist_.resize(count, nullptr);
}

void Tasks::clear() {
    for (std::size_t index = 0; index < checklist_.size(); ++index) {
        if (checklist_[index]) {
            tasks.free.push(checklist_[index]);
            checklist_[index] = nullptr;
        }
    }
}

bool Tasks::has(std::size_t index) noexcept { 
    return checklist_[index] ? true : false;
}

auto Tasks::get(std::size_t index) -> Task* { 
    return checklist_[index];
}

}