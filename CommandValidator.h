#ifndef COMMANDVALIDATOR_H
#define COMMANDVALIDATOR_H
#include "Helper.h"
#include "KnownOperators.h"

class CommandValidator
{
public:
    CommandValidator(){}

    bool validateComandEnter(const std::vector<std::string>& strVec) const;
    bool validateComandCompOrPrint(const std::vector<std::string>& strVec) const;
    bool validateComandCompTreeExist(const std::string &strVec) const;


};

#endif // COMMANDVALIDATOR_H
