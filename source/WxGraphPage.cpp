#include "vfxlab/WxGraphPage.h"
#include "vfxlab/MessageID.h"
#include "vfxlab/RenderAdapter.h"

#include <ee0/WxStageCanvas.h>

#include <vfxgraph/RenderContext.h>

#include <boost/filesystem.hpp>

namespace vfxlab
{

WxGraphPage::WxGraphPage(const ur::Device& dev, wxWindow* parent, const ee0::GameObj& root,
                         const ee0::SubjectMgrPtr& preview_sub_mgr)
    : bp::WxGraphPage<vfxgraph::Variant>(parent, root, preview_sub_mgr, MSG_RENDERER_CHANGED, "vfxgraph", "vfxlab",
        [&](const bp::Node& front, dag::Node<vfxgraph::Variant>& back) {
        auto dir = boost::filesystem::path(m_filepath).parent_path().string();
        RenderAdapter::Front2Back(dev, front, back, dir);
    })
{
}

void WxGraphPage::SetCanvas(const std::shared_ptr<ee0::WxStageCanvas>& canvas)
{
    GetImpl().SetCanvas(canvas);

    auto ctx = std::make_shared<vfxgraph::RenderContext>();
    m_ctx = ctx;

    ctx->ur_dev = &canvas->GetRenderDevice();
    ctx->ur_ctx = canvas->GetRenderContext().ur_ctx.get();

    GetSceneTree()->GetCurrEval()->SetContext(ctx);
}

void WxGraphPage::OnEvalChangeed()
{
    auto root = GetSceneTree()->GetRootNode();

    std::vector<bp::NodePtr> nodes;

    assert(root->HasSharedComp<n0::CompComplex>());
    auto& ccomplex = root->GetSharedComp<n0::CompComplex>();
    for (auto& child : ccomplex.GetAllChildren())
    {
        if (!child->HasUniqueComp<bp::CompNode>()) {
            continue;
        }
        auto bp_node = child->GetUniqueComp<bp::CompNode>().GetNode();
        if (bp_node) {
            nodes.push_back(bp_node);
        }
    }

    m_front_eval.Rebuild(nodes, *GetSceneTree()->GetRootGraph());
}

}