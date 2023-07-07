#include "graph_minic.h"
#include "symbol.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 创建GV的上下文
GVC_t *gv = gvContext();

// 创建一个图形
Agraph_t *g = agopen((char *)"ast", Agdirected, nullptr);

// 获取创建图形节点的编号Label
string getNodeLabelName()
{
    static int g_node_num = 0;
    return to_string(g_node_num++);
}

// 获取创建图形边的编号Label
string getEdgeLabelName()
{
    static int g_edge_num = 0;
    return to_string(g_edge_num++);
}

Agnode_t *AST_Exp::gen_graph(bool option)
{

}

Agnode_t *AST_CompUnit::gen_graph(bool option)
{
    // 创建一个图形节点，确保每个节点的编号唯一
    std::string label_name = getNodeLabelName();
    Agnode_t *node = agnode(g, (char *)label_name.c_str(), 1);
    agsafeset(node, (char *)"label", (char *)"CompUnit", (char *)"");
    agsafeset(node, (char *)"shape", (char *)"ellipse", (char *)"");
    Agnode_t *tmp;
    for (auto &decl : this->list_decl) {
        //!!!这里没有const变量，需要可以加,这里还有待修正
        auto ast_decl = dynamic_cast<AST_VarDecl *>(decl.get());
        for (auto &def : ast_decl->list_vardecl->vec) {
            tmp = def->gen_graph();
            // 创建边，每条边不设置名字
            agedge(g, node, tmp, "", 1);
        }
    }
    for (auto &func : this->list_func) {
        //!!!这里没有const变量，需要可以加,这里还有待修正
        auto ast_func = dynamic_cast<AST_FuncDef *>(func.get());
        tmp = ast_func->gen_graph();
        // 创建边，每条边不设置名字
        agedge(g, node, tmp, "", 1);
    }
    return node;
}

Agnode_t *AST_FuncDef::gen_graph(bool option)
{
    string name1 = getNodeLabelName();
    string name2 = getNodeLabelName();
    string name3 = getNodeLabelName();
    Agnode_t *func = agnode(g, (char *)name1.c_str(), 1);
    agsafeset(func, (char *)"label", (char *)func_name->c_str(), (char *)"");
    agsafeset(func, (char *)"shape", (char *)"ellipse", (char *)"");
    Agnode_t *type = agnode(g, (char *)name2.c_str(), 1);
    agsafeset(type, (char *)"label", (char *)func_type->c_str(), (char *)"");
    agsafeset(type, (char *)"shape", (char *)"ellipse", (char *)"");
    agedge(g, func, type, "", 1);
    if (tag == DECL_PARAM || tag == DEF_PARAM) {
        Agnode_t *params = agnode(g, (char *)name3.c_str(), 1);
        for (auto &func_param : func_params->vec) {
            Agnode_t *param = func_param->gen_graph();
            agedge(g, params, param, "", 1);
        }
        agsafeset(params, (char *)"label", (char *)"func_params", (char *)"");
        agedge(g, func, params, "", 1);
    } else {
        Agnode_t *funcParam = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(funcParam, (char *)"label", (char *)"funcParam", (char *)"");
        agedge(g, func, funcParam, "", 1);
    }
    if (tag == DEF_NOPARAM || tag == DEF_PARAM) {
        Agnode_t *block = func_block->gen_graph();
        agsafeset(block, (char *)"label", (char *)"func_block", (char *)"");
        agedge(g, func, block, "", 1);
    }
    return func;
}

Agnode_t *AST_FuncFParam::gen_graph(bool option)
{
    if (tag == VARIABLE) {
        Agnode_t *vardef = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(vardef, (char *)"label", (char *)"paramdecl", (char *)"");
        Agnode_t *int_ = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(int_, (char *)"label", (char *)"int", (char *)"");
        agedge(g, vardef, int_, "", 1);
        Agnode_t *val = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(val, (char *)"label", (char *)param_name->c_str(), (char *)"");
        agedge(g, vardef, val, "", 1);
        return vardef;
    } else {
        Agnode_t *vardef = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(vardef, (char *)"label", (char *)"paramdecl", (char *)"");
        Agnode_t *int_ = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(int_, (char *)"label", (char *)"int", (char *)"");
        agedge(g, vardef, int_, "", 1);

        Agnode_t *val_array = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(val_array, (char *)"label", (char *)(*param_name + "[]").c_str(), (char *)"");
        if (ArrayIndexList->is_zero) {
            Agnode_t *tmp = agnode(g, (char *)getNodeLabelName().c_str(), 1);
            agsafeset(tmp, (char *)"label", (char *)"0", (char *)"");
            agedge(g, val_array, tmp, "", 1);
        }
        for (auto &index : ArrayIndexList->vec) {
            Agnode_t *tmp = index->gen_graph();
            agedge(g, val_array, tmp, "", 1);
        }
        agedge(g, vardef, val_array, "", 1);
        return vardef;
    }
}

