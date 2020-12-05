#include "vfxlab/PinCallback.h"
#include "vfxlab/PinType.h"

#include <painting0/Color.h>
#include <blueprint/Pin.h>

#include <string>
#include <set>

namespace
{

const pt0::Color COL_DEFAULT   = pt0::Color(255, 255, 255);

const pt0::Color COL_TEXTURE   = pt0::Color(132, 228, 231);

std::string get_desc_func(const std::string& name, int type)
{
    std::string ret = name;
    switch (type)
    {
    case vfxlab::PIN_TEXTURE:
        ret += "(T)";
        break;
    case vfxlab::PIN_FLOAT:
        ret += "(1)";
        break;
    case vfxlab::PIN_FLOAT2:
        ret += "(2)";
        break;
    case vfxlab::PIN_FLOAT3:
        ret += "(3)";
        break;
    case vfxlab::PIN_FLOAT4:
        ret += "(4)";
        break;
    }
    return ret;
}

const pt0::Color& get_color_func(int type)
{
    switch (type)
    {
    case vfxlab::PIN_TEXTURE:
        return COL_TEXTURE;
    default:
        return COL_DEFAULT;
    }
}

bool can_type_cast_func(int type_from, int type_to)
{
    if (type_from == type_to) {
        return true;
    }
    if (type_from == bp::PIN_ANY_VAR ||
        type_to == bp::PIN_ANY_VAR) {
        return true;
    }
    
    return false;
}

}

namespace vfxlab
{

void InitPinCallback()
{
    bp::Pin::SetExtendFuncs({
        get_desc_func,
        get_color_func,
        can_type_cast_func
    });
}

}