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
	char getSymbol() const;
	const std::string getName() const;
	virtual int getMove() const;
};

