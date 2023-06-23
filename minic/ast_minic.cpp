/*
一点说明
code_vec=code_vec+code_localval+code_tmpval+code_stmt;
*/

#include "ast_minic.h"
#include "symbol.h"
#include "utils.h"


IRCode code_vec;
IRCode code_localval;
IRCode code_tmpval;
IRCode code_stmt;
SymTabStk stk;
MinicType::TYPE tmp;
WhileStack wst;
ForStack forst;
FuncTabStack fts;
int flag = 0;//用来指示是否是条件


// 1 表示形参; 2表示实参; 0表示内部

string AST_CompUnit::done(bool option)
{
    stk.push();
    cout << "decl i32 @getint()" << endl;
    cout << "decl i32 @getch()" << endl;
    cout << "decl i32 @getarray(*i32)" << endl;
    cout << "decl @putint(i32)" << endl;
    cout << "decl @putch(i32)" << endl;
    cout << "decl @putarray(i32, *i32)" << endl;
    cout << "decl @putch(*i8)" << endl;

    //增加了内置函数调用的形参类型记录
    stk.insertFunc(string("getint"), MinicType::FUNC_INT);
    stk.insertFunc(string("getch"), MinicType::FUNC_INT);
    stk.insertFunc(string("getarray"), MinicType::FUNC_INT);
    stk.insertFunc(string("putint"), MinicType::FUNC_VOID);
    stk.insertFunc(string("putch"), MinicType::FUNC_VOID);
    stk.insertFunc(string("putarray"), MinicType::FUNC_VOID);
    stk.insertFunc(string("putch"), MinicType::FUNC_VOID);

    //int getint()
    FuncTab *functab = new FuncTab("getint");
    fts.insert(*functab);

    //int getarray(int a[])
    functab = new FuncTab("getarray");
    Func_t *func_t = new Func_t("array", "a", "[0]");
    functab->insert(*func_t);
    fts.insert(*functab);

    //int getch()
    functab = new FuncTab("getch");
    fts.insert(*functab);

    //void putint(int a)
    functab = new FuncTab("putint");
    func_t = new Func_t("i32", "a");
    functab->insert(*func_t);
    fts.insert(*functab);

    //void putch(int a)
    functab = new FuncTab("putch");
    func_t = new Func_t("i32", "a");
    functab->insert(*func_t);
    fts.insert(*functab);

    //void putarray(int n,int a[])
    functab = new FuncTab("putarray");
    func_t = new Func_t("i32", "n");
    functab->insert(*func_t);
    func_t = new Func_t("array", "a[]", "[0]");
    functab->insert(*func_t);
    fts.insert(*functab);

    for (auto &decl : this->list_decl) {
        //!!!这里没有const变量，需要可以加,这里还有待修正
        auto ast_decl = dynamic_cast<AST_VarDecl *>(decl.get());
        //auto var_decl = dynamic_cast<AST_VarDecl *>(ast_decl->decl.get());
        ast_decl->done(true);
    }

    for (auto &func : list_func) {
        func->done();
    }
    stk.pop();
    return "";
}


