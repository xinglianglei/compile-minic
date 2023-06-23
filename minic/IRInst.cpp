#include "IRInst.h"

/// @brief 构造函数
IRInst::IRInst()
{
    // 未知指令
    op = "";
}

/// @brief 构造函数
/// @param op 
/// @param result 
/// @param srcVal1 
/// @param srcVal2 
IRInst::IRInst(string _op, string _result) :
    op(_op), dstValue(_result)
{}

/// @brief 析构函数
IRInst::~IRInst()
{

}

/// @brief 获取指令操作码
/// @return 指令操作码
string IRInst::getOp()
{
    return op;
}

/// @brief 获取源操作数列表
/// @return 源操作数列表
std::vector<string > &IRInst::getSrc()
{
    return srcValues;
}

/// @brief 获取目的操作数，或者结果操作数
/// @return 目的操作数，或者结果操作数
string IRInst::getDst()
{
    return dstValue;
}

/*string IRInst::getSrcVal1()
{
    return srcVal1;
}

string IRInst::getSrcVal2()
{
    return srcVal1;
}*/

/// @brief 转换成字符串
/// @param str 转换后的字符串
/*
void IRInst::toString(std::string &str)
{
    // 未知指令
    str = "Unkown IR Instruction";
}*/

/// @brief 构造函数
/// @param op 操作符
/// @param result 结果操作数
/// @param srcVal1 源操作数1
/// @param srcVal2 源操作数2
BinaryIRInst::BinaryIRInst(string _op, string _result, string _srcVal1, string _srcVal2) :
    IRInst(_op, _result)
{
    srcValues.push_back(_srcVal1);
    srcValues.push_back(_srcVal2);
}

/// @brief 析构函数
BinaryIRInst::~BinaryIRInst()
{

}

/// @brief 转换成字符串
/// @param str 转换后的字符串
/*
void BinaryIRInst::toString(std::string &str)
{
    string result;
    string src1, *src2;
    if (op != IRINST_OP_NEG && op != IRINST_OP_INT && op != IRINST_OP_REAL)
        src1 = srcValues[0], src2 = srcValues[1], result = dstValue;
    else
        src1 = srcValues[0], result = dstValue;

    switch (op) {
    case IRINST_OP_ADD:

        // 加法指令，二元运算
        src1->getName();
        src2->getName();
        str = result->getName() + " = add " + src1->getName() + ", " + src2->getName();
        break;
    case IRINST_OP_MUL:

        // 减法指令，二元运算
        str = result->getName() + " = mul " + src1->getName() + ", " + src2->getName();
        break;
    case IRINST_OP_SUB:

        // 减法指令，二元运算
        str = result->getName() + " = sub " + src1->getName() + ", " + src2->getName();
        break;
    case IRINST_OP_DIV:

        // 除法指令，二元运算
        str = result->getName() + " = div " + src1->getName() + ", " + src2->getName();
        break;
    case IRINST_OP_REM:

        // 取余指令，二元运算
        str = result->getName() + " = rem " + src1->getName() + ", " + src2->getName();
        break;
    case IRINST_OP_NEG:

        // 取负指令，一元运算
        str = result->getName() + " = neg " + src1->getName();
        break;

    case IRINST_OP_INT:

        // float->int，一元运算
        str = result->getName() + " = int " + src1->getName();
        break;

    case IRINST_OP_REAL:

        // int->float，一元运算
        str = result->getName() + " = real " + src1->getName();
        break;

    default:
        // 未知指令
        IRInst::toString(str);
        break;
    }
}*/

/// @brief 无参数的函数调用
/// @param name 函数名
/// @param result 保存返回值的Value
FuncCallIRInst::FuncCallIRInst(std::string _name) :
    IRInst("call", nullptr), name(_name)
{}

/// @brief 含有参数的函数调用
/// @param _srcVal1 函数的实参Value
/// @param result 保存返回值的Value
FuncCallIRInst::FuncCallIRInst(std::string _name, string _srcVal1, string _result) :
    IRInst("call", _result), name(_name)
{
    srcValues.push_back(_srcVal1);
}

/// @brief 含有参数的函数调用
/// @param srcVal 函数的实参Value
/// @param result 保存返回值的Value
FuncCallIRInst::FuncCallIRInst(std::string _name, std::vector<string > &_srcVal, string _result) :
    IRInst("call", _result), name(_name)
{
    // 实参拷贝
    srcValues = _srcVal;
}

/// @brief 析构函数
FuncCallIRInst::~FuncCallIRInst()
{

}

/*
/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void FuncCallIRInst::toString(std::string &str)
{
    string result = dstValue;

    // TODO 这里应该根据函数名查找函数定义或者声明获取函数的类型
    // 这里假定所有函数返回类型要么是i32，要么是void
    // 函数参数的类型是i32

    if (!dstValue) {

        // 函数没有返回值设置
        str = "call void @" + name + "(";
    } else {

        // 函数有返回值要设置到结果变量中
        str = result->getName() + " = call int @" + name + "(";
    }

    for (size_t k = 0; k < srcValues.size(); ++k) {

        str += "i32 " + srcValues[k]->getName();

        if (k != (srcValues.size() - 1)) {

            str += ", ";
        }
    }

    str += ")";
}*/

/// @brief 赋值IR指令
/// @param _result 
/// @param _srcVal1 
AssignIRInst::AssignIRInst(string _result, string _srcVal1) :
    IRInst("=", _result)
{
    srcValues.push_back(_srcVal1);
}

/// @brief 析构函数
AssignIRInst::~AssignIRInst()
{

}

/*
/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void AssignIRInst::toString(std::string &str)
{
    string src1 = srcValues[0], *result = dstValue;

    str = result->getName() + " = assign " + src1->getName();
}*/
