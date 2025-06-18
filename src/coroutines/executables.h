#include <chrono>
#include <coroutine>
#include <functional>
#include <iostream>
#include <thread>

class CancellationToken;

struct ExecutableAwaitable {
    ExecutableAwaitable(std::chrono::milliseconds d);
    std::chrono::milliseconds duration;
    std::coroutine_handle<> handle;

    bool await_ready() const noexcept;
    void await_suspend(std::coroutine_handle<> h);
    void await_resume() const noexcept;
};

struct ExecutableAwaitableCoroutineTask {
    struct promise_type {
        ExecutableAwaitableCoroutineTask get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};

ExecutableAwaitableCoroutineTask do_with_executable(
    std::function<void(std::vector<uint8_t>, CancellationToken&)> executable, std::chrono::milliseconds d);