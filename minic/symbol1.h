#ifndef SYMBOL_H
#define SYMBOL_H

#include <map>
#include <string>
#include <memory>
#include <variant>
#include <vector>
#include <stack>
#include <tuple>
#include "utils.h"

using namespace std;

class ValueType {
public:
    enum Type {
        INT, VOID_FUNC, INT_FUNC, ARRAY
    };
    Type type;
    int val;
    //???
};

class FuncTab;
class SymTabStack;

typedef variant<int, string> symbol;
typedef map<string, symbol> symtab;
extern FuncTab functab;
extern SymTabStack symtabstk;
extern class IRCode code_vec;

class SymTabStack {
private:
    int s_cnt = 0;
    vector<symtab> st_stack;

public:
    void push();

    void pop();

    void insert(unique_ptr<string> &sym, int val);

    string insert(unique_ptr<string> &sym);

    bool exist(unique_ptr<string> &sym, bool is_cur);

    symbol find(unique_ptr<string> &sym);
};

class FuncTab {
private:
    map<string, string> func_tab;
    bool exist(string func_name);

public:
    void insert(string func_name, string func_type);

    string find(unique_ptr<string> &func_name);
};

#endif

