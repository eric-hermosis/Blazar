#ifndef TENSORS_HPP_0x45524943 
#define TENSORS_HPP_0x45524943 

#include <blazar/variables.hpp>
#include <blazar/storage.hpp>

namespace blazar {
  
class Tensor : public Variable {
public:
    using Variable::Variable; 
 

    void initialize(Environment const& environment) const {
        storage_ = Storage(this->bytes(), environment);
    }

private:
    mutable Storage storage_; 
};

};

#endif