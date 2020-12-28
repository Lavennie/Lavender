#include "World.h"
#include <iostream>

namespace Lavender
{
	World::World(float fov, Vector2 windowSize, float zNear, float zFar) :
		m_Camera(fov, windowSize.x / windowSize.y, zNear, zFar),
		m_IdeaLayer(),
		m_SubIdeaLayer(),
		m_InfoLayer(),
		m_RealLayer()
	{}

	void World::Update()
	{
		const float CAMERA_MOVE_SPEED = 0.1f;
		const float CAMERA_ROTATE_SPEED = 0.1f;
		m_Camera.rotation = Quaternion(0, Input::DeltaMousePosition().x * CAMERA_ROTATE_SPEED, 0) * 
			m_Camera.rotation * Quaternion(-Input::DeltaMousePosition().y * CAMERA_ROTATE_SPEED, 0, 0);

		Vector3 translation;
		if (Input::KeyDown(0x41))
		{
			translation.x -= CAMERA_MOVE_SPEED;
		}
		if (Input::KeyDown(0x44))
		{
			translation.x += CAMERA_MOVE_SPEED;
		}
		if (Input::KeyDown(VK_SHIFT))
		{
			translation.y -= CAMERA_MOVE_SPEED;
		}
		if (Input::KeyDown(VK_SPACE))
		{
			translation.y += CAMERA_MOVE_SPEED;
		}
		if (Input::KeyDown(0x53))
		{
			translation.z -= CAMERA_MOVE_SPEED;
		}
		if (Input::KeyDown(0x57))
		{
			translation.z += CAMERA_MOVE_SPEED;
		}
		m_Camera.position += m_Camera.rotation * translation;
	}
	void World::Render()
	{

	}
	void World::UpdateSound()
	{

	}

	Idea& World::InitIdea()
	{
		Idea* idea = m_IdeaLayer.AddNew(nullptr);
		return *idea;
	}
	SubIdea& World::InitSubIdea(const Idea& idea)
	{
		return *m_SubIdeaLayer.AddNew(&idea);
	}
	Info& World::InitInfo(const Idea& idea)
	{
		return *m_InfoLayer.AddNew(&idea);
	}
	Real& World::InitRealRoot(const Info& info)
	{
		return *m_RealLayer.AddNewRoot(&info);
	}

	Camera* World::GetCamera()
	{
		return &m_Camera;
	}
	const Matrix4& World::GetProjectionMatrix() const
	{
		return m_Camera.GetProjectionMatrix();
	}
	void World::SetProjectionMatrix(float fov, float ar, float zNear, float zFar)
	{
		m_Camera.SetProjectionMatrix(fov, ar, zNear, zFar);
	}
}