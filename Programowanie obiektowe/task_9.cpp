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

    ~Container() 
    {
        while (!isEmpty())
        {
            pop();
        }
        
    }


};



template <typename T>
class Node {
public:
    Node(T value) : data(value), next(nullptr) {}
    T data;
    Node<T> *next;
};



template <typename T>
class Queue : public Container<T>
{
private:
    Node<T> *head;
    Node<T> *tail;
    size_t  count;

public:
    Queue() : head(nullptr), tail(nullptr), count(0)
    {

    }
    
    void push(const T &value) override
    {
        Node<T> *_Node =new Node<T>(value);
        if(isEmpty())
        {
            head = tail =_Node;
        }
        else
        {
            tail->next = _Node;
            tail = _Node;
        }

        ++count;
    }

    T pop()
    {
        if (isEmpty())
        {
            throw std::out_of_range("Queue is empty");
        }
    }


};


int main ()
{


    return 0;
}

