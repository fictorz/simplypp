#include "executables.h"

#include <chrono>
#include <coroutine>
#include <functional>
#include <iostream>
#include <thread>

#include "timeout_awaitable.h"

ExecutableAwaitable::ExecutableAwaitable(std::chrono::milliseconds d) : duration(d), handle(nullptr) {}

bool ExecutableAwaitable::await_ready() const noexcept {
    return false;
}

void ExecutableAwaitable::await_suspend(std::coroutine_handle<> h) {
    handle = h;
    std::thread([this]() {
        std::cout << "Await_suspend\n";
        std::this_thread::sleep_for(duration);
        handle.resume();
    }).detach();
}

void ExecutableAwaitable::await_resume() const noexcept {
    std::cout << "Executable finished\n";
}

ExecutableAwaitableCoroutineTask do_with_executable(
    std::function<void(std::vector<uint8_t>, CancellationToken&)> executable,
    std::chrono::milliseconds timeout_duration) {
    std::cout << "do_with_executable\n";
    CancellationToken token;
    std::atomic<bool> finishedWork = {false};

    std::jthread worker([&]() {
        executable(std::vector<uint8_t>{'d'}, token);
        while (!finishedWork) {
            std::this_thread::sleep_for(std::chrono::milliseconds(timeout_duration));
        }
    });

    co_await TimeoutAwaitable{timeout_duration, &token};

    if (token.is_cancelled()) {
        std::cout << "Cancelled due to timeout\n";
    } else {
        std::cout << "Completed within time\n";
    }

    co_return;
}