#include "vfxlab/Evaluator.h"
#include "vfxlab/node/PassEnd.h"

#include <vfxgraph/Node.h>
#include <vfxgraph/DrawList.h>
#include <vfxgraph/typedef.h>
#include <vfxgraph/RenderContext.h>

namespace
{

class PassCmp
{
public:
	bool operator () (const std::shared_ptr<vfxlab::node::PassEnd>& p0,
                      const std::shared_ptr<vfxlab::node::PassEnd>& p1) const {
        return p0->GetOrder() < p1->GetOrder();
    }
}; // PassCmp

}

namespace vfxlab
{

void Evaluator::Rebuild(const std::vector<bp::NodePtr>& nodes, 
	                    const bp::BackendGraph<vfxgraph::Variant>& eval)
{
    Clear();

    std::vector<vfxgraph::NodePtr> back_nodes;
    for (auto& n : nodes) 
    {
        auto back_node = eval.QueryBackNode(*n);
        if (back_node) {
            back_nodes.push_back(std::static_pointer_cast<vfxgraph::Node>(back_node));
        }
    }
    m_passes.push_back(std::make_unique<vfxgraph::DrawList>(back_nodes));
}

void Evaluator::Draw(const std::shared_ptr<vfxgraph::RenderContext>& rc) const
{
    for (auto& p : m_passes) {
        bool finished = p->Draw(rc);
        if (finished) {
            break;
        }
    }
}

void Evaluator::Clear()
{
	m_passes.clear();
}

}