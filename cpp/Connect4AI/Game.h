#pragma once
#include "Types.h"
#include "Player.h"
#include "Board.h"
#include <expected>

class Game
{
private:
	bool isGameOver;
	Player* currentPlayer;
	Position lastMove;
public:
	Board* board;
	Player* players[2];
public:
	Game(Player* player1, Player* player2);

	// Getters
	bool getIsGameOver() const;
	Player* getCurrentPlayer() const;
	Position getLastMove() const;

	void switchTurn();
	bool isColValid(int col) const;
	std::expected<int, std::string> playMove(int col);
	bool checkWin() const;
	bool checkDraw() const;
	void printResults();
	

};
