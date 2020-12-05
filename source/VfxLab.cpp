#include "vfxlab/VfxLab.h"
#include "vfxlab/PinCallback.h"
#include "vfxlab/Node.h"
#include "vfxlab/RegistNodes.h"

#include <blueprint/CompNode.h>
#include <blueprint/NodeBuilder.h>
#include <blueprint/node/Commentary.h>
#include <blueprint/node/Function.h>
#include <blueprint/node/Input.h>
#include <blueprint/node/Output.h>

#include <node0/CompIdentity.h>
#include <node0/SceneNode.h>
#include <node2/UpdateSystem.h>
#include <renderpipeline/RenderPipeline.h>
#include <vfxgraph/VfxGraph.h>

namespace bp
{
extern void regist_sm_rttr();
extern void regist_pt0_rttr();
}

namespace vfxlab
{
extern void nodes_regist_rttr();
}

namespace vfxlab
{

CU_SINGLETON_DEFINITION(VfxLab);

VfxLab::VfxLab()
{
    rp::RenderPipeline::Instance();
    vfxgraph::VfxGraph::Instance();

    RegistRTTR();

	Init();
	InitNodes();

    InitPinCallback();
}

void VfxLab::RegistRTTR()
{
    bp::regist_sm_rttr();
    bp::regist_pt0_rttr();

    //prop_types_regist_rttr();
    nodes_regist_rttr();

	//vfxlab::prop_types_regist_rttr();
	vfxlab::nodes_regist_rttr();
}

void VfxLab::Init()
{
}

void VfxLab::InitNodes()
{
    const int bp_count = 1;

	auto list = rttr::type::get<Node>().get_derived_classes();
	m_nodes.reserve(bp_count + list.size());

    m_nodes.push_back(std::make_shared<bp::node::Commentary>());

	for (auto& t : list)
	{
		auto obj = t.create();
		assert(obj.is_valid());
		auto node = obj.get_value<bp::NodePtr>();
		assert(node);
		m_nodes.push_back(node);
	}
}

}