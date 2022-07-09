#include "sudoku.h"

Sudoku::Sudoku(std::string name)
{
	std::ifstream file(name);
	if (!file)
	{
		std::cout << "error::creation_infile\n";
		this->created = false;
		return;
	}

	this->name = name;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int data = 0;

			file >> data;

			if (data)
				this->map[i][j] = Ceil(data);
		}
	}

	file.close();
}

Sudoku::~Sudoku()
{
	if (!this->created)
		return;

	this->name.erase(this->name.size() - 4, this->name.size() - 1);
	this->name += "Solution.txt";

	std::ofstream file(this->name);
	if (!file) {
		std::cout << "error::creation_outfile\n";
		return;
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			file << this->map[i][j].data << " ";
		}
		file << "\n";
	}

	file.close();
}

void Sudoku::display()
{
	if (!this->created)
		return;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::cout << this->map[i][j].data << " ";
			
			if ((j + 1) % 3 == 0 && (j + 1) != 9)
				std::cout << "| ";
		}
		std::cout << "\n";

		if ((i + 1) % 3 == 0 && (i + 1) != 9)
			std::cout << "---------------------\n";
	}
}

void Sudoku::solution()
{
	if (!this->created)
		return;

	while(true)
	{
		this->history.push(std::list<std::pair<int, int>>());
		bool error = true;
		bool used = false;

		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				analyzeCeil(i, j, used);

		if (!used)
			return;

		std::pair<int, int> solution = searchMinEntropy(error);

		if (!error) {
			this->map[solution.first][solution.second].set();
			this->history.top().push_back(solution);
		}
		else {
			rollback();
		}
	}
}

void Sudoku::analyzeCeil(int i, int j, bool& used)
{
	if (this->map[i][j].data != 0)
		return;

	used = true;

	//analyze row
	for (int n = 0; n < 9; n++)
	{
		if (n == j)
			continue;

		if (this->map[i][n].data != 0) {
			if (this->map[i][j].erase(this->map[i][n].data))
				this->history.top().push_back(std::make_pair(i, j));
		}
	}

	//analyze column
	for (int m = 0; m < 9; m++)
	{
		if (m == i)
			continue;

		if (this->map[m][j].data != 0) {
			if (this->map[i][j].erase(this->map[m][j].data))
				this->history.top().push_back(std::make_pair(i, j));
		}
	}

	//analyze box
	int boxX = i / 3;
	int boxY = j / 3;
	for (int m = boxX * 3; m < boxX * 3 + 3; m++)
	{
		for (int n = boxY * 3; n < boxY * 3 + 3; n++)
		{
			if (m == i && n == j)
				continue;

			if (this->map[m][n].data != 0) {
				if (this->map[i][j].erase(this->map[m][n].data))
					this->history.top().push_back(std::make_pair(i, j));
			}
		}
	}
}

std::pair<int, int> Sudoku::searchMinEntropy(bool& error)
{
	std::pair<int, int> result;
	int minEntropy = 10;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (this->map[i][j].data != 0)
				continue;

			if (this->map[i][j].solutionsSize() == 0)
				continue;

			if (this->map[i][j].solutionsSize() < minEntropy) {
				minEntropy = this->map[i][j].solutionsSize();
				result = std::make_pair(i, j);
				error = false;
			}
		}
	}

	return result;
}

void Sudoku::rollback()
{
	//returning to begin of current iteration
	while (!this->history.top().empty())
	{
		this->map[this->history.top().back().first][this->history.top().back().second].rollback();
		this->history.top().pop_back();
	}
	this->history.pop();

	//returning to end of iteration with more than one choice
	while (map[this->history.top().back().first][this->history.top().back().second].solutionsSize() == 0)
	{
		while (!this->history.top().empty())
		{
			this->map[this->history.top().back().first][this->history.top().back().second].rollback();
			this->history.top().pop_back();
		}
		this->history.pop();
	}

	//returning to begin of iteration with more than one choice
	std::pair<int, int> pair = this->history.top().back();
	this->map[this->history.top().back().first][this->history.top().back().second].data = 0;
	this->history.top().pop_back();
	while (!this->history.top().empty())
	{
		this->map[this->history.top().back().first][this->history.top().back().second].rollback();
		this->history.top().pop_back();
	}
	this->history.pop();
	this->history.top().push_front(pair);
}
