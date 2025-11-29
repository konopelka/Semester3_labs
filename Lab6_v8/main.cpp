#include <iostream>
#include <limits>
#include "guess_game.h"
#include <windows.h>

void runGuessGameDemo();

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	runGuessGameDemo();

    std::cout << "Гра \"Вгадай число\"\n";
    std::cout << "Я загадав ціле число від 1 до 100\n\n";

    std::cout << "Протокол відповідей:\n";
    std::cout << "1 - вказане число більше ніж загадане\n";
	std::cout << "0 - вказане число дорівнює загаданому\n";
	std::cout << "-1 - вказане число менше ніж загадане\n\n";

    auto game = GuessGame::startGame();

    std::cout << "Спробуй вгадати\n";

    while (!game.isFinished())
    {
        int userGuess = 0;
        if (!(std::cin >> userGuess))
        {
            std::cout << "Некоректне введення\n";
            return 0;
        }

        if (userGuess < 1 || userGuess > 100)
        {
            std::cout << "Число має бути від 1 до 100\n\n";
            continue;
        }

        int reply = game.makeGuess(userGuess);

        std::cout << reply << "\n";
        if (reply != 0)
        {
            std::cout << "Cпробуй ще\n";
        }
        else
        {
            std::cout << "Вітаю! Ти вгадав число\n";
        }
    }

    std::cout << "Гра завершена.\n";
    return 0;
}
