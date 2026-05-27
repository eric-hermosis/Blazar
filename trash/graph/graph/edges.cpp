#include <blazar/graph/edges.hpp>
#include <blazar/graph/nodes.hpp>

namespace blazar {
 
Edge::Edge(Vertex const& source, Vertex const& target)
:   source_(source.node())
,   target_(target.node()) {
    target_->link(source_);
}

}