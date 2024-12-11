#include <iostream>
#include <thread>
#include <vector>

class RaceConditionExample {
public:
    RaceConditionExample() : counter(0) {}

    void incrementCounter() {
        for (int i = 0; i < 1000; ++i) {
            ++counter;
        }
    }

    int getCounter() const {
        return counter;
    }

private:
    int counter;
};

int main() {
    RaceConditionExample example;
    std::vector<std::thread> threads;

    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(&RaceConditionExample::incrementCounter, &example);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Final counter value: " << example.getCounter() << std::endl;

    return 0;
}
