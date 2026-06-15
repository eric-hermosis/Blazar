#ifndef EXECUTION_HPP_0x45524943  
#define EXECUTION_HPP_0x45524943  

#include <vector>
#include <memory>
#include <blazar/graph.hpp>
#include <blazar/storage.hpp>

namespace blazar {

class Task;

} namespace blazar::execution {
 
class Item { 
public:
    void succeed(Item const& other);
    

private:
    Task* task_;
};  

class Visitor {
public:
    explicit Visitor(std::size_t size); 
    void resize(std::size_t size);  
    void visit(std::size_t index); 
    bool visited(std::size_t index) const; 
    void reset(); 
    std::size_t size() const;

private:
    std::vector<std::uint64_t> bits_;
};

class Plan {
public:
    Plan(std::size_t);
    ~Plan();
    Plan(Plan const&) = delete;
    Plan(Plan && other) = delete;
    auto operator=(Plan const&) = delete;
    auto operator=(Plan&&) noexcept = delete;

    template<class Expression>
    Plan(Expression const& expression) : Plan(expression.index()) {
        auto item = expression.forward(*this);
    }

    template<class Expression>
    auto visited(Expression const& expression) -> bool {
        return visitor_->visited(expression.index());
    }

    template<class Expression>
    void visit(Expression const& expression) {
        visitor_->visit(expression.index());
    }

private:     
    std::unique_ptr<Visitor> visitor_ = nullptr; 
};

}

#endif