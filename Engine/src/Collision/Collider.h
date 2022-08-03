#pragma once

namespace Lavender
{
	struct Collider
	{
	public:
		enum class Type { Point, Sphere };

	public:
		Collider() {}
		virtual ~Collider() {}

		virtual Type GetType() const = 0;
	};
}

