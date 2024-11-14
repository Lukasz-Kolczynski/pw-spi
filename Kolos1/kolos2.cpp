#include <iostream>


class ICommand 
{
public:
    virtual char getCommand() const = 0;
    virtual ~ICommand()
    {
        std::cout << "Destruktor został użyty...\n" << std::endl;
    }
};

class SystemUptime : public ICommand
{
public:
    SystemUptime()
    {
        std::cout << "\nKonstruktor SyS.Uptime został użyty..." << std::endl;
    }

    ~SystemUptime()
    {
        std::cout << "\nDestruktor Sys.Uptime został użyty...\n" << std::endl;
    }
    char getCommand() const override 
    {
        return 'U';
    }

};


class SystemMemory : public ICommand
{
public:
    SystemMemory() 
    {
        std::cout << "\nKonstruktor Sys.Memory został użyty..." << std::endl;
    }

    ~SystemMemory()
    {
        std::cout << "Destruktor Sys.Memory został użyty...\n" << std::endl;
    }

    char getCommand()const override
    {
        return 'M';
    }


};

void printCommand(const ICommand& c)
    {
        std::cout << c.getCommand() << std::endl;
    }


int main()
{
    ICommand *ptr1 = new SystemUptime();
        printCommand(*ptr1);
    ICommand *ptr2 = new SystemMemory();
        printCommand(*ptr2);


    delete ptr1;
    delete ptr2;
    

    return 0;
}