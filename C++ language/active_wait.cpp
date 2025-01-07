#include <thread>
#include <iostream>
#include <string>
#include <unistd.h>

std::string sharedString;
volatile bool flag = false;

void threadFunc() {
    std::cout << "wątek oczekuje na zmianę flagi\n";
    while (!flag);
    sleep (3);

    std::cout << "wątek zaczyna działanie\n";
    std::cout << sharedString << std::endl;
    sharedString = "kot ma ale";

    flag = false;
}

int main() {
    std::thread t(threadFunc);
    sleep(3);

    {
        std::lock guard lock(mutex); 
        sharedString = "zmiana w main()";
        std::cout << "main zmienia flagę\n";
        flag = true;
    }

    sharedString = "ala ma kota";
    std::cout << "main zmienia flagę\n";
    flag = true;
    while(flag);
    std::cout << sharedString << std::endl;

    t.join();
    return 0;
}