Agnode_t *AST_Block::gen_graph(bool option)
{
    Agnode_t *block = agnode(g, (char *)getNodeLabelName().c_str(), 1);
    agsafeset(block, (char *)"label", (char *)"block", (char *)"");
    agsafeset(block, (char *)"shape", (char *)"ellipse", (char *)"");

    Agnode_t *tmp;

    for (auto &item_block : list_block->vec) {
        auto item = dynamic_cast<AST_BlockItem *>(item_block.get());
        if (item->is_stmt) {
            tmp = item->elem->gen_graph();
            agedge(g, block, tmp, "", 1);
        } else {
            auto decl = dynamic_cast<AST_VarDecl *>((item->elem).get());
            for (auto &item_decl : decl->list_vardecl->vec) {
                tmp = item_decl->gen_graph();
                agedge(g, block, tmp, "", 1);
            }
        }
    }
    return block;
}

Agnode_t *AST_BlockItem::gen_graph(bool option)
{
    return elem->gen_graph();
}

Agnode_t *AST_Stmt::gen_graph(bool option)
{
    if (tag == RETURN) {
        Agnode_t *stmt = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(stmt, (char *)"shape", (char *)"ellipse", (char *)"");
        agsafeset(stmt, (char *)"label", (char *)"ret", (char *)"");
        if (exp != nullptr) {
            Agnode_t *ret_exp = exp->gen_graph();
            agedge(g, stmt, ret_exp, "", 1);
        }
        return stmt;
    } else if (tag == ASSIGN) {
        Agnode_t *stmt = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(stmt, (char *)"shape", (char *)"ellipse", (char *)"");
        agsafeset(stmt, (char *)"label", (char *)"=", (char *)"");
        Agnode_t *left = lval->gen_graph();
        Agnode_t *right = exp->gen_graph();
        agedge(g, stmt, left, "", 1);
        agedge(g, stmt, right, "", 1);
        return stmt;
    } else if (tag == BLOCK) {
        Agnode_t *stmt = block->gen_graph();
        return stmt;
    } else if (tag == EXP) {
        Agnode_t *stmt = exp->gen_graph();
        return stmt;
    } else if (tag == WHILE) {
        Agnode_t *stmt = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(stmt, (char *)"shape", (char *)"ellipse", (char *)"");
        agsafeset(stmt, (char *)"label", (char *)"while", (char *)"");
        Agnode_t *while_cond = cond->gen_graph();
        agsafeset(while_cond, (char *)"label", (char *)"while_cond", (char *)"");
        Agnode_t *while_body = body->gen_graph();
        agsafeset(while_body, (char *)"label", (char *)"while_body", (char *)"");
        agedge(g, stmt, while_cond, "", 1);
        agedge(g, stmt, while_body, "", 1);
        return stmt;
    } else if (tag == IF) {
        Agnode_t *stmt = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(stmt, (char *)"shape", (char *)"ellipse", (char *)"");
        agsafeset(stmt, (char *)"label", (char *)"if", (char *)"");
        Agnode_t *if_cond = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(if_cond, (char *)"label", (char *)"if_cond", (char *)"");
        Agnode_t *cond_ = cond->gen_graph();
        agedge(g, if_cond, cond_, "", 1);

        Agnode_t *t_body_ = body->gen_graph();
        Agnode_t *t_body;
        if (strcmp(agnameof(t_body_), "block") == 0) {
            t_body = t_body_;
        } else {
            t_body = agnode(g, (char *)getNodeLabelName().c_str(), 1);
            agsafeset(t_body, (char *)"label", (char *)"then_body", (char *)"");

            agedge(g, t_body, t_body_, "", 1);
        }

        if (else_body != nullptr) {
            Agnode_t *e_body_ = else_body->gen_graph();
            Agnode_t *e_body;
            if (strcmp(agnameof(e_body_), "block") == 0) {
                e_body = e_body_;
            } else {
                e_body = agnode(g, (char *)getNodeLabelName().c_str(), 1);
                agsafeset(e_body, (char *)"label", (char *)"else_body", (char *)"");

                agedge(g, e_body, e_body_, "", 1);
            }
            agedge(g, stmt, e_body, "", 1);
        }
        agedge(g, stmt, if_cond, "", 1);
        agedge(g, stmt, t_body, "", 1);
        return stmt;
    } else if (tag == FOR) {
        Agnode_t *stmt = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(stmt, (char *)"shape", (char *)"ellipse", (char *)"");
        agsafeset(stmt, (char *)"label", (char *)"for", (char *)"");
        Agnode_t *for_init_ = exp->gen_graph();
        Agnode_t *for_init = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(for_init, (char *)"label", (char *)"for_init", (char *)"");
        agedge(g, for_init, for_init_, "", 1);
        Agnode_t *for_cond_ = cond->gen_graph();
        Agnode_t *for_cond = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(for_cond, (char *)"label", (char *)"for_cond", (char *)"");
        agedge(g, for_cond, for_cond_, "", 1);
        Agnode_t *for_body_ = body->gen_graph();
        Agnode_t *for_body = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(for_body, (char *)"label", (char *)"for_body", (char *)"");
        agedge(g, for_body, for_body_, "", 1);
        Agnode_t *for_update_ = exp2->gen_graph();
        Agnode_t *for_update = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(for_update, (char *)"label", (char *)"for_update", (char *)"");
        agedge(g, for_update, for_update_, "", 1);
        agedge(g, stmt, for_init, "", 1);
        agedge(g, stmt, for_cond, "", 1);
        agedge(g, stmt, for_body, "", 1);
        agedge(g, stmt, for_update, "", 1);
        return stmt;
    } else if (tag == BREAK) {
        Agnode_t *stmt = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(stmt, (char *)"shape", (char *)"ellipse", (char *)"");
        agsafeset(stmt, (char *)"label", (char *)"break", (char *)"");
        return stmt;
    } else if (tag == CONTINUE) {
        Agnode_t *stmt = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(stmt, (char *)"shape", (char *)"ellipse", (char *)"");
        agsafeset(stmt, (char *)"label", (char *)"continue", (char *)"");
        return stmt;
    } else {
        cout << "ERROR-stmt_tag" << endl;
        return nullptr;
    }
}

