#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>

std::atomic<bool> foo = false;

void second_thread() {
	while (true) {
		if (foo) {
			std::cout << "-----------------------------------------------" << '\n';
			std::cout << "      | processing a notification... |" << '\n';
			std::cout << "-----------------------------------------------" << '\n';
			foo = false;
		}
	}
}

int main() {
	std::thread sub_thread = std::thread(&second_thread);

	int count = 0;

	while (true) {
		if (count % 10 == 0) {
			foo = true;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		std::cout << "Main thread working on gathering notifications..." << '\n';

		count++;
	}

	return 0;
}