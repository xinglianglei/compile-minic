#ifndef AST_H
#define AST_H


#include <cassert>
#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include <sstream>
#include <string>

using namespace std;


enum ast_op_type {
    AST_OP_NULL,  // 终结符节点
    AST_OP_ADD,   // 二元运算符+
    AST_OP_MUL,   // 二元运算符*
    AST_OP_SUB,   // 二元运算符-
    AST_OP_DIV,   // 二元运算符/
    AST_OP_MOD,   // 二元运算符%

    AST_OP_OPT,   // 一元运算符+
    AST_OP_NEG,   // 一元运算符-
    AST_OP_NOT,   // 一元运算符!
    AST_OP_ASSIGN, // 赋值语句

    AST_OP_MAX,   // 非法运算符

    // TODO 抽象语法树其它内部节点运算符追加
    AST_OP_INT,    // 整型数
    AST_OP_VOID,   // 空类型
    AST_OP_IF,     // 条件判断if
    AST_OP_ELSE,   // else
    AST_OP_WHILE,  // while
    AST_OP_BREAK,  // break
    AST_OP_CONTINUE, // continue
    AST_OP_RETURN, // return
    AST_OP_LE,      // <=
    AST_OP_GE,      // >=
    AST_OP_LT,      // <
    AST_OP_GT,      // >
    AST_OP_NE,      // !=
    AST_OP_EQ,      // ==
    AST_OP_AND,     // &&
    AST_OP_OR,      // ||
    AST_OP_LINC,    // ++a
    AST_OP_LDEC,    // --a
    AST_OP_RINC,    // a++
    AST_OP_RDEC,    // a--
    AST_OP_INCR,    // ++
    AST_OP_DECR,    // --

};

class AST_Base;
class AST_ExpBase;
class AST_Vec;

class AST_FuncDef;
class AST_FuncFParam;
class AST_Block;
class AST_BlockItem;
class AST_Stmt;

class AST_Decl;
class AST_VarDecl;

class AST_VarDef;        // expbase
class AST_ConstExp;      // expbase
class AST_Initial;       // expbase

class AST_Exp;
class AST_Exp1;
class AST_Unary;
class AST_Primary;
class AST_LVal;
class AST_MulExp;
class AST_AddExp;
class AST_RelExp;
class AST_EqExp;
class AST_LAnd;
class AST_Lor;
class AST_FuncCall;

class AST_Base {
public:
    virtual ~AST_Base() = default;
    virtual string done(bool option = false) = 0; // overide <<
};

class AST_Vec {
public:
    bool is_zero;
    vector<unique_ptr<AST_Base>> vec;
    void push(unique_ptr<AST_Base> &ptr)
    {
        vec.push_back(move(ptr));
    }

};

class AST_Exp :public AST_Base {
public:
    bool is_number = false;
    int int_val;
    string id_val;

    virtual string get_value()
    {
        if (is_number) {
            return to_string(int_val);
        } else {
            return id_val;
        }
    }
    void copy_value(unique_ptr<AST_Exp> &sour)
    {
        is_number = sour->is_number;
        int_val = sour->int_val;
        id_val = sour->id_val;
    }
    virtual int getValue() = 0; // overide <<
};

class AST_CompUnit : public AST_Base {
public:
    vector<unique_ptr<AST_Base>> list_func;
    vector<unique_ptr<AST_Base>> list_decl;

    //AST_ComUnit() {}
    virtual string done(bool option = false) override;
};

class AST_FuncDef : public AST_Base {
public:
    enum TAG { DECL_NOPARAM, DECL_PARAM, DEF_NOPARAM, DEF_PARAM };
    TAG tag;
    unique_ptr<string> func_type;
    unique_ptr<string> func_name;
    unique_ptr<AST_Vec> func_params;
    unique_ptr<AST_Base> func_block;

    virtual string done(bool option = false) override;
};

class AST_FuncFParam :public AST_Base {
public:
    enum TAG { VARIABLE, ARRAY };
    TAG tag;
    //bool is_zero;
    unique_ptr<string> param_type;
    unique_ptr<string> param_name;
    unique_ptr<AST_Vec> ArrayIndexList;

    virtual string done(bool option = false) override;
};

class ArrayIndexExpList : public AST_Base {
public:
    std::vector<std::unique_ptr<AST_Exp>> exps;
};

