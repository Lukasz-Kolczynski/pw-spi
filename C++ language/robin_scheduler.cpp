#include<iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <string>
#include <vector>

struct Process 
{
    std::string n;
    int l;
    int s;

    Process(const std::string& _name, int _length, int _start) : n(_name), l(_length), s(_start) {}
};

class RoundRobinScheduler
{
private:
    int time_quantum;
    int current_time;
    std::queue<Process> waiting_queue;
    std::queue<Process> ready_queue;

public:
    RoundRobinScheduler (int _time_quantum) : time_quantum(_time_quantum), current_time(0) {}

    void loadProcceses(const std::string& file_path) 
    {
        std::ifstream file(file_path);
        if (!file.is_open())
        {
            std::cerr << "Błąd otwarcia pliku." << file_path << std::endl;
            exit(1);
        }

        std::string line;
        while (std::getline(file, line))
        {
         
        }
        
    }
};



