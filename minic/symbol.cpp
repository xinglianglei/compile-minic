#include "Symbol.h"
#include <iostream>
using namespace std;

void NameOrder::reset()
{
    cnt_val = 0;
    cnt_label = 1;
}

string NameOrder::getTmpName()
{
    return "%t" + to_string(cnt_val++);
}

string NameOrder::getLocalName()
{
    return "%l" + to_string(cnt_val++);
}

string NameOrder::getGlobalName(const string &s)
{
    //auto i = no.find(s);
    return "@" + s;
    /*if (i == no.end()) {
        no.insert(make_pair(s, 1));
        return "@" + s + "_0";
    }
    return "@" + s + "_" + to_string(i->second++);*/
}
string NameOrder::getLabelName()
{
    return ".L" + to_string(cnt_label++);
}

string NameOrder::getTmpArrayName(const vector<int> &vec)
{
    std::string ans = "";
    for (int i = vec.size() - 1; i >= 0; --i) {
        ans = "[" + ans + std::to_string(vec[i]) + "]";
    }
    return "%t" + ans + to_string(cnt_val++);
}

string NameOrder::getTmpPtrName()
{
    return "%t" + to_string(cnt_val++);
}

MinicType::MinicType() :type(INT), value(-1) {}

MinicType::MinicType(TYPE _t) :type(_t), value(-1) {}

MinicType::MinicType(TYPE _t, int _v) : type(_t), value(_v) {}

MinicType::MinicType(TYPE _t, const std::vector<int> &len) :type(_t), value(-1)
{
    buildFromArrayType(len);
}

MinicType::~MinicType()
{
    /*auto p = next;
    if (p != nullptr) {
        auto prev = p;
        p = p->next;
        delete prev;
    }*/
}

void MinicType::buildFromArrayType(const vector<int> &len)
{
    /*TYPE t = ARRAY;
    MinicType *p = this;
    for (int i : len) {
        p->type = t;
        p->value = i;
        p->next = new MinicType();
        p = p->next;
    }
    p->next = new MinicType();
    p = p->next;
    p->type = INT;*/
    for (auto i : len) {
        array_index.push_back(i);
    }
}

void MinicType::getArrayType(vector<int> &len)
{
    len.clear();
    /*MinicType *p = this;
    //注意这里一定是p->value!!!
    while (p->next != nullptr && (p->type == ARRAY)) {
        len.push_back(p->value);
        p = p->next;
    }*/
    for (auto i : array_index) {
        len.push_back(i);
    }
    return;
}

Sym_t::Sym_t(const string &_ident, const string &_ir_name, MinicType *_type) : ident(_ident), ir_name(_ir_name), type(_type)
{}

Sym_t::~Sym_t()
{
    if (type) delete type;
}

SymTab_t::~SymTab_t()
{
    for (auto &p : symbol_tb) {
        delete p.second;
    }
}

void SymTab_t::insert(Sym_t *symbol)
{
    symbol_tb.insert({ symbol->ident, symbol });
}

void SymTab_t::insert(const string &ident, const string &ir_name, MinicType::TYPE _type, int value)
{
    MinicType *ty = new MinicType(_type, value);
    Sym_t *sym = new Sym_t(ident, ir_name, ty);
    insert(sym);
}

void SymTab_t::insertINT(const string &ident, const string &ir_name)
{
    insert(ident, ir_name, MinicType::INT, UNKNOWN);
}

void SymTab_t::insertFunc(const string &ident, const string &ir_name, MinicType::TYPE _type)
{
    insert(ident, ir_name, _type, UNKNOWN);
}

void SymTab_t::insertArray(const string &ident, const string &ir_name, const vector<int> &len, MinicType::TYPE _type)
{
    MinicType *ty = new MinicType(_type, len);
    Sym_t *sym = new Sym_t(ident, ir_name, ty);
    insert(sym);
}

bool SymTab_t::exists(const string &ident)
{
    return symbol_tb.find(ident) != symbol_tb.end();
}

Sym_t *SymTab_t::Search(const string &ident)
{
    return symbol_tb.find(ident)->second;
}

int SymTab_t::getValue(const string &ident)
{
    return symbol_tb.find(ident)->second->type->value;
}

MinicType *SymTab_t::getType(const string &ident)
{
    return symbol_tb.find(ident)->second->type;
}

string SymTab_t::getName(const string &ident)
{
    if (symbol_tb.find(ident) != nullptr)
        return symbol_tb.find(ident)->second->ir_name;
    else
        return "";
}

void Label_t::insert_T(int index)
{
    t_line.push_back(index);
}

