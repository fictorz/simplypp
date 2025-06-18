#ifndef _COROUTINES_COROUTINES_H_
#define _COROUTINES_COROUTINES_H_

#include <coroutine>

class SimpleAwaiter {
public:
  bool await_ready() const noexcept;
  void await_suspend(std::coroutine_handle<>) const noexcept;
  void await_resume() const noexcept;
};

struct CoroutineTask {
  struct promise_type {
    CoroutineTask get_return_object() { return CoroutineTask{}; }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
  };
};

CoroutineTask my_coroutine();
CoroutineTask my_coroutine_await();

#endif // _COROUTINES_COROUTINES_H_