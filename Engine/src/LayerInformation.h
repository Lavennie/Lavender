#pragma once
#include <vector>
#include "Information.h"

namespace Lavender
{
	class LayerInformation
	{
	private:
		std::vector<Information> m_Information;
	public:
		LayerInformation(int infoCount);
	};
}