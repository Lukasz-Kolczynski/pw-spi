#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>

class BuddyAllocator {
protected:
    size_t memory_size;
    size_t max_splits;
    size_t min_block_size;
    std::map<size_t, std::vector<size_t>> free_blocks;

public:
    BuddyAllocator(size_t memory_size, size_t max_splits) {
        if ((memory_size & (memory_size - 1)) != 0) {
            throw std::invalid_argument("Memory size must be a power of 2.");
        }

        this->memory_size = memory_size;
        this->max_splits = max_splits;
        this->min_block_size = memory_size / (1 << max_splits);

        free_blocks[memory_size].push_back(0);
    }

    std::pair<size_t, size_t> alloc(size_t size) {
        if (size <= 0) {
            throw std::invalid_argument("Requested size must be greater than 0.");
        }

        size_t block_size = 1 << static_cast<size_t>(std::ceil(std::log2(size)));

        if (block_size < min_block_size) {
            block_size = min_block_size;
        }

        if (block_size > memory_size) {
            return {0, 0};

        for (auto& [current_size, blocks] : free_blocks) {
            if (current_size >= block_size && !blocks.empty()) {
                size_t address = blocks.front();
                blocks.erase(blocks.begin());

                while (current_size > block_size) {
                    current_size /= 2;
                    size_t buddy_address = address + current_size;
                    free_blocks[current_size].push_back(buddy_address);
                }

                return {address, block_size};
            }
        }

        return {0, 0};
    }

    void free(size_t address, size_t size) {
        if (size <= 0 || free_blocks.find(size) == free_blocks.end()) {
            throw std::invalid_argument("Invalid size for freeing memory.");
        }

        size_t block_size = size;

        while (block_size <= memory_size) {
            size_t buddy_address = address ^ block_size;

            auto& blocks = free_blocks[block_size];
            auto it = std::find(blocks.begin(), blocks.end(), buddy_address);

            if (it != blocks.end()) {
                blocks.erase(it);
                address = std::min(address, buddy_address);
                block_size *= 2;
            } else {
                free_blocks[block_size].push_back(address);
                std::sort(free_blocks[block_size].begin(), free_blocks[block_size].end());
                break;
            }
        }
    }

    friend void print() const {
        for (const auto& [size, blocks] : free_blocks) {
            if (!blocks.empty()) {
                std::cout << "Block size " << size << ": ";
                for (size_t addr : blocks) {
                    std::cout << addr << " ";
                }
                std::cout << std::endl;
            }
        }
    }
};

int main() {
    BuddyAllocator allocator(1024, 5);

    std::cout << "Initial state:" << std::endl;
    allocator.print();

    auto [addr1, size1] = allocator.alloc(200);
    std::cout << "\nAllocated " << size1 << " bytes at address " << addr1 << std::endl;
    allocator.print();

    auto [addr2, size2] = allocator.alloc(100);
    std::cout << "\nAllocated " << size2 << " bytes at address " << addr2 << std::endl;
    allocator.print();

    allocator.free(addr1, size1);
    std::cout << "\nFreed " << size1 << " bytes at address " << addr1 << std::endl;
    allocator.print();

    allocator.free(addr2, size2);
    std::cout << "\nFreed " << size2 << " bytes at address " << addr2 << std::endl;
    allocator.print();

    return 0;
}
