#include <iostream>
#include <cstring>
#include <cstdlib>

class TimeLength
{
private:
    char *copy;
    unsigned long hours;
    unsigned long minutes;
    unsigned long seconds;

public:
    TimeLength(const char* seconds_update) 
    {
        copy = strdup(seconds_update);
        unsigned long totalSeconds = strtoul(seconds_update, NULL , 10);

        hours = totalSeconds / 3600;
        minutes = (totalSeconds % 3600) /60;
        seconds = totalSeconds % 60;

    }

    ~TimeLength()
    {
        delete [] copy;
    }

    TimeLength(const TimeLength &next)
    {
        copy = strdup (next.copy);
        hours = next.hours;
        minutes = next.minutes;
        seconds = next.seconds;
    }

    friend std::ostream& operator << (std::ostream& out, const TimeLength &source)
    {
        out << source.hours << "h " << source.minutes << "min " << source.seconds << "sec" << std::endl;
        return out;
    }

    const char* getString() const
    {
        return copy; 
    }

    static TimeLength createZeroLength()
    {
        return TimeLength("0");
    }

};


int main()
{
    TimeLength uptime("19592");
    std::cout << uptime << std::endl;

    
    std::cout << "======" << std::endl;

    std::cout << uptime.getString() << std::endl;

    std::cout << "======" << std::endl;

    TimeLength zeroLength = TimeLength::createZeroLength();
    std::cout << "\nTest metody createZero: \n" <<zeroLength<< std::endl;

    return 0;
}