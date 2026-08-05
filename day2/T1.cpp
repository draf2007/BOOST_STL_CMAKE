#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <coroutine>

//co_yield 
//co_await
//co_return

struct Generator {
	struct promise_type {
		int current_value;

		Generator get_return_object() {
			return Generator{ std::coroutine_handle<promise_type>::from_promise(*this) };
		}

		std::suspend_always initial_suspend() { return {}; };
		std::suspend_always final_suspend() noexcept { return {}; };
		void unhandled_exception() { std::terminate(); }

		std::suspend_always yield_value(int value) {
			current_value = value;
			return {};
		}

		void return_void() noexcept {}
	};

	std::coroutine_handle<promise_type> h;

	~Generator() { if (h) h.destroy(); }

	bool move_next() {
		h.resume();
		return !h.done();
	}

	int current()
	{
		return h.promise().current_value;
	}
};

Generator counter()
{
	std::cout << "internal \n";
	std::cout << "Coroutine started\n";
	co_yield 1;
	std::cout << "internal \n";
	std::cout << "step 1 passed\n";
	co_yield 2;
	std::cout << "internal \n";
	std::cout << "Coroutine ended\n";
}

int main()
{
	std::cout << "pre counter\n";
	Generator gen = counter();
	std::cout << "after counter\n";

	while (gen.move_next()) {
		std::cout << "external: \n";
		std::cout << "Got value: " << gen.current() << "\n";
	};
}

