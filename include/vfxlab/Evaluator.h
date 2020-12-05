#pragma once

#include <blueprint/typedef.h>
#include <blueprint/BackendGraph.h>

#include <vfxgraph/Variant.h>
#include <vfxgraph/DrawList.h>

#include <boost/noncopyable.hpp>

#include <vector>

namespace vfxgraph { class DrawList; class RenderContext; }

namespace vfxlab
{

class Evaluator : boost::noncopyable
{
public:
	void Rebuild(const std::vector<bp::NodePtr>& nodes,
		const bp::BackendGraph<vfxgraph::Variant>& eval);

	void Draw(const std::shared_ptr<vfxgraph::RenderContext>& rc) const;

	bool IsEmpty() const { return m_passes.empty(); }

private:
	void Clear();

private:
	std::vector<std::unique_ptr<vfxgraph::DrawList>> m_passes;

}; // Evaluator

}