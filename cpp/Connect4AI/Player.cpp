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
