#include "vfxlab/Node.h"
#include "vfxlab/RenderAdapter.h"

#include <blueprint/Pin.h>
#include <blueprint/BackendAdapter.h>

#include <dag/Node.h>
#include <vfxgraph/Node.h>

namespace vfxlab
{

Node::Node(const std::string& title, bool preview)
    : bp::Node(title)
    , m_preview(preview)
{
}

Node::~Node() = default;

void Node::InitPins(const std::string& name)
{
	auto back2front = [](const dag::Node<vfxgraph::Variant>::Port& back) -> bp::PinDesc
	{
        bp::PinDesc front;

        front.type = RenderAdapter::TypeBackToFront(back.var.type.type, 1);
        const_cast<vfxgraph::Node::Port&>(back).var.full_name = back.var.type.name;
        front.name = back.var.full_name;

        return front;
	};

    bp::BackendAdapter<vfxgraph::Variant>
        trans("vfxgraph", back2front);
    trans.InitNodePins(*this, name);
}

}