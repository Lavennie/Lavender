#pragma once
#include "Rendering/Mesh.h"
#include "Rendering/Shader.h"
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

	struct PropertyFloat final : public PropertyComponent
	{
	private:
		float m_Value;
	public:
		PropertyFloat(float value) : m_Value(value) {}
		const void* GetValue() const override { return &m_Value; }
		float Get() const { return m_Value; }
	};
	struct PropertyInt final : public PropertyComponent
	{
	private:
		int m_Value;
	public:
		PropertyInt(int value) : m_Value(value) {}
		const void* GetValue() const override { return &m_Value; }
		int Get() const { return m_Value; }
	};
	struct PropertyString final : public PropertyComponent
	{
	private:
		string m_Value;
	public:
		PropertyString(string value) : m_Value(value) {}
		const void* GetValue() const override { return &m_Value; }
		const string& Get() const { return m_Value; }
	};
	struct PropertyMesh final : public PropertyComponent
	{
	private:
		Mesh* m_Value;
	public:
		PropertyMesh(Mesh* value) : m_Value(value) {}
		const void* GetValue() const override { return m_Value; }
		const Mesh* Get() const { return m_Value; }
	};
	struct PropertyShader final : public PropertyComponent
	{
	private:
		Shader* m_Value;
	public:
		PropertyShader(Shader* value) : m_Value(value) {}
		const void* GetValue() const override { return m_Value; }
		const Shader* Get() const { return m_Value; }
	};
#pragma endregion

#pragma region Property value
	struct PropertyValue 
	{
		virtual PropertyComponent* GetComponent(unsigned int index) const = 0;
		virtual unsigned int GetComponentCount() const = 0;
	};

	struct PropertyVector3 : public PropertyValue
	{
	private:
		PropertyFloat m_X;
		PropertyFloat m_Y;
		PropertyFloat m_Z;
	public:
		PropertyVector3(const Vector3& position) : m_X(position.x), m_Y(position.y), m_Z(position.z) {}
		virtual PropertyComponent* GetComponent(unsigned int index) const override { return (PropertyComponent*)(&m_X + index); }
		virtual unsigned int GetComponentCount() const override { return 3; }
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
		virtual PropertyComponent* GetComponent(unsigned int index) const override { return (PropertyComponent*)(&m_X + index); }
		virtual unsigned int GetComponentCount() const override { return 4; }
		Quaternion GetValue() const { return Quaternion(m_X.Get(), m_Y.Get(), m_Z.Get(), m_W.Get()); }
	};
	struct PropertyModel : public PropertyValue
	{
	private:
		PropertyMesh m_Mesh;
	public:
		PropertyModel(Mesh* mesh) : m_Mesh(mesh) { }
		virtual PropertyComponent* GetComponent(unsigned int index) const override { return (PropertyComponent*)&m_Mesh; }
		virtual unsigned int GetComponentCount() const override { return 1; }
		const Mesh* GetValue() const { return m_Mesh.Get(); }
	};
	struct PropertyShading : public PropertyValue
	{
	private:
		PropertyShader m_Shader;
	public:
		PropertyShading(Shader* shader) : m_Shader(shader) {}
		virtual PropertyComponent* GetComponent(unsigned int index) const override { return (PropertyComponent*)&m_Shader; }
		virtual unsigned int GetComponentCount() const override { return 1; }
		const Shader* GetValue() const { return m_Shader.Get(); }
	};
#pragma endregion

	struct Property final
	{
	public:
		enum class Type { Position, Rotation, Scale, Mesh, Shader };
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

