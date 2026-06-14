#include <blazar/execution.hpp>
#include <blazar/storage.hpp> 

namespace blazar::execution {

Item::Item(Storage const& storage) {
    memory_ = storage.get();
}  

}