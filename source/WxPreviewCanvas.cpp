#include "vfxlab/WxPreviewCanvas.h"
#include "vfxlab/MessageID.h"
#include "vfxlab/WxGraphPage.h"

#include <ee0/WxStagePage.h>
#include <ee0/SubjectMgr.h>

#include <renderpipeline/RenderMgr.h>
#include <vfxgraph/RenderContext.h>
#include <painting3/PerspCam.h>

namespace vfxlab
{

WxPreviewCanvas::WxPreviewCanvas(const ur::Device& dev, ee0::WxStagePage* stage,
                                 ECS_WORLD_PARAM const ee0::RenderContext& rc)
    : ee3::WxStageCanvas(dev, stage, ECS_WORLD_VAR &rc, nullptr, true)
{
    auto sub_mgr = stage->GetSubjectMgr();
    sub_mgr->RegisterObserver(MSG_RENDERER_CHANGED, this);
}

WxPreviewCanvas::~WxPreviewCanvas()
{
    if (m_graph_page)
    {
        auto sub_mgr = m_graph_page->GetSubjectMgr();
        sub_mgr->UnregisterObserver(ee0::MSG_NODE_SELECTION_INSERT, this);
    }

    auto sub_mgr = m_stage->GetSubjectMgr();
    sub_mgr->UnregisterObserver(MSG_RENDERER_CHANGED, this);
}

void WxPreviewCanvas::OnNotify(uint32_t msg, const ee0::VariantSet& variants)
{
    ee3::WxStageCanvas::OnNotify(msg, variants);

	switch (msg)
	{
    case MSG_RENDERER_CHANGED:
        SetDirty();
        break;
	}
}

void WxPreviewCanvas::DrawBackground3D() const
{
//    ee3::WxStageCanvas::DrawBackgroundGrids(10.0f, 0.2f);
//    ee3::WxStageCanvas::DrawBackgroundCross();
}

void WxPreviewCanvas::DrawForeground3D() const
{
    if (!m_graph_page) {
        return;
    }

    auto& eval = m_graph_page->GetFrontEval();
    if (eval.IsEmpty()) {
        return;
    }

    auto& ctx = *GetRenderContext().ur_ctx;
    rp::RenderMgr::Instance()->SetRenderer(m_dev, ctx, rp::RenderType::EXTERN);

    auto rc = std::make_shared<vfxgraph::RenderContext>();
    rc->ur_dev = &m_dev;
    rc->ur_ctx = GetRenderContext().ur_ctx.get();

    eval.Draw(rc);
}

void WxPreviewCanvas::DrawForeground2D() const
{
}

void WxPreviewCanvas::OnTimer()
{
    SetDirty();
}

}