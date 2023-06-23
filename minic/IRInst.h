#pragma once

#include <vector>

#include "symbol.h"

/// @brief IR指令的基类
class IRInst {

protected:
    /// @brief 构造函数
    IRInst();

    /// @brief 构造函数
    /// @param op 
    /// @param result 
    /// @param srcVal1 
    /// @param srcVal2 
    IRInst(string op, string result = NULL);

public:
    /// @brief 析构函数
    virtual ~IRInst();

    /// @brief 获取指令操作码
    /// @return 指令操作码
    string getOp();

    /// @brief 获取源操作数列表
    /// @return 源操作数列表
    std::vector<string> &getSrc();

    /// @brief 获取目的操作数，或者结果操作数
    /// @return 目的操作数，或者结果操作数
    string getDst();

    /*string getSrcVal1();

    string getSrcVal2();*/

    /// @brief 转换成字符串
    //virtual void toString(std::string &str);

protected:

    /// @brief IR指令操作码
    string op;

    /// @brief 源操作树
    std::vector<string> srcValues;

    /// @brief 目的操作数或结果或跳转指令的目标
    string dstValue;
};

/// @brief 二元运算指令
class BinaryIRInst : public IRInst {

public:
    /// @brief 构造函数
    /// @param op 
    /// @param result 
    /// @param srcVal1 
    /// @param srcVal2 
    BinaryIRInst(string op, string result, string srcVal1, string srcVal2);

    /// @brief 析构函数
    virtual ~BinaryIRInst() override;

    /// @brief 转换成字符串
    //void toString(std::string &str) override;

};

/// @brief 函数调用指令
class FuncCallIRInst : public IRInst {

protected:

    /// @brief 函数名
    std::string name;

public:

    /// @brief 无参数并且没有要设置的返回值的函数调用
    /// @param name 函数名
    FuncCallIRInst(std::string _name);

    /// @brief 含有参数的函数调用
    /// @param _srcVal1 函数的实参Value
    /// @param result 保存返回值的Value
    FuncCallIRInst(std::string _name, string _srcVal1, string _result = NULL);

    /// @brief 含有参数的函数调用
    /// @param srcVal 函数的实参Value
    /// @param result 保存返回值的Value
    FuncCallIRInst(std::string _name, std::vector<string> &_srcVal, string _result = NULL);

    /// @brief 析构函数
    virtual ~FuncCallIRInst() override;

    /// @brief 转换成字符串
    //void toString(std::string &str) override;
};

/// @brief 赋值指令或者说复制指令
class AssignIRInst : public IRInst {

public:
    /// @brief 构造函数
    /// @param result 
    /// @param srcVal1 
    AssignIRInst(string result, string srcVal1);

    /// @brief 析构函数
    virtual ~AssignIRInst() override;

    /// @brief 转换成字符串
    //void toString(std::string &str) override;

};
