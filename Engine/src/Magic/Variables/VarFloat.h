#pragma once
#include "Magic/Variable.h"

class VarFloat : public Variable {
public:
	VarFloat()
	{
		setValue<float>(0);
	}

	VarFloat(float value)
	{
		setValue<float>(value);
	}
};

