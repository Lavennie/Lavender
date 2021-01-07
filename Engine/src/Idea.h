#pragma once
#include <vector>
#include "Property.h"

namespace Lavender
{
	using namespace std;
	typedef vector<Property> Properties;

	class Idea
	{
		friend class SubIdea;
		friend class Info;
	protected:
		Vector3 m_Pos;
		Quaternion m_Rot;
		Vector3 m_Scl;
		Properties m_Properties;

	public:
		Idea();
		Idea(const Vector3& position, const Quaternion& rotation = Quaternion(0, 0, 0, 1), const Vector3& scale = Vector3(1, 1, 1));

		const Vector3& GetPosition() const;
		const Quaternion& GetRotation() const;
		const Vector3& GetScale() const;

		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void SetScale(float x, float y, float z);
		void SetPosition(const Vector3& position);
		void SetRotation(const Quaternion& rotation);
		void SetScale(const Vector3& scale);

		virtual const Property* GetProperty(Property::Type type) const;
		virtual void SetProperty(Property::Type type, const Property* value);

		template <class T, class... V>
		void AddProperty(Property::Type type, V&&... parameters)
		{
			T propertyValue(parameters...);
			m_Properties.emplace_back(type, &propertyValue);
		}
	};
}