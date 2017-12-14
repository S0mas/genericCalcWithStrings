#include <QCoreApplication>
#include "IExpressionTree.h"
#include "Logger.h"

bool Logger::debugPrintsOn = false;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    IExpressionTree expr;
    std::string variant;
    Logger::printInfo("Choose calculator type. Options: int double or string. exit for quit.");
    while(variant != "exit")
    {
        std::cin >> variant;
        if(variant == "int")
            expr.expTree = new ExpressionTree<int>();
        else if(variant == "double")
            expr.expTree = new ExpressionTree<double>();
        else if(variant == "string")
            expr.expTree = new ExpressionTree<std::string>();
        std::cin.clear();
        std::cin.sync();
        if(expr.expTree != nullptr)
            expr.run();
        else
            Logger::printError("Unsuported type of calculator.");
    }
    return a.exec();
}
