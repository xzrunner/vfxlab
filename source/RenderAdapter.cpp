#include "vfxlab/RenderAdapter.h"
#include "vfxlab/PinType.h"
#include "vfxlab/RegistNodes.h"

#include <unirender/Device.h>
#include <facade/ImageLoader.h>

#include <boost/filesystem.hpp>

namespace
{

std::vector<std::pair<int, vfxgraph::VarType>> PAIR_TYPES = 
{
	{ vfxlab::PIN_TEXTURE,     vfxgraph::VarType::Texture },
	{ vfxlab::PIN_FLOAT,       vfxgraph::VarType::Float },
	{ vfxlab::PIN_FLOAT2,      vfxgraph::VarType::Float2 },
	{ vfxlab::PIN_FLOAT3,      vfxgraph::VarType::Float3 },
	{ vfxlab::PIN_FLOAT4,      vfxgraph::VarType::Float4 },
};

}

namespace vfxlab
{

int RenderAdapter::TypeBackToFront(vfxgraph::VarType type, int count)
{
    int ret = -1;

	for (auto& pair : PAIR_TYPES) {
		if (pair.second == type) {
			ret = pair.first;
			break;
		}
	}
	assert(ret >= 0);

    return ret;
}

vfxgraph::VarType RenderAdapter::TypeFrontToBack(int type)
{
	for (auto& pair : PAIR_TYPES) {
		if (pair.first == type) {
			return pair.second;
		}
	}
	assert(0);
	return vfxgraph::VarType::Unknown;
}

void RenderAdapter::Front2Back(const ur::Device& dev, const bp::Node& front,
                               dag::Node<vfxgraph::Variant>& back, const std::string& dir)
{
    auto type = front.get_type();
    if (type == rttr::type::get<node::Texture>())
    {
        auto& src = static_cast<const node::Texture&>(front);
        auto& dst = static_cast<vfxgraph::node::Texture&>(back);

        // update texture
        if (src.m_filepath != dst.GetFilepath() ||
            !dst.GetTexture())
        {
            auto filepath = boost::filesystem::absolute(src.m_filepath, dir).string();
            facade::ImageLoader loader(filepath);

            if (loader.Load(dev)) {
                dst.SetFilepath(filepath);
                dst.SetTexture(loader.GetTexture());
            } else {
                dst.SetFilepath("");
                dst.SetTexture(nullptr);
            }
        }

        // update sample
        if (src.m_wrap != dst.GetWrapping() ||
            src.m_filter != dst.GetFiltering() ||
            !dst.GetSampler())
        {
            ur::TextureWrap ur_wrap;
            switch (src.m_wrap)
            {
            case vfxgraph::node::Texture::Wrapping::Repeat:
                ur_wrap = ur::TextureWrap::Repeat;
                break;
            case vfxgraph::node::Texture::Wrapping::MirroredRepeat:
                ur_wrap = ur::TextureWrap::MirroredRepeat;
                break;
            case vfxgraph::node::Texture::Wrapping::ClampToEdge:
                ur_wrap = ur::TextureWrap::ClampToEdge;
                break;
            case vfxgraph::node::Texture::Wrapping::ClampToBorder:
                ur_wrap = ur::TextureWrap::ClampToBorder;
                break;
            default:
                assert(0);
            }

            ur::TextureMinificationFilter ur_min_filter;
            ur::TextureMagnificationFilter ur_mag_filter;
            switch (src.m_filter)
            {
            case vfxgraph::node::Texture::Filtering::Nearest:
                ur_min_filter = ur::TextureMinificationFilter::Nearest;
                ur_mag_filter = ur::TextureMagnificationFilter::Nearest;
                break;
            case vfxgraph::node::Texture::Filtering::Linear:
                ur_min_filter = ur::TextureMinificationFilter::Linear;
                ur_mag_filter = ur::TextureMagnificationFilter::Linear;
                break;
            }

            dst.SetWrapping(src.m_wrap);
            dst.SetFiltering(src.m_filter);

            auto sampler = dev.CreateTextureSampler(ur_min_filter, ur_mag_filter, ur_wrap, ur_wrap);
            dst.SetSampler(sampler);
        }
    }
}

}