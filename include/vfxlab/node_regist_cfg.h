#ifndef EXE_FILEPATH
#error "You must define EXE_FILEPATH macro before include this file"
#endif

#undef NO_PARM_FILEPATH

// common

#define NODES_GROUP_NAME Common

#define PARM_NODE_TYPE Float
#define PARM_NODE_NAME float1
#include EXE_FILEPATH

#define PARM_NODE_TYPE Float2
#define PARM_NODE_NAME float2
#include EXE_FILEPATH

#define PARM_NODE_TYPE Float3
#define PARM_NODE_NAME float3
#include EXE_FILEPATH

#define PARM_NODE_TYPE Float4
#define PARM_NODE_NAME float4
#include EXE_FILEPATH

#define PARM_NODE_TYPE Texture
#define PARM_NODE_NAME texture
#define ENABLE_NODE_PREVIEW
#include EXE_FILEPATH

#undef NODES_GROUP_NAME

// fluid2d

#define NODES_GROUP_NAME Fluid2d

#define NO_PARM_FILEPATH
#define PARM_NODE_TYPE Copy
#define PARM_NODE_NAME copy
#include EXE_FILEPATH

#define NO_PARM_FILEPATH
#define PARM_NODE_TYPE RKAdvect
#define PARM_NODE_NAME rk_advect
#include EXE_FILEPATH

#undef NODES_GROUP_NAME
