#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>

std::condition_variable foo;
std::mutex mtx;

void second_thread() {
	while (true) {
		std::unique_lock<std::mutex> ul(mtx);
		foo.wait(ul);
		std::cout << "-----------------------------------------------" << '\n';
		std::cout << "      | processing a notification... |" << '\n';
		std::cout << "-----------------------------------------------" << '\n';
	}
}

int main() {
	std::thread sub_thread = std::thread(&second_thread);

	int count = 0;

	while (true) {
		if (count % 10 == 0) {
			foo.notify_one();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		std::cout << "Main thread working on gathering notifications..." << '\n';

		count++;
	}

	return 0;
}