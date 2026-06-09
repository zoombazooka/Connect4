#pragma once
#include <string>

class Player
{
private:
	std::string name;
	char symbol;

public:
	Player();
	Player(const char newSymbol, std::string newName);
	virtual ~Player() = default;
	char getSymbol() const;
	const std::string getName() const;
	virtual int getMove() const = 0;
};

