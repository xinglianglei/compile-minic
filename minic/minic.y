%code requires {
  #include <memory>
  #include <string>
  #include "ast_minic.h"
}

%{
#include <cstdio>
#include <cstring>

// 词法分析头文件
#include "lexer.h"

// bison生成的头文件
#include "parser.h"

// 抽象语法树函数定义原型头文件
#include "ast_minic.h"

// LR分   析失败时所调用函数的原型声明
void yyerror(char * msg);
using namespace std;

%}

// 联合体声明，用于后续终结符和非终结符号属性指定使用
%union {
    digit_int_attr int_val; // 整型字面量
    var_id_attr id_val;     // 标识符（变量名）
    AST_Base *ast_baseVal;
    AST_Vec *ast_vecVal;
    AST_Exp *ast_expVal;
    enum ast_op_type ast_op_type;
    //unique_ptr <string> str_val(new string);
    string *str_val;
    int val;
};

// 文法的开始符号
%parse-param { std::unique_ptr<BaseAST> &root }

// 指定文法的终结符号，<>可指定文法属性
%token <int_val> NUM
%token <id_val> IDENT

%token IF ELSE WHILE
%token BREAK CONT RET

%token INT VOID

%token INCR DECR        
%token GE LE EQ NE AND OR

// 指定文法的非终结符号，<>可指定文法属性 
%type <ast_baseVal> FuncDef Decl VarDecl VarDef Block CompUnit
%type <ast_baseVal> BlockItem Stmt MatchedStmt OpenStmt SimpleStmt FuncFParam 
%type <ast_expVal> ConstExp InitVal Exp UnaryExp PrimaryExp LVal
%type <ast_expVal> AddExp MulExp RelExp EqExp LAndExp LOrExp Cond
%type <str_val> BType FuncType
%type <ast_op_type> UnaryOp 
%type <val> Number
%type <ast_vecVal> BlockItemList VarDefList FuncFParams FuncRParams InitValList ArrayIndexList

