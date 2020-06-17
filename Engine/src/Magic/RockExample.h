#pragma once
#include <Magic/MagicHeader.h>
#include <map>

using namespace std;

namespace Lavender {

	class RockExample: public TempSceneObject, AutoPackObj
	{
		RockExample(){
			this->var.addData(VariableType::Enabled, VarBool(true));
		}

		void Update() {
			this->var.setData(VariableType::Enabled, false);
		}
	};
	
}

