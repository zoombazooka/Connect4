#include <iostream>

class Board
{
private:
	char state[6][7]; // 6 rows and 7 columns
	int minRows, maxRows, minCols, maxCols;

public:
	Board()
	{
		minRows = 0;
		maxRows = 5;
		minCols = 0;
		maxCols = 6;
		for (int i = minRows; i <= maxRows; i++)
		{
			for (int j = minCols; j <= maxCols; j++)
			{
				state[i][j] = ' '; // Initialize all cells to empty
			}
		}
	}

	void displayBoard()
	{
		for (int i = maxRows; i >= minRows; i--)
		{
			for (int j = minCols; j <= maxCols; j++)
			{
				std::cout << "| " << state[i][j] << " |";
			}
			std::cout << std::endl;
			std::cout << "-----------------------------" << std::endl;
		}
		std::cout << "  0   1   2   3   4   5   6 " << std::endl; // Column indices
	}
};