#include "ast_minic.h"
#include "symbol.h"
#include "utils.h"

IRCode code_vec;
IRCode code_val;
IRCode code_stmt;
SymTabStk stk;
MinicType::TYPE tmp;
BlockController bc;
WhileStack wst;

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

    stk.insertFunc(string("getint"), MinicType::FUNC_INT);
    stk.insertFunc(string("getch"), MinicType::FUNC_INT);
    stk.insertFunc(string("getarray"), MinicType::FUNC_INT);
    stk.insertFunc(string("putint"), MinicType::FUNC_VOID);
    stk.insertFunc(string("putch"), MinicType::FUNC_VOID);
    stk.insertFunc(string("putarray"), MinicType::FUNC_VOID);
    stk.insertFunc(string("putch"), MinicType::FUNC_VOID);

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
    stk.reset();
    if (*func_type == "int")
        tmp = MinicType::FUNC_INT;
    else
        tmp = MinicType::FUNC_VOID;
    stk.insertFunc(*func_name, tmp); //函数表
    code_vec.append("declare " + *func_type + "@" + *func_name + "(");
    //压入一个符号表，新的作用域
    stk.push();
    if (tag == AST_FuncDef::DECL_PARAM || tag == AST_FuncDef::DEF_PARAM) {
        int param_num = 0;
        for (auto &param : func_params->vec) {
            if (param_num != 0)
                code_vec.append(",");
            param->done();
            param_num++;
        }
    }
    code_vec.append(")");
    code_vec.append("\tentry");
    string return_Val, return_Label;
    if (*func_type == "int") {
        stk.insertLocalINT("return");
        return_Val = stk.getName("return");
        return_Label = stk.getLabelName();
    } else {
        return_Label = stk.getLabelName();
    }

    if (tag == AST_FuncDef::DECL_NOPARAM || tag == AST_FuncDef::DECL_PARAM)
        code_vec.append(";");
    else {
        code_vec.append(" {\n");
        auto ast_block = dynamic_cast<AST_Block *>(func_block.get());
        ast_block->func_params = func_params.get();
        ast_block->done();
        code_vec.code_label(return_Label);
        if (*func_type == "int")
            code_vec.append("\texit " + return_Val + "\n");
        else
            code_vec.append("\texit\n");
        code_vec.append("}\n\n");
    }
    return "";
}

