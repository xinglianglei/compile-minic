#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <memory>
using namespace std;

class NameOrder {
public:
    int cnt_val;
    int cnt_label;
    unordered_map<string, int> no;

    NameOrder() :cnt_val(0), cnt_label(2) {}
    void reset();
    string getTmpName();
    string getLocalName();
    string getGlobalName(const string &s);
    string getLabelName();
    string getTmpArrayName(const vector<int> &vec);
    string getTmpPtrName();
};

class Func_t {
public:
    string param_Type;
    string param_Name;
    string param_ArrayType;
    Func_t();
    Func_t(string param_Type, string param_Name, string param_ArrayType = "") : param_Type(param_Type), param_Name(param_Name), param_ArrayType(param_ArrayType) {}
};

class FuncTab {
public:
    string func_Name;
    vector<Func_t> func_Params;
    bool is_none = false;
    FuncTab(string func_Name) :func_Name(func_Name) {}
    void insert(Func_t func_t);
};

class FuncTabStack {
public:
    string current_func;//当前函数名
    int cnt;//当前函数参数
    vector<FuncTab> func_Tabs;
    FuncTab findFunc(const string &func_Name);
    void insert(FuncTab func_Tab);
};

class MinicType {
public:
    enum TYPE {
        INT, FUNC_VOID, FUNC_INT, ARRAY
    };

    TYPE type;
    int value;
    MinicType *next;

    MinicType();
    MinicType(TYPE _type);
    MinicType(TYPE _type, int _value);
    MinicType(TYPE _type, const vector<int> &len);

    ~MinicType();
    void buildFromArrayType(const vector<int> &len);
    void getArrayType(vector<int> &len);
};

class Sym_t {
public:
    string ident;   // SysY标识符，诸如x,y
    string ir_name;    // KoopaIR中的具名变量，诸如@x_1, @y_1, ..., @n_2
    MinicType *type;
    Sym_t(const string &_ident, const string &_ir_name, MinicType *_type);
    ~Sym_t();
};

class SymTab_t {
public:
    const int UNKNOWN = -1;
    unordered_map<string, Sym_t *> symbol_tb;  // ident -> Symbol *
    SymTab_t() = default;
    ~SymTab_t();
    void insert(Sym_t *symbol);
    void insert(const string &ident, const string &name, MinicType::TYPE _type, int value);
    void insertINT(const string &ident, const string &name);
    void insertFunc(const string &ident, const string &name, MinicType::TYPE _t);
    void insertArray(const string &ident, const string &name, const vector<int> &len, MinicType::TYPE _t);
    bool exists(const string &ident);
    Sym_t *Search(const string &ident);
    int getValue(const string &ident);
    MinicType *getType(const string &ident);
    string getName(const string &ident);

};

class Label_t {
public:
    vector<int> t_line;
    vector<int> f_line;

    void insert_T(int index);
    void insert_F(int index);
};

class SymTabStk {
public:
    deque<unique_ptr<SymTab_t>> sym_tb_st;
    deque<unique_ptr<Label_t>> lab_t;
    NameOrder nm;
    string true_s;
    string false_s;

    const int UNKNOWN = -1;
    void push();
    //void push_block();
    void pop();
    //void pop_block();
    void reset();
    void insert(Sym_t *symbol);
    //插入全局变量
    void insertGlobalINT(const string &ident);
    //插入局部INT变量
    void insertLocalINT(const string &ident);
    //void insertTmpINT(const string &ident);
    //插入函数
    void insertFunc(const string &ident, MinicType::TYPE _t);
    //插入全局数组
    void insertGlobalArray(const string &ident, const vector<int> &len, MinicType::TYPE _t);
    //插入局部数组
    void insertLocalArray(const string &ident, const vector<int> &len, MinicType::TYPE _t);
    bool exists(const string &ident);
    int getValue(const string &ident);
    MinicType *getType(const string &ident);
    string getName(const string &ident);

    string getTmpName();   // inherit from name manager
    string getLabelName(); // inherit from name manager
    string getArrayType(const vector<int> &vec);
    string getTmpArrayName(const vector<int> &vec);
    string getTmpPtrName();
    void insert_Label();
    void insert_T(int index);
    void insert_F(int index);
};



