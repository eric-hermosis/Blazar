#include <stack>
#include <blazar/execution.hpp>
#include <blazar/storage.hpp> 
#include <blazar/trace.hpp>

namespace blazar::execution {  

Item::Item(Task* task) {
    task_ = task; 
}
 
auto Item::get() const -> Task* {
    return task_;
}

void Item::succeed(Item const& other) {
    if (task_ && other.task_) {
        task_-> link(other.task_);
    }
} 

static thread_local struct {
    std::stack<std::unique_ptr<Tasks>> free;
} pool;

Items::Items(std::size_t count) { 
    if (pool.free.empty()) {
        tasks_ = std::make_unique<Tasks>(count); 
    } 
    
    else { 
        tasks_ = std::move(pool.free.top());
        tasks_-> resize(count);  
        pool.free.pop();
    }
}

Items::~Items() {
    if (tasks_) {
        tasks_->clear();
        pool.free.push(std::move(tasks_));
    }
};  

bool Items::has(Index index) {
    return tasks_->has(index);
}

auto Items::get(Index index) -> Item {
    return Item(tasks_->get(index));
}

auto Items::create(Index index) -> Item {
    return Item(tasks_->create(index));
}

}