Agnode_t *AST_ConstExp::gen_graph(bool option)
{

    return exp->gen_graph();
}

Agnode_t *AST_LVal::gen_graph(bool option)
{
    if (tag == VARIABLE) {
        Agnode_t *val = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(val, (char *)"label", (char *)ident->c_str(), (char *)"");
        return val;
    } else {
        Agnode_t *val_array = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(val_array, (char *)"label", (char *)(*ident + "[]").c_str(), (char *)"");
        if (exps->is_zero) {
            Agnode_t *tmp = agnode(g, (char *)getNodeLabelName().c_str(), 1);
            agsafeset(tmp, (char *)"label", (char *)"0", (char *)"");
            agedge(g, val_array, tmp, "", 1);
        }
        for (auto &index : exps->vec) {
            Agnode_t *tmp = index->gen_graph();
            agedge(g, val_array, tmp, "", 1);
        }
        return val_array;
    }
}

Agnode_t *AST_Decl::gen_graph(bool option)
{

}

Agnode_t *AST_VarDecl::gen_graph(bool option)
{
    /*//创建一个图形节点，确保每个节点的编号唯一
    std::string label_name = getNodeLabelName();
    Agnode_t *node = agnode(g, (char *)label_name.c_str(), 1);
    if (node != nullptr) {

        // 设置图形节点的属性，显示的Label名字
        agsafeset(node, (char *)"label", (char *)ident, (char *)"");
        agsafeset(node, (char *)"shape", (char *)"ellipse", (char *)"");

        // 创建边，每条边不设置名字
        agedge(g, node, left, "", 1);

    }*/

}

Agnode_t *AST_VarDef::gen_graph(bool option)
{
    /*std::string label_name = getNodeLabelName();
    Agnode_t *node = agnode(g, (char *)label_name.c_str(), 1);
    if (node != nullptr) {

        // 设置图形节点的属性，显示的Label名字

        agsafeset(node, (char *)"label", (char *)ident->c_str(), (char *)"");
        agsafeset(node, (char *)"shape", (char *)"ellipse", (char *)"");
    }
    return node;*/
    Agnode_t *vardef = agnode(g, (char *)getNodeLabelName().c_str(), 1);
    agsafeset(vardef, (char *)"label", (char *)"vardef", (char *)"");
    Agnode_t *int_ = agnode(g, (char *)getNodeLabelName().c_str(), 1);
    agsafeset(int_, (char *)"label", (char *)"int", (char *)"");
    agedge(g, vardef, int_, "", 1);
    if (tag == VARIABLE) {
        Agnode_t *val = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(val, (char *)"label", (char *)ident->c_str(), (char *)"");
        agedge(g, vardef, val, "", 1);
        return vardef;
    } else {
        Agnode_t *val_array = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(val_array, (char *)"label", (char *)(*ident + "[]").c_str(), (char *)"");
        for (auto &index : arrayIndexList->vec) {
            Agnode_t *tmp = index->gen_graph();
            agedge(g, val_array, tmp, "", 1);
        }
        agedge(g, vardef, val_array, "", 1);
        return vardef;
    }
}

