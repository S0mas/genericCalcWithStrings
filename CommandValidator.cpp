#include "CommandValidator.h"

bool CommandValidator::validateComandEnter(const std::vector<std::string>& strVec) const
{
    for(auto& str : strVec)
    {
        if(!Helper::isKnownOperator(str) && !Helper::constainsOnlyLettersOrNumbers(str) && !Helper::isNumber(str))
            return false;
    }
    return true;
}

bool CommandValidator::validateComandCompOrPrint(const std::vector<std::string>& strVec) const
{
    return strVec.empty();
}

bool CommandValidator::validateComandCompTreeExist(const std::string& strVec) const
{
    return !strVec.empty();
}
