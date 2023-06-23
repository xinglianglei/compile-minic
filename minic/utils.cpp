#include "utils.h"
#include "IRCode.h"
InterCode itcode;
void IRCode::append(const string &str)
{
    code += str;
}

void IRCode::code_entry()
{
    code += "\tentry\n";
    IRInst *inst = new BinaryIRInst("entry", "entry", "", "");
    itcode.addInst(inst);
    itcode.addcode("\tentry\n");
}

void IRCode::code_single(const string &op, const string &tg, const string &str1)
{
    code += "\t" + tg + " = " + op + " " + str1 + "\n";
    itcode.addInst(new BinaryIRInst(op, tg, str1, ""));
    itcode.addcode("\t" + tg + " = " + op + " " + str1 + "\n");
}

void IRCode::code_binary(const string &op, const string &tg, const string &str1, const string &str2)
{
    code += "\t" + tg + " = " + op + " " + str1 + ", " + str2 + "\n";
    itcode.addInst(new BinaryIRInst(op, tg, str1, str2));
    itcode.addcode("\t" + tg + " = " + op + " " + str1 + ", " + str2 + "\n");
}

void IRCode::code_label(const string &label)
{
    code += label + ":\n";
    itcode.addInst(new BinaryIRInst("label", label, "", ""));
    itcode.addcode(label + ":\n");
}

void IRCode::code_assign(const string &str, const string &str1)
{
    code += "\t" + str + "=" + str1 + "\n";
    itcode.addInst(new AssignIRInst(str, str1));
    itcode.addcode("\t" + str + "=" + str1 + "\n");
}

void IRCode::code_exit(const string &str)
{
    code += "\texit " + str + "\n";
    itcode.addInst(new BinaryIRInst("exit", str, "", ""));
    itcode.addcode("\texit " + str + "\n");
}

void IRCode::code_globalInt(const string &name, const string &type, const string &info)
{
    code += "declare " + type + " " + name + " " + info + "\n";
}

void IRCode::code_globalArray(const string &name, const string &type, const string &info)
{
    code += "declare i32 " + name + type + " " + info + "\n";
}

void IRCode::code_valDecl(const string &name, const string &type, const string &info)
{
    code += "\tdeclare " + type + " " + name + " " + info + "\n";
}

void IRCode::code_arrayDecl(const string &name, const string &type, const string &info)
{
    code += "\tdeclare i32 " + name + type + " " + info + "\n";
}

void IRCode::code_cmp(const string &tg, const string &op, const string &str1, const string &str2)
{
    code += "\t" + tg + "=cmp " + op + " " + str1 + ", " + str2 + "\n";
    itcode.addInst(new BinaryIRInst(op, tg, str1, str2));
    itcode.addcode("\t" + tg + "=cmp " + op + " " + str1 + ", " + str2 + "\n");
}

void IRCode::code_bc(const string &tg, const string &str1, const string &str2)
{
    code += "\tbc " + tg + ",label" + str1 + " ,label" + str2 + " \n";
    itcode.addInst(new BinaryIRInst("bc", tg, str1, str2));
    itcode.addcode("\tbc " + tg + ",label" + str1 + " ,label" + str2 + " \n");
}

void IRCode::code_br(const string &tg)
{
    code += "\tbr label " + tg + "\n";
    itcode.addInst(new BinaryIRInst("br", tg, "", ""));
    itcode.addcode("\tbr label " + tg + "\n");
}

void IRCode::code_call(const std::string &to, const std::string &func, const std::vector<std::string> &params)
{
    string tmp_code;
    if (to.length()) {
        tmp_code += "\t" + to + " = call i32 ";
    } else {
        tmp_code += "\tcall void ";
    }
    tmp_code += func + '(';
    if (params.size()) {
        int n = params.size();
        tmp_code += params[0];
        for (int i = 1; i < n; ++i) {
            tmp_code += ", " + params[i];
        }
    }
    tmp_code += ")\n";
    code += tmp_code;
    itcode.addInst(new FuncCallIRInst(func, "", to));
    itcode.addcode(tmp_code);
}
const char *IRCode::c_str() { return code.c_str(); }