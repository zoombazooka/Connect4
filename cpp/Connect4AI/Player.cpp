#include "Player.h"

Player::Player()
{
	symbol = 'N';
	name = "anonymous";
}
Player::Player(const char newSymbol, std::string newName)
{
	symbol = newSymbol;
	name = newName;
}

char Player::getSymbol() const
{
	return symbol;
}
const std::string Player::getName() const
{
	return name;
}