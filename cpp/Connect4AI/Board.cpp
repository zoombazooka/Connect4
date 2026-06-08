#include <iostream>
#include <array>
#include "Types.h"
#include "Board.h"
#include <optional>


Board::Board()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			state[i][j] = ' '; // Initialize all cells to empty
		}
	}
}

void Board::displayBoard() const
{
	for (int i = ROWS - 1; i >= 0; i--)
	{
		std::cout << "| ";
		for (int j = 0; j < COLS; j++)
		{
			std::cout << state[i][j] << " | ";
		}
		std::cout << "\n";
		std::cout << "-----------------------------\n";
	}
	std::cout << "  0   1   2   3   4   5   6 \n\n\n"; // Column indices
}

Position Board::placePiece(const int col, const char symbol)
{
	Position pos{-1, -1};
	for (int row = 0; row < ROWS; row++)
	{
		if (state[row][col] == ' ')
		{
			state[row][col] = symbol;
			pos = { row, col };
			return pos; // Return the row where the piece was placed
		}
	}
	return pos; // Column is full
}

void Board::removePiece(const Position pos)
{
	if (isPosValid(pos))
	{
		state[pos.row][pos.col] = ' '; // Remove the piece by setting it back to empty
	}
}

bool Board::isColumnFull(const int col) const
{
	return state[ROWS-1][col] != ' ';
}

bool Board::isPosValid(const Position pos) const
{
	return pos.row >= 0 && pos.row < ROWS && pos.col >= 0 && pos.col < COLS;
}

bool Board::isBoardFull() const
{
	for (int col = 0; col < COLS; col++)
	{
		if (!isColumnFull(col))
		{
			return false; // At least one column has space
		}
	}
	return true; // All columns are full
}

int Board::streakInDirection(const Position pos, const Direction direction, const char symbol) const
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

bool Board::is4InARow(const Position pos, const char symbol) const
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


std::optional<std::array<char, 4>> Board::getWindow(const Position startPos, const Direction direction) const
{
	const int windowSize = 4; // We want a window of 4 positions
	Position currentPos{.row = startPos.row + (direction.rowDelta * 4), .col = startPos.col + (direction.colDelta * 4) }; // farthest position for checking validation of window
	std::array<char, 4> window {0}; // 4 positions in the window
	if (!isPosValid(currentPos))
	{
		return std::nullopt;
	}
	currentPos.row = startPos.row;
	currentPos.col = startPos.col;
	for (int i = 0; i < windowSize; i++)
	{
		window[i] = state[currentPos.row][currentPos.col];
		currentPos.row += direction.rowDelta; // update row
		currentPos.col += direction.colDelta; // update col
	}
	return window; // Return pointer to the first element of the window
}
