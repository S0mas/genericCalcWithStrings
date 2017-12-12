#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include <algorithm>
#include <map>
#include <typeinfo>
#include "ExpressionNode.h"
class AbstractExpressionTree
{
public:
    virtual void createExpTree(const std::vector<std::string>& strVec) = 0;
    virtual std::string getResult() const = 0;
    virtual std::string toString() const = 0;
    virtual std::vector<std::string> toStringVec() const = 0;
};
template<class T>
class ExpressionTree : public AbstractExpressionTree
{

public:
    ExpressionTree() : root(nullptr) {}
    ExpressionTree(const ExpressionTree& other) : root(nullptr)
    {
        createExpTree(other.toStringVec());
    }
    ~ExpressionTree()
    {
        clearTree();
    }

    void createExpTree(const std::vector<std::string>& strVec)
    {
        clearTree();
        std::vector<AbstractExpressionNode<T>*> expVec = translateStringVecToExpVec(strVec);
        createExpTreeRec(&root, expVec);
    }

    std::string getResult() const
    {
        T v;
        return internalGetResult(v);
    }

    std::string toString() const
    {
        std::string str;
        for(auto& ex : toStringVec())
            str += ex + " ";
        if(!str.empty())
            str.pop_back();
        return str;
    }

    std::vector<std::string> toStringVec() const
    {
        std::vector<std::string> strVec;
        toStringVecRec(root, strVec);
        return strVec;
    }
private:
    std::string internalGetResult(const int& v) const
    {
        return std::to_string(root->getValue());
    }

    std::string internalGetResult(const double& v) const
    {
        return std::to_string(root->getValue());
    }

    std::string internalGetResult(const std::string& v) const
    {
        return root->getValue();
    }

    void toStringVecRec(const AbstractExpressionNode<T>* root, std::vector<std::string>& strVec) const
    {
        if(root)
        {
            strVec.push_back(root->toString());
            for(auto& child : root->childs)
                toStringVecRec(child, strVec);
        }
    }

    void clearTree()
    {
        if(root)
        {
            delete root;
            root = nullptr;
        }
    }

    void createExpTreeRec(AbstractExpressionNode<T>** root, std::vector<AbstractExpressionNode<T>*>& expVec)
    {
        if(!expVec.empty())
        {
            *root = expVec.front();
            expVec.erase(expVec.begin());
        }
        else
            *root = getFulfillConstans();

        for(auto& child : (*root)->childs)
            createExpTreeRec(&child, expVec);
    }

    std::vector<AbstractExpressionNode<T>*> translateStringVecToExpVec(const std::vector<std::string>& strVec) const
    {
        std::vector<AbstractExpressionNode<T>*> expVec;
        for(auto& str : strVec)
            expVec.push_back(getExpNode(str));
        return expVec;
    }

    AbstractExpressionNode<T>* getExpNode(const std::string& str) const
    {
        AbstractExpressionNode<T>* result = nullptr;
        if(Helper::isKnownOperator(str))
            result = new Operator<T>(str);
        else if(Helper::isNumber(str) || Helper::constainsOnlyLettersOrNumbers(str))
            result = new Constant<T>(str);

        return result;
    }

    AbstractExpressionNode<T>* getFulfillConstans() const
    {
        return new Constant<T>("1");
    }

    AbstractExpressionNode<T>* root;
};

#endif //EXPRESSIONTREE_H
