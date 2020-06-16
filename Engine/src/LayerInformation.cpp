#include "LayerInformation.h"

namespace Lavender
{
	LayerInformation::LayerInformation(int infoCount) : m_Information(std::vector<Information>())
	{
		m_Information.reserve(infoCount);
	}
}