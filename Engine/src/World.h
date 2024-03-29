#pragma once
#include <memory>
#include "LayerConcept.h"
#include "LayerReal.h"
#include "Rendering/Camera.h"
#include "Rendering/Shader.h"
#include "Input/Input.h"
#include "Core.h"

namespace Lavender
{
	using namespace std;

	class World
	{
	private:
		Camera m_Camera;
		LayerConcept<Idea> m_IdeaLayer;
		LayerConcept<SubIdea> m_SubIdeaLayer;
		LayerConcept<Info> m_InfoLayer;
		LayerReal m_RealLayer;
	private:
		World(const World&) = delete;
		World& operator=(const World&) = delete;
	public:
		World(float fov, Vector2 windowSize, float zNear, float);

		void Update();
		void Render();
		void UpdateSound();
		void UpdateColliders();

		Idea& InitIdea(const Vector3& position = Vector3(0, 0, 0), const Quaternion& rotation = Quaternion(), const Vector3& scale = Vector3(1, 1, 1));
		SubIdea& InitSubIdea(const Idea& idea);
		Info& InitInfo(const Idea& idea);
		Real& InitRealRoot(const Info& info);

		Camera* GetCamera();
		Matrix4 GetProjectionMatrix() const;
		void SetProjectionMatrix(float fov, float ar, float zNear, float zFar);
	};
}

