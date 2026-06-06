#pragma once
#include <string>
class Player
{
private:
	char symbol;
	std::string name;

public:
	Player();
	Player(const char newSymbol, std::string newName);
	virtual int getMove() const;
};

