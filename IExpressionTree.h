#ifndef IEXPRESSIONTREE_H
#define IEXPRESSIONTREE_H
#include "ExpressionTree.h"
#include "CommandValidator.h"
#include "ErrorsMsg.h"

class IExpressionTree
{
public:
    IExpressionTree()
    {
        expTree = nullptr;
    }
    ~IExpressionTree()
    {
        if(expTree)
        {
            delete expTree;
            expTree = nullptr;
        }
    }
    void run();//infinite loop
private:
    std::string getCommand() const;

    void processCommand(std::vector<std::string>& strVec);
    void commandEnter(const std::vector<std::string> &strVec);
    void commandComp(const std::vector<std::string> &strVec);
    void commandPrint() const;
    void commandHelp() const;
    void commandDebug();
    void wasExprFixed(const std::vector<std::string> &input, const std::vector<std::string> &output) const;
public:
    AbstractExpressionTree* expTree;
    CommandValidator cmdValidator;
};

#endif // IEXPRESSIONTREE_H
