#include <iostream>
#include <string>
#include "board.h"
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
        mygame.board->displayBoard();
        column = mygame.getCurrentPlayer()->getMove();

        auto result = mygame.playMove(column);
        if (!result)
        {
            std::cout << result.error() << std::endl;
            continue;
        }
        mygame.printResults();
        mygame.switchTurn();
    }
    mygame.board->displayBoard();
}