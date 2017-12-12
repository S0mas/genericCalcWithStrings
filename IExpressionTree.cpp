#include "IExpressionTree.h"

void IExpressionTree::run()
{
    while(true)
    {
        std::vector<std::string> command(Helper::splitString(getCommand()));
        processCommand(command);
    }
}

std::string IExpressionTree::getCommand() const
{
    std::string str;

    std::getline(std::cin, str);
    return str;
}

void IExpressionTree::processCommand(std::vector<std::string>& strVec)
{
    if(strVec.empty())
        return;

    const std::string command = strVec.front();
    //Proceed with arguments only
    strVec.erase(strVec.begin());

    if(command == "debug")
        commandDebug();
    else if(command == "enter")
        cmdValidator.validateComandEnter(strVec) ? commandEnter(strVec) : Logger::printError(ErrorsMsg::unrecognizedSymbol);
    else if(command == "print")
        cmdValidator.validateComandCompOrPrint(strVec) ? commandPrint() : Logger::printError(ErrorsMsg::invalidArgsNumber);
    else if(command == "comp")
    {
        if(cmdValidator.validateComandCompTreeExist(expTree->toString()))
            cmdValidator.validateComandCompOrPrint(strVec) ?commandComp(strVec) : Logger::printError(ErrorsMsg::invalidArgsNumber);
        else
            Logger::printError(ErrorsMsg::noExpression);
    }
    else if(command == "help")
        commandHelp();
    else
        Logger::printError(ErrorsMsg::invalidCommand);
}

void IExpressionTree::commandEnter(const std::vector<std::string>& strVec)
{
    expTree->createExpTree(strVec);
    wasExprFixed(strVec, expTree->toStringVec());
    commandPrint();
}

void IExpressionTree::commandComp(const std::vector<std::string>& strVec)
{
    std::vector<double> valuesVec;
    std::transform(strVec.begin(), strVec.end(), std::back_inserter(valuesVec),
                   [](const std::string& str) { return std::stod(str); });

    Logger::printInfo(expTree->getResult());
}

void IExpressionTree::commandPrint() const
{
    const std::string& expression = expTree->toString();
    if(expression == "")
        Logger::printWarning("No expression to print.");
    else
        Logger::printInfo(expression);
}

void IExpressionTree::commandHelp() const
{
    Logger::printInfo("Options:\n"
                     "enter <expression> - to create expression ex. + 5 5, and operators: +, -, *, / are valid.\n"
                     "comp - calculate value of expression with defined variabls values \n"
                     "print - print actual expression\n"
                     "help - show this menu\n");
}

void IExpressionTree::wasExprFixed(const std::vector<std::string> &input, const std::vector<std::string> &output) const
{
    if(input.size() > output.size())
        Logger::printWarning("Expression was fixed by removing of invalid part.");
    else if(input.size() < output.size())
        Logger::printWarning("Expression was fixed by adding some '1' values.");
}

void IExpressionTree::commandDebug()
{
    Logger::debugPrintsOn = !Logger::debugPrintsOn;
}
