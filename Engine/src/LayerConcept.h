#pragma once
#include <vector>
#include <memory>
#include "Idea.h"
#include "SubIdea.h"
#include "Info.h"

namespace Lavender
{
	using namespace std;

	template <class T>
	class LayerConcept
	{
	private:
		vector<unique_ptr<T>> m_Concepts;

	private:
		LayerConcept(const LayerConcept&) = delete;
		LayerConcept& operator=(const LayerConcept&) = delete;
	public:
		LayerConcept() : m_Concepts() {}

		T* AddNew(const Idea* source);
		T* AddNew(const Vector3& position, const Quaternion& rotation, const Vector3& scale);
	};

	template <>
	Idea* LayerConcept<Idea>::AddNew(const Idea* source) = delete;
	template <>
	SubIdea* LayerConcept<SubIdea>::AddNew(const Vector3& position, const Quaternion& rotation, const Vector3& scale) = delete;
	template <>
	Info* LayerConcept<Info>::AddNew(const Vector3& position, const Quaternion& rotation, const Vector3& scale) = delete;
}