string AST_FuncDef::done(bool option)
{
    string name = *func_name;
    if (stk.getName(name) != "") {
        return "";
    }
    stk.reset();
    string type;
    if (*func_type == "int") {
        tmp = MinicType::FUNC_INT;
        type = "i32";
    } else {
        tmp = MinicType::FUNC_VOID;
        type = "void";
    }
    stk.insertFunc(*func_name, tmp); //函数表
    code_vec.append("define " + type + " @" + *func_name + "(");
    //压入一个符号表，新的作用域
    stk.push();
    //保证返回值一定是l0
    string return_Val, return_Label;
    if (*func_type == "int") {
        stk.insertLocalINT("return");
        return_Val = stk.getName("return");
        code_localval.code_valDecl(return_Val, "i32");
        return_Label = stk.getLabelName();
    } else {
        return_Label = stk.getLabelName();
    }

    //开启形参
    int params_num = 0;//后续处理空字符组会用到
    if (tag == AST_FuncDef::DECL_PARAM || tag == AST_FuncDef::DEF_PARAM) {
        for (auto &param : func_params->vec) {
            if (params_num != 0)
                code_vec.append(",");
            param->done();
            params_num++;
        }
    }
    //关闭形参
    code_vec.append(")");

    if (tag == AST_FuncDef::DECL_NOPARAM || tag == AST_FuncDef::DECL_PARAM)
        code_vec.append(";\n");
    else {
        code_vec.append(" {\n");
        code_stmt.code_entry();
        //code_stmt.append("\tentry\n");
        //解决函数形参赋值局部变量
        int param_num;
        if (type == "i32")
            param_num = 1;
        else
            param_num = 0;
        if (tag == AST_FuncDef::DEF_PARAM) {
            FuncTab *functab = new FuncTab(*func_name);
            for (auto &param : func_params->vec) {
                auto paramItem = dynamic_cast<AST_FuncFParam *>(param.get());
                //cout << (paramItem->tag == AST_FuncFParam::VARIABLE) << endl;
                if (paramItem->tag == AST_FuncFParam::VARIABLE) {
                    stk.insertLocalINT(*(paramItem->param_name));
                    string localName = stk.getName(*(paramItem->param_name));
                    code_localval.code_valDecl(localName, "i32");
                    code_stmt.code_assign(localName, "%t" + to_string(param_num));
                    //code_stmt.append("\t" + localName + "=" + "%t" + to_string(param_num) + "\n");
                    param_num++;

                    //记录
                    Func_t *func_t = new Func_t("i32", *(paramItem->param_name));
                    functab->insert(*func_t);
                } else {
                    //获取数组维度
                    vector<int> len;
                    for (auto &ce : paramItem->ArrayIndexList->vec) {
                        auto ce_ = dynamic_cast<AST_Exp *>(ce.get());
                        len.push_back(ce_->getValue());
                    }
                    /*if (paramItem->ArrayIndexList->vec.size() == 0) {
                        len.push_back(0);
                    }*/
                    //获取数组类型
                    string array_type = stk.getArrayType(len);
                    //修正数组类型
                    if (paramItem->ArrayIndexList->is_zero) {
                        array_type.replace(0, 1, "[0]");
                    } else {
                        array_type.replace(0, 3, "[0]");
                    }
                    //插入局部变量,注意这里插入数组，不是INT
                    stk.insertLocalArray(*(paramItem->param_name), len, MinicType::ARRAY);
                    //找到局部变量
                    string localName = stk.getName(*(paramItem->param_name));
                    //插入定义语句
                    code_localval.code_arrayDecl(localName, array_type, " ;" + *(paramItem->param_name));
                    code_stmt.code_assign(localName, "%t" + to_string(param_num));
                    //code_stmt.append("\t" + localName + "=" + "%t" + to_string(param_num) + "\n");
                    //记录
                    Func_t *func_t = new Func_t("array", *(paramItem->param_name), array_type);
                    functab->insert(*func_t);
                    param_num++;
                }
            }
            //插入函数栈
            fts.insert(*functab);
        }
        auto ast_block = dynamic_cast<AST_Block *>(func_block.get());
        ast_block->func_params = func_params.get();
        ast_block->done();
        if (stk.nm.cnt_label > 2)
            code_stmt.code_label(return_Label);
        if (*func_type == "int")
            code_stmt.code_exit(return_Val);
        //code_stmt.append("\texit " + return_Val + "\n");
        else
            code_stmt.code_exit("");
        //code_stmt.append("\texit\n");
        code_stmt.append("}\n\n");
    }
    code_vec.append(code_localval.code);
    code_vec.append(code_tmpval.code);
    code_vec.append(code_stmt.code);
    code_localval.code.clear();
    code_tmpval.code.clear();
    code_stmt.code.clear();
    return "";
}

string AST_FuncFParam::done(bool option)
{
    if (tag == AST_FuncFParam::VARIABLE) {
        string tmpName = stk.getTmpName();
        code_vec.append("i32 " + tmpName);
        //stk.insertLocalINT(*param_name);
        //string localName = stk.getName(*param_name);
        //code_stmt.append("\t" + localName + "=" + tmpName + "\n");
    } else {
        string tmpName = stk.getTmpName();
        code_vec.append("i32 " + tmpName);
        int param_num = 0;
        //处理空数组
        if ((*ArrayIndexList).vec.size() > 0) {
            for (auto &index : (*ArrayIndexList).vec) {
                auto index_exp = dynamic_cast<AST_ConstExp *>(index.get());
                string val = (index_exp->get_value());
                if (param_num == 0) {
                    if (ArrayIndexList->is_zero) {
                        code_vec.append("[0]");
                        code_vec.append("[" + val + "]");
                        param_num++;
                    } else {
                        code_vec.append("[0]");
                        param_num++;
                    }
                } else {
                    code_vec.append("[" + val + "]");
                    param_num++;
                }
            }
        } else {
            code_vec.append("[0]");
        }

    }
    return "";
}

string AST_Block::done(bool option)
{
    stk.push();
    for (auto &item : list_block->vec)
        item->done();
    stk.pop();
    return "";
}

string AST_BlockItem::done(bool option)
{
    if (is_stmt) {
        auto elem_ = dynamic_cast<AST_Stmt *>(elem.get());
        elem_->done();
    } else {
        auto elem_ = dynamic_cast<AST_VarDecl *>(elem.get());
        elem_->done();
    }
    return "";
}

