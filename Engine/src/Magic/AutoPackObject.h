#pragma once
#include <Magic\VariablePack.h>

class AutoPackObj {
protected:
	VariablePack var;

	AutoPackObj()
	{
		var = VariablePack();

		Scene::Register(this);
	}
	void Move() {

	}
};