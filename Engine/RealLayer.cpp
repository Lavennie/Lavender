#include "RealLayer.h"

namespace Lavender
{

	RealLayer::RealLayer() : m_Root(new Object()) { }
	RealLayer::~RealLayer()
	{
		delete m_Root;
	}
}