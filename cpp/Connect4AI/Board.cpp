#include <iostream>

class Board
{
private:
	char state[6][7]; // 6 rows and 7 columns
	int minRows, maxRows, minCols, maxCols;

public:
	Board()
		: minRows(0), maxRows(5), minCols(0), maxCols(6)
	{
		for (int i = minRows; i <= maxRows; i++)
		{
			for (int j = minCols; j <= maxCols; j++)
			{
				state[i][j] = ' '; // Initialize all cells to empty
			}
		}
	}

	void displayBoard() const
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

	int placePiece(const int col, const char symbol)
	{
		for (int row = minRows; row <= maxRows; row++)
		{
			if (state[row][col] == ' ')
			{
				state[row][col] = symbol;
				return row; // Return the row where the piece was placed
			}
		}
		return -1; // Column is full
	}

	void removePiece(const int pos[2])
	{
		if (isPosValid(pos))
		{
			state[pos[0]][pos[1]] = ' '; // Remove the piece by setting it back to empty
		}
	}

	bool isColumnFull(const int col) const
	{
		return state[maxRows][col] != ' ';
	}

	bool isPosValid(const int pos[2]) const
	{
		return pos[0] >= minRows && pos[0] <= maxRows && pos[1] >= minCols && pos[1] <= maxCols;
	}

	bool isBoardFull() const
	{
		for (int col = minCols; col <= maxCols; col++)
		{
			if (!isColumnFull(col))
			{
				return false; // At least one column has space
			}
		}
		return true; // All columns are full
	}

	int streakInDirection(const int pos[2], const int direction[2], const char symbol) const
	{
		int streak = 0;
		int currentPos[2] = { pos[0], pos[1] };
		while (isPosValid(currentPos) && state[currentPos[0]][currentPos[1]] == symbol && streak < 4)
		{
			streak++;
			currentPos[0] += direction[0];
			currentPos[1] += direction[1];
		}
		return streak;
	}

	bool is4InARow(const int pos[2], const char symbol) const
	{
		const int dirAmount = 4;
		const int directions[dirAmount][2] = { {0, 1}, {1, 0}, {1, 1}, {1, -1} }; // Horizontal, Vertical, Diagonal (top-left to bottom-right), Diagonal (top-right to bottom-left)
		int direction[2] = { 0 };
		int oppDirection[2] = { 0 };
		for (int i = 0; i < dirAmount; i++)
		{
			// set direction and oppDirection based on the current direction in the loop
			for (int j = 0; j < 2; j++)
			{
				direction[j] = directions[i][j];
				oppDirection[j] = -direction[j];
			}

			
			int count = streakInDirection(pos, direction, symbol) + streakInDirection(pos, oppDirection, symbol) - 1; // Subtract 1 to avoid double counting the current piece
			if (count >= 4)
			{
				return true; // Found a streak of 4 or more
			}
		}
		return false; // No streak of 4 found
	}


	char* const getWindow(const int startPos[2], const int direction[2]) const
	{
		const int windowSize = 4; // We want a window of 4 positions
		int currentPos[2] = { startPos[0], startPos[1] };
		char* window = new char[windowSize]; // 4 positions in the window
		for (int i = 0; i < windowSize; i++)
		{
			if (!isPosValid(currentPos))
			{
				return nullptr; // Return null pointer if the window goes out of bounds
			}
			window[i] = state[currentPos[0]][currentPos[1]];
			currentPos[0] += direction[0]; // update col
			currentPos[1] += direction[1]; // update row
		}
		return window; // Return pointer to the first element of the window
	}
};