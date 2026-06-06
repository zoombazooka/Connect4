#include "Board.h"
#include "Game.h"
#include "Player.h"
#include <expected>

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

std::expected<bool, std::string> Game::playMove(int col)
{
	if (!isColValid(col))
	{
		return std::unexpected("Invalid column index! please input 0-6");
	}
	if (board->isColumnFull(col))
	{
		return std::unexpected("Column is full! choose a different one!");
	}
	lastMove = board->placePiece(col, currrentPlayer->getSymbol());
	return true;
}