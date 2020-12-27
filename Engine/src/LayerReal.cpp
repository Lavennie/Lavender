#include "LayerReal.h"

namespace Lavender
{
	LayerReal::LayerReal() : m_Root() { }

	Real* LayerReal::AddNewRoot(const Info* info)
	{
		m_Root.push_back(make_unique<Real>(info));
		return m_Root[m_Root.size() - 1].get();
	}
}