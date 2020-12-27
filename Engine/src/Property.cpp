#include "Property.h"
namespace Lavender
{
	Property::Property(Type type, void* value) : m_Type(type), m_Value(value) { }

	Property::Type Property::GetType() const { return m_Type; }
	const void* Property::GetValue() const { return &m_Value; }
}