#include "vfxlab/RegistNodes.h"

#include <ee0/ReflectPropTypes.h>

#include <js/RTTR.h>

#define REGIST_NODE_RTTI(type, name, prop)                                \
	rttr::registration::class_<vfxlab::node::type>("vfxlab::"#name) \
		.constructor<>()                                                  \
		prop                                                              \
	;

#define PROP
#define REGIST_NODE_RTTI_DEFAULT(type, name) REGIST_NODE_RTTI(type, name, PROP)

RTTR_REGISTRATION
{

// base

rttr::registration::class_<vfxlab::Node>("vfxlab::node")
.property("name", &vfxlab::Node::GetName, &vfxlab::Node::SetName)
(
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Name"))
)
;

#define EXE_FILEPATH "vfxlab/node_rttr_gen.h"
#define SKIP_FILE_NODE
#include "vfxlab/node_regist_cfg.h"
#undef SKIP_FILE_NODE
#undef EXE_FILEPATH

}

namespace vfxlab
{

void nodes_regist_rttr()
{
}

}