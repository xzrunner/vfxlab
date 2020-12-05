#pragma once

#include <dag/Node.h>
#include <vfxgraph/Variant.h>

namespace bp { class Node; }
namespace ur { class Device; }

namespace vfxlab
{

class Evaluator;

class RenderAdapter
{
public:
    static int TypeBackToFront(vfxgraph::VarType type, int count);
	static vfxgraph::VarType TypeFrontToBack(int type);

    static void Front2Back(const ur::Device& dev, const bp::Node& front,
        dag::Node<vfxgraph::Variant>& back, const std::string& dir);

}; // RenderAdapter

}