string AST_FuncFParam::done(bool option)
{
    if (tag == AST_FuncFParam::VARIABLE)
        code_vec.append(*param_type + *param_name);
    else {
        code_vec.append(*param_type + *param_name);
        int param_num = 0;
        for (auto &index : (*ArrayIndexList).vec) {
            auto index_exp = dynamic_cast<AST_ConstExp *>(index.get());
            string val = (index_exp->get_value());
            if (param_num == 0)
                code_vec.append("[0]");
            else {
                code_vec.append("[" + val + "]");
                param_num++;
            }
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
    //if (!bc.alive()) return;
    if (tag == RETURN) {
        // bc.finish()写在这里不对！
        if (exp) {
            string ret_name = exp->done();
            //return ret_name;
            code_vec.append("\t%l0=" + ret_name + "\n");
            code_vec.code_br(".L1");
        } else {
            code_vec.code_br(".L1");
        }
        //bc.finish();
    } else if (tag == ASSIGN) {
        string val = exp->done();
        string to = lval->done(true);
        code_vec.append("\t" + to + "=" + val + "\n");
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
        string while_entry = stk.getLabelName();
        string while_body = stk.getLabelName();
        string while_end = stk.getLabelName();

        wst.append(while_entry, while_body, while_end);

        code_vec.code_br(while_entry);

        //bc.set();
        code_vec.code_label(while_entry);
        string cond_ = cond->done();
        code_vec.code_bc(cond_, while_body, while_end);

        //bc.set();
        code_vec.code_label(while_body);
        body->done();
        if (bc.alive())
            code_vec.code_br(while_entry);

        bc.set();
        code_vec.code_label(while_end);
        wst.quit(); // 该while处理已结束，退栈
    } else if (tag == BREAK) {
        code_vec.code_br(wst.getEndName());  // 跳转到while_end
        bc.finish();                // 当前IR的block设为不活跃
    } else if (tag == CONTINUE) {
        code_vec.code_br(wst.getEntryName());// 跳转到while_entry
        bc.finish();                // 当前IR的block设为不活跃
    } else if (tag == IF) {
        string s = cond->done();
        string t = stk.getLabelName();
        string e = stk.getLabelName();
        string j = stk.getLabelName();
        code_vec.code_bc(s, t, else_body == nullptr ? j : e);

        // IF Stmt
        bc.set();
        code_vec.code_label(t);
        body->done();
        if (bc.alive())
            code_vec.code_br(j);

        // else stmt
        if (else_body != nullptr) {
            bc.set();
            code_vec.code_label(e);
            else_body->done();
            if (bc.alive())
                code_vec.code_br(j);

        }
        // end
        bc.set();
        code_vec.code_label(j);
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
                code_vec.append("\t" + tmp + "=" + stk.getName(*ident) + "\n");
                return tmp;
            } else {
                return stk.getName(*ident);
            }
        } else {
            // func(ident)
            if (ty->value == -1) {
                string tmp = stk.getTmpName();
                code_vec.append(tmp + "=" + stk.getName(*ident));;
                return tmp;
            }
            string tmp = stk.getTmpName();
            string tmp2 = stk.getName(*ident);
            code_vec.append(tmp + "*" + tmp2);
            return tmp;
        }
    } else {/*
        vector<string> index;
        vector<int> len;

        for (auto &e : exps) {
            index.push_back(e->done());
        }

        MinicType *ty = stk.getType(ident);
        ty->getArrayType(len);

        // hint: len可以是-1开头的，说明这个数组是函数中使用的参数
        // 如 a[-1][3][2],表明a是参数 a[][3][2], 即 *[3][2].
        // 此时第一步不能用getelemptr，而应该getptr

        string name = stk.getName(*ident);
        string tmp;
        if (len.size() != 0 && len[0] == 0) {
            vector<int> sublen(len.begin() + 1, len.end());
            string tmp_val = stk.getTmpName();
            ks.load(tmp_val, name);
            string first_indexed = st.getTmpName();
            ks.getptr(first_indexed, tmp_val, index[0]);
            if (index.size() > 1) {
                tmp = getElemPtr(
                    first_indexed,
                    vector<string>(
                        index.begin() + 1, index.end()
                    )
                );
            } else {
                tmp = first_indexed;
            }

        } else {
            tmp = getElemPtr(name, index);
        }


        if (index.size() < len.size()) {
            // 一定是作为函数参数即实参使用，因为下标不完整
            string real_param = st.getTmpName();
            ks.getelemptr(real_param, tmp, "0");
            return real_param;
        }
        if (dump_ptr) return tmp;
        string tmp2 = st.getTmpName();
        ks.load(tmp2, tmp);
        return tmp2;*/
        return "";
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

string AST_VarDef::done(bool option)
{
    if (tag == AST_VarDef::VARIABLE) {
        if (option) {
            stk.insertGlobalINT(*ident);
            string name = stk.getName(*ident);
            code_vec.code_globalInt(name);
        }

        else {
            stk.insertLocalINT(*ident);
            string name = stk.getName(*ident);
            code_vec.code_valDecl(name);
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

        string op_ = op == AST_OP_NEG ? "neg" : "not";
        string c = stk.getTmpName();
        code_vec.code_binary(op_, c, "0", b);
        return c;
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
            string op_ = "LINC";
            code_vec.code_binary(op_, c, "0", b);
            auto self = dynamic_cast<AST_LVal *>(selfExp.get());
            string val_id = stk.getName((*self->ident));
            code_vec.append("\t" + val_id + "=" + c + "\n");
            return c;
        } else if (op == AST_OP_RINC) {
            string c = stk.getTmpName();
            string op_ = "RINC";
            code_vec.code_binary(op_, c, "0", b);
            auto self = dynamic_cast<AST_LVal *>(selfExp.get());
            string val_id = stk.getName((*self->ident));
            code_vec.append("\t" + val_id + "=" + c + "\n");
            return b;
        } else if (op == AST_OP_LDEC) {
            string c = stk.getTmpName();
            string op_ = "LDEC";
            code_vec.code_binary(op_, c, "0", b);
            auto self = dynamic_cast<AST_LVal *>(selfExp.get());
            string val_id = stk.getName((*self->ident));
            code_vec.append("\t" + val_id + "=" + c + "\n");
            return c;
        } else {
            string c = stk.getTmpName();
            string op_ = "RDEC";
            code_vec.code_binary(op_, c, "0", b);
            auto self = dynamic_cast<AST_LVal *>(selfExp.get());
            string val_id = stk.getName((*self->ident));
            code_vec.append("\t" + val_id + "=" + c + "\n");
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
    code_vec.code_binary(op_, c, a, b);
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

    string op_ = op == AST_OP_ADD ? "add" : "sub";

    c = stk.getTmpName();
    code_vec.code_binary(op_, c, a, b);
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
        op_ = "LT";
        break;
    case AST_OP_GT:
        op_ = "GT";
        break;
    case AST_OP_LE:
        op_ = "LE";
        break;
    case AST_OP_GE:
        op_ = "GE";
        break;
    }
    string dest = stk.getTmpName();
    code_vec.code_cmp(dest, op_, a, b);
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
    code_vec.code_binary(op_, dest, a, b);
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

    string lhs = landExp->done();
    string s_1 = stk.getLabelName();
    string true_s = stk.getLabelName();
    string false_s = stk.getLabelName();

    code_vec.code_bc(lhs, s_1, false_s);
    code_vec.code_label(s_1);

    //sbc.set();
    string rhs = eqExp->done();
    //string tmp = stk.getTmpName();
    code_vec.code_bc(rhs, true_s, false_s);
    //stk.store(tmp, result);
    //stk.jump(end_s);

    //bc.set();
    code_vec.code_label(true_s);
    string ret = stk.getTmpName();
    code_vec.append("\t" + ret + "=1" + "\n");
    code_vec.code_label(false_s);
    code_vec.append("\t" + ret + "=0" + "\n");
    return ret;
}

int AST_LAnd::getValue()
{
    if (only_eq == true) return eqExp->getValue();
    int a = landExp->getValue(), b = eqExp->getValue();
    return a && b;  // 注意是逻辑与
}

string AST_LOr::done(bool option)
{
    if (only_land == true) return landExp->done();

    // 修改支持短路逻辑
    /*string result = stk.getVarName("SCRES");
    code_vec.alloc(result);
    stk.store("0", result);*/

    string lhs = landExp->done();
    string s_1 = stk.getLabelName();
    string true_s = stk.getLabelName();
    string false_s = stk.getLabelName();

    code_vec.code_bc(lhs, true_s, s_1);
    code_vec.code_label(s_1);

    //sbc.set();
    string rhs = lorExp->done();
    //string tmp = stk.getTmpName();
    code_vec.code_bc(rhs, true_s, false_s);
    //stk.store(tmp, result);
    //stk.jump(end_s);

    //bc.set();
    code_vec.code_label(true_s);
    string ret = stk.getTmpName();
    code_vec.append("\t" + ret + "=1" + "\n");
    code_vec.code_label(false_s);
    code_vec.append("\t" + ret + "=0" + "\n");
    return ret;
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

string AST_FuncCall::done(bool option)
{
    if (is_param) {
        for (auto &rparam : params->vec)
            rparam->done();
    }

    string func_name = stk.getName(*id_val);
    MinicType *func_type = stk.getType(func_name);
    string type;
    if (func_type->type == MinicType::FUNC_INT)
        type = "i32";
    else
        type = "";
    code_vec.append("call " + type + " " + func_name + "(");

    if (is_param) {
        int param_cnt = 0;
        for (auto &param : params->vec) {
            auto param_ast = dynamic_cast<AST_Exp1 *>(param.get());
            if (param_cnt++ > 0) {
                cout << ", ";
            }
            code_vec.append(param_ast->done());
        }
    }

    cout << ");" << endl;
}

int AST_FuncCall::getValue()
{
    return -1;
}