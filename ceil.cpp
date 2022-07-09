#include "ceil.h"

Ceil::Ceil(int data)
{
	this->data = data;
	this->solutions = Solutions(data);
}

Ceil::~Ceil()
{
	
}

bool Ceil::erase(int data)
{
	if (!this->solutions.erase(data))
		return false;

	this->history.push(data);

	return true;
}

void Ceil::rollback()
{
	this->data = 0;
	this->solutions.rollback(this->history.top());
	this->history.pop();
}

int Ceil::solutionsSize()
{
	return this->solutions.size();
}

void Ceil::set()
{
	this->data = this->solutions.set();
	this->history.push(data);
}