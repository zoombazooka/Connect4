#pragma once

struct Position
{
	int row;
	int col;

	bool operator==(Position other) const
	{
		return row == other.row && col == other.col;
	}
};

struct Direction
{
	int rowDelta;
	int colDelta;
};