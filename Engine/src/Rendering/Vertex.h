#pragma once
#include "Math/Vector2.h"
#include "Math/Vector3.h"

namespace Lavender
{
	struct Vertex
	{
		Vector3 position;
		Vector2 texCoord;
		Vector3 normal;

		Vertex();
		Vertex(Vector3 position, Vector2 texCoord, Vector3 normal);
	};
}