class AST_Block : public AST_Base {
public:
    unique_ptr<AST_Vec> list_block;
    AST_Vec *func_params = nullptr;
    bool is_null = true;
    AST_Block() {}
    AST_Block(unique_ptr<AST_Vec> &list_block) :
        list_block(move(list_block)), is_null(false)
    {}
    virtual string done(bool option = false) override;
};

class AST_BlockItem :public AST_Base {
public:
    unique_ptr<AST_Base> elem;
    bool is_stmt;

    AST_BlockItem(unique_ptr<AST_Base> &elem, bool is_stmt)
        :elem(move(elem)), is_stmt(is_stmt)
    {}
    virtual string done(bool option = false) override;
};

//合起来处理,转了一下类型捏
class AST_Stmt : public AST_Exp {
public:
    unique_ptr<AST_Exp> exp;
    unique_ptr<AST_Exp> exp2;
    unique_ptr<AST_Exp> lval;
    unique_ptr<AST_Exp> cond; //while/if
    unique_ptr<AST_Base> body;//while/if
    unique_ptr<AST_Base> else_body;
    //修改了类型
    unique_ptr<AST_Base> block;
    enum TAG { RETURN, ASSIGN, BLOCK, EXP, WHILE, BREAK, CONTINUE, IF, FOR };
    TAG tag;
    virtual string done(bool option = false) override;
    virtual int getValue() override;
};

class AST_ConstExp :public AST_Exp {
public:
    unique_ptr<AST_Exp> exp;

    AST_ConstExp(unique_ptr<AST_Exp> &exp) : exp(move(exp)) {}

    virtual string done(bool option = false) override;
    virtual int getValue() override;
};

class AST_Decl :public AST_Base {
public:
    unique_ptr<AST_Base> decl;

    AST_Decl(unique_ptr<AST_Base> &decl) : decl(move(decl)) {}
    virtual string done(bool option = false) override;
};

class AST_VarDecl : public AST_Base {
public:
    unique_ptr<string> list_btype;
    unique_ptr<AST_Vec> list_vardecl;

    AST_VarDecl(unique_ptr<string> &list_btype, unique_ptr<AST_Vec> &list_vardecl)
        : list_btype(move(list_btype)), list_vardecl(move(list_vardecl))
    {}
    virtual string done(bool option = false) override;
};


class AST_VarDef : public AST_Base {
public:
    enum TAG { VARIABLE, ARRAY };
    TAG tag;
    unique_ptr<string> ident;
    unique_ptr<AST_Vec> arrayIndexList;   // size != 0, Array
    unique_ptr<AST_Exp> initVal;   // nullptr implies no init_val
    //void Dump(bool is_global = false) const;
    virtual string done(bool option = false) override;
};

class AST_Initial :public AST_Exp {
public:
    unique_ptr<AST_Exp> exp;
    unique_ptr<AST_Vec> initValList;
    enum TAG { EXP, INITVALLIST };
    TAG tag;
    virtual string done(bool option = false) override;
    virtual int getValue() override;
};

class AST_Exp1 : public AST_Exp {
public:
    unique_ptr<AST_Exp> xxx;

    AST_Exp1(unique_ptr<AST_Exp> &add2) :xxx(move(add2)) {}
    virtual string done(bool option = false) override;
    virtual int getValue() override;
};

class AST_Cond : public AST_Exp {
public:
    unique_ptr<AST_Exp> lor;
    AST_Cond(unique_ptr<AST_Exp> &lor) :lor(move(lor)) {}
    virtual string done(bool option = false) override;
    virtual int getValue() override;
};

/*class AST_SelfExp : public AST_Exp {
public:
    enum ast_op_type op;
    unique_ptr<AST_Exp> lval;
    virtual string done(bool option = false) override;
    virtual int getValue() override;
};*/

//!!!!!!有问题
class AST_Unary :public AST_Exp {
public:
    enum TAG { ONLY_P, UU, SELF };
    TAG tag;
    enum ast_op_type op;
    unique_ptr<AST_Exp> primaryExp;
    unique_ptr<AST_Exp> unaryExp;
    unique_ptr<AST_Exp> selfExp;

    virtual string done(bool option = false) override;
    virtual int getValue() override;
};

class AST_Primary : public AST_Exp {
public:
    enum TAG {
        LVAL, EXP, NUM
    };
    TAG tag;
    unique_ptr<AST_Exp> exp;
    unique_ptr<AST_Exp> lval;

    virtual string done(bool option = false) override;
    virtual int getValue() override;
};