string AST_Stmt::done(bool option)
{
    if (tag == RETURN) {
        if (exp) {
            string ret_name = exp->done();
            //return ret_name;
            code_stmt.code_assign("%l0", ret_name);
            //code_stmt.append("\t%l0 = " + ret_name + "\n");
            if (stk.nm.cnt_label > 2) {
                code_stmt.code_br(".L1");
            }
        } else {
            code_stmt.code_br(".L1");
        }
    } else if (tag == ASSIGN) {

        string val = exp->done();
        string to = lval->done(true);
        string flag = "*";
        //同指针，换右值
        if ((val.find(flag) != string::npos) && (to.find(flag) != string::npos)) {
            string tmp = stk.getTmpName();
            code_tmpval.code_valDecl(tmp, "i32");
            code_stmt.code_assign(tmp, val);
            //code_stmt.append("\t" + tmp + "=" + val + "\n");
            code_stmt.code_assign(to, tmp);
            //code_stmt.append("\t" + to + "=" + tmp + "\n");
        } else
            code_stmt.code_assign(to, val);
        //code_stmt.append("\t" + to + "=" + val + "\n");
    } else if (tag == BLOCK) {
        auto block_ = dynamic_cast<AST_Block *>(block.get());
        //修改了
        for (auto &item : block_->list_block->vec) {
            auto blockitem = dynamic_cast<AST_BlockItem *>(item.get());
            //if(blockitem->is_stmt)
            blockitem->elem->done();
        }
    } else if (tag == EXP) {
        if (exp) {
            exp->done();
        }
    } else if (tag == WHILE) {
        stk.push();
        flag = 0;
        string while_entry = stk.getLabelName();
        string while_body = stk.getLabelName();
        string while_end = stk.getLabelName();

        forst.append(while_entry, while_end);

        code_stmt.code_br(while_entry);

        code_stmt.code_label(while_entry);
        //string cond_ = cond->done();
        //code_stmt.code_bc(cond_, while_body, while_end);
        stk.insert_Label();
        string s = cond->done();
        //注意!!!
        if (flag == 0) {
            string tmp_s;
            if (s.find("*") != string::npos) {
                tmp_s = stk.getTmpName();
                code_tmpval.code_valDecl(tmp_s, "i32");
                code_stmt.code_assign(tmp_s, s);
                //code_stmt.append("\t" + tmp_s + "=" + s + "\n");
            } else tmp_s = s;
            code_stmt.code_bc(tmp_s, while_body, while_end);
        }

        for (auto index : stk.lab_t.back()->f_line) {
            if (while_end.size() > 3)
                code_stmt.code.replace(index, 4, while_end);
            else
                code_stmt.code.replace(index, 3, while_end);
        }
        for (auto index : stk.lab_t.back()->t_line) {
            if (while_body.size() > 3)
                code_stmt.code.replace(index, 4, while_body);
            else
                code_stmt.code.replace(index, 3, while_body);
        }

        code_stmt.code_label(while_body);
        body->done();
        code_stmt.code_br(while_entry);

        code_stmt.code_label(while_end);
        forst.quit(); // 该while处理已结束，退栈
        flag = 0;
        stk.pop();
    } else if (tag == BREAK) {
        code_stmt.code_br(forst.getBreakName());  // 跳转到while_end
    } else if (tag == CONTINUE) {
        code_stmt.code_br(forst.getContinueName());// 跳转到while_entry
    } else if (tag == IF) {
        stk.push();
        flag = 0;
        string t = stk.getLabelName();
        string e = stk.getLabelName();
        string j = stk.getLabelName();

        //短路回填,顺序还没撸出来
        stk.insert_Label();
        string s = cond->done();
        if (flag == 0) {
            string tmp_s;
            if (s.find("*") != string::npos) {
                tmp_s = stk.getTmpName();
                code_tmpval.code_valDecl(tmp_s, "i32");
                code_stmt.code_assign(tmp_s, s);
                //code_stmt.append("\t" + tmp_s + "=" + s + "\n");
            } else tmp_s = s;
            code_stmt.code_bc(tmp_s, t, else_body == nullptr ? j : e);
        }

        if (else_body != nullptr) {
            for (auto index : stk.lab_t.back()->f_line) {
                if (e.size() > 3)
                    code_stmt.code.replace(index, 4, e);
                else
                    code_stmt.code.replace(index, 3, e);
            }
        } else {
            for (auto index : stk.lab_t.back()->f_line) {
                if (j.size() > 3)
                    code_stmt.code.replace(index, 4, j);
                else
                    code_stmt.code.replace(index, 3, j);
            }
        }
        for (auto index : stk.lab_t.back()->t_line) {
            if (t.size() > 3)
                code_stmt.code.replace(index, 4, t);
            else
                code_stmt.code.replace(index, 3, t);
        }

        // IF Stmt
        code_stmt.code_label(t);
        body->done();
        code_stmt.code_br(j);

        // else stmt
        if (else_body != nullptr) {
            code_stmt.code_label(e);
            else_body->done();
            code_stmt.code_br(j);

        }
        // end
        code_stmt.code_label(j);
        flag = 0;
        stk.pop();
    } else if (tag == FOR) {
        stk.push();
        flag = 0;
        string s = stk.getLabelName();
        string b = stk.getLabelName();
        string c = stk.getLabelName();
        string e = stk.getLabelName();
        exp->done();
        //wst.append(while_entry, while_body, while_end);
        forst.append(s, e);
        //入口
        code_stmt.code_br(s);

        code_stmt.code_label(s);
        stk.insert_Label();
        string cond_ = cond->done();

        if (flag == 0) {
            string tmp_cond;
            if (cond_.find("*") != string::npos) {
                tmp_cond = stk.getTmpName();
                code_tmpval.code_valDecl(tmp_cond, "i32");
                code_stmt.code_assign(tmp_cond, cond_);
                //code_stmt.append("\t" + tmp_cond + "=" + cond_ + "\n");
            } else tmp_cond = cond_;
            code_stmt.code_bc(tmp_cond, b, e);
        }

        for (auto index : stk.lab_t.back()->t_line) {
            code_stmt.code.replace(index, 3, b);
        }
        for (auto index : stk.lab_t.back()->f_line) {
            code_stmt.code.replace(index, 3, e);
        }
        code_stmt.code_label(b);
        body->done();
        code_stmt.code_br(s);

        code_stmt.code_label(c);
        exp2->done();
        code_stmt.code_br(b);
        code_stmt.code_label(e);
        forst.quit(); // 该while处理已结束，退栈
        flag = 0;
        stk.pop();
    }
    return"";
}

