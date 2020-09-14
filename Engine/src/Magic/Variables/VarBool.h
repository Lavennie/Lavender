#pragma once
#include <Magic/Variable.h>


class VarBool : public Variable {
public:
	VarBool()
	{
		setValue<bool>(true);
	}

	VarBool(bool value)
	{
		setValue<bool>(value);
	}
};
