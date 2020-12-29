#pragma once
#include "Rendering/Mesh.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"
#include <string>
#include <memory>
#include <iostream>
#include <vector>

namespace Lavender
{
	using namespace std;

#pragma region Property value components
	struct PropertyComponent
	{
		virtual const void* GetValue() const = 0;
	};

	struct PropertyFloat : public PropertyComponent
	{
	private:
		float m_Value;
	public:
		PropertyFloat(float value) : m_Value(value) {}
		const void* GetValue() const override { return &m_Value; }
		float Get() const { return m_Value; }
	};
	struct PropertyInt : public PropertyComponent
	{
	private:
		int m_Value;
	public:
		PropertyInt(int value) : m_Value(value) {}
		const void* GetValue() const override { return &m_Value; }
		int Get() const { return m_Value; }
	};
	struct PropertyString : public PropertyComponent
	{
	private:
		string m_Value;
	public:
		PropertyString(string value) : m_Value(value) {}
		const void* GetValue() const override { return &m_Value; }
		const string& Get() const { return m_Value; }
	};
	struct PropertyMesh : public PropertyComponent
	{
	private:
		Mesh* m_Value;
	public:
		PropertyMesh(Mesh* value) : m_Value(value) {}
		const void* GetValue() const override { return m_Value; }
		const Mesh* Get() const { return m_Value; }
	};
#pragma endregion

#pragma region Property value
	struct PropertyValue 
	{
		virtual PropertyComponent* GetComponent(size_t index) const = 0;
		virtual size_t GetComponentCount() const = 0;
	};

	struct PropertyVector3 final : public PropertyValue
	{
	private:
		PropertyFloat m_X;
		PropertyFloat m_Y;
		PropertyFloat m_Z;
	public:
		PropertyVector3(const Vector3& position) : m_X(position.x), m_Y(position.y), m_Z(position.z) {}
		PropertyComponent* GetComponent(size_t index) const override { return (PropertyComponent*)(&m_X + index); }
		size_t GetComponentCount() const override { return 3; }
		Vector3 GetValue() const { return Vector3(m_X.Get(), m_Y.Get(), m_Z.Get()); }
	};
	struct PropertyRotation : public PropertyValue
	{
	private:
		PropertyFloat m_X;
		PropertyFloat m_Y;
		PropertyFloat m_Z;
		PropertyFloat m_W;
	public:
		PropertyRotation(const Quaternion& rotation) : m_X(rotation.v.x), m_Y(rotation.v.y), m_Z(rotation.v.z), m_W(rotation.w) {}
		PropertyComponent* GetComponent(size_t index) const override { return (PropertyComponent*)(&m_X + index); }
		size_t GetComponentCount() const override { return 4; }
		Quaternion GetValue() const { return Quaternion(m_X.Get(), m_Y.Get(), m_Z.Get(), m_W.Get()); }
	};
	struct PropertyModel final : public PropertyValue
	{
	private:
		PropertyMesh m_Mesh;
	public:
		PropertyModel(Mesh* mesh) : m_Mesh(mesh) { }
		PropertyComponent* GetComponent(size_t index) const override { return (PropertyComponent*)&m_Mesh; }
		size_t GetComponentCount() const override { return 1; }
		const Mesh* GetValue() const { return m_Mesh.Get(); }
	};
#pragma endregion

	struct Property final
	{
	public:
		enum class Type { Position, Rotation, Scale, Mesh };
	private:
		Type m_Type;
		unique_ptr<PropertyValue> m_Value;

	private:
		Property(const Property&) = delete;
		Property& operator=(const Property&) = delete;
	public:
		Property(Property&&) = default;
		Property& operator=(Property&&) = default;
		Property() = delete;
		Property(Type type, PropertyValue* value);

		Type GetType() const;
		PropertyValue* GetValue() const;
	};
}

