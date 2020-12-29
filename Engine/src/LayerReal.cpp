#include "LayerReal.h"

namespace Lavender
{
	LayerReal::LayerReal() : m_Root() { }

	Real* LayerReal::AddNewRoot(const Info* info)
	{
		m_Root.push_back(make_unique<Real>(info));
		return m_Root.back().get();
	}

	Real* LayerReal::GetRootAt(unsigned int index)
	{
		if (index >= GetRootCount()) { return nullptr; }
		return m_Root[index].get();
	}
	unsigned int LayerReal::GetRootCount() { return m_Root.size(); }
}