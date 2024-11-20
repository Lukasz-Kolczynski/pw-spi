#include <iostream>
#include <stdexcept>

double div ( double a, double b) 
{
    if (b==0)
    {
        throw std::invalid_argument("BOOM!");
    }
    return a/b;
}

int main()
{
    double a = 5;
    double b = 0;  

    std::cout << div(a,b) << std::endl;

    return 0;
}