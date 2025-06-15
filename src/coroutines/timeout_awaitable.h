#include <chrono>
#include <coroutine>
#include <iostream>
#include <thread>

class CancellationToken {
   public:
    void cancel() { cancelled = true; }
    bool is_cancelled() const { return cancelled.load(); }

    std::atomic<bool> cancelled{false};
};

class TimeoutAwaitable {
   public:
    TimeoutAwaitable(std::chrono::milliseconds d, CancellationToken* t);

    bool await_ready() const noexcept;
    void await_suspend(std::coroutine_handle<> h);
    void await_resume() const noexcept;

   private:
    std::chrono::milliseconds duration;
    std::coroutine_handle<> handle;
    CancellationToken* token;
};

struct TimeoutAwaitableCoroutineTask {
    struct promise_type {
        TimeoutAwaitableCoroutineTask get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};

TimeoutAwaitableCoroutineTask do_with_timeout();