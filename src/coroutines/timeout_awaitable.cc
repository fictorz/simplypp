#include "timeout_awaitable.h"

#include <chrono>
#include <coroutine>
#include <iostream>
#include <thread>

TimeoutAwaitable::TimeoutAwaitable(std::chrono::milliseconds d, CancellationToken* t)
    : duration(d), handle(nullptr), token(t) {}  // timed_out_(false),

bool TimeoutAwaitable::await_ready() const noexcept {
    return false;
}

void TimeoutAwaitable::await_suspend(std::coroutine_handle<> h) {
    handle = h;

    std::thread([h, this]() {
        std::this_thread::sleep_for(duration);
        if (!token->is_cancelled()) {
            std::cout << "[Timeout] Triggered\n";
            token->cancel();
            h.resume();
        }
    }).detach();
}

void TimeoutAwaitable::await_resume() const noexcept {
    std::cout << "Timeout finished\n";
}

TimeoutAwaitableCoroutineTask do_with_timeout() {
    std::cout << "Waiting 2 seconds...\n";
    CancellationToken token;
    co_await TimeoutAwaitable{std::chrono::milliseconds(2000), &token};
    std::cout << "Resumed after timeout\n";
}