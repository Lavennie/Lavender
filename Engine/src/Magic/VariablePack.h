#pragma once
#include <Magic\Variable.h>
#include "VariableType.h"
#include <list>
#include <map>
using namespace std;

class VariablePack {
protected:

	map<VariableType, Variable> variables;
public:

	void addData(VariableType type, Variable value) {
		//types.Add(type);
		//objects.Add(new T());
		variables[type] = value;
	}

	template<typename T>
	T getData(VariableType type) {
		// for i in objects
		// if objects
		return variables[type].getValue<T>();
	}

	template<typename T>
	void setData(VariableType type, T value) {
		variables[type].setValue<T>(value);
	}
};

