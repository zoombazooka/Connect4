#pragma once
#include "Types.h"

class Board
{
private:
	char state[6][7]; // 6 rows and 7 columns

public:
	static constexpr int ROWS = 5;
	static constexpr int COLS = 6;

public:
	Board();

	void displayBoard() const;

	int placePiece(const int col, const char symbol);

	void removePiece(const Position pos);

	bool isColumnFull(const int col) const;

	bool isPosValid(const Position pos) const;

	bool isBoardFull() const;

	int streakInDirection(const Position pos, const Direction direction, const char symbol) const;

	bool is4InARow(const Position pos, const char symbol) const;

	char* const getWindow(const Position startPos, const Direction direction) const;
};