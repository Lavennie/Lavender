#pragma once
#include "Rendering/Mesh.h"

namespace Lavender
{
	class Property
	{
	public:
		enum class Type { Mesh, Position, Rotation };
	private:
		Type m_Type;
		void* m_Value;
	public:
		Property() = delete;
		Property(Type type, void* value);
		Type GetType() const;
		const void* GetValue() const;
	};
}

