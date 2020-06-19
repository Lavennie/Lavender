#pragma once
#include "Magic/VariablePack.h"
#include "Magic/Scene/Scene.h"

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