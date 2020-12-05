#pragma once

#include "vfxlab/Node.h"

#include <vfxgraph/node/Texture.h>

namespace vfxlab
{

void nodes_regist_rttr();

namespace node
{

#define EXE_FILEPATH "vfxlab/node_def_gen.h"
#include "vfxlab/node_regist_cfg.h"
#undef EXE_FILEPATH

#define GRP_DEFINE_NODE(type, name, preview, group, prop) \
class type : public Node                                  \
{                                                         \
public:                                                   \
	type()                                                \
		: Node(#name, preview)                            \
	{                                                     \
		InitPins(#name);                                  \
        SetGroup(XSTR(group));                            \
	}                                                     \
                                                          \
	prop                                                  \
	RTTR_ENABLE(Node)                                     \
};

#define GRP_NODE_PROP

}
}