class AST_LVal :public AST_Exp {
public:
    enum TAG { VARIABLE, ARRAY };
    TAG tag;
    unique_ptr<string> ident;
    unique_ptr<AST_Vec> exps;

    virtual string done(bool option = false) override;
    virtual int getValue() override;
};

//op是不是缺个*？
class AST_MulExp :public AST_Exp {
public:
    enum ast_op_type op;
    unique_ptr<AST_Exp> mulExp;
    unique_ptr<AST_Exp> unaryExp;

    AST_MulExp(unique_ptr<AST_Exp> &unaryExp) :unaryExp(move(unaryExp)) {}
    AST_MulExp(enum ast_op_type op, unique_ptr<AST_Exp> &mulExp, unique_ptr<AST_Exp> &unaryExp)
        : op(op), mulExp(move(mulExp)), unaryExp(move(unaryExp))
    {}
    virtual string done(bool option = false) override;
    virtual int getValue() override;
};

class AST_AddExp : public AST_Exp {
public:
    enum ast_op_type op;
    unique_ptr<AST_Exp> addExp;
    unique_ptr<AST_Exp> mulExp;
    AST_AddExp(unique_ptr<AST_Exp> &mulExp) :mulExp(move(mulExp)) {}
    AST_AddExp(enum ast_op_type op, unique_ptr<AST_Exp> &addExp, unique_ptr<AST_Exp> &mulExp) :
        op(op), addExp(move(addExp)), mulExp(move(mulExp))
    {}
    virtual string done(bool option = false) override;
    virtual int getValue() override;
};

class AST_RelExp :public AST_Exp {
public:
    enum ast_op_type op;
    unique_ptr<AST_Exp> relExp;
    unique_ptr<AST_Exp> addExp;

    AST_RelExp(unique_ptr<AST_Exp> &addExp) :addExp(move(addExp)) {}
    AST_RelExp(enum ast_op_type op, unique_ptr<AST_Exp> &relExp, unique_ptr<AST_Exp> &addExp)
        :op(op), relExp(move(relExp)), addExp(move(addExp))
    {}
    virtual string done(bool option = false) override;
    virtual int getValue() override;
};


class AST_EqExp : public AST_Exp {
public:
    enum ast_op_type op;
    unique_ptr<AST_Exp> eqExp;
    unique_ptr<AST_Exp> relExp;
    AST_EqExp(unique_ptr<AST_Exp> &relExp) :relExp(move(relExp)) {}
    AST_EqExp(enum ast_op_type op, unique_ptr<AST_Exp> &eqExp, unique_ptr<AST_Exp> &relExp)
        :op(op), eqExp(move(eqExp)), relExp(move(relExp))
    {}
    virtual string done(bool option = false) override;
    virtual int getValue() override;
};

class AST_LAnd :public AST_Exp {
public:
    bool only_eq;
    unique_ptr<AST_Exp> landExp;
    unique_ptr<AST_Exp> eqExp;

    AST_LAnd(unique_ptr<AST_Exp> &eqExp) :only_eq(true), eqExp(move(eqExp)) {}
    AST_LAnd(unique_ptr<AST_Exp> &landExp, unique_ptr<AST_Exp> &eqExp)
        :only_eq(false), landExp(move(landExp)), eqExp(move(eqExp))
    {}
    virtual string done(bool option = false) override;
    virtual int getValue() override;
};
class AST_LOr :public AST_Exp {
public:
    bool only_land;
    unique_ptr<AST_Exp> landExp;
    unique_ptr<AST_Exp> lorExp;

    AST_LOr(unique_ptr<AST_Exp> &landExp) : only_land(true), landExp(move(landExp)) {}
    AST_LOr(unique_ptr<AST_Exp> &lorExp, unique_ptr<AST_Exp> &landExp)
        :only_land(false), lorExp(move(lorExp)), landExp(move(landExp))
    {}
    virtual string done(bool option = false) override;
    virtual int getValue() override;
};

//不继承Exp了，改为Base
class AST_FuncCall :public AST_Exp {
public:
    unique_ptr<string> id_val;
    unique_ptr<AST_Vec> params;
    bool is_param = false;

    AST_FuncCall(unique_ptr<string> &id_val) :id_val(move(id_val)) {}
    AST_FuncCall(unique_ptr<string> &id_val, unique_ptr<AST_Vec> &params)
        :id_val(move(id_val)), params(move(params)), is_param(true)
    {}

    virtual string done(bool option = false) override;
    virtual int getValue() override;
};
#endif

