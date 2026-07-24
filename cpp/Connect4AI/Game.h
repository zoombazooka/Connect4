#pragma once
#include "Types.h"
#include "Player.h"
#include "Board.h"
#include <expected>
#include <array>

class Game
{
private:
	std::array<Player*, 2> players;
	Player* currentPlayer;
	Position lastMove;
	Board board;
	bool isGameOver;
public:
	Game(Player* player1, Player* player2);
	~Game();

	// Getters
	bool getIsGameOver() const;
	Player* getCurrentPlayer() const;
	Position getLastMove() const;

	void displayBoard() const;
	void switchTurn();
	bool isColValid(int col) const;
	std::optional<int> playMove(int col);
	bool checkWin() const;
	bool checkDraw() const;
	void evaluateEndOfGame();
	

};
