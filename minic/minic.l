%{

/* 这里声明语义动作符程序所需要的函数原型或者变量原型或定义等 */
/* 主要包含头文件，extern的全局变量，定义的全局变量等 */

#include <cstdio>
#include <cstring>
#include <string>

// 此文件定义了文法中终结符的类别
#include "parser.h"

using namespace std;
%}

/* 使它不要添加默认的规则,这样输入无法被给定的规则完全匹配时，词法分析器可以报告一个错误 */
%option nodefault

/* 产生yywrap函数 */
%option noyywrap

/* flex 生成的扫描器用全局变量yylineno 维护着输入文件的当前行编号 */
%option yylineno

/* 区分大小写 */
%option case-sensitive

/* yytext的类型为指针类型，即char * */
%option pointer

/* 生成可重用的扫描器API，这些API用于多线程环境 */
/* %option reentrant */

%x COMMENT
/* 辅助定义式或者宏，后面使用时带上大括号 */

num			[1-9][0-9]*|0
Octal         0[0-7]*
Hexadecimal   0[xX][0-9a-fA-F]+

ident       [A-Za-z_][A-Za-z0-9_]*
white		[\t\040]
white_line  [\r\n]


/* 正规式定义 */
%%
"/*"        {
                // 进入注释子有限自动机
                BEGIN(COMMENT); 
            }

<COMMENT>"*/" { 
                // 结束注释子有限自动机
                BEGIN(INITIAL); 
            }

<COMMENT>([^*]|\n)+|.  {
                ; // 注释子有限自动机中，忽略所有字符，含换行符等
            }

<COMMENT><<EOF>> {
                // 注释子有限自动机，没有遇到*/但是文件结束
                printf("Line %d: Unterminated comment\n", yylineno); 
                return YYerror; 
            }

"//".*\n    {
                ; // 忽略行注释
            }

"if"        {cout<<yytext<<endl;return IF;}
"else"      {cout<<yytext<<endl;return ELSE;} 
"while"     {cout<<yytext<<endl;return WHILE;}
"break"     {cout<<yytext<<endl;return BREAK;}
"continue"  {cout<<yytext<<endl;return CONT;}
"return"    {cout<<yytext<<endl;return RET;}
"for"       {cout<<yytext<<endl;return FOR;}

"int"       {
                cout<<yytext<<endl;
                return T_INT;}
"void"      {cout<<yytext<<endl;
            return T_VOID;}

"("			{cout<<yytext<<endl;return '(';}
")"			{cout<<yytext<<endl;return ')';}
"["			{cout<<yytext<<endl;return '[';}
"]"			{cout<<yytext<<endl;return ']';}
"{"			{cout<<yytext<<endl;return '{';}
"}"			{cout<<yytext<<endl;return '}';}

"*"			{cout<<yytext<<endl;return '*';}
"+"			{cout<<yytext<<endl;return '+';}
"/"			{cout<<yytext<<endl;return '/';}
"-"			{cout<<yytext<<endl;return '-';}
"%"         {cout<<yytext<<endl;return '%';}
"++"        {cout<<yytext<<endl;return INCR;}
"--"        {cout<<yytext<<endl;return DECR;}

"="         {cout<<yytext<<endl;return '=';}

">"         {cout<<yytext<<endl;return '>';}
"<"         {cout<<yytext<<endl;return '<';}
">="        {cout<<yytext<<endl;return GE;}
"<="        {cout<<yytext<<endl;return LE;}
"=="        {cout<<yytext<<endl;return EQ;}
"!="        {cout<<yytext<<endl;return NE;}
"&&"        {cout<<yytext<<endl;return AND;}
"||"        {cout<<yytext<<endl;return OR;}

"!"         {cout<<yytext<<endl;return '!';}
"&"         {cout<<yytext<<endl;return '&';}
"|"         {cout<<yytext<<endl;return '|';}

","         {cout<<yytext<<endl;return ',';}
";"         {cout<<yytext<<endl;return ';';}

{num}		{
                cout<<yytext<<endl;
                yylval.int_val.val = (int)strtol(yytext, (char **)NULL, 10);
                yylval.int_val.lineno = yylineno;
                return NUM;
            }
{Octal}         {
                cout<<yytext<<endl; 
                yylval.int_val.val = strtol(yytext, nullptr, 0); 
                //cout<<yylval.int_val.val<<endl;
                yylval.int_val.lineno = yylineno;
                return NUM; }
{Hexadecimal}   { 
                //cout<<"十六进制"<<endl;
                cout<<yytext<<endl; 
                yylval.int_val.val = strtol(yytext, nullptr, 0); 
                //cout<<yylval.int_val.val<<endl;
                yylval.int_val.lineno = yylineno;
                return NUM; }

{ident}    { 
                cout<<yytext<<endl;
                yylval.id_val.id = new string(yytext); 
                yylval.id_val.lineno = yylineno;
                return IDENT; 
            }

{white}+	 ;

{white_line}+ ;

.			{
                printf("Line %d: Invalid char %s\n", yylineno, yytext);
                return YYUNDEF;
            }
%%
