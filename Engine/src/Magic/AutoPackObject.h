#pragma once
#include "Magic/VariablePack.h"
#include "vector"

class AutoPackObj {



public:
	static vector<AutoPackObj*> allObjects;

	AutoPackObj()
	{
		var = VariablePack();
		AutoPackObj::allObjects.push_back(this);
	}

	~AutoPackObj() {
		// Empty all object on closing game.
		// !Might pop incorrect item when destroyed.
		AutoPackObj::allObjects.pop_back();
	}
protected:
	VariablePack var;

	
	void Move() {

	}
};