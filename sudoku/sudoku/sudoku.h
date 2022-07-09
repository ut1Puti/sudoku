#pragma once
#include <fstream>
#include <list>

#include "ceil.h"

class Sudoku
{
public:
	Sudoku(std::string name);
	~Sudoku();
	void display();
	void solution();
private:
	Ceil map[9][9];
	bool created = true;
	bool used = false;
	std::stack<std::list<std::pair<int, int>>> history;
	std::string name;

	void analyzeCeil(int i, int j);
	std::pair<int, int> searchMinEntropy(bool& error);
	void rollback();
};