#include <iostream>
#include <thread>
#include <vector>



void loop(int n) 
{
    for (int i = 0; i <2000000; i++);
    std::cout << "Koniec wątku" << n << std::endl;
}

int main()
{
    std::vector<std::thread>threads;
    for (int i = 0; i < 4; i++)
    {
        threads.push_back(std::thread(loop, i));
    }
    for (int i = 0; i < 4; i++)
    {
        std::cout << "Oczekiwanie na wątek" << std::endl;
        threads[i].join();
    }

    return 0;
}