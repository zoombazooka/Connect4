#pragma once
#include "Player.h"
#include <string>
#include "Board.h"

class AI : Player
{
private:
	char oppSymbol;

	AI();
	AI(char newSymbol, std::string newName);
	int getMove() const override;
	int getRandomMove(Board board) const;
};