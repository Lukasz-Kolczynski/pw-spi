
#include <iostream>
#include <unordered_map>

bool areAnagrams(const std::string& str1, const std::string& str2)
{
    if (str1.size() != str2.size())
    return false;

    std::unordered_map<char, int> charCount;

    for (char ch : str1)
    {
        charCount[std::tolower(ch)]++;
    }

    for (char ch : str2)
    {
        char lowerChar = std::tolower(ch);
        if (--charCount[lowerChar] < 0) return false;
    }

    return true;
}

int main()
{
    std::string str1 = "listen";
    std::string str2 = "silent";
    std::cout<< std::boolalpha << areAnagrams(str1, str2) << std::endl;

    return 0;
}


/*
#include <iostream>
#include <string>
#include <set>

std::set<std::string>getAll(const std::string &str)
{
    std::set<std::string>sub;

    for(size_t i = 0; i < str.size(); i++) 
    {
        std::string current = "";
        for(size_t j = i; j < str.size(); ++j)
        {
        current += str[j];
        sub.insert(current);
        }
    }
    return sub;
}


int main()
{
    std::string str ="amongus";
    auto sub = getAll(str);
    for (const auto& sub1 : sub)
    {
        std::cout << sub1 << " " << std::endl;
    }
    
    return 0;
}
*/

/*
#include <iostream>
#include <array>
#include <algorithm>

template <typename T, std::size_t N>
void bubbleS(std::array<T, N>& arr)
{
    for (std::size_t i = 0; i < N - 1; ++i)
    {
        for(std::size_t j = 0; j < N - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main()
{
    std::array<int, 5> arr = {32, 65, 2, 10, 7};
    bubbleS(arr);
    for (const auto& el : arr)
    {
        std::cout << el << " ";
    }

    return 0;
}

*/