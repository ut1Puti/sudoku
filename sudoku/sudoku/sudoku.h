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
	std::string name;

	Ceil map[9][9];
	bool created = true;
	std::stack<std::list<std::pair<int, int>>> history;

	void analyzeCeil(int i, int j, bool& used);
	std::pair<int, int> searchMinEntropy(bool& error);
	void rollback();
};