string AST_LVal::done(bool option)
{
    if (tag == VARIABLE) {
        // Hint: a single a ident be a array address
        MinicType *ty = stk.getType(*ident);
        if (ty->type == MinicType::INT) {
            if (option == false) {
                string tmp = stk.getTmpName();
                code_tmpval.code_valDecl(tmp, "i32");
                code_stmt.code_assign(tmp, stk.getName(*ident));
                //code_stmt.append("\t" + tmp + "=" + stk.getName(*ident) + "\n");
                return tmp;
            } else {
                return stk.getName(*ident);
            }
        } else {
            FuncTab functab = fts.findFunc(fts.current_func);
            string paramType = functab.func_Params[fts.cnt].param_ArrayType;
            // func(ident) 参数的类型不一定，可能是i32 i8 i1
            if (ty->value == -1) {
                string tmp = stk.getTmpName();
                code_tmpval.code_arrayDecl(tmp, paramType, " ;*ident");
                code_stmt.code_assign(tmp, stk.getName(*ident));
                //code_stmt.append(tmp + "=" + stk.getName(*ident) + "\n");
                return tmp;
            }
            string tmp = stk.getTmpName();
            code_tmpval.code_arrayDecl(tmp, paramType, " ;*ident");
            code_stmt.code_assign(tmp, stk.getName(*ident));
            //code_stmt.append("\t" + tmp + "=" + stk.getName(*ident) + "\n");
            return tmp;
        }
    } else {
        vector<string> index;
        vector<int> len;

        for (auto &e : exps->vec) {
            string tmp_ = e->done();
            if (tmp_.find("*") != string::npos) {
                string tmp = stk.getTmpName();
                code_tmpval.code_valDecl(tmp, "i32");
                code_stmt.code_assign(tmp, tmp_);
                //code_stmt.append("\t" + tmp + "=" + tmp_ + "\n");
                tmp_ = tmp;
            }
            index.push_back(tmp_);
        }

        MinicType *type = stk.getType(*ident);
        type->getArrayType(len);

        //找到数组对应的局部变量
        string tmp_val = stk.getName(*ident);
        //找到数组的维度
        string tmp_type = stk.getArrayType(len);
        //code_tmpval.code_arrayDecl(tmp_val, tmp_type, " ;" + *ident);
        //string first_indexed = stk.getTmpName();
        //code_stmt.append(tmp_val + "=" + name);
        //这是两个用来计算数组地址的乘加临时变量
        string tmp_name, tmp_name1;
        //cout << tmp_type << endl;
        tmp_name1 = index[0];
        if (index.size() == 0) {
            return tmp_val;
        }

        for (int i = 0; i < index.size() - 1; i++) {
            tmp_name = stk.getTmpName();
            cout << tmp_name << endl;
            code_tmpval.code_valDecl(tmp_name, "i32");

            code_stmt.code_binary("mul", tmp_name, tmp_name1, to_string(len[i + 1]));
            tmp_name1 = stk.getTmpName();
            code_tmpval.code_valDecl(tmp_name1, "i32");
            code_stmt.code_binary("add", tmp_name1, tmp_name, index[i + 1]);
        }

        tmp_name = stk.getTmpName();
        code_tmpval.code_valDecl(tmp_name, "i32");
        code_stmt.code_binary("mul", tmp_name, tmp_name1, "4");
        //装着数组元素的地址
        string location = stk.getTmpName();
        code_tmpval.code_valDecl(location, "i32*");
        code_stmt.code_binary("add", location, tmp_val, tmp_name);
        //统一处理
        /*if (index.size() < len.size())
            return location;
        else*/
        return "*" + location;
    }
}

int AST_LVal::getValue()
{
    return stk.getValue(*ident);
}

string AST_Decl::done(bool option)
{
    auto decl_ = dynamic_cast<AST_VarDecl *>(decl.get());
    if (option)
        decl_->done(true);
    else
        decl_->done(false);
    return "";
}

string AST_VarDecl::done(bool option)
{
    for (auto &def : list_vardecl->vec) {
        if (option)
            def->done(true);
        else
            def->done(false);
    }
    return "";
}

//增加了对数组的处理
string AST_VarDef::done(bool option)
{
    if (tag == AST_VarDef::VARIABLE) {
        if (option) {
            stk.insertGlobalINT(*ident);
            string name = stk.getName(*ident);
            code_vec.code_globalInt(name, "i32", ";" + *ident);
        }

        else {
            stk.insertLocalINT(*ident);
            string name = stk.getName(*ident);
            code_localval.code_valDecl(name, "i32", ";" + *ident);
            //code_stmt.code_valDecl(name, "i32");
        }
    } else {
        vector<int> len;
        for (auto &ce : arrayIndexList->vec) {
            auto ce_ = dynamic_cast<AST_Exp *>(ce.get());
            //cout << ce_->getValue() << endl;
            len.push_back(ce_->getValue());
        }
        if (option) {
            stk.insertGlobalArray(*ident, len, MinicType::ARRAY);

            string name = stk.getName(*ident);
            string array_type = stk.getArrayType(len);

            int tot_len = 1;
            for (auto i : len) tot_len *= i;
            string *init = new string[tot_len];
            for (int i = 0; i < tot_len; ++i)
                init[i] = "0";

            code_vec.code_globalArray(name, array_type, " ;" + *ident);
        } else {
            stk.insertLocalArray(*ident, len, MinicType::ARRAY);

            string name = stk.getName(*ident);
            string array_type = stk.getArrayType(len);

            int tot_len = 1;
            for (auto i : len) tot_len *= i;
            string *init = new string[tot_len];
            for (int i = 0; i < tot_len; ++i)
                init[i] = "0";

            code_localval.code_arrayDecl(name, array_type, " ;" + *ident);
        }
    }

    //注意，定义 没有初值
    return "";
}

