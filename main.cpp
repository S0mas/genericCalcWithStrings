#include <QCoreApplication>
#include "IExpressionTree.h"
#include "Logger.h"

bool Logger::debugPrintsOn = false;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    IExpressionTree expr;
    expr.expTree = new ExpressionTree<std::string>();
    expr.run();
    return a.exec();
}
