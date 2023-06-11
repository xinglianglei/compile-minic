#pragma once
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <stack>

using namespace std;

class IRCode {
private:
    string code;

public:
    void append(const string &str)
    {
        code += str;
    }

    void code_binary(const string &op, const string &tg, const string &str1, const string &str2)
    {
        code += "\t" + tg + " = " + op + " " + str1 + ", " + str2 + "\n";
    }

    void code_label(const string &label)
    {
        code += label + ":\n";
    }

    void code_ret(const string &str)
    {
        code += "exit " + str + "\n";
    }

    void code_globalInt(const string &name)
    {
        code += "declare i32 " + name + "\n";
    }

    void code_globalArray(const string &name, const string &type)
    {
        code += "declare i32 " + name + type + "\n";
    }

    void code_valDecl(const string &name)
    {
        code += "\tdeclare i32 " + name + "\n";
    }

    void code_arrayDecl(const string &name, const string &type)
    {
        code += "\tdeclare i32 " + name + type + "\n";
    }

    void code_cmp(const string &tg, const string &op, const string &str1, const string &str2)
    {
        code += "\t" + tg + "=cmp " + op + str1 + ", " + str2 + "\n";
    }

    void code_bc(const string &tg, const string &str1, const string &str2)
    {
        code += "\tbc" + tg + ",label" + str1 + ",label" + str2 + "\n";
    }

    void code_br(const string &tg)
    {
        code += "\tbr Label" + tg + "\n";
    }

    void code_call(const std::string &to, const std::string &func, const std::vector<std::string> &params)
    {
        if (to.length()) {
            code += "\t" + to + " = call i32";
        } else {
            code += "\tcall void";
        }
        code += func + '(';
        if (params.size()) {
            int n = params.size();
            code += params[0];
            for (int i = 1; i < n; ++i) {
                code += ", " + params[i];
            }
        }
        code += ")\n";
    }
    const char *c_str() { return code.c_str(); }
};

class BlockController {
private:
    bool f = true;
public:
    bool alive()
    {
        return f;
    }

    void finish()
    {
        f = false;
    }

    void set()
    {
        f = true;
    }
};

class WhileName {
public:
    string entry_name, body_name, end_name;
    WhileName(const std::string &_entry, const std::string &_body, const std::string &_end) : entry_name(_entry), body_name(_body), end_name(_end) {}
};

class WhileStack {
private:
    stack<WhileName> whiles;
public:
    void append(const std::string &_entry, const std::string &_body, const std::string &_end)
    {
        whiles.emplace(_entry, _body, _end);
    }
    void quit()
    {
        whiles.pop();
    }
    string getEntryName()
    {
        return whiles.top().entry_name;
    }
    string getBodyName()
    {
        return whiles.top().body_name;
    }
    string getEndName()
    {
        return whiles.top().end_name;
    }
};