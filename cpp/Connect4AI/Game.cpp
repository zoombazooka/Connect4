#include "Board.h"
#include "Game.h"
#include "Player.h"
#include <expected>
#include <iostream>

Game::Game(Player* player1, Player* player2)
	: isGameOver(false), board(new Board), currentPlayer(player1), lastMove(NULL, NULL)
{
	players[0] = player1;
	players[1] = player2;
}


void Game::switchTurn()
{
	currentPlayer = currentPlayer == players[0] ? currentPlayer = players[1] : currentPlayer = players[0];
}

// Getters
bool Game::getIsGameOver() const
{
	return isGameOver;
}

Player* Game::getCurrentPlayer() const
{
	return currentPlayer;
}

Position Game::getLastMove() const
{
	return lastMove;
}

bool Game::isColValid(int col) const
{
	return col >= 0 && col <= Board::COLS;
}

std::expected<int, std::string> Game::playMove(int col)
{
	if (board->isColumnFull(col))
	{
		return std::unexpected("Column is full! choose a different one!\n");
	}
	lastMove = board->placePiece(col, currentPlayer->getSymbol());
	return col;
}

bool Game::checkWin() const
{
	return board->is4InARow(lastMove, currentPlayer->getSymbol());
}

bool Game::checkDraw() const
{
	return board->isBoardFull();
}


void Game::printResults()
{
	if (checkWin())
	{
		isGameOver = true;
		std::cout << currentPlayer->getName() << "(" << currentPlayer->getSymbol() << ") Won!GG!\n\n" << std::endl;
		return;
	}
	if (checkDraw())
	{
		isGameOver = true;
		std::cout << "It's a draw! GG!\n\n" << std::endl;
		return;
	}
}
	