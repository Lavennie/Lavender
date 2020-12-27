#pragma once
#include <vector>
#include <memory>
#include "Idea.h"

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

		// in case of Idea set param to nullptr
		T* AddNew(const Idea* idea)
		{
			m_Concepts.push_back(make_unique<T>(idea));
			return m_Concepts[m_Concepts.size() - 1].get();
		}
	};
}