string AST_Exp1::done(bool option)
{
    return xxx->done();
}

int AST_Exp1::getValue()
{
    return xxx->getValue();
}

string AST_Cond::done(bool option)
{
    return lor->done();
}

int AST_Cond::getValue()
{
    return lor->getValue();
}

string AST_Primary::done(bool option)
{
    switch (tag) {
    case EXP:
        return exp->done();
    case NUM:
        return to_string(int_val);
    case LVAL:
        return lval->done();
    }
    return "";
}

int AST_Primary::getValue()
{
    switch (tag) {
    case EXP:
        return exp->getValue();
    case NUM:
        return int_val;
    case LVAL:
        return lval->getValue();
    }
    return -1;  // make g++ happy
}

string AST_Unary::done(bool option)
{
    if (tag == ONLY_P) {
        auto primaryExp_ = dynamic_cast<AST_Primary *>(primaryExp.get());
        return primaryExp_->done();
    } else if (tag == UU) {
        string b = unaryExp->done();
        if (op == AST_OP_OPT) return b;
        //分类讨论了，取负和取非，没有取非运算，所以用比较来代替!!!
        if (op == AST_OP_NEG) {
            string op_ = "neg";
            string c = stk.getTmpName();
            code_tmpval.code_valDecl(c, "i32");
            //code_stmt.code_binary(op_, c, "", b);
            code_stmt.code_single(op_, c, b);
            return c;
        } else {
            string c = stk.getTmpName();
            code_tmpval.code_valDecl(c, "i1");
            if (b.find("*") != string::npos) {
                string tmp = stk.getTmpName();
                code_tmpval.code_valDecl(tmp, "i32");
                code_stmt.code_assign(tmp, b);
                //code_stmt.append("\t" + tmp + "=" + b + "\n");
                code_stmt.code_cmp(c, "eq", tmp, "0");
            } else
                code_stmt.code_cmp(c, "eq", b, "0");
            return c;
        }

    } else {
        /*// Func_Call
        string name = stk.getName(ident);
        string tmp = "";
        vector<string> par;
        if (st.getType(ident)->ty == SysYType::SYSY_FUNC_INT) {
            tmp = st.getTmpName();
        }
        if (func_params) {
            int n = func_params->exps.size();
            for (int i = 0; i < n; ++i) {
                par.push_back(func_params->exps[i]->Dump());
            }
        }
        ks.call(tmp, st.getName(ident), par);
        return tmp;*/
        string b = selfExp->done();
        if (op == AST_OP_LINC) {
            string c = stk.getTmpName();
            code_tmpval.code_valDecl(c, "i32");
            string op_ = "LINC";
            code_stmt.code_binary(op_, c, "0", b);
            auto self = dynamic_cast<AST_LVal *>(selfExp.get());
            string val_id = stk.getName((*self->ident));
            code_stmt.code_assign(val_id, c);
            //code_stmt.append("\t" + val_id + "=" + c + "\n");
            return c;
        } else if (op == AST_OP_RINC) {
            string c = stk.getTmpName();
            code_tmpval.code_valDecl(c, "i32");
            string op_ = "RINC";
            code_stmt.code_binary(op_, c, "0", b);
            auto self = dynamic_cast<AST_LVal *>(selfExp.get());
            string val_id = stk.getName((*self->ident));
            code_stmt.code_assign(val_id, c);
            //code_stmt.append("\t" + val_id + "=" + c + "\n");
            return b;
        } else if (op == AST_OP_LDEC) {
            string c = stk.getTmpName();
            code_tmpval.code_valDecl(c, "i32");
            string op_ = "LDEC";
            code_stmt.code_binary(op_, c, "0", b);
            auto self = dynamic_cast<AST_LVal *>(selfExp.get());
            string val_id = stk.getName((*self->ident));
            code_stmt.code_assign(val_id, c);
            //code_stmt.append("\t" + val_id + "=" + c + "\n");
            return c;
        } else {
            string c = stk.getTmpName();
            code_tmpval.code_valDecl(c, "i32");
            string op_ = "RDEC";
            code_stmt.code_binary(op_, c, "0", b);
            auto self = dynamic_cast<AST_LVal *>(selfExp.get());
            string val_id = stk.getName((*self->ident));
            code_stmt.code_assign(val_id, c);
            //code_stmt.append("\t" + val_id + "=" + c + "\n");
            return b;
        }
        return "";
    }
}

int AST_Unary::getValue()
{
    if (tag == ONLY_P) return primaryExp->getValue();
    if (tag == UU) {
        int v = unaryExp->getValue();
        if (op == AST_OP_OPT) return v;
        return op == AST_OP_NEG ? -v : !v;
    }
    if (tag == SELF) {
        int v = selfExp->getValue();
        if (op == AST_OP_LINC) return v++;
        if (op == AST_OP_LDEC) return v--;
        return v;
    }
}

