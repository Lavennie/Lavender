#pragma once

class Variable {
	void* value;

public:
	template<typename T>
	void setValue(T val) {
		this->value = &val;
	}
	template<typename T>
	T getValue() {
		return (T)this->*value;
	}
};

