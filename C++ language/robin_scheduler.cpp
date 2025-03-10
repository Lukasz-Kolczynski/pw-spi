#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>

struct Process {
    std::string name;
    int length;
    int start;

    Process(const std::string& n, int l, int s) : name(n), length(l), start(s) {}
};

class RoundRobinScheduler {
public:
    RoundRobinScheduler(int time_quantum) : time_quantum(time_quantum), current_time(0) {}

    void loadProcesses(const std::string& file_path) {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << file_path << std::endl;
            exit(1);
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string name;
            int length, start;

            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            if (pos1 == std::string::npos || pos2 == std::string::npos) {
                std::cerr << "Error: Wrong line in CSV: " << line << std::endl;
                continue;
            }

            name = line.substr(0, pos1);
            length = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            start = std::stoi(line.substr(pos2 + 1));

            waiting_queue.emplace(name, length, start);
        }
    }

    void schedule() {
        while (!waiting_queue.empty() || !ready_queue.empty()) {
            while (!waiting_queue.empty() && waiting_queue.front().start <= current_time) {
                Process process = waiting_queue.front();
                waiting_queue.pop();
                std::cout << "T=" << current_time << ": New process " << process.name
                          << " is waiting for execution (length=" << process.length << ")" << std::endl;
                ready_queue.push(process);
            }

            if (!ready_queue.empty()) {
                Process process = ready_queue.front();
                ready_queue.pop();
                int run_time = std::min(process.length, time_quantum);

                std::cout << "T=" << current_time << ": " << process.name
                          << " will be running for " << run_time << " time units. Time left: "
                          << process.length - run_time << std::endl;

                current_time += run_time;
                process.length -= run_time;

                if (process.length > 0) {
                    ready_queue.push(process);
                } else {
                    std::cout << "T=" << current_time << ": Process " << process.name << " has been finished" << std::endl;
                }
            } else {
                std::cout << "T=" << current_time << ": No processes currently available" << std::endl;
                current_time++;
            }
        }

        std::cout << "T=" << current_time << ": No more processes in queues" << std::endl;
    }

private:
    int time_quantum;
    int current_time;
    std::queue<Process> waiting_queue;
    std::queue<Process> ready_queue;
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./rr <file.csv> <time_quantum>" << std::endl;
        return 1;
    }

    std::string file_path = argv[1];
    int time_quantum = std::stoi(argv[2]);

    RoundRobinScheduler scheduler(time_quantum);
    scheduler.loadProcesses(file_path);
    scheduler.schedule();

    return 0;
}
