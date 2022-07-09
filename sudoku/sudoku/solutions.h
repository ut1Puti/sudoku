#pragma once
#include <iostream>
#include <memory>
#include <stack>

class Solutions
{
public:
	Solutions(int data = 0);
	~Solutions();

	bool erase(int data);
	void rollback(int data);

	int size();
	int set();
private:
	bool valid[9];
};