string AST_MulExp::done(bool option)
{
    if (mulExp == NULL) return unaryExp->done();
    string a, b, c;

    a = mulExp->done();
    b = unaryExp->done();

    string op_ = op == AST_OP_MUL ? "mul" : (op == AST_OP_DIV ? "div" : "mod");

    c = stk.getTmpName();
    string tmp_a, tmp_b;
    if (a.find("*") != string::npos) {
        tmp_a = stk.getTmpName();
        code_tmpval.code_valDecl(tmp_a, "i32");
        code_stmt.code_assign(tmp_a, a);
        //code_stmt.append("\t" + tmp_a + "=" + a + "\n");
    } else tmp_a = a;
    if (b.find("*") != string::npos) {
        tmp_b = stk.getTmpName();
        code_tmpval.code_valDecl(tmp_b, "i32");
        code_stmt.code_assign(tmp_b, b);
        //code_stmt.append("\t" + tmp_b + "=" + b + "\n");
    } else tmp_b = b;
    code_tmpval.code_valDecl(c, "i32");
    code_stmt.code_binary(op_, c, tmp_a, tmp_b);
    return c;
}

int AST_MulExp::getValue()
{
    if (mulExp == NULL) return unaryExp->getValue();

    int a = mulExp->getValue(), b = unaryExp->getValue();

    return op == AST_OP_MUL ? a * b : (op == AST_OP_DIV ? a / b : a % b);
}

string AST_AddExp::done(bool option)
{
    if (addExp == NULL) return mulExp->done();
    string a, b, c;

    a = addExp->done();
    b = mulExp->done();
    string flag = "*";
    string op_ = op == AST_OP_ADD ? "add" : "sub";

    c = stk.getTmpName();
    code_tmpval.code_valDecl(c, "i32");

    string tmp_a, tmp_b;
    if ((a.find(flag) != string::npos)) {
        tmp_a = stk.getTmpName();
        code_tmpval.code_valDecl(tmp_a, "i32");
        code_stmt.code_assign(tmp_a, a);
        //code_stmt.append("\t" + tmp_a + "=" + a + "\n");
    } else {
        tmp_a = a;
    }
    if ((b.find(flag) != string::npos)) {
        tmp_b = stk.getTmpName();
        code_tmpval.code_valDecl(tmp_b, "i32");
        code_stmt.code_assign(tmp_b, b);
        //code_stmt.append("\t" + tmp_b + "=" + b + "\n");
    } else {
        tmp_b = b;
    }
    code_stmt.code_binary(op_, c, tmp_a, tmp_b);

    return c;
}

int AST_AddExp::getValue()
{
    if (addExp == NULL) return mulExp->getValue();

    int a = addExp->getValue(), b = mulExp->getValue();
    return op == AST_OP_ADD ? a + b : a - b;
}

string AST_RelExp::done(bool option)
{
    if (relExp == NULL) return addExp->done();
    string a = relExp->done(), b = addExp->done();
    string op_;
    switch (op) {
    case AST_OP_LT:
        op_ = "lt";
        break;
    case AST_OP_GT:
        op_ = "gt";
        break;
    case AST_OP_LE:
        op_ = "le";
        break;
    case AST_OP_GE:
        op_ = "ge";
        break;
    }
    string dest = stk.getTmpName();
    code_tmpval.code_valDecl(dest, "i1");
    string tmp_a, tmp_b;
    if (a.find("*") != string::npos) {
        tmp_a = stk.getTmpName();
        code_tmpval.code_valDecl(tmp_a, "i32");
        code_stmt.code_assign(tmp_a, a);
        //code_stmt.append("\t" + tmp_a + "=" + a + "\n");
    } else tmp_a = a;
    if (b.find("*") != string::npos) {
        tmp_b = stk.getTmpName();
        code_tmpval.code_valDecl(tmp_b, "i32");
        code_stmt.code_assign(tmp_b, b);
        //code_stmt.append("\t" + tmp_b + "=" + b + "\n");
    } else tmp_b = b;
    code_stmt.code_cmp(dest, op_, tmp_a, tmp_b);
    return dest;
}

int AST_RelExp::getValue()
{
    if (relExp == NULL) return addExp->getValue();

    int a = relExp->getValue(), b = addExp->getValue();
    switch (op) {
    case AST_OP_LT:
        return a < b;
    case AST_OP_GT:
        return a > b;
    case AST_OP_LE:
        return a <= b;
    case AST_OP_GE:
        return a >= b;
    }
}

string AST_EqExp::done(bool option)
{
    if (eqExp == NULL) return relExp->done();
    string a = eqExp->done(), b = relExp->done();
    string op_ = op == AST_OP_EQ ? "eq" : "ne";
    string dest = stk.getTmpName();
    code_tmpval.code_valDecl(dest, "i1");
    string tmp_a, tmp_b;
    if (a.find("*") != string::npos) {
        tmp_a = stk.getTmpName();
        code_tmpval.code_valDecl(tmp_a, "i32");
        code_stmt.code_assign(tmp_a, a);
        //code_stmt.append("\t" + tmp_a + "=" + a + "\n");
    } else tmp_a = a;
    if (b.find("*") != string::npos) {
        tmp_b = stk.getTmpName();
        code_tmpval.code_valDecl(tmp_b, "i32");
        code_stmt.code_assign(tmp_b, b);
        //code_stmt.append("\t" + tmp_b + "=" + b + "\n");
    } else tmp_b = b;
    code_stmt.code_cmp(dest, op_, tmp_a, tmp_b);
    //code_stmt.code_binary(op_, dest, a, b);
    return dest;
}

