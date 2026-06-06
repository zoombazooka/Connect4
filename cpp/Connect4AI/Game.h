#pragma once
#include "Types.h"
#include "Player.h"
#include "Board.h"

class Game
{
private:
	bool isGameOver;
	Board* board;
	Player players[2];
	Player* currrentPlayer;
	Position lastMove;
public:
	Game(Player player1, Player player2);
	void switchTurn();
	bool isColValid(int col) const;
	bool playMove(int col);
	bool checkWin() const;
	bool checkDraw() const;
	void printResults();

};