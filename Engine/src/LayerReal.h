#pragma once
#include <vector>
#include <memory>
#include "Real.h"

namespace Lavender
{
	using namespace std;

	class LayerReal
	{
	private:
		vector<unique_ptr<Real>> m_Root;

	private:
		LayerReal(const LayerReal&) = delete;
		LayerReal& operator=(const LayerReal&) = delete;
	public:
		LayerReal();

		Real* AddNewRoot(const Info* info);

		Real* GetRootAt(unsigned int index);
		unsigned int GetRootCount();
	};
}