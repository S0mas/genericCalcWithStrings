#ifndef HELPER_H
#define HELPER_H
#include <cctype>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <stdlib.h>
#include <cstdlib>

class Helper
{
public:

    static inline bool isNumber(const std::string& str)
    {
        bool negative = false;
        bool real = false;
        bool firstChar = true;

        for(const char& sign : str)
        {
            if(!isdigit(sign))
            {
                //First char can be "-" for negative numbers (one per number)
                if(firstChar && !negative && !real && sign == '-')
                {
                    negative = true;
                    continue;
                }
                //All but first character can be "." or "," for real numbers (one per number)
                if(!firstChar && !real && (sign == '.' || sign == ','))
                {
                    real = true;
                    continue;
                }
                return false;
            }
            firstChar = false;
        }

       return true;
    }

    static inline bool constainsOnlyLettersOrNumbers(const std::string& str)
    {
        for(const char& sign : str)
        {
            if(!isdigit(sign) && !isalpha(sign))
                return false;
        }

       return true;
    }

    static inline bool isKnownOperator(const std::string& str)
    {
        if(str == "*" || str == "-" || str == "+" || str == "/")
            return true;
       return false;
    }

    static inline std::vector<std::string> splitString(const std::string& str)
    {
        std::stringstream ss(str);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> strVec(begin, end);
        return strVec;
    }

    static inline const std::string converAddressToString(const void* address)
    {
        std::stringstream ss;
        ss << address;
        return ss.str();
    }
};

#endif // HELPER_H