void Label_t::insert_F(int index)
{
    f_line.push_back(index);
}


void SymTabStk::push()
{
    sym_tb_st.emplace_back(new SymTab_t());
}

void SymTabStk::pop()
{
    sym_tb_st.pop_back();
}

void SymTabStk::reset()
{
    nm.reset();
}

void SymTabStk::insert(Sym_t *symbol)
{
    sym_tb_st.back()->insert(symbol);
}

void SymTabStk::insertGlobalINT(const string &ident)
{
    string ir_name = nm.getGlobalName(ident);
    sym_tb_st.back()->insertINT(ident, ir_name);
}

void SymTabStk::insertLocalINT(const string &ident)
{
    string ir_name = nm.getLocalName();
    sym_tb_st.back()->insertINT(ident, ir_name);
}
/*
void SymTabStk::insertTmpINT(const string &ident)
{
    string ir_name = nm.getTmpName();
    sym_tb_st.back()->insertINT(ident, ir_name);
}*/


void SymTabStk::insertFunc(const string &ident, MinicType::TYPE _type)
{
    string ir_name = "@" + ident;
    sym_tb_st.back()->insertFunc(ident, ir_name, _type);
}

void SymTabStk::insertGlobalArray(const string &ident, const vector<int> &len, MinicType::TYPE _type)
{
    string ir_name = nm.getGlobalName(ident);
    sym_tb_st.back()->insertArray(ident, ir_name, len, _type);
}

void SymTabStk::insertLocalArray(const string &ident, const vector<int> &len, MinicType::TYPE _type)
{
    string ir_name = nm.getLocalName();
    sym_tb_st.back()->insertArray(ident, ir_name, len, _type);
}

bool SymTabStk::exists(const string &ident)
{
    for (int i = (int)sym_tb_st.size() - 1; i >= 0; --i) {
        if (sym_tb_st[i]->exists(ident))
            return true;
    }
    return false;
}

int SymTabStk::getValue(const string &ident)
{
    int i = (int)sym_tb_st.size() - 1;
    for (; i >= 0; --i) {
        if (sym_tb_st[i]->exists(ident))
            break;
    }
    return sym_tb_st[i]->getValue(ident);
}

MinicType *SymTabStk::getType(const string &ident)
{
    int i = (int)sym_tb_st.size() - 1;
    for (; i >= 0; --i) {
        if (sym_tb_st[i]->exists(ident))
            break;
    }
    return sym_tb_st[i]->getType(ident);
}

//返回字符串对于的IR变量名
string SymTabStk::getName(const string &ident)
{
    int i = (int)sym_tb_st.size() - 1;
    for (; i >= 0; --i) {
        if (sym_tb_st[i]->exists(ident))
            break;
    }
    if (i < 0)
        return "";
    return sym_tb_st[i]->getName(ident);
}

//仅仅是得到一个临时变量
string SymTabStk::getTmpName()
{
    return nm.getTmpName();
}
/*
string SymTabStk::getLocalName(const string &ident)
{
    return nm.getLocalName(const string & ident);
}*/

//仅仅是得到一个Label值
string SymTabStk::getLabelName()
{
    return nm.getLabelName();
}
/*string SymTabStk::getGlobalName(const string &var)
{
    return nm.getGlobalName(var);
}*/

string SymTabStk::getArrayType(const vector<int> &vec)
{
    // int a[w0][w1]...[wn-1]
    std::string ans = "";
    for (int i = 0; i < vec.size(); ++i) {
        ans = ans + "[" + to_string(vec[i]) + "]";
    }
    return ans;
}
string SymTabStk::getTmpArrayName(const vector<int> &vec)
{
    return nm.getTmpArrayName(vec);
}

string SymTabStk::getTmpPtrName()
{
    return nm.getTmpPtrName();
}

void SymTabStk::insert_Label()
{
    lab_t.emplace_back(new Label_t());
}

void SymTabStk::insert_T(int index)
{
    lab_t.back()->insert_T(index);
}

void SymTabStk::insert_F(int index)
{
    lab_t.back()->insert_F(index);
}

FuncTab FuncTabStack::findFunc(const string &func_Name)
{
    for (auto func : func_Tabs) {
        if (func.func_Name == func_Name) {
            return func;
        }
    }
    FuncTab tmp("");
    tmp.is_none = true;
    return tmp;
}

void FuncTabStack::insert(FuncTab func_Tab)
{
    func_Tabs.push_back(func_Tab);
}

void FuncTab::insert(Func_t func_t)
{
    func_Params.push_back(func_t);
}
