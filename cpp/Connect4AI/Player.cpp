#include "Player.h"

Player::Player()	: name("anonymous"), symbol('N')
{}

Player::Player(const char newSymbol, std::string newName)
	: name(newName), symbol(newSymbol)
{}

char Player::getSymbol() const
{
	return symbol;
}
const std::string Player::getName() const
{
	return name;
}