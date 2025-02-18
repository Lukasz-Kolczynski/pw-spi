#include<iostream>
#include<vector>
#include<utility>
#include <map>


template <typename T>

std::pair <T , unsigned int>

findMostOccurences(const std::vector<T> &v)  
{
    if(v.empty())
    {
        throw std::length_error("Vector is empty");
    }

    std::map<T, size_t> map;

    for (const auto &value : v)
    {
        map[value] += 1;
    }
    //for(const std::pair<T, size_t &value : map)
    std::pair<int, unsigned int> result;
    result.second = 0;
    for (const auto &value : map)
    {
        if (value.second > result.second)
        {
            result.first = value.first;
            result.second = value.second;
        }
    
        //std::cout << value.first << " " << value.second << std::endl;
    }

    return result;
}


int main() 
{
    std::vector<int> numbers = {1,23,4,5,5,6,7,7,8,98,6,5,4,34,5,7,5,7,5};
    std::pair<int, unsigned int> result = findMostOccurences<int>(numbers);
    std::cout << "Najczęsciej występuje: " << result.first <<std::endl;
    std::cout << "Występuje " << result.first << " razy" <<std::endl;
    return 0;
}