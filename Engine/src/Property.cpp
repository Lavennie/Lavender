#include "Property.h"
#include "Logging/Logging.h"
#include <iostream>
namespace Lavender
{
	Property::Property(Type type, PropertyValue* value) : m_Type(type)
	{
		switch (type)
		{
		case Property::Type::Position:
		case Property::Type::Scale:
			m_Value = make_unique<PropertyVector3>(*(PropertyVector3*)value);
			break;
		case Property::Type::Rotation:
			m_Value = make_unique<PropertyRotation>(*(PropertyRotation*)value);
			break;
		case Property::Type::Mesh:
			m_Value = make_unique<PropertyModel>(*(PropertyModel*)value);
			break;
		case Property::Type::Shader:
			m_Value = make_unique<PropertyShading>(*(PropertyShading*)value);
			break;
		default:
			Log::PrintError("Property constructor does not support given Property::Type");
			break;
		}
	}
	Property::Type Property::GetType() const { return m_Type; }
	PropertyValue* Property::GetValue() const { return m_Value.get(); }
}