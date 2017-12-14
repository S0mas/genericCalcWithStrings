#ifndef KNOWNOPERATORS_H
#define KNOWNOPERATORS_H
#include <vector>
#include <string>
#include <functional>
#include <cmath>
#include <map>
#include "Logger.h"

std::string minus(std::string a, std::string b);
std::string multiplies(std::string a, std::string b);
std::string multiplies2(std::string a, std::string b);
std::string divides(std::string a, std::string b);
template<class T>
class KnownOperators
{
public:
    bool isKnownOperator(const std::string& str) const
    {
        for(const std::string& op : operators)
            if(op == str) return true;
        return false;
    }

    const std::vector<std::string>& getOperators() const
    {
        return operators;
    }

    const std::function<T(T, T)> getFunction(const std::string& op) const
    {
        return operatorsFunctionMap.find(op)->second;
    }

    static KnownOperators<T>* getInstance()
    {

        static KnownOperators<T> instance;
        return &instance;
    }
private:
    KnownOperators()
    {
        T v;
        init(v);
        operators.push_back("+");
        operators.push_back("-");
        operators.push_back("*");
        operators.push_back("/");
    }

    void init(const int& v)
    {
        operatorsFunctionMap.insert(std::make_pair<std::string, std::function<int(int, int)>>("+", std::plus<int>()));
        operatorsFunctionMap.insert(std::make_pair<std::string, std::function<int(int, int)>>("-", std::minus<int>()));
        operatorsFunctionMap.insert(std::make_pair<std::string, std::function<int(int, int)>>("*", std::multiplies<int>()));
        operatorsFunctionMap.insert(std::make_pair<std::string, std::function<int(int, int)>>("/", std::divides<int>()));
    }

    void init(const double& v)
    {
        operatorsFunctionMap.insert(std::make_pair<std::string, std::function<double(double, double)>>("+", std::plus<double>()));
        operatorsFunctionMap.insert(std::make_pair<std::string, std::function<double(double, double)>>("-", std::minus<double>()));
        operatorsFunctionMap.insert(std::make_pair<std::string, std::function<double(double, double)>>("*", std::multiplies<double>()));
        operatorsFunctionMap.insert(std::make_pair<std::string, std::function<double(double, double)>>("/", std::divides<double>()));
    }

    void init(const std::string& v)
    {
        operatorsFunctionMap.insert(std::make_pair<std::string, std::function<std::string(std::string, std::string)>>("+", std::plus<std::string>()));
        operatorsFunctionMap.insert(std::make_pair<std::string, std::function<std::string(std::string, std::string)>>("-", std::function<std::string(std::string, std::string)>(minus)));
        operatorsFunctionMap.insert(std::make_pair<std::string, std::function<std::string(std::string, std::string)>>("*", std::function<std::string(std::string, std::string)>(multiplies)));
        operatorsFunctionMap.insert(std::make_pair<std::string, std::function<std::string(std::string, std::string)>>("/", std::function<std::string(std::string, std::string)>(divides)));
    }

    static KnownOperators<T>* singleton;
    std::vector<std::string> operators;
    std::map<std::string, std::function<T(T, T)>> operatorsFunctionMap;


};
template <typename T>
KnownOperators<T>* KnownOperators<T>::singleton;
#endif // KNOWNOPERATORS_H
