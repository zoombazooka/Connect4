#include "HumanPlayer.h"
#include <iostream>
#include <stdexcept>

HumanPlayer::HumanPlayer(char newSymbol, std::string newName) : Player(newSymbol, newName) { }


int HumanPlayer::getMove() const
{
    int playerCol = -1;
    std::cout << "Please input the col index (0-6): \n";
    while (true)
    {
        // std::cin >> age evaluates to false if the user types letters
        while (!(std::cin >> playerCol)) {
            std::cout << "Invalid input. Please enter a number (0-6): \n";
            // 1. Clear the error flag so cin can work again
            std::cin.clear();
            // 2. Ignore all the characters left in the buffer up to the next newline
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (playerCol <= 6 && playerCol >= 0)
        {
            return playerCol;
        }
        std::cout << "Invalid input. Please enter a number (0-6): \n";
    }
}