%%
    Input       : CompUnit
                {
                    cout<<"Input : CompUnit"<<endl;
                    root=unique_ptr<AST_CompUnit>((AST_CompUnit*)($1));
                };
    CompUnit    : CompUnit Decl
                {
                    cout<<"CompUnit : CompUnit Decl"<<endl;
                    auto ptr=(AST_CompUnit *)($1);
                    ptr->list_decl.push_back(unique_ptr<AST_Base>($2));
                    $$=ptr; 
                }
                | CompUnit FuncDef
                {
                    cout<<"CompUnit : CompUnit FuncDef"<<endl;
                    auto ptr=(AST_CompUnit *)($1);
                    auto func=unique_ptr<AST_Base>($2);
                    ptr->list_func.push_back(func);
                    $$=ptr;
                }
                | Decl
                {
                    cout<<"CompUnit : Decl"<<endl;
                    auto decl=unique_ptr<AST_Base>($1);
                    auto ptr=new AST_CompUnit();
                    ptr->list_decl.push_back(decl);
                    $$=ptr;
                }
                | FuncDef
                {
                    cout<<"CompUnit : FuncDef"<<endl;
                    auto func=unique_ptr<AST_Base>($1);
                    auto ptr=new AST_CompUnit();
                    ptr->list_func.push_back(func);
                    $$=ptr;
                };
    Decl        : VarDecl
                {
                    cout<<"Decl : VarDecl"<<endl;
                    $$=$1;
                };
    BType       : INT
                {
                    cout<<"cout : INT"<<endl;
                    auto btype=new string("int");
                    //auto btype=unique_ptr<string>(tmp);
                    $$=btype;
                };
    VarDecl     : BType VarDefList ';'
                {
                    cout<<"VarDecl : BType VarDefList ';'"<<endl;
                    auto btype=unique_ptr<string>($1);
                    auto varDefList=unique_ptr<AST_Vec>($2);
                    auto ptr=new AST_VarDecl(btype,varDefList);
                    $$=ptr;
                };
    VarDefList  : VarDefList ',' VarDef
                {
                    cout<<"VarDefList  : VarDefList ',' VarDef"<<endl;
                    auto ptr=$1;
                    auto varDef=unique_ptr<AST_Base>($3);
                    ptr->push(varDef);
                    $$=ptr;
                }
                | VarDef
                {
                    cout<<"VarDefList  : VarDefList ',' VarDef"<<endl;
                    auto varDef=unique_ptr<AST_Base>($1);
                    auto ptr=new AST_Vec();
                    ptr->push(varDef);
                    $$=ptr;
                };
    
    VarDef      : IDENT ArrayIndexList
                {
                    cout<<"VarDef : IDENT ArrayIndexList"<<endl;
                    auto ptr=new AST_VarDef();
                    ptr->tag=AST_VarDef::ARRAY;
                    ptr->ident=unique_ptr<string>($1.id);
                    ptr->arrayIndexList=unique_ptr<AST_Vec>($2);
                    $$=ptr;
                }
                | IDENT
                {
                    cout<<"VarDef : IDENT ArrayIndexList"<<endl;
                    auto ptr=new AST_VarDef();
                    ptr->tag=AST_VarDef::VARIABLE;
                    ptr->ident=unique_ptr<string>($1.id);
                    $$=ptr;
                }
                | IDENT ArrayIndexList '=' InitVal
                {
                    cout<<"VarDef IDENT ArrayIndexList '=' InitVal"<<endl;
                    auto ptr=new AST_VarDef();
                    ptr->tag=AST_VarDef::ARRAY;
                    ptr->ident=unique_ptr<string>($1.id);
                    ptr->arrayIndexList=unique_ptr<AST_Vec>($2);
                    ptr->initVal=unique_ptr<AST_Exp>($4);
                    $$=ptr;
                }
                | IDENT '=' InitVal
                {
                    cout<<"VarDef : IDENT '=' InitVal"<<endl;
                    auto ptr=new AST_VarDef();
                    ptr->tag=AST_VarDef::VARIABLE;
                    ptr->ident=unique_ptr<string>($1.id);
                    ptr->initVal=unique_ptr<AST_Exp>($3);
                    $$=ptr;
                };
    InitVal     : Exp
                {
                    cout<<"InitVal : Exp"<<endl;
                    auto ptr=new AST_Initial();
                    ptr->tag=AST_Initial::EXP;
                    ptr->exp=unique_ptr<AST_Exp>($1);
                    $$=ptr;
                }
                | '{' '}'
                {
                    cout<<"InitVal : {}"<<endl;
                    auto ptr=new AST_Initial();
                    ptr->tag=AST_Initial::INITVALLIST;
                    $$=ptr;
                }
                | '{' InitValList '}'
                {
                    cout<<"InitVal : '{' InitValList '}'"<<endl;
                    auto ptr=new AST_Initial();
                    ptr->tag=AST_Initial::INITVALLIST;
                    ptr->initValList=unique_ptr<AST_Vec>($2);
                    $$=ptr;
                };
    InitValList :  InitVal
                {
                    cout<<"InitValList :  InitVal"<<endl;
                    auto initVal=unique_ptr<AST_Base>($1);
                    auto ptr=new AST_Vec();
                    ptr->push(initVal);
                    $$=ptr;
                }
                | InitValList ',' InitVal
                {
                    cout<<"InitValList : InitValList ',' InitVal"<<endl;
                    auto initVal=unique_ptr<AST_Base>($3);
                    auto ptr=(AST_Vec*)$1;
                    ptr->push(initVal);
                    $$=ptr;
                };
    FuncDef     : FuncType IDENT '(' ')' Block
                {
                    cout<<"FuncDef : FuncType IDENT '(' ')' Block"<<endl;
                    auto funcType=unique_ptr<string>($1);
                    auto funcName=unique_ptr<string>($2.id);
                    auto funcBlock=unique_ptr<AST_Base>($5);
                    auto ptr=new AST_FuncDef(funcType, funcName, funcBlock);
                    $$=ptr;
                }
                | FuncType IDENT '(' FuncFParams ')' Block
                {
                    cout<<"FuncDef : FuncType IDENT '(' FuncFParams ')' Block"<<endl;
                    auto funcType=unique_ptr<string>($1);
                    auto funcName=unique_ptr<string>($2.id);
                    auto funcFParams=unique_ptr<AST_Vec>($4);
                    auto funcBlock=unique_ptr<AST_Base>($6);
                    auto ptr=new AST_FuncDef(funcType,funcName,funcFParams,funcBlock);
                    $$=ptr;
                };
    FuncType    : VOID
                {
                    cout<<"FuncType : VOID"<<endl;
                    auto type=new string("void");
                    $$=type;
                }
                | INT
                {
                    cout<<"FuncType : INT"<<endl;
                    auto type=new string("int");
                    $$=type;
                };
    FuncFParams : FuncFParam
                {
                    cout<<"FuncFParams : FuncFParam"<<endl;
                    auto param=unique_ptr<AST_Base>($1);
                    auto ptr=new AST_Vec();
                    ptr->push(param);
                    $$=ptr;
                } 
                | FuncFParams ',' FuncFParam
                {
                    cout<<"FuncFParams : FuncFParams ',' FuncFParam"<<endl;
                    auto param=unique_ptr<AST_Base>($3);
                    auto ptr=$1;
                    ptr->push(param);
                    $$=ptr;
                };
    FuncFParam  : BType IDENT
                {
                    cout<<"FuncFParam  : BType IDENT"<<endl;
                    auto ptr=new AST_FuncFParam();
                    ptr->tag=AST_FuncFParam::VARIABLE;
                    ptr->param_type=unique_ptr<string>($1);
                    ptr->param_name=unique_ptr<string>($2.id);
                    $$=ptr;
                }   
                | BType IDENT '[' ']'
                {
                    cout<<"FuncFParam  : BType IDENT '[' ']'"<<endl;
                    auto ptr=new AST_FuncFParam();
                    ptr->tag=AST_FuncFParam::ARRAY;
                    ptr->param_type=unique_ptr<string>($1);
                    ptr->param_name=unique_ptr<string>($2.id);
                    $$=ptr;
                }
                | BType IDENT '[' ']' ArrayIndexList
                {
                    cout<<"FuncFParam  : BType IDENT '[' ']' ArrayIndexList"<<endl;
                    auto ptr=new AST_FuncFParam();
                    ptr->tag=AST_FuncFParam::ARRAY;
                    ptr->param_type=unique_ptr<string>($1);
                    ptr->param_name=unique_ptr<string>($2.id);
                    ptr->ArrayIndexList=unique_ptr<AST_Vec>($5);
                    $$=ptr;
                };
    ArrayIndexList : '[' Exp ']'
                    {
                        cout<<"ArrayIndexList : '[' Exp ']'"<<endl;
                        auto exp=unique_ptr<AST_Base>($2);
                        auto ptr=new AST_Vec();
                        ptr->push(exp);
                        $$=ptr;
                    } 
                    | ArrayIndexList '[' Exp ']'
                    {
                        cout<<"ArrayIndexList : ArrayIndexList '[' Exp ']'"<<endl;
                        auto ptr=$1;
                        auto exp=unique_ptr<AST_Base>($3);
                        ptr->push(exp);
                        $$=ptr;
                    };
    Block       :'{' BlockItemList'}'
                {
                    cout << "Block : '{' BlockItemList'}'" <<endl;
                    auto blocks=unique_ptr<AST_Vec>($2);
                    auto ptr=new AST_Block(blocks);
                    $$=ptr;
                };
    BlockItemList   :
                {
                    cout<< "BlockItemList   :"<<endl;
                    auto ptr=new AST_Vec();
                    $$=ptr;
                }
                | BlockItemList BlockItem
                {
                    cout<< "BlockItemList   : BlockItemList BlockItem" <<endl;
                    auto blocks=$1;
                    auto item=unique_ptr<AST_Base>($2);
                    blocks->push(item);
                    $$=blocks;
                };
    BlockItem   : Decl
                {
                    cout<< "------BlockItem : Decl------"<<endl;
                    auto decl=unique_ptr<AST_Base>($1);
                    auto ptr=new AST_BlockItem(decl,false);
                    $$=ptr;
                }
                | Stmt
                {
                    cout<< "------BlockItem : Stmt------"<<endl;
                    auto stmt=unique_ptr<AST_Base>($1);
                    auto ptr=new AST_BlockItem(stmt,true);
                    $$=ptr;
                };
    Stmt        : MatchedStmt{
                    $$=$1;
                }
                | OpenStmt{
                    $$=$1;
                };
    MatchedStmt : IF '(' Exp ')' MatchedStmt ELSE MatchedStmt{
                    cout<<"MatchedStmt : IF '(' Exp ')' MatchedStmt ELSE MatchedStmt"<<endl;
                    auto ptr =new AST_Stmt();
                    ptr->tag=AST_Stmt::IF;
                    ptr->cond=unique_ptr<AST_Exp>($3);
                    ptr->body=unique_ptr<AST_Base>($5);
                    ptr->else_body=unique_ptr<AST_Base>($7);
                    $$=ptr;
                }
                |
                SimpleStmt{
                    cout<<"MatchedStmt : SimpleStmt"<<endl;
                    $$=$1;
                };
    OpenStmt    : IF '(' Exp ')' Stmt {
                    cout<<"OpenStmt : IF '(' Exp ')' Stmt"<<endl;
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::IF;
                    ptr->cond=unique_ptr<AST_Exp>($3);
                    ptr->body=unique_ptr<AST_Base>($5);
                    $$=ptr;
                } 
                | IF '(' Exp ')' MatchedStmt ELSE OpenStmt {
                    cout<<"OpenStmt : IF '(' Exp ')' MatchedStmt ELSE OpenStmt"<<endl;
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::IF;
                    ptr->cond=unique_ptr<AST_Exp>($3);
                    ptr->body=unique_ptr<AST_Base>($5);
                    ptr->else_body=unique_ptr<AST_Base>($7);
                    $$=ptr;
                };
    SimpleStmt  : LVal '=' Exp ';'
                {
                    cout<<"SimpleStmt : LVal '=' Exp ';'"<<endl;
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::ASSIGN;
                    ptr->lval=unique_ptr<AST_Exp>($1);
                    ptr->exp=unique_ptr<AST_Exp>($3);
                    $$=ptr;
                }
                | ';'
                {
                    cout<<"SimpleStmt : ';'"<<endl;
                    //TODO ????????????????????
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::EXP;
                    $$=ptr;
                }
                | Exp ';'
                {
                    cout<<"SimpleStmt : Exp ';'"<<endl;
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::EXP;
                    ptr->exp=unique_ptr<AST_Exp>($1);
                    $$=ptr;
                }
                | Block
                {
                    cout<<"SimpleStmt : Block"<<endl;
                    //TODO ????????????????????
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::BLOCK;
                    ptr->block=unique_ptr<AST_Vec>((AST_Vec*)$1);
                    $$=ptr;

                }
                | WHILE '(' Cond ')' Stmt
                {
                    cout<<"SimpleStmt : WHILE '(' Cond ')' Stmt"<<endl;
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::WHILE;
                    ptr->cond=unique_ptr<AST_Exp>($3);
                    ptr->body=unique_ptr<AST_Base>($5);
                    $$=ptr;
                }
                | BREAK ';'
                {
                    cout<<"BREAK ';'"<<endl;
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::BREAK;
                    $$=ptr;
                }
                | CONT ';'
                {
                    cout<<"CONT ';'"<<endl;
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::CONTINUE;
                    $$=ptr;
                }
                | RET ';'
                {
                    cout<<"RET ';'"<<endl;
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::RETURN;
                    $$=ptr;
                }
                | RET Exp ';'
                {
                    cout<<"RET Exp ';'"<<endl;
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::RETURN;
                    ptr->exp=unique_ptr<AST_Exp>($2);
                    $$=ptr;
                };
    Exp         : AddExp
                {
                    cout<<"Exp : AddExp"<<endl;
                    auto andExp=unique_ptr<AST_Exp>($1);
                    auto ptr=new AST_Exp1(andExp);
                    $$=ptr;
                };
    Cond        :LOrExp
                {
                    cout<<"Cond :LOrExp"<<endl;
                    //!!!需新建cond类
                    auto lorExp=unique_ptr<AST_Exp>($1);
                    auto ptr=new AST_Cond(lorExp);
                    $$=ptr;
                };
    LVal        : IDENT
                {
                    cout<<"LVal : IDENT"<<endl;
                    auto ptr=new AST_LVal();
                    ptr->tag=AST_LVal::VARIABLE;
                    ptr->ident=unique_ptr<string>($1.id);
                    $$=ptr;
                }
                | IDENT ArrayIndexList
                {
                    cout<<"LVal : IDENT ArrayIndexList"<<endl;
                    auto ptr=new AST_LVal();
                    ptr->tag=AST_LVal::ARRAY;
                    ptr->exps=unique_ptr<AST_Vec>($2);
                    ptr->ident=unique_ptr<string>($1.id);
                    $$=ptr;
                };
    PrimaryExp  : '(' Exp ')'
                {
                    cout<<"PrimaryExp  : '(' Exp ')'"<<endl;
                    auto ptr=new AST_Primary();
                    ptr->tag=AST_Primary::EXP;
                    ptr->exp=unique_ptr<AST_Exp>($2);
                    $$=ptr;
                }
                | LVal
                {
                    cout<<"PrimaryExp  : LVal"<<endl;
                    auto ptr=new AST_Primary();
                    ptr->tag=AST_Primary::LVAL;
                    ptr->lval=unique_ptr<AST_Exp>($1);
                    $$=ptr;
                }
                | Number
                {
                    cout<<"PrimaryExp  : Number"<<endl;
                    auto ptr=new AST_Primary();
                    ptr->tag=AST_Primary::NUM;
                    ptr->int_val= $1;
                    $$=ptr;

                };
    Number      : NUM
                {
                    cout<<"Number : NUM"<<endl;
                    $$=$1.val;
                };
    //！！！！！有问题
    UnaryExp    : PrimaryExp 
                {
                    cout<<"UnaryExp :PrimaryExp"<<endl;
                    auto primaryExp = unique_ptr<AST_Exp>($1);
                    auto ptr=new AST_Unary(primaryExp);
                    $$=ptr;
                }
                | IDENT '(' ')'
                {
                    cout<<"UnaryExp : IDENT ( ) "<<endl;
                    auto funcName = unique_ptr<string>($1.id);
                    auto ptr=new AST_FuncCall(funcName);
                    $$=ptr;
                }
                | IDENT '(' FuncRParams ')'
                {
                    cout<<"UnaryExp : IDENT ( FuncRParams )"<<endl;
                    auto funcName = unique_ptr<string>($1.id);
                    auto funcRParams = unique_ptr<AST_Vec>($3);
                    auto ptr=new AST_FuncCall(funcName,funcRParams);
                    $$=ptr;
                } 
                | UnaryOp UnaryExp
                {
                    cout<<"UnaryExp :UnaryOp UnaryExp"<<endl;
                    auto unaryExp=unique_ptr<AST_Exp>($2);
                    auto ptr=new AST_Unary($1,unaryExp);
                    $$=ptr;
                };
    UnaryOp     : '+'
                {
                    cout<<"UnaryOp :'+'"<<endl;
                    $$=AST_OP_OPT;
                }
                | '-'
                {
                    cout<<"UnaryOp :'-'"<<endl;
                    $$=AST_OP_NEG;
                }
                | '!'
                {
                    cout<<"UnaryOp :'!'"<<endl;
                    $$=AST_OP_NOT;
                };
    FuncRParams : Exp 
                {
                    cout<<"FuncRParams : Exp"<<endl;
                    auto paramVec=new AST_Vec();
                    auto exp=unique_ptr<AST_Base>($1);
                    paramVec->push(exp);
                    $$=paramVec;
                }
                | FuncRParams ',' Exp 
                {
                    cout<<"FuncRParams : FuncRParams , Exp"<<endl;
                    auto paramVec = $1;
                    auto exp=unique_ptr<AST_Base>($3);
                    paramVec->push(exp);
                    $$=paramVec; //???
                };
    MulExp      : UnaryExp
                {
                    cout<<"MulExp :UnaryExp"<<endl;
                    auto unaryExp=unique_ptr<AST_Exp>($1);
                    auto ptr=new AST_MulExp(unaryExp);
                    $$=ptr;
                }
                | MulExp '*' UnaryExp
                {
                    cout<<"MulExp :MulExp '*' UnaryExp"<<endl;
                    auto mulExp=unique_ptr<AST_Exp>($1);
                    auto unaryExp=unique_ptr<AST_Exp>($3);
                    auto ptr=new AST_MulExp(AST_OP_MUL,mulExp,unaryExp);
                    $$=ptr;
                }
                | MulExp '/' UnaryExp
                {
                    cout<<"MulExp :MulExp '/' UnaryExp"<<endl;
                    auto mulExp=unique_ptr<AST_Exp>($1);
                    auto unaryExp=unique_ptr<AST_Exp>($3);
                    auto ptr=new AST_MulExp(AST_OP_DIV,mulExp,unaryExp);
                    $$=ptr;
                }
                | MulExp '%' UnaryExp
                {
                    cout<<"MulExp :MulExp '%' UnaryExp"<<endl;
                    auto mulExp=unique_ptr<AST_Exp>($1);
                    auto unaryExp=unique_ptr<AST_Exp>($3);
                    auto ptr=new AST_MulExp(AST_OP_MOD,mulExp,unaryExp);
                    $$=ptr;
                };
    AddExp      : MulExp
                {
                    cout<<"AddExp :MulExp "<<endl;
                    auto mul=unique_ptr<AST_Exp>($1);
                    auto ptr=new AST_AddExp(mul);
                    $$=ptr;
                }
                | AddExp '+' MulExp
                {
                    cout<<"AddExp :AddExp '+' MulExp"<<endl;
                    auto add=unique_ptr<AST_Exp>($1);
                    auto mul=unique_ptr<AST_Exp>($3);
                    auto ptr=new AST_AddExp(AST_OP_ADD,add,mul);
                    $$=ptr;
                }
                | AddExp '-' MulExp
                {
                    cout<<"AddExp :AddExp '-' MulExp"<<endl;
                    auto add=unique_ptr<AST_Exp>($1);
                    auto mul=unique_ptr<AST_Exp>($3);
                    auto ptr=new AST_AddExp(AST_OP_SUB,add,mul);
                    $$=ptr;
                };
    RelExp      : AddExp
                {
                    cout<<"RelExp :AddExp"<<endl;
                    auto add=unique_ptr<AST_Exp>($1);
                    auto ptr=new AST_RelExp(add);
                    $$=ptr;
                }
                | RelExp '<' AddExp
                {
                    cout <<"RelExp :RelExp '<' AddExp"<<endl;
                    auto rel=unique_ptr<AST_Exp>($1);
                    auto add=unique_ptr<AST_Exp>($3);
                    auto ptr=new AST_RelExp(AST_OP_LT,rel,add);
                    $$=ptr;
                }
                | RelExp '>' AddExp
                {
                    cout <<"RelExp :RelExp '>' AddExp"<<endl;
                    auto rel=unique_ptr<AST_Exp>($1);
                    auto add=unique_ptr<AST_Exp>($3);
                    auto ptr=new AST_RelExp(AST_OP_GT,rel,add);
                    $$=ptr;
                }
                | RelExp LE AddExp
                {
                    cout <<"RelExp :RelExp '<=' AddExp"<<endl;
                    auto rel=unique_ptr<AST_Exp>($1);
                    auto add=unique_ptr<AST_Exp>($3);
                    auto ptr=new AST_RelExp(AST_OP_LE,rel,add);
                    $$=ptr;
                }
                | RelExp GE AddExp
                {
                    cout <<"RelExp :RelExp '>=' AddExp"<<endl;
                    auto rel=unique_ptr<AST_Exp>($1);
                    auto add=unique_ptr<AST_Exp>($3);
                    auto ptr=new AST_RelExp(AST_OP_GE,rel,add);
                    $$=ptr;
                };
    EqExp       : RelExp
                {
                    cout<<"EqExp :RelExp"<<endl;
                    auto rel=unique_ptr<AST_Exp>($1);
                    auto ptr=new AST_EqExp(rel);
                    $$=ptr;
                }
                | EqExp EQ RelExp
                {
                    cout<<"EqExp :EqExp EQ RelExp"<<endl;
                    auto eq=unique_ptr<AST_Exp>($1);
                    auto rel=unique_ptr<AST_Exp>($3);
                    auto ptr=new AST_EqExp(AST_OP_EQ,eq,rel);
                    $$=ptr;
                }
                | EqExp NE RelExp
                {
                    cout<<"EqExp :EqExp NE RelExp"<<endl;
                    auto eq=unique_ptr<AST_Exp>($1);
                    auto rel=unique_ptr<AST_Exp>($3);
                    auto ptr=new AST_EqExp(AST_OP_NE,eq,rel);
                    $$=ptr;

                };
    LAndExp     : EqExp
                {
                    cout<<"LAndExp :EqExp"<<endl;
                    auto eq=unique_ptr<AST_Exp>($1);
                    auto ptr=new AST_LAnd(eq);
                    $$=ptr;
                }
                | LAndExp AND EqExp
                {
                    cout<<"LAndExp :LAndExp AND EqExp"<<endl;
                    auto land=unique_ptr<AST_Exp>($1);
                    auto eq=unique_ptr<AST_Exp>($3);
                    auto ptr=new AST_LAnd(land,eq);
                    $$=ptr;
                };
    LOrExp      : LAndExp
                {
                    cout<<"LOrExp :LAndExp"<<endl;
                    auto land=unique_ptr<AST_Exp>($1);
                    auto ptr=new AST_LOr(land);
                    $$=ptr;
                }
                | LOrExp OR LAndExp
                {
                    cout<<"LOrExp :LOrExp OR LAndExp"<<endl;
                    auto land=unique_ptr<AST_Exp>($3);
                    auto lor=unique_ptr<AST_Exp>($1);
                    auto ptr=new AST_LOr(lor,land);
                    $$=ptr;
                };
    ConstExp    : AddExp
                {
                    cout<<"ConstExp :AddExp"<<endl;
                    auto addExp=unique_ptr<AST_Exp>($1);
                    auto ptr=new AST_ConstExp(addExp);
                    $$=ptr;
                };    

%%

// 语法识别错误要调用函数的定义
void yyerror(char * msg)
{
    printf("Line %d: %s\n", yylineno, msg);
}
