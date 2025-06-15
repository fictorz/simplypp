#include "coroutines.h"

#include <coroutine>
#include <iostream>

bool SimpleAwaiter::await_ready() const noexcept {
    return false;  // causes suspension
}

void SimpleAwaiter::await_suspend(std::coroutine_handle<> /*h*/) const noexcept {
    std::cout << "Suspending coroutine\n";
}

void SimpleAwaiter::await_resume() const noexcept {
    std::cout << "Resuming coroutine\n";
}

CoroutineTask my_coroutine() {
    std::cout << "Before co_await\n";
    std::cout << "After co_await\n";
    co_return;
}

CoroutineTask my_coroutine_await() {
    std::cout << "Before co_await\n";
    co_await SimpleAwaiter{};
    std::cout << "After co_await\n";
}
