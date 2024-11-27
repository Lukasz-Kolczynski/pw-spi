#include <iostream>
#include <stdexcept>


template<typename T>
class Container 
{
public:
    virtual void push(const T &value)=0;
    virtual T pop()=0;
    virtual bool isEmpty() const=0;
    virtual size_t size() const=0;

    ~Container() {}

};


int main ()
{


    return 0;
}

