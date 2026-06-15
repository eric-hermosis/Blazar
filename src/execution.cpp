#include <stack>
#include <blazar/execution.hpp>
#include <blazar/storage.hpp> 

namespace blazar::execution { 
  
Visitor::Visitor(std::size_t size) {
    resize(size);
}

void Visitor::resize(std::size_t size) {
    bits_.resize((size + 63) / 64, 0);
}

void Visitor::visit(std::size_t index) {
    std::size_t word = index / 64;
    std::size_t bit  = index % 64;
    bits_.at(word) |= (std::uint64_t(1) << bit);
}

bool Visitor::visited(std::size_t index) const {
    std::size_t word = index / 64;
    std::size_t bit  = index % 64;
    return bits_.at(word) & (std::uint64_t(1) << bit);
}

void Visitor::reset() {
    std::fill(bits_.begin(), bits_.end(), 0);
}

std::size_t Visitor::size() const {
    return bits_.size();
} 

static thread_local struct {
    std::stack<std::unique_ptr<Visitor>> free;
} pool;
 
Plan::Plan(std::size_t size) {
    if (pool.free.empty()) {
        visitor_ = std::make_unique<Visitor>(size);
    } 
    
    else {
        visitor_ = std::move(pool.free.top());
        visitor_->resize(size);
        visitor_->reset();
        pool.free.pop();
    }
}

Plan::~Plan() {
    if (visitor_) {
        pool.free.push(std::move(visitor_));
    }
}

}