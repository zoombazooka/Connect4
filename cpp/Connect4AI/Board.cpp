#include <iostream>
#include "Types.h"
#include "Board.h"

class Board
{
private:
	char state[6][7]; // 6 rows and 7 columns
	static constexpr int ROWS = 6;
	static constexpr int COLS = 7;


public:
	Board()
	{
		for (int i = 0; i <= ROWS; i++)
		{
			for (int j = 0; j <= COLS; j++)
			{
				state[i][j] = ' '; // Initialize all cells to empty
			}
		}
	}

	void displayBoard() const
	{
		for (int i = ROWS; i >= 0; i--)
		{
			for (int j = 0; j <= COLS; j++)
			{
				std::cout << "| " << state[i][j] << " |";
			}
			std::cout << "\n";
			std::cout << "-----------------------------\n";
		}
		std::cout << "  0   1   2   3   4   5   6 \n"; // Column indices
	}

	int placePiece(const int col, const char symbol)
	{
		for (int row = 0; row <= ROWS; row++)
		{
			if (state[row][col] == ' ')
			{
				state[row][col] = symbol;
				return row; // Return the row where the piece was placed
			}
		}
		return -1; // Column is full
	}

	void removePiece(const Position pos)
	{
		if (isPosValid(pos))
		{
			state[pos.row][pos.col] = ' '; // Remove the piece by setting it back to empty
		}
	}

	bool isColumnFull(const int col) const
	{
		return state[ROWS][col] != ' ';
	}

	bool isPosValid(const Position pos) const
	{
		return pos.row >= 0 && pos.row <= ROWS && pos.col >= 0 && pos.col <= COLS;
	}

	bool isBoardFull() const
	{
		for (int col = 0; col <= COLS; col++)
		{
			if (!isColumnFull(col))
			{
				return false; // At least one column has space
			}
		}
		return true; // All columns are full
	}

	int streakInDirection(const Position pos, const Direction direction, const char symbol) const
	{
		int streak = 0;
		Position currentPos{.row = pos.row, .col = pos.col };
		while (isPosValid(currentPos) && state[currentPos.row][currentPos.col] == symbol && streak < 4)
		{
			streak++;
			currentPos.row += direction.rowDelta;
			currentPos.col += direction.colDelta;
		}
		return streak;
	}

	bool is4InARow(const Position pos, const char symbol) const
	{
		const int dirAmount = 4;
		const Direction  directions[dirAmount] = { {0, 1}, {1, 0}, {1, 1}, {1, -1} }; // Horizontal, Vertical, Diagonal (top-left to bottom-right), Diagonal (top-right to bottom-left)
		Direction oppDirection = { 0 };
		for (int i = 0; i < dirAmount; i++)
		{
			oppDirection.rowDelta = -directions[i].rowDelta;
			oppDirection.colDelta = -directions[i].colDelta;
			int count = streakInDirection(pos, directions[i], symbol) + streakInDirection(pos, oppDirection , symbol) - 1; // Subtract 1 to avoid double counting the current piece
			if (count >= 4)
			{
				return true; // Found a streak of 4 or more
			}
		}
		return false; // No streak of 4 found
	}


	char* const getWindow(const Position startPos, const Direction direction) const
	{
		const int windowSize = 4; // We want a window of 4 positions
		Position currentPos{.row = startPos.row, .col = startPos.col };
		char* window = new char[windowSize]; // 4 positions in the window
		for (int i = 0; i < windowSize; i++)
		{
			if (!isPosValid(currentPos))
			{
				return nullptr; // Return null pointer if the window goes out of bounds
			}
			window[i] = state[currentPos.row][currentPos.col];
			currentPos.row += direction.rowDelta; // update col
			currentPos.col += direction.colDelta; // update row
		}
		return window; // Return pointer to the first element of the window
	}
};