#pragma once

#include <string>
using namespace std;

typedef struct digit_int_attr {
    int val;     // 整数值
    int lineno;  // 行号
} digit_int_attr;

typedef struct var_id_attr {
    string *id; // 变量名
    int lineno;   // 行号
} var_id_attr;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse(void *YYPARSE_PARAM);
#else
int yyparse();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse(void);
#else
int yyparse();
#endif
#endif /* ! YYPARSE_PARAM */

#ifdef BISON_USE
#include "minic_yacc.h"
#else
#include "mybison.h"
#endif

