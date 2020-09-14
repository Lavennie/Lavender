#include "Vertex.h"

namespace Lavender
{
	Vertex::Vertex() : position(Vector3()), texCoord(Vector2()), normal(Vector3()) {}
	Vertex::Vertex(Vector3 position, Vector2 texCoord, Vector3 normal) : position(position), texCoord(texCoord), normal(normal) { }
}