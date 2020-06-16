#include "RealLayer.h"

namespace Lavender
{
	RealLayer::RealLayer() : m_Root(std::make_unique<Object>(nullptr)) { }
}