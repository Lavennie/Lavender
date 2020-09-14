#pragma once
#include <memory>
#include "Object.h"

namespace Lavender
{
	class LayerReal
	{
	private:
		std::unique_ptr<Object> m_Root;
	public:
		LayerReal();
	};
}