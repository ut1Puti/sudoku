#pragma once

#include "solutions.h"

class Ceil
{
public:
	int data;

	Ceil(int data = 0);
	~Ceil();

	bool erase(int data);
	void rollback();

	int solutionsSize();
	void set();
private:
	Solutions solutions;
	std::stack<int> history;
};