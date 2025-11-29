#include <iostream>
#include "guess_game.h"

void runGuessGameDemo()
{
    std::cout << "Демо \n";

    auto game = GuessGame::startGame();

    int low = 1;
    int high = 100;
    int step = 0;

    while (!game.isFinished() && low <= high)
    {
        int guess = (low + high) / 2;
        ++step;

        int reply = game.makeGuess(guess);

        std::cout << "спроба " << step << ": " << guess << "\tвідповідь = " << reply << "\n";

        if (reply < 0)
        {
            low = guess + 1;
        }
        else if (reply > 0)
        {
            high = guess - 1;
        }
        else
        {
            std::cout << "Число вгадано\n";
            break;
        }
    }

    std::cout << "Кінець демо\n\n";
}