int AST_EqExp::getValue()
{
    if (eqExp == NULL) return relExp->getValue();
    int a = eqExp->getValue(), b = relExp->getValue();
    return op == AST_OP_EQ ? (a == b) : (a != b);
}

string AST_LAnd::done(bool option)
{
    if (only_eq == true) return eqExp->done();

    // 修改支持短路逻辑
    /*string result = stk.getVarName("SCRES");
    code_vec.alloc(result);
    stk.store("0", result);*/

    //标志
    flag++;

    string lhs = eqExp->done();
    string s_1 = stk.getLabelName();
    //string true_s = stk.getLabelName();
    //string false_s = stk.getLabelName();
    string true_s = ".LT";
    string false_s = ".LF";

    //处理为指针的情况
    string tmp_lhs;
    if (lhs.find("*") != string::npos) {
        tmp_lhs = stk.getTmpName();
        code_tmpval.code_valDecl(tmp_lhs, "i32");
        code_stmt.code_assign(tmp_lhs, lhs);
        //code_stmt.append("\t" + tmp_lhs + "=" + lhs + "\n");
    } else tmp_lhs = lhs;
    code_stmt.code_bc(tmp_lhs, s_1, false_s);

    //获取false_s中F的位置
    stk.insert_F(code_stmt.code.size() - 5);
    code_stmt.code_label(s_1);

    string rhs = landExp->done(true);
    if (option) {
        return rhs;
    }
    //string tmp = stk.getTmpName();
    //处理为指针的情况
    string tmp_rhs;
    if (rhs.find("*") != string::npos) {
        tmp_rhs = stk.getTmpName();
        code_tmpval.code_valDecl(tmp_rhs, "i32");
        code_stmt.code_assign(tmp_rhs, rhs);
        //code_stmt.append("\t" + tmp_rhs + "=" + rhs + "\n");
    } else tmp_rhs = rhs;
    code_stmt.code_bc(tmp_rhs, true_s, false_s);
    //获取true_s中T的位置 false_s中F的位置
    stk.insert_F(code_stmt.code.size() - 5);
    stk.insert_T(code_stmt.code.size() - 15);

    //stk.store(tmp, result);
    //stk.jump(end_s);

    /*code_stmt.code_label(true_s);
    string ret = stk.getTmpName();
    code_tmpval.code_valDecl(ret, "i1");
    code_stmt.append("\t" + ret + "=1" + "\n");
    code_stmt.code_label(false_s);
    code_stmt.append("\t" + ret + "=0" + "\n");*/
    return rhs;
}

int AST_LAnd::getValue()
{
    if (only_eq == true) return eqExp->getValue();
    int a = landExp->getValue(), b = eqExp->getValue();
    return a && b;  // 注意是逻辑与
}

string AST_LOr::done(bool option)
{
    //只有cond过来的exp需要直接输出
    if (only_land == true) return landExp->done();

    // 修改支持短路逻辑
    /*string result = stk.getVarName("SCRES");
    code_vec.alloc(result);
    stk.store("0", result);*/
    //标志
    flag++;

    string lhs = landExp->done(true);
    string s_1 = stk.getLabelName();
    //string true_s = stk.getLabelName();
    //string false_s = stk.getLabelName();
    string true_s = ".LT";
    string false_s = ".LF";

    //处理为指针的情况
    string tmp_lhs;
    if (lhs.find("*") != string::npos) {
        tmp_lhs = stk.getTmpName();
        code_tmpval.code_valDecl(tmp_lhs, "i32");
        code_stmt.code_assign(tmp_lhs, lhs);
        //code_stmt.append("\t" + tmp_lhs + "=" + lhs + "\n");
    } else tmp_lhs = lhs;
    code_stmt.code_bc(tmp_lhs, true_s, s_1);
    //获取true_s中T的位置
    if (s_1.size() > 3)
        stk.insert_T(code_stmt.code.size() - 16);
    else
        stk.insert_T(code_stmt.code.size() - 15);
    code_stmt.code_label(s_1);

    string rhs = lorExp->done();
    //string tmp = stk.getTmpName();
    //处理为指针的情况
    string tmp_rhs;
    if (rhs.find("*") != string::npos) {
        tmp_rhs = stk.getTmpName();
        code_tmpval.code_valDecl(tmp_rhs, "i32");
        code_stmt.code_assign(tmp_rhs, rhs);
        //code_stmt.append("\t" + tmp_rhs + "=" + rhs + "\n");
    } else tmp_rhs = rhs;
    code_stmt.code_bc(tmp_rhs, true_s, false_s);
    //获取true_s中T的位置 false_s中F的位置

    stk.insert_T(code_stmt.code.size() - 15);
    stk.insert_F(code_stmt.code.size() - 5);

    //stk.store(tmp, result);
    //stk.jump(end_s);

    /*code_stmt.code_label(true_s);
    string ret = stk.getTmpName();
    code_tmpval.code_valDecl(ret, "i1");
    code_stmt.append("\t" + ret + "=1" + "\n");
    code_stmt.code_label(false_s);
    code_stmt.append("\t" + ret + "=0" + "\n");*/
    return rhs;
}

int AST_LOr::getValue()
{
    if (only_land == true) return landExp->getValue();
    int a = lorExp->getValue(), b = landExp->getValue();
    return a || b;
}

