#include "Board.h"
#include "Game.h"
#include "Player.h"
#include <optional>
#include <iostream>

Game::Game(Player* player1, Player* player2)
	: currentPlayer(player1), lastMove(-1, -1), board(Board()), isGameOver(false)
{
	players[0] = player1;
	players[1] = player2;
}

Game::~Game()
{
	std::cout << "game ended!";
}


void Game::switchTurn()
{
	currentPlayer = (currentPlayer == players[0]) ? players[1] : players[0];
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

void Game::displayBoard() const
{
	board.displayBoard();
}

bool Game::isColValid(int col) const
{
	return col >= 0 && col < Board::COLS;
}

std::optional<int> Game::playMove(int col)
{
	if (!isColValid(col))
	{
		std::cout << "Invalid Column! only 0-6!\n";
		return std::nullopt;

	}
	if (board.isColumnFull(col))
	{
		std::cout << "Column is full! choose a different one!\n";
		return std::nullopt;
	}
	Position res = board.placePiece(col, currentPlayer->getSymbol());
	lastMove = res == Position{ -1, -1 } ? lastMove : res;
	if (lastMove == Position{ -1, -1 })
	{
		return std::nullopt;
	}
	return col;
}

bool Game::checkWin() const
{
	return board.is4InARow(lastMove, currentPlayer->getSymbol());
}

bool Game::checkDraw() const
{
	return board.isBoardFull();
}


void Game::evaluateEndOfGame()
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
	