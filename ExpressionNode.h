#ifndef EXPRESSIONNODE_H
#define EXPRESSIONNODE_H
#include "Helper.h"
#include "KnownOperators.h"
#include "Logger.h"

template <class T>
class AbstractExpressionNode
{
public:
    AbstractExpressionNode() {}

    virtual ~AbstractExpressionNode()
    {
        Logger::printDebug("Deleted Node Address: " + Helper::converAddressToString(static_cast<const void*>(this)));
        for(auto& child : childs)
        {
            if(child)
            {
                delete child;
                child = nullptr;
            }
        }
    }
    virtual std::string getValue() const = 0;
    virtual std::string toString() const = 0;

    std::vector<AbstractExpressionNode<T>*> childs;
};

template<class T>
class Constant : public AbstractExpressionNode<T>
{
public:
    Constant(const std::string& value)
        :  value(value) {}

    virtual ~Constant() {Logger::printDebug("Deleting Constant: " + toString());}

    virtual std::string getValue() const override       { return value; }
    virtual std::string toString() const override       { return getValue(); }
private:
    const std::string value;
};

template<class T>
class Operator : public AbstractExpressionNode<T>
{
public:
    Operator(const std::string& type)
       : type(type)
    {
        AbstractExpressionNode<T>::childs.push_back(nullptr);
        AbstractExpressionNode<T>::childs.push_back(nullptr);
    }
    virtual ~Operator() {Logger::printDebug("Deleting.. Operator " + toString());}

    virtual std::string getValue() const override
    {
        T v;
        return specializationGetValue(v);
    }
    virtual std::string toString() const override       { return type; }
private:
    std::string specializationGetValue(const int& v) const
    {
        return std::to_string(KnownOperators<T>::getInstance()->getFunction(type)(stoi(AbstractExpressionNode<T>::childs[0]->getValue()), stoi(AbstractExpressionNode<T>::childs[1]->getValue())));
    }
    std::string specializationGetValue(const double& v) const
    {
        return std::to_string(KnownOperators<T>::getInstance()->getFunction(type)(stod(AbstractExpressionNode<T>::childs[0]->getValue()), stod(AbstractExpressionNode<T>::childs[1]->getValue())));
    }
    std::string specializationGetValue(const std::string& v) const
    {
        return KnownOperators<T>::getInstance()->getFunction(type)(AbstractExpressionNode<T>::childs[0]->getValue(), AbstractExpressionNode<T>::childs[1]->getValue());
    }
    const std::string type;
};

#endif // EXPRESSIONNODE_H
