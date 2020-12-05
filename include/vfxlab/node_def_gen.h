#define XSTR(s) STR(s)
#define STR(s) #s

#ifndef PARM_NODE_TYPE
#error "You must define PARM_NODE_TYPE macro before include this file"
#endif

#ifndef PARM_NODE_NAME
#error "You must define PARM_NODE_NAME macro before include this file"
#endif

#ifndef PARM_FILEPATH
#define PARM_FILEPATH vfxgraph/node/##PARM_NODE_TYPE##.parm.h
#endif

class PARM_NODE_TYPE : public Node
{
public:
	PARM_NODE_TYPE()
#ifdef ENABLE_NODE_PREVIEW
        : Node(XSTR(PARM_NODE_TYPE), true)
#else
        : Node(XSTR(PARM_NODE_TYPE), false)
#endif // ENABLE_NODE_PREVIEW
	{
        InitPins(XSTR(PARM_NODE_NAME));

#ifdef NODES_GROUP_NAME
        SetGroup(XSTR(NODES_GROUP_NAME));
#endif // NODES_GROUP_NAME
	}

#define PARAM_INFO(id, type, name, member, default_val) \
    type member = type##default_val;
#ifndef NO_PARM_FILEPATH
#include XSTR(PARM_FILEPATH)
#endif // NO_PARM_FILEPATH
#undef  PARAM_INFO

	RTTR_ENABLE(Node)
};

#undef PARM_NODE_NAME
#undef PARM_NODE_TYPE
#undef PARM_FILEPATH

#undef NO_PARM_FILEPATH
#undef ENABLE_NODE_PREVIEW