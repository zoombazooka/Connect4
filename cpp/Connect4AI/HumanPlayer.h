#pragma once
#include "Player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer(char newSymbol, std::string newName);
	int getMove() const override;
};