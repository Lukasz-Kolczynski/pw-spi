#include <iostream>
#include <iomanip> 

class Logger {
public:
    enum LogLevel {
        Debug,
        Info,
        Warning,
        Error
    };

    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void setVerbosity(LogLevel level) {
        this->verbosity = level;
    }

    void log(LogLevel level, const std::string &message)
    {
        if (level < this->verbosity)
        {
            /* Do not spam */
            return;
        }

        time_t time = std::time(nullptr);
        std::cerr << std::put_time(std::localtime(&time), "%F %T%z") << " ";

        switch (level)
        {
            case Debug: std::cerr << "[DEBUG]"; break;
            case Info: std::cerr << "[INFO]"; break;
            case Warning: std::cerr << "[WARN]"; break;
            case Error: std::cerr << "[ERR]"; break;
        }

        std::cerr << " " << message << std::endl;
    }
private:
    Logger() : verbosity(Debug) {}
    LogLevel verbosity;
};


int main()
{
    Logger logger = Logger::getInstance();
    logger.setVerbosity(Logger::Info);
    logger.log(Logger::Debug, "Testowy print debugowy");
    logger.log(Logger::Info, "Testowy print info");
    return 0;
}