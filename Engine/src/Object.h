#pragma once
#include <memory>
#include <vector>
#include "Information.h"

namespace Lavender
{
	// Entity in REAL layer. Has children that build a hiearachy
	class Object
	{
	private:
		std::weak_ptr<Information> m_Info;
		std::vector<std::unique_ptr<Object>> m_Children;

	public:
		Object(std::shared_ptr<Information> info);
	};
}


