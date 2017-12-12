#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>

class Logger
{
public:
    static void printDebug(const std::string& msg)      { if(debugPrintsOn) printLog("DBG: " + msg); }
    static void printInfo(const std::string& msg)       { printLog("INF: " + msg); }
    static void printWarning(const std::string& msg)    { printLog("WRN: " + msg); }
    static void printError(const std::string& msg)      { printLog("ERR: " + msg); }

    static bool debugPrintsOn;
private:
    static void printLog(const std::string& msg)        { std::cout << msg << std::endl; }

    Logger(){}
};

#endif // LOGGER_H
