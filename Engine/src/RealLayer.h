#pragma once
#include <memory>
#include "Object.h"

namespace Lavender
{
	class RealLayer
	{
	private:
		std::unique_ptr<Object> m_Root;
	public:
		RealLayer();
	};
}