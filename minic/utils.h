#pragma once
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <stack>

using namespace std;

class IRCode {
public:
    string code;

public:
    void append(const string &str);

    void code_entry();

    void code_single(const string &op, const string &tg, const string &str1);

    void code_binary(const string &op, const string &tg, const string &str1, const string &str2);

    void code_label(const string &label);

    void code_assign(const string &str, const string &str1);

    void code_exit(const string &str);

    void code_globalInt(const string &name, const string &type, const string &info = "");

    void code_globalArray(const string &name, const string &type, const string &info = "");

    void code_valDecl(const string &name, const string &type, const string &info = "");

    void code_arrayDecl(const string &name, const string &type, const string &info = "");

    void code_cmp(const string &tg, const string &op, const string &str1, const string &str2);

    void code_bc(const string &tg, const string &str1, const string &str2);

    void code_br(const string &tg);

    void code_call(const std::string &to, const std::string &func, const std::vector<std::string> &params);

    const char *c_str();
};

class While_t {
public:
    string entry_name, body_name, end_name;
    While_t(const std::string &_entry, const std::string &_body, const std::string &_end) : entry_name(_entry), body_name(_body), end_name(_end) {}
};

class WhileStack {
private:
    stack<While_t> whiles;
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

class For_t {
public:
    string c_name, b_name;
    For_t(const std::string &c_name, const std::string &b_name) : c_name(c_name), b_name(b_name) {}
};

class ForStack {
private:
    stack<For_t> fors;
public:
    void append(const std::string &c_name, const std::string &b_name)
    {
        fors.emplace(c_name, b_name);
    }
    void quit()
    {
        fors.pop();
    }
    string getContinueName()
    {
        return fors.top().c_name;
    }
    string getBreakName()
    {
        return fors.top().b_name;
    }
};