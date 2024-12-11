#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <stdexcept>


class Config 
{
public:
    Config(const Config&) = delete;
    Config& operator = (const Config&) = delete;

    ~Config()
    {
        saveConfig();
    }

    static Config& getInstance()
    {   
        Config* instance = nullptr;
        if(!instance)
        {
            instance = new Config();
        }
        return *instance;
    }

    void set(const std::string& key, const std::string& value)
    {
        stringConfig[key] = value;
    }

    void set(const std::string& key, const int value)
    {
        intConfig[key] = value;
    }

    std::string getString(const std::string& key)
    {
        if (stringConfig.find(key) != stringConfig.end())
        {
            return stringConfig[key];
        }
        throw std::runtime_error("Nie znaleziono klucza w konfiguracji string");
    }

    int getInt(const std::string& key)
    {
        if (intConfig.find(key) != intConfig.end())
        {
            return intConfig[key];
        }
        throw std::runtime_error("Nie znaleziono klucza w konfiguracji int");
    }

    Config* Config::instance = nullptr;

private:
    std::unordered_map<std::string, std::string> stringConfig;
    std::unordered_map<std::string, int> intConfig;
    static Config* instance;
    const std::string stringConfigFile= "string_task11.txt";
    const std::string intConfigFile= "int_task11.txt";

    Config() 
    {
        loadConfig();
    }

    void loadConfig() 
    {
        std::ifstream stringFile(stringConfigFile);
        if(stringFile.is_open())
        {
            std::string key, value;
            while (stringFile >> key >> value)
            {
                stringConfig[key] = value;
            }
            stringFile.close();
        }

        std::ifstream intFile(intConfigFile);
        if (intFile.is_open())
        {
            std::string key;
            int value;
            while (intFile >> key >> value) {
                intConfig[key] = value;
            }
            intFile.close();
        }

    }

    void saveConfig() const 
    {
        std::ofstream stringFile(stringConfigFile);
        if (stringFile.is_open()) 
        {
            for (const auto&pair : stringConfig)
            {
                stringFile << pair.first << " " << pair.second << "\n";
            }
            stringFile.close();
        }
        std::ofstream intFile(intConfigFile);
        if (intFile.is_open())
        {
            for (const auto& pair : intConfig)
            {
                intFile << pair.first << " " << pair.second << "\n";
            }
            intFile.close();
        }
    }

};



int main()
{



    return 0;
}