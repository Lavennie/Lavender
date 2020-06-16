#include "Object.h"

namespace Lavender
{
	Object::Object(std::shared_ptr<Information> info) : m_Info(info), m_Children(std::vector<std::unique_ptr<Object>>())
	{
	}
}