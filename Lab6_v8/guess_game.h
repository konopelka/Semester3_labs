#pragma once

#include <coroutine>
#include <string>

class GuessGame
{
public:
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    explicit GuessGame(handle_type h);
    GuessGame(const GuessGame&) = delete;
    GuessGame(GuessGame&& other) noexcept;
    ~GuessGame();

    int makeGuess(int guess);

    bool isFinished() const;

    static GuessGame startGame();

private:
    handle_type coro;

    static int lastGuess;
    static int lastAnswer;

public:
    struct promise_type
    {
        GuessGame get_return_object()
        {
            return GuessGame{ handle_type::from_promise(*this) };
        }

        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend()   noexcept { return {}; }

        void return_void() noexcept {}
        void unhandled_exception()
        {
            std::terminate();
        }
    };
};
