#include "LayerReal.h"

namespace Lavender
{
	LayerReal::LayerReal() : m_Root(std::make_unique<Object>(nullptr)) { }
}