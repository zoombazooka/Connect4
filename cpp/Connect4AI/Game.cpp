#include "Board.h"
#include "Game.h"
#include "Player.h"

Game::Game(Player player1, Player player2)
	: isGameOver(false), board(new Board), currrentPlayer(&player1), lastMove(NULL, NULL)
{
	players[0] = player1;
	players[1] = player2;
}


void Game::switchTurn()
{
	currrentPlayer = currrentPlayer == &players[0] ? currrentPlayer = &players[1] : currrentPlayer = &players[0];
}

bool Game::isColValid(int col) const
{
	return col >= 0 && col <= Board::COLS;
}