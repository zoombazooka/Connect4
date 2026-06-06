#include <iostream>
#include "board.h"

int main()
{
    std::cout << "Hello World!\n";
    Board b1 = Board();
    b1.displayBoard();
    b1.placePiece(3, 'O');
    b1.displayBoard();
}