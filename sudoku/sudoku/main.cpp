#include <string>

#include "sudoku.h"

int main()
{
	std::string name;
	std::getline(std::cin, name);

	Sudoku sudoku(name);
	sudoku.display();
	std::cout << "\n";
	sudoku.solution();
	std::cout << "\n";
	sudoku.display();
	return 0;
}