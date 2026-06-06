#include <iostream>
#include <string>
#include "board.h"
#include "HumanPlayer.h"
#include "Game.h"

int main()
{
    std::cout << "Hello World!\n";
    Board b1 = Board();
    b1.displayBoard();
    b1.placePiece(3, 'O');
    b1.displayBoard();
}