string AST_ConstExp::done(bool option)
{
    return exp->done();
}

int AST_ConstExp::getValue()
{
    return exp->getValue();
}

string AST_Initial::done(bool option)
{
    //处理数组另加
    return exp->done();
}

int AST_Initial::getValue()
{
    return exp->getValue();
}

/*string AST_FuncCall::done(bool option)
{
    fts.current_func = *id_val;
    vector<string> args;
    fts.cnt = 0;
    //如果参数是i32但是返回值为*i32，需要赋给临时变量
    if (is_param) {
        int param_cnt = 0;
        FuncTab functab = fts.findFunc(*id_val);
        string param_type;
        string tmp_result;
        for (auto &rparam : params->vec) {
            param_type = functab.func_Params[param_cnt].param_Type;
            string result = rparam->done();
            if (param_type == "i32") {
                if (result.find("*") != string::npos) {
                    tmp_result = stk.getTmpName();
                    code_tmpval.code_valDecl(tmp_result, "i32");
                    code_stmt.append("\t" + tmp_result + "=" + result + "\n");
                } else tmp_result = result;
            } else tmp_result = result;
            args.push_back(tmp_result);
            fts.cnt++;
        }
    }

    string func_name = stk.getName(*id_val);
    MinicType *func_type = stk.getType(*id_val);
    string type, return_val;
    if (func_type->type == MinicType::FUNC_INT) {
        type = "i32";
        return_val = stk.getTmpName();
        code_tmpval.code_valDecl(return_val, "i32");
        code_stmt.append("\t" + return_val + "=call " + type + " " + func_name + "(");
    } else {
        type = "void";
        code_stmt.append("\tcall " + type + " " + func_name + "(");
    }
    if (is_param) {
        int param_cnt = 0;
        FuncTab functab = fts.findFunc(*id_val);
        if (functab.is_none == true) {
            string param_type;
            for (auto &param : params->vec) {
                //param_type = functab.func_Params[param_cnt].param_Type;
                auto param_ast = dynamic_cast<AST_Exp1 *>(param.get());
                if (param_cnt > 0) {
                    code_stmt.append(", ");
                }
                //这个地方的变量类型可调！！！
                string tmp = args[param_cnt];
                code_stmt.append("i32 " + tmp);
                param_cnt++;
            }
        } else {
            string param_type;
            for (auto &param : params->vec) {
                param_type = functab.func_Params[param_cnt].param_Type;
                auto param_ast = dynamic_cast<AST_Exp1 *>(param.get());
                if (param_cnt > 0) {
                    code_stmt.append(", ");
                }
                //这个地方的变量类型可调！！！
                string tmp = args[param_cnt];
                if (param_type == "i32")
                    code_stmt.append("i32 " + tmp);
                else
                    code_stmt.append("i32 " + tmp + functab.func_Params[param_cnt].param_ArrayType);
                param_cnt++;
            }
        }


    }
    code_stmt.append(");\n");
    if (func_type->type == MinicType::FUNC_INT) {
        return return_val;
    } else
        return "";
}*/

string AST_FuncCall::done(bool option)
{
    fts.current_func = *id_val;
    vector<string> args;
    fts.cnt = 0;
    //如果参数是i32但是返回值为*i32，需要赋给临时变量
    if (is_param) {
        int param_cnt = 0;
        FuncTab functab = fts.findFunc(*id_val);
        string param_type;
        string tmp_result;
        for (auto &rparam : params->vec) {
            param_type = functab.func_Params[param_cnt].param_Type;
            string result = rparam->done();

            if (param_type == "i32") {
                if (result.find("*") != string::npos) {
                    tmp_result = stk.getTmpName();
                    code_tmpval.code_valDecl(tmp_result, "i32");
                    code_stmt.code_assign(tmp_result, result);
                    //code_stmt.append("\t" + tmp_result + "=" + result + "\n");
                } else tmp_result = result;
            } else tmp_result = result;

            param_type = functab.func_Params[param_cnt].param_Type;
            auto param_ast = dynamic_cast<AST_Exp1 *>(rparam.get());
            //这个地方的变量类型可调！！！
            //string tmp = args[param_cnt];
            if (param_type == "i32")
                args.push_back("i32 " + tmp_result);
            //code_stmt.append("i32 " + tmp);
            else
                args.push_back("i32 " + tmp_result + functab.func_Params[param_cnt].param_ArrayType);
            //code_stmt.append("i32 " + tmp + functab.func_Params[param_cnt].param_ArrayType);
            param_cnt++;
            fts.cnt++;
        }
    }
    string func_name = stk.getName(*id_val);
    MinicType *func_type = stk.getType(*id_val);
    string type, return_val;
    if (func_type->type == MinicType::FUNC_INT) {
        //type = "i32";
        return_val = stk.getTmpName();
        code_tmpval.code_valDecl(return_val, "i32");
        //code_stmt.append("\t" + return_val + "=call " + type + " " + func_name + "(");
        code_stmt.code_call(return_val, func_name, args);
    } else {
        //type = "void";
        //code_stmt.append("\tcall " + type + " " + func_name + "(");
        code_stmt.code_call("", func_name, args);
    }

    if (func_type->type == MinicType::FUNC_INT) {
        return return_val;
    } else
        return "";
}
int AST_FuncCall::getValue()
{
    return -1;
}

int AST_Stmt::getValue()
{
    return -1;
}