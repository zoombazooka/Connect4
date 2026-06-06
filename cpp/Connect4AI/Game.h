#pragma once
#include "Types.h"
#include "Player.h"
#include "Board.h"
#include <expected>

class Game
{
private:
	bool isGameOver;
	Board* board;
	Player* players[2];
	Player* currentPlayer;
	Position lastMove;
public:
	Game(Player* player1, Player* player2);
	void switchTurn();
	bool isColValid(int col) const;
	std::expected<bool, std::string> playMove(int col);
	bool checkWin() const;
	bool checkDraw() const;
	void printResults();
	

};
