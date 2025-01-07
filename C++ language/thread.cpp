#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <cstring>
#include <cctype>

#define DIGIT_COUNT 10

struct Context {
    unsigned long count[DIGIT_COUNT] = {0};
    std::mutex mutex;
};

void count_digits(Context& ctx, const char* data, size_t start, size_t end) {
    unsigned long local_count[DIGIT_COUNT] = {0};

    for (size_t i = start; i < end; ++i) {
        if (isdigit(data[i])) {
            local_count[data[i] - '0']++;
        }
    }

    std::lock_guard<std::mutex> lock(ctx.mutex);
    for (int i = 0; i < DIGIT_COUNT; ++i) {
        ctx.count[i] += local_count[i];
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Użycie: " << argv[0] << " <ścieżka do pliku> <liczba wątków>\n";
        return 1;
    }

    const char* file_path = argv[1];
    int thread_count = std::stoi(argv[2]);

    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku: " << file_path << "\n";
        return 1;
    }

    size_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> data(file_size);
    file.read(data.data(), file_size);
    file.close();

    Context ctx;
    size_t chunk_size = (file_size + thread_count - 1) / thread_count;

    std::vector<std::thread> threads;
    for (int i = 0; i < thread_count; ++i) {
        size_t start = i * chunk_size;
        size_t end = std::min(start + chunk_size, file_size);
        threads.emplace_back(count_digits, std::ref(ctx), data.data(), start, end);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Stan liczników cyfr:\n";
    for (int i = 0; i < DIGIT_COUNT; ++i) {
        std::cout << "Cyfra " << i << ": " << ctx.count[i] << "\n";
    }

    return 0;
}
