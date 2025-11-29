#include "guess_game.h"
#include <random>
#include <iostream>

int GuessGame::lastGuess = 0;
int GuessGame::lastAnswer = 0;

GuessGame::GuessGame(handle_type h)
    : coro(h)
{
}

GuessGame::GuessGame(GuessGame&& other) noexcept
    : coro(other.coro)
{
    other.coro = nullptr;
}

GuessGame::~GuessGame()
{
    if (coro)
    {
        coro.destroy();
    }
}

int GuessGame::makeGuess(int guess)
{
    lastGuess = guess;

    if (coro && !coro.done())
    {
        coro.resume();
    }

    return lastAnswer;
}

bool GuessGame::isFinished() const
{
    return !coro || coro.done();
}

GuessGame GuessGame::startGame()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    int secretNumber = dist(gen);

    while (true)
    {
        int guess = lastGuess;

        if (guess < secretNumber)
            lastAnswer = -1;
        else if (guess > secretNumber)
            lastAnswer = 1;
        else
            lastAnswer = 0;

        if (lastAnswer == 0)
        {
            co_return;
        }

        co_await std::suspend_always{};
    }
}
