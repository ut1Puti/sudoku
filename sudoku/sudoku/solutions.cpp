#include "solutions.h"

Solutions::Solutions(int data)
{
	memset(this->valid, data == 0 ? true : false, sizeof(this->valid));
}

Solutions::~Solutions()
{
	
}

bool Solutions::erase(int data)
{
	if (this->valid[data - 1] == false)
		return false;

	this->valid[data - 1] = false;

	return true;
}

void Solutions::rollback(int data)
{
	this->valid[data - 1] = true;
}

int Solutions::size()
{
	int result = 0;

	for (int i = 0; i < 9; i++)
		if (this->valid[i] == true)
			result++;

	return result;
}

int Solutions::set()
{
	for (int i = 0; i < 9; i++)
	{
		if (this->valid[i]) {
			erase(i + 1);
			return i + 1;
		}
	}

	return -1;
}