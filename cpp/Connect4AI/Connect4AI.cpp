#include <iostream>
#include <string>
#include "Board.h"
#include "HumanPlayer.h"
#include "Game.h"

int main()
{
    HumanPlayer player1('O', "p1");
    HumanPlayer player2('X', "p2");
    int column = 0;

    Game mygame(&player1, &player2);
    while (!mygame.getIsGameOver())
    {
        mygame.displayBoard();
        column = mygame.getCurrentPlayer()->getMove();

        auto result = mygame.playMove(column);
        if (!result)
        {
            continue;
        }
        mygame.evaluateEndOfGame();
        mygame.switchTurn();
    }
    mygame.displayBoard();
}