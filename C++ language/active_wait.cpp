#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <cstring>

#define DIGIT_COUNT 10

struct context {
    unsigned long count[DIGIT_COUNT] = {0};
    std::mutex mutex;
};

void count_digits(context& ctx, const char* data, size_t start, size_t end) {
    unsigned long local_count[DIGIT_COUNT] = {0}; 

    for (size_t i = start; i < end; ++i) {
        if (data[i] >= '0' && data[i] <= '9') {
            local_count[data[i] - '0']++;
        }
    }

    std::lock_guard<std::mutex> guard(ctx.mutex);
    for (int i = 0; i < DIGIT_COUNT; ++i) {
        ctx.count[i] += local_count[i];
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Użycie: " << argv[0] << " <ścieżka_do_pliku> <ilość_wątków>" << std::endl;
        return 1;
    }

    std::string file_path = argv[1];
    int thread_count = std::stoi(argv[2]);

    if (thread_count < 1) {
        std::cerr << "Ilość wątków musi być >= 1" << std::endl;
        return 1;
    }

    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Nie można otworzyć pliku: " << file_path << std::endl;
        return 1;
    }

    size_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> file_data(file_size);
    if (!file.read(file_data.data(), file_size)) {
        std::cerr << "Błąd odczytu pliku: " << file_path << std::endl;
        return 1;
    }

    context ctx;

    size_t chunk_size = (file_size + thread_count - 1) / thread_count;
    std::vector<std::thread> threads;

    for (int i = 0; i < thread_count; ++i) {
        size_t start = i * chunk_size;
        size_t end = std::min(start + chunk_size, file_size);

        threads.emplace_back(count_digits, std::ref(ctx), file_data.data(), start, end);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Stan liczników cyfr:" << std::endl;
    for (int i = 0; i < DIGIT_COUNT; ++i) {
        std::cout << "Cyfra " << i << ": " << ctx.count[i] << std::endl;
    }

    return 0;
}
