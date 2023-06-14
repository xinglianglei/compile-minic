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

// LR分析失败时所调用函数的原型声明
int yylex();
void yyerror(std::unique_ptr<AST_Base> &root, const char *s);
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
    string *str_val;
    int val;
};

// 文法的开始符号
%parse-param { std::unique_ptr<AST_Base> &root }

// 指定文法的终结符号，<>可指定文法属性
%token <int_val> NUM
%token <id_val> IDENT

%token IF ELSE WHILE
%token BREAK CONT RET

%token T_INT T_VOID

%token INCR DECR        
%token GE LE EQ NE AND OR

// 指定文法的非终结符号，<>可指定文法属性 
%type <ast_baseVal> FuncDef Decl VarDecl VarDef Block CompUnit
%type <ast_baseVal> BlockItem Stmt MatchedStmt OpenStmt SimpleStmt FuncFParam 
%type <ast_expVal> ConstExp InitVal Exp UnaryExp PrimaryExp LVal SelfExp
%type <ast_expVal> AddExp MulExp RelExp EqExp LAndExp LOrExp Cond
%type <str_val> BType
%type <ast_op_type> UnaryOp SelfOp
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
                    ptr->list_func.push_back(unique_ptr<AST_Base>($2));
                    $$=ptr;
                }
                | Decl
                {
                    cout<<"CompUnit : Decl"<<endl;
                    auto ptr=new AST_CompUnit();
                    ptr->list_decl.push_back(unique_ptr<AST_Base>($1));
                    $$=ptr;
                }
                | FuncDef
                {
                    cout<<"CompUnit : FuncDef"<<endl;
                    auto ptr=new AST_CompUnit();
                    ptr->list_func.push_back(unique_ptr<AST_Base>($1));
                    $$=ptr;
                };
    Decl        : VarDecl
                {
                    cout<<"Decl : VarDecl"<<endl;
                    $$=$1;
                };
    BType       : T_INT
                {
                    cout<<"BType : T_INT"<<endl;
                    auto btype=new string("int");
                    //auto btype=unique_ptr<string>(tmp);
                    $$=btype;
                }
                | T_VOID
                {
                    cout<<"BType : T_VOID"<<endl;
                    auto btype=new string("void");
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
                    cout<<"VarDef : IDENT"<<endl;
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
    FuncDef     :  BType IDENT '(' ')' Block
                {
                    cout<<"FuncDef : BType IDENT '(' ')' Block"<<endl;
                    auto ptr=new AST_FuncDef();
                    auto tmp=(AST_Block*)($5);
                    if(tmp->is_null)
                        ptr->tag=AST_FuncDef::DECL_NOPARAM;
                    else
                        ptr->tag=AST_FuncDef::DEF_NOPARAM;
                    ptr->func_type=unique_ptr<string>($1);
                    ptr->func_name=unique_ptr<string>($2.id);
                    cout<<"函数名："+*(ptr->func_name)<<endl;
                    ptr->func_block=unique_ptr<AST_Base>($5);
                    $$=ptr;
                }
                | BType IDENT '(' FuncFParams ')' Block
                {
                    cout<<"FuncDef : BType IDENT '(' FuncFParams ')' Block"<<endl;
                    auto ptr=new AST_FuncDef();
                    auto tmp=(AST_Block*)($6);
                    if(tmp->is_null)
                        ptr->tag=AST_FuncDef::DECL_PARAM;
                    else
                        ptr->tag=AST_FuncDef::DEF_PARAM;
                    ptr->func_type=unique_ptr<string>($1);
                    ptr->func_name=unique_ptr<string>($2.id);
                    cout<<"函数名："+*(ptr->func_name)<<endl;
                    ptr->func_params=unique_ptr<AST_Vec>($4);
                    ptr->func_block=unique_ptr<AST_Base>($6);
                    $$=ptr;
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
    //这里的第一个数组维度可以没有,也可以有
    FuncFParam  : BType IDENT
                {
                    cout<<"FuncFParam  : BType IDENT"<<endl;
                    auto ptr=new AST_FuncFParam();
                    ptr->tag=AST_FuncFParam::VARIABLE;
                    ptr->param_type=unique_ptr<string>($1);
                    ptr->param_name=unique_ptr<string>($2.id);
                    $$=ptr;
                }   
                | BType IDENT ArrayIndexList
                {
                    cout<<"FuncFParam  : BType IDENT '[' ']'"<<endl;
                    auto ptr=new AST_FuncFParam();
                    ptr->tag=AST_FuncFParam::ARRAY;
                    ptr->param_type=unique_ptr<string>($1);
                    ptr->param_name=unique_ptr<string>($2.id);
                    ptr->ArrayIndexList=unique_ptr<AST_Vec>($3);
                    //ptr->is_zero=$3->is_zero;
                    $$=ptr;
                };
                /*BType IDENT '[' ']'
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
                }
                | BType IDENT '[' ConstExp ']'
                {
                    cout<<"FuncFParam  : BType IDENT '['ConstExp ']'"<<endl;
                    auto exp=unique_ptr<AST_Base>($4);
                    auto ptr=new AST_FuncFParam();
                    ptr->tag=AST_FuncFParam::ARRAY;
                    ptr->param_type=unique_ptr<string>($1);
                    ptr->param_name=unique_ptr<string>($2.id);
                    $$=ptr;
                }
                | BType IDENT '[' ConstExp ']' ArrayIndexList
                {
                    cout<<"FuncFParam  : BType IDENT '[' ConstExp ']' ArrayIndexList"<<endl;
                    auto ptr=new AST_FuncFParam();
                    ptr->tag=AST_FuncFParam::ARRAY;
                    ptr->param_type=unique_ptr<string>($1);
                    ptr->param_name=unique_ptr<string>($2.id);
                    ptr->ArrayIndexList=unique_ptr<AST_Vec>($5);
                    $$=ptr;
                }*/;
                //！！！这里应该是constexp,!!!
    ArrayIndexList : '['  ']'
                    {
                        cout<<"ArrayIndexList : '['  ']'"<<endl;
                        auto ptr=new AST_Vec();
                        ptr->is_zero=true;
                        $$=ptr;
                    } 
                    | '[' ConstExp ']'
                    {
                        cout<<"ArrayIndexList : '[' Exp ']'"<<endl;
                        auto exp=unique_ptr<AST_Base>($2);
                        auto ptr=new AST_Vec();
                        ptr->push(exp);
                        ptr->is_zero=false;
                        $$=ptr;
                    } 
                    | ArrayIndexList '[' ConstExp ']'
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
                }
                | ';'
                {
                    cout<<"Block : ;"<<endl;
                    auto ptr=new AST_Block();
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
                    cout<<"Stmt:MatchedStmt"<<endl;
                    $$=$1;
                }
                | OpenStmt{
                    cout<<"Stmt:OpenStmt"<<endl;
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
                    //修改了类型
                    ptr->block=unique_ptr<AST_Base>($1);
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
    Exp         : LOrExp
                {
                    cout<<"Exp : LOrExp"<<endl;
                    auto lorExp=unique_ptr<AST_Exp>($1);
                    auto ptr=new AST_Exp1(lorExp);
                    $$=ptr;
                };
    Cond        : LOrExp
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
                    auto ptr=new AST_Unary();
                    ptr->tag=AST_Unary::ONLY_P;
                    ptr->primaryExp=unique_ptr<AST_Exp>($1);
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
                    auto ptr=new AST_Unary();
                    ptr->tag=AST_Unary::UU;
                    ptr->op=$1;
                    ptr->unaryExp=unique_ptr<AST_Exp>($2);
                    $$=ptr;
                }
                | SelfOp LVal
                {
                    cout<<"Unary : SelfOp LVal"<<endl;
                    auto ptr=new AST_Unary();
                    ptr->tag=AST_Unary::SELF;
                    if($1==AST_OP_INCR)
                        ptr->op=AST_OP_LINC;
                    else
                        ptr->op=AST_OP_LDEC;
                    ptr->selfExp=unique_ptr<AST_Exp>($2);
                    $$=ptr;
                }
                | LVal SelfOp
                {
                    cout<<"Unary : LVal SelfOp"<<endl;
                    auto ptr=new AST_Unary();
                    ptr->tag=AST_Unary::SELF;
                    if($2==AST_OP_INCR)
                        ptr->op=AST_OP_RINC;
                    else
                        ptr->op=AST_OP_RDEC;
                    ptr->selfExp=unique_ptr<AST_Exp>($1);
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
    SelfOp      : INCR
                {
                    cout<<"SelfOp : INCR"<<endl;
                    $$=AST_OP_INCR;
                } 
                | DECR
                {
                    cout<<"SelfOp : DECR"<<endl;
                    $$=AST_OP_DECR;
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
    ConstExp    : Exp
                {
                    cout<<"ConstExp :Exp"<<endl;
                    auto Exp=unique_ptr<AST_Exp>($1);
                    auto ptr=new AST_ConstExp(Exp);
                    $$=ptr;
                };    

%%

// 语法识别错误要调用函数的定义
void yyerror(unique_ptr<AST_Base> &ast, const char *s) {
  cerr << "error: " << s << endl;
}