Agnode_t *AST_Initial::gen_graph(bool option)
{

}

Agnode_t *AST_Exp1::gen_graph(bool option)
{
    return xxx->gen_graph();
}

Agnode_t *AST_Cond::gen_graph(bool option)
{
    Agnode_t *cond = agnode(g, (char *)getNodeLabelName().c_str(), 1);
    agsafeset(cond, (char *)"label", (char *)"cond", (char *)"");
    Agnode_t *exp = lor->gen_graph();
    agedge(g, cond, exp, "", 1);
    return cond;
}

Agnode_t *AST_Unary::gen_graph(bool option)
{
    if (tag == ONLY_P) {
        return primaryExp->gen_graph();
    } else if (tag == UU) {
        Agnode_t *u_op = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        if (op == AST_OP_OPT) {
            return unaryExp->gen_graph();
        } else if (op == AST_OP_NEG) {
            agsafeset(u_op, (char *)"label", (char *)"neg", (char *)"");
            Agnode_t *exp = unaryExp->gen_graph();
            agedge(g, u_op, exp, "", 1);
            return u_op;
        } else {
            agsafeset(u_op, (char *)"label", (char *)"not", (char *)"");
            Agnode_t *exp = unaryExp->gen_graph();
            agedge(g, u_op, exp, "", 1);
            return u_op;
        }
    } else {
        Agnode_t *self_op = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        if (op == AST_OP_LINC) {
            agsafeset(self_op, (char *)"label", (char *)"LINC", (char *)"");
        } else if (op == AST_OP_LDEC) {
            agsafeset(self_op, (char *)"label", (char *)"LDNC", (char *)"");
        } else if (op == AST_OP_RINC) {
            agsafeset(self_op, (char *)"label", (char *)"RINC", (char *)"");
        } else {
            agsafeset(self_op, (char *)"label", (char *)"RDEC", (char *)"");
        }
        Agnode_t *exp = selfExp->gen_graph();
        agedge(g, self_op, exp, "", 1);
        return self_op;
    }
}

Agnode_t *AST_Primary::gen_graph(bool option)
{
    if (tag == LVAL) {
        return lval->gen_graph();
    } else if (tag == EXP) {
        return exp->gen_graph();
    } else {
        string *num = new string(to_string(int_val));
        Agnode_t *val = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(val, (char *)"label", (char *)num->c_str(), (char *)"");
        return val;
    }
}

Agnode_t *AST_MulExp::gen_graph(bool option)
{
    if (mulExp == NULL) return unaryExp->gen_graph();
    Agnode_t *op_ = agnode(g, (char *)getNodeLabelName().c_str(), 1);
    if (op == AST_OP_MUL) {
        agsafeset(op_, (char *)"label", (char *)"*", (char *)"");
    } else if (op == AST_OP_DIV) {
        agsafeset(op_, (char *)"label", (char *)"/", (char *)"");
    } else {
        agsafeset(op_, (char *)"label", (char *)"%", (char *)"");
    }
    Agnode_t *left = mulExp->gen_graph();
    Agnode_t *right = unaryExp->gen_graph();
    agedge(g, op_, left, "", 1);
    agedge(g, op_, right, "", 1);
    return op_;
}

Agnode_t *AST_AddExp::gen_graph(bool option)
{
    if (addExp == NULL) return mulExp->gen_graph();
    Agnode_t *op_ = agnode(g, (char *)getNodeLabelName().c_str(), 1);
    if (op == AST_OP_ADD) {
        agsafeset(op_, (char *)"label", (char *)"+", (char *)"");
    } else if (op == AST_OP_SUB) {
        agsafeset(op_, (char *)"label", (char *)"-", (char *)"");
    }
    Agnode_t *left = addExp->gen_graph();
    Agnode_t *right = mulExp->gen_graph();
    agedge(g, op_, left, "", 1);
    agedge(g, op_, right, "", 1);
    return op_;
}

