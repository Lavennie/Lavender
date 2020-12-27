#include "World.h"

namespace Lavender
{
	World::World() :
		m_Camera(80, 4.0f / 3.0f, 1.0f, 10.0f),
		m_IdeaLayer(),
		m_SubIdeaLayer(),
		m_InfoLayer(),
		m_RealLayer()
	{}

	void World::Update(const Input& input)
	{
		const float CAMERA_MOVE_SPEED = 0.1f;
		const float CAMERA_ROTATE_SPEED = 1.0f;
		if (input.KeyDown(0x51))
		{
			m_Camera.rotation *= Quaternion(0, -CAMERA_ROTATE_SPEED, 0);
		}
		if (input.KeyDown(0x45))
		{
			m_Camera.rotation *= Quaternion(0, CAMERA_ROTATE_SPEED, 0);
		}

		Vector3 translation;
		if (input.KeyDown(0x41))
		{
			translation.x -= CAMERA_MOVE_SPEED;
		}
		if (input.KeyDown(0x44))
		{
			translation.x += CAMERA_MOVE_SPEED;
		}
		if (input.KeyDown(VK_SHIFT))
		{
			translation.y -= CAMERA_MOVE_SPEED;
		}
		if (input.KeyDown(VK_SPACE))
		{
			translation.y += CAMERA_MOVE_SPEED;
		}
		if (input.KeyDown(0x53))
		{
			translation.z -= CAMERA_MOVE_SPEED;
		}
		if (input.KeyDown(0x57))
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
}