Agnode_t *AST_RelExp::gen_graph(bool option)
{
    if (relExp == NULL) return addExp->gen_graph();
    Agnode_t *op_ = agnode(g, (char *)getNodeLabelName().c_str(), 1);
    string op_label;
    switch (op) {
    case AST_OP_LT:
        op_label = "<";
        break;
    case AST_OP_GT:
        op_label = ">";
        break;
    case AST_OP_LE:
        op_label = "<=";
        break;
    case AST_OP_GE:
        op_label = ">=";
        break;
    }
    agsafeset(op_, (char *)"label", (char *)op_label.c_str(), (char *)"");
    Agnode_t *left = relExp->gen_graph();
    Agnode_t *right = addExp->gen_graph();
    agedge(g, op_, left, "", 1);
    agedge(g, op_, right, "", 1);
    return op_;
}

Agnode_t *AST_EqExp::gen_graph(bool option)
{
    if (eqExp == NULL) return relExp->gen_graph();
    Agnode_t *op_ = agnode(g, (char *)getNodeLabelName().c_str(), 1);
    if (op == AST_OP_EQ) {
        agsafeset(op_, (char *)"label", (char *)"==", (char *)"");
    } else if (op == AST_OP_NE) {
        agsafeset(op_, (char *)"label", (char *)"!=", (char *)"");
    }
    Agnode_t *left = eqExp->gen_graph();
    Agnode_t *right = relExp->gen_graph();
    agedge(g, op_, left, "", 1);
    agedge(g, op_, right, "", 1);
    return op_;
}

Agnode_t *AST_LAnd::gen_graph(bool option)
{
    if (only_eq == true) return eqExp->gen_graph();
    Agnode_t *op_ = agnode(g, (char *)getNodeLabelName().c_str(), 1);
    agsafeset(op_, (char *)"label", (char *)"&&", (char *)"");
    Agnode_t *left = landExp->gen_graph();
    Agnode_t *right = eqExp->gen_graph();
    agedge(g, op_, left, "", 1);
    agedge(g, op_, right, "", 1);
    return op_;
}

Agnode_t *AST_LOr::gen_graph(bool option)
{
    if (only_land == true) return landExp->gen_graph();
    Agnode_t *op_ = agnode(g, (char *)getNodeLabelName().c_str(), 1);
    agsafeset(op_, (char *)"label", (char *)"||", (char *)"");
    Agnode_t *left = lorExp->gen_graph();
    Agnode_t *right = landExp->gen_graph();
    agedge(g, op_, left, "", 1);
    agedge(g, op_, right, "", 1);
    return op_;
}

Agnode_t *AST_FuncCall::gen_graph(bool option)
{
    Agnode_t *funcCall = agnode(g, (char *)getNodeLabelName().c_str(), 1);
    agsafeset(funcCall, (char *)"label", (char *)id_val->c_str(), (char *)"");
    if (params != nullptr) {
        for (auto &param : params->vec) {
            /*Agnode_t *vardef = agnode(g, (char *)getNodeLabelName().c_str(), 1);
            agsafeset(vardef, (char *)"label", (char *)"param", (char *)"");
            Agnode_t *int_ = agnode(g, (char *)getNodeLabelName().c_str(), 1);
            agsafeset(int_, (char *)"label", (char *)"int", (char *)"");
            agedge(g, vardef, int_, "", 1);*/

            Agnode_t *tmp = param->gen_graph();
            /*agedge(g, vardef, tmp, "", 1);
            agedge(g, funcCall, vardef, "", 1);*/
            agedge(g, funcCall, tmp, "", 1);
        }
    } else {
        Agnode_t *funcParam = agnode(g, (char *)getNodeLabelName().c_str(), 1);
        agsafeset(funcParam, (char *)"label", (char *)"funcParam", (char *)"");
        agedge(g, funcCall, funcParam, "", 1);
    }
    return funcCall;
}

// 遍历抽象语法树生成图片
Agnode_t *OutputAST(AST_CompUnit *root, const std::string filePath)
{
    //gvFreeContext(gv);
    // 设置graph的属性
    // agsafeset(g, (char *)"rankdir", (char *)"LR", (char *)"LR");
    // 指定输出的图像质量
    agsafeset(g, (char *)"dpi", (char *)"600", (char *)"");

    root->gen_graph();

    // 设置图形的布局
    gvLayout(gv, g, "dot");

    string fileExtName;

    string::size_type pos = filePath.find_last_of('.');
    if (pos == string::npos) {
        fileExtName = "png";
    } else {
        fileExtName = filePath.substr(pos + 1);
    }

    // 输出到一个文件中，png格式
    gvRenderFilename(gv, g, fileExtName.c_str(), filePath.c_str());

    // 关闭图形上下文，并清理资源
    gvFreeLayout(gv, g);
    agclose(g);
    gvFreeContext(gv);
}

