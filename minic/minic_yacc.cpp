/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 7 "D:/CompilerTools/code/minic/minic.y"

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


#line 91 "D:/CompilerTools/code/minic/minic_yacc.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "minic_yacc.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_IDENT = 4,                      /* IDENT  */
  YYSYMBOL_IF = 5,                         /* IF  */
  YYSYMBOL_ELSE = 6,                       /* ELSE  */
  YYSYMBOL_WHILE = 7,                      /* WHILE  */
  YYSYMBOL_BREAK = 8,                      /* BREAK  */
  YYSYMBOL_CONT = 9,                       /* CONT  */
  YYSYMBOL_RET = 10,                       /* RET  */
  YYSYMBOL_T_INT = 11,                     /* T_INT  */
  YYSYMBOL_T_VOID = 12,                    /* T_VOID  */
  YYSYMBOL_INCR = 13,                      /* INCR  */
  YYSYMBOL_DECR = 14,                      /* DECR  */
  YYSYMBOL_GE = 15,                        /* GE  */
  YYSYMBOL_LE = 16,                        /* LE  */
  YYSYMBOL_EQ = 17,                        /* EQ  */
  YYSYMBOL_NE = 18,                        /* NE  */
  YYSYMBOL_AND = 19,                       /* AND  */
  YYSYMBOL_OR = 20,                        /* OR  */
  YYSYMBOL_21_ = 21,                       /* ';'  */
  YYSYMBOL_22_ = 22,                       /* ','  */
  YYSYMBOL_23_ = 23,                       /* '='  */
  YYSYMBOL_24_ = 24,                       /* '{'  */
  YYSYMBOL_25_ = 25,                       /* '}'  */
  YYSYMBOL_26_ = 26,                       /* '('  */
  YYSYMBOL_27_ = 27,                       /* ')'  */
  YYSYMBOL_28_ = 28,                       /* '['  */
  YYSYMBOL_29_ = 29,                       /* ']'  */
  YYSYMBOL_30_ = 30,                       /* '+'  */
  YYSYMBOL_31_ = 31,                       /* '-'  */
  YYSYMBOL_32_ = 32,                       /* '!'  */
  YYSYMBOL_33_ = 33,                       /* '*'  */
  YYSYMBOL_34_ = 34,                       /* '/'  */
  YYSYMBOL_35_ = 35,                       /* '%'  */
  YYSYMBOL_36_ = 36,                       /* '<'  */
  YYSYMBOL_37_ = 37,                       /* '>'  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_Input = 39,                     /* Input  */
  YYSYMBOL_CompUnit = 40,                  /* CompUnit  */
  YYSYMBOL_Decl = 41,                      /* Decl  */
  YYSYMBOL_BType = 42,                     /* BType  */
  YYSYMBOL_VarDecl = 43,                   /* VarDecl  */
  YYSYMBOL_VarDefList = 44,                /* VarDefList  */
  YYSYMBOL_VarDef = 45,                    /* VarDef  */
  YYSYMBOL_InitVal = 46,                   /* InitVal  */
  YYSYMBOL_InitValList = 47,               /* InitValList  */
  YYSYMBOL_FuncDef = 48,                   /* FuncDef  */
  YYSYMBOL_FuncFParams = 49,               /* FuncFParams  */
  YYSYMBOL_FuncFParam = 50,                /* FuncFParam  */
  YYSYMBOL_ArrayIndexList = 51,            /* ArrayIndexList  */
  YYSYMBOL_Block = 52,                     /* Block  */
  YYSYMBOL_BlockItemList = 53,             /* BlockItemList  */
  YYSYMBOL_BlockItem = 54,                 /* BlockItem  */
  YYSYMBOL_Stmt = 55,                      /* Stmt  */
  YYSYMBOL_MatchedStmt = 56,               /* MatchedStmt  */
  YYSYMBOL_OpenStmt = 57,                  /* OpenStmt  */
  YYSYMBOL_SimpleStmt = 58,                /* SimpleStmt  */
  YYSYMBOL_Exp = 59,                       /* Exp  */
  YYSYMBOL_Cond = 60,                      /* Cond  */
  YYSYMBOL_LVal = 61,                      /* LVal  */
  YYSYMBOL_PrimaryExp = 62,                /* PrimaryExp  */
  YYSYMBOL_Number = 63,                    /* Number  */
  YYSYMBOL_UnaryExp = 64,                  /* UnaryExp  */
  YYSYMBOL_UnaryOp = 65,                   /* UnaryOp  */
  YYSYMBOL_SelfOp = 66,                    /* SelfOp  */
  YYSYMBOL_FuncRParams = 67,               /* FuncRParams  */
  YYSYMBOL_MulExp = 68,                    /* MulExp  */
  YYSYMBOL_AddExp = 69,                    /* AddExp  */
  YYSYMBOL_RelExp = 70,                    /* RelExp  */
  YYSYMBOL_EqExp = 71,                     /* EqExp  */
  YYSYMBOL_LAndExp = 72,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 73,                    /* LOrExp  */
  YYSYMBOL_ConstExp = 74                   /* ConstExp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   236

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  92
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  154

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   275


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,     2,     2,    35,     2,     2,
      26,    27,    33,    30,    22,    31,     2,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    21,
      36,    23,    37,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    28,     2,    29,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    24,     2,    25,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    65,    65,    70,    77,    84,    91,    98,   103,   110,
     117,   125,   133,   142,   151,   159,   169,   178,   186,   193,
     201,   209,   217,   232,   248,   256,   265,   274,   325,   332,
     341,   349,   356,   363,   368,   376,   383,   390,   394,   398,
     408,   412,   420,   429,   438,   446,   454,   465,   474,   481,
     488,   495,   503,   510,   518,   526,   535,   543,   551,   560,
     566,   574,   581,   589,   598,   610,   622,   627,   632,   637,
     642,   648,   656,   664,   671,   679,   687,   695,   702,   710,
     718,   725,   733,   741,   749,   757,   764,   772,   781,   788,
     796,   803,   811
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "IDENT", "IF",
  "ELSE", "WHILE", "BREAK", "CONT", "RET", "T_INT", "T_VOID", "INCR",
  "DECR", "GE", "LE", "EQ", "NE", "AND", "OR", "';'", "','", "'='", "'{'",
  "'}'", "'('", "')'", "'['", "']'", "'+'", "'-'", "'!'", "'*'", "'/'",
  "'%'", "'<'", "'>'", "$accept", "Input", "CompUnit", "Decl", "BType",
  "VarDecl", "VarDefList", "VarDef", "InitVal", "InitValList", "FuncDef",
  "FuncFParams", "FuncFParam", "ArrayIndexList", "Block", "BlockItemList",
  "BlockItem", "Stmt", "MatchedStmt", "OpenStmt", "SimpleStmt", "Exp",
  "Cond", "LVal", "PrimaryExp", "Number", "UnaryExp", "UnaryOp", "SelfOp",
  "FuncRParams", "MulExp", "AddExp", "RelExp", "EqExp", "LAndExp",
  "LOrExp", "ConstExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-138)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       8,  -138,  -138,    11,     8,  -138,    38,  -138,  -138,  -138,
    -138,  -138,    -2,    46,  -138,   142,     1,   166,     2,  -138,
      72,  -138,    36,  -138,  -138,    19,   204,  -138,  -138,  -138,
    -138,  -138,    60,  -138,  -138,  -138,   204,    76,    21,    61,
       0,    79,    71,    89,    42,   110,     7,  -138,  -138,  -138,
      90,   142,   204,    25,  -138,   173,    92,  -138,  -138,    50,
      94,  -138,  -138,    95,  -138,   204,   204,   204,   204,   204,
     204,   204,   204,   204,   204,   204,   204,   204,  -138,  -138,
    -138,    95,     8,    42,  -138,  -138,    96,  -138,  -138,    30,
     142,  -138,  -138,  -138,  -138,  -138,    21,    21,    61,    61,
      61,    61,     0,     0,    79,    71,    74,    92,  -138,  -138,
    -138,   204,  -138,  -138,    98,   100,   106,   109,   180,  -138,
    -138,  -138,    72,  -138,  -138,  -138,  -138,  -138,  -138,   118,
       4,  -138,   204,   204,  -138,  -138,  -138,   119,  -138,   204,
     116,   117,    89,  -138,   126,   128,   128,  -138,  -138,   144,
    -138,   128,  -138,  -138
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     8,     9,     0,     2,     5,     0,     7,     6,     1,
       3,     4,    14,     0,    12,     0,     0,     0,    13,    10,
       0,    59,    54,    69,    70,     0,     0,    66,    67,    68,
      16,    17,    57,    60,    58,    73,     0,     0,    77,    80,
      85,    88,    90,    52,     0,     0,     0,    24,    28,    92,
       0,     0,     0,    14,    11,     0,    55,    18,    20,     0,
       0,    65,    63,    54,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    32,    33,
      22,    26,     0,     0,    29,    15,     0,    61,    71,     0,
       0,    19,    56,    74,    75,    76,    78,    79,    84,    83,
      81,    82,    86,    87,    89,    91,     0,    27,    25,    23,
      30,     0,    62,    21,     0,     0,     0,     0,     0,    32,
      31,    35,     0,    46,    34,    36,    37,    38,    40,     0,
      57,    72,     0,     0,    48,    49,    50,     0,    45,     0,
       0,     0,    53,    51,     0,     0,     0,    43,    41,    37,
      47,     0,    39,    42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -138,  -138,  -138,    -3,   -13,  -138,  -138,   131,   -20,  -138,
     149,  -138,    66,   -16,   -37,  -138,  -138,   -38,  -137,     6,
    -138,   -17,  -138,   -35,  -138,  -138,   -26,  -138,   -28,  -138,
      44,   -12,    43,    85,    86,    29,   112
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,     4,     5,     6,     7,    13,    14,    30,    59,
       8,    46,    47,    18,   123,   106,   124,   125,   126,   127,
     128,    31,   141,    32,    33,    34,    35,    36,    37,    89,
      38,    39,    40,    41,    42,    43,    50
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      49,    10,    64,    45,    61,    58,    56,    80,   149,    60,
      62,     9,     1,     2,   152,    70,    71,    23,    24,     1,
       2,    15,    21,    22,    16,    51,    17,   139,    44,    82,
      52,    85,    23,    24,    83,    49,    72,    73,    88,    93,
      94,    95,    12,    25,    57,    26,   109,    56,    15,    27,
      28,    29,   111,    17,    65,    66,    67,   112,    98,    99,
     100,   101,    55,    78,    17,   107,    79,    19,    20,    45,
     113,   130,    90,    23,    24,    91,    53,    21,    22,   114,
      63,   115,   116,   117,   118,     1,     2,    23,    24,   129,
      76,    68,    69,   122,   131,   119,    74,    75,    79,   120,
      26,   137,    61,   121,    27,    28,    29,   148,   150,    77,
     130,   130,    96,    97,    81,   140,   130,   102,   103,    84,
      52,    92,   144,    17,   132,   110,   133,   134,   129,   129,
     135,    21,    22,   114,   129,   115,   116,   117,   118,   138,
     143,    23,    24,   145,   146,    21,    22,   147,   108,   119,
     151,    54,    79,    11,    26,    23,    24,   153,    27,    28,
      29,   104,   142,   105,    86,     0,    25,     0,    26,    21,
      22,     0,    27,    28,    29,     0,    21,    22,     0,    23,
      24,     0,     0,    21,    22,     0,    23,    24,     0,     0,
       0,     0,    26,    23,    24,    48,    27,    28,    29,    26,
      87,   136,     0,    27,    28,    29,    26,    21,    22,     0,
      27,    28,    29,     0,     0,     0,     0,    23,    24,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      26,     0,     0,     0,    27,    28,    29
};

static const yytype_int16 yycheck[] =
{
      17,     4,    37,    16,    32,    25,    22,    44,   145,    26,
      36,     0,    11,    12,   151,    15,    16,    13,    14,    11,
      12,    23,     3,     4,    26,    23,    28,    23,    27,    22,
      28,    51,    13,    14,    27,    52,    36,    37,    55,    65,
      66,    67,     4,    24,    25,    26,    83,    63,    23,    30,
      31,    32,    22,    28,    33,    34,    35,    27,    70,    71,
      72,    73,    26,    21,    28,    81,    24,    21,    22,    82,
      90,   106,    22,    13,    14,    25,     4,     3,     4,     5,
       4,     7,     8,     9,    10,    11,    12,    13,    14,   106,
      19,    30,    31,   106,   111,    21,    17,    18,    24,    25,
      26,   118,   130,   106,    30,    31,    32,   145,   146,    20,
     145,   146,    68,    69,     4,   132,   151,    74,    75,    29,
      28,    27,   139,    28,    26,    29,    26,    21,   145,   146,
      21,     3,     4,     5,   151,     7,     8,     9,    10,    21,
      21,    13,    14,    27,    27,     3,     4,    21,    82,    21,
       6,    20,    24,     4,    26,    13,    14,   151,    30,    31,
      32,    76,   133,    77,    52,    -1,    24,    -1,    26,     3,
       4,    -1,    30,    31,    32,    -1,     3,     4,    -1,    13,
      14,    -1,    -1,     3,     4,    -1,    13,    14,    -1,    -1,
      -1,    -1,    26,    13,    14,    29,    30,    31,    32,    26,
      27,    21,    -1,    30,    31,    32,    26,     3,     4,    -1,
      30,    31,    32,    -1,    -1,    -1,    -1,    13,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    -1,    30,    31,    32
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    11,    12,    39,    40,    41,    42,    43,    48,     0,
      41,    48,     4,    44,    45,    23,    26,    28,    51,    21,
      22,     3,     4,    13,    14,    24,    26,    30,    31,    32,
      46,    59,    61,    62,    63,    64,    65,    66,    68,    69,
      70,    71,    72,    73,    27,    42,    49,    50,    29,    59,
      74,    23,    28,     4,    45,    26,    51,    25,    46,    47,
      59,    66,    64,     4,    61,    33,    34,    35,    30,    31,
      15,    16,    36,    37,    17,    18,    19,    20,    21,    24,
      52,     4,    22,    27,    29,    46,    74,    27,    59,    67,
      22,    25,    27,    64,    64,    64,    68,    68,    69,    69,
      69,    69,    70,    70,    71,    72,    53,    51,    50,    52,
      29,    22,    27,    46,     5,     7,     8,     9,    10,    21,
      25,    41,    42,    52,    54,    55,    56,    57,    58,    59,
      61,    59,    26,    26,    21,    21,    21,    59,    21,    23,
      59,    60,    73,    21,    59,    27,    27,    21,    55,    56,
      55,     6,    56,    57
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    40,    40,    40,    40,    41,    42,    42,
      43,    44,    44,    45,    45,    45,    45,    46,    46,    46,
      47,    47,    48,    48,    49,    49,    50,    50,    51,    51,
      51,    52,    52,    53,    53,    54,    54,    55,    55,    56,
      56,    57,    57,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    59,    60,    61,    61,    62,    62,    62,    63,
      64,    64,    64,    64,    64,    64,    65,    65,    65,    66,
      66,    67,    67,    68,    68,    68,    68,    69,    69,    69,
      70,    70,    70,    70,    70,    71,    71,    71,    72,    72,
      73,    73,    74
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     1,     1,     1,
       3,     3,     1,     2,     1,     4,     3,     1,     2,     3,
       1,     3,     5,     6,     1,     3,     2,     3,     2,     3,
       4,     3,     1,     0,     2,     1,     1,     1,     1,     7,
       1,     5,     7,     4,     1,     2,     1,     5,     2,     2,
       2,     3,     1,     1,     1,     2,     3,     1,     1,     1,
       1,     3,     4,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     3,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       1,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (root, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, root); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, std::unique_ptr<AST_Base> &root)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (root);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, std::unique_ptr<AST_Base> &root)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, root);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, std::unique_ptr<AST_Base> &root)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], root);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, root); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, std::unique_ptr<AST_Base> &root)
{
  YY_USE (yyvaluep);
  YY_USE (root);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (std::unique_ptr<AST_Base> &root)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Input: CompUnit  */
#line 66 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"Input : CompUnit"<<endl;
                    root=unique_ptr<AST_CompUnit>((AST_CompUnit*)((yyvsp[0].ast_baseVal)));
                }
#line 1278 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 3: /* CompUnit: CompUnit Decl  */
#line 71 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"CompUnit : CompUnit Decl"<<endl;
                    auto ptr=(AST_CompUnit *)((yyvsp[-1].ast_baseVal));
                    ptr->list_decl.push_back(unique_ptr<AST_Base>((yyvsp[0].ast_baseVal)));
                    (yyval.ast_baseVal)=ptr; 
                }
#line 1289 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 4: /* CompUnit: CompUnit FuncDef  */
#line 78 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"CompUnit : CompUnit FuncDef"<<endl;
                    auto ptr=(AST_CompUnit *)((yyvsp[-1].ast_baseVal));
                    ptr->list_func.push_back(unique_ptr<AST_Base>((yyvsp[0].ast_baseVal)));
                    (yyval.ast_baseVal)=ptr;
                }
#line 1300 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 5: /* CompUnit: Decl  */
#line 85 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"CompUnit : Decl"<<endl;
                    auto ptr=new AST_CompUnit();
                    ptr->list_decl.push_back(unique_ptr<AST_Base>((yyvsp[0].ast_baseVal)));
                    (yyval.ast_baseVal)=ptr;
                }
#line 1311 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 6: /* CompUnit: FuncDef  */
#line 92 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"CompUnit : FuncDef"<<endl;
                    auto ptr=new AST_CompUnit();
                    ptr->list_func.push_back(unique_ptr<AST_Base>((yyvsp[0].ast_baseVal)));
                    (yyval.ast_baseVal)=ptr;
                }
#line 1322 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 7: /* Decl: VarDecl  */
#line 99 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"Decl : VarDecl"<<endl;
                    (yyval.ast_baseVal)=(yyvsp[0].ast_baseVal);
                }
#line 1331 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 8: /* BType: T_INT  */
#line 104 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"BType : T_INT"<<endl;
                    auto btype=new string("int");
                    //auto btype=unique_ptr<string>(tmp);
                    (yyval.str_val)=btype;
                }
#line 1342 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 9: /* BType: T_VOID  */
#line 111 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"BType : T_VOID"<<endl;
                    auto btype=new string("void");
                    //auto btype=unique_ptr<string>(tmp);
                    (yyval.str_val)=btype;
                }
#line 1353 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 10: /* VarDecl: BType VarDefList ';'  */
#line 118 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"VarDecl : BType VarDefList ';'"<<endl;
                    auto btype=unique_ptr<string>((yyvsp[-2].str_val));
                    auto varDefList=unique_ptr<AST_Vec>((yyvsp[-1].ast_vecVal));
                    auto ptr=new AST_VarDecl(btype,varDefList);
                    (yyval.ast_baseVal)=ptr;
                }
#line 1365 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 11: /* VarDefList: VarDefList ',' VarDef  */
#line 126 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"VarDefList  : VarDefList ',' VarDef"<<endl;
                    auto ptr=(yyvsp[-2].ast_vecVal);
                    auto varDef=unique_ptr<AST_Base>((yyvsp[0].ast_baseVal));
                    ptr->push(varDef);
                    (yyval.ast_vecVal)=ptr;
                }
#line 1377 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 12: /* VarDefList: VarDef  */
#line 134 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"VarDefList  : VarDefList ',' VarDef"<<endl;
                    auto varDef=unique_ptr<AST_Base>((yyvsp[0].ast_baseVal));
                    auto ptr=new AST_Vec();
                    ptr->push(varDef);
                    (yyval.ast_vecVal)=ptr;
                }
#line 1389 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 13: /* VarDef: IDENT ArrayIndexList  */
#line 143 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"VarDef : IDENT ArrayIndexList"<<endl;
                    auto ptr=new AST_VarDef();
                    ptr->tag=AST_VarDef::ARRAY;
                    ptr->ident=unique_ptr<string>((yyvsp[-1].id_val).id);
                    ptr->arrayIndexList=unique_ptr<AST_Vec>((yyvsp[0].ast_vecVal));
                    (yyval.ast_baseVal)=ptr;
                }
#line 1402 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 14: /* VarDef: IDENT  */
#line 152 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"VarDef : IDENT"<<endl;
                    auto ptr=new AST_VarDef();
                    ptr->tag=AST_VarDef::VARIABLE;
                    ptr->ident=unique_ptr<string>((yyvsp[0].id_val).id);
                    (yyval.ast_baseVal)=ptr;
                }
#line 1414 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 15: /* VarDef: IDENT ArrayIndexList '=' InitVal  */
#line 160 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"VarDef IDENT ArrayIndexList '=' InitVal"<<endl;
                    auto ptr=new AST_VarDef();
                    ptr->tag=AST_VarDef::ARRAY;
                    ptr->ident=unique_ptr<string>((yyvsp[-3].id_val).id);
                    ptr->arrayIndexList=unique_ptr<AST_Vec>((yyvsp[-2].ast_vecVal));
                    ptr->initVal=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    (yyval.ast_baseVal)=ptr;
                }
#line 1428 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 16: /* VarDef: IDENT '=' InitVal  */
#line 170 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"VarDef : IDENT '=' InitVal"<<endl;
                    auto ptr=new AST_VarDef();
                    ptr->tag=AST_VarDef::VARIABLE;
                    ptr->ident=unique_ptr<string>((yyvsp[-2].id_val).id);
                    ptr->initVal=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    (yyval.ast_baseVal)=ptr;
                }
#line 1441 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 17: /* InitVal: Exp  */
#line 179 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"InitVal : Exp"<<endl;
                    auto ptr=new AST_Initial();
                    ptr->tag=AST_Initial::EXP;
                    ptr->exp=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    (yyval.ast_expVal)=ptr;
                }
#line 1453 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 18: /* InitVal: '{' '}'  */
#line 187 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"InitVal : {}"<<endl;
                    auto ptr=new AST_Initial();
                    ptr->tag=AST_Initial::INITVALLIST;
                    (yyval.ast_expVal)=ptr;
                }
#line 1464 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 19: /* InitVal: '{' InitValList '}'  */
#line 194 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"InitVal : '{' InitValList '}'"<<endl;
                    auto ptr=new AST_Initial();
                    ptr->tag=AST_Initial::INITVALLIST;
                    ptr->initValList=unique_ptr<AST_Vec>((yyvsp[-1].ast_vecVal));
                    (yyval.ast_expVal)=ptr;
                }
#line 1476 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 20: /* InitValList: InitVal  */
#line 202 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"InitValList :  InitVal"<<endl;
                    auto initVal=unique_ptr<AST_Base>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_Vec();
                    ptr->push(initVal);
                    (yyval.ast_vecVal)=ptr;
                }
#line 1488 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 21: /* InitValList: InitValList ',' InitVal  */
#line 210 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"InitValList : InitValList ',' InitVal"<<endl;
                    auto initVal=unique_ptr<AST_Base>((yyvsp[0].ast_expVal));
                    auto ptr=(AST_Vec*)(yyvsp[-2].ast_vecVal);
                    ptr->push(initVal);
                    (yyval.ast_vecVal)=ptr;
                }
#line 1500 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 22: /* FuncDef: BType IDENT '(' ')' Block  */
#line 218 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"FuncDef : BType IDENT '(' ')' Block"<<endl;
                    auto ptr=new AST_FuncDef();
                    auto tmp=(AST_Block*)((yyvsp[0].ast_baseVal));
                    if(tmp->is_null)
                        ptr->tag=AST_FuncDef::DECL_NOPARAM;
                    else
                        ptr->tag=AST_FuncDef::DEF_NOPARAM;
                    ptr->func_type=unique_ptr<string>((yyvsp[-4].str_val));
                    ptr->func_name=unique_ptr<string>((yyvsp[-3].id_val).id);
                    cout<<"函数名："+*(ptr->func_name)<<endl;
                    ptr->func_block=unique_ptr<AST_Base>((yyvsp[0].ast_baseVal));
                    (yyval.ast_baseVal)=ptr;
                }
#line 1519 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 23: /* FuncDef: BType IDENT '(' FuncFParams ')' Block  */
#line 233 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"FuncDef : BType IDENT '(' FuncFParams ')' Block"<<endl;
                    auto ptr=new AST_FuncDef();
                    auto tmp=(AST_Block*)((yyvsp[0].ast_baseVal));
                    if(tmp->is_null)
                        ptr->tag=AST_FuncDef::DECL_PARAM;
                    else
                        ptr->tag=AST_FuncDef::DEF_PARAM;
                    ptr->func_type=unique_ptr<string>((yyvsp[-5].str_val));
                    ptr->func_name=unique_ptr<string>((yyvsp[-4].id_val).id);
                    cout<<"函数名："+*(ptr->func_name)<<endl;
                    ptr->func_params=unique_ptr<AST_Vec>((yyvsp[-2].ast_vecVal));
                    ptr->func_block=unique_ptr<AST_Base>((yyvsp[0].ast_baseVal));
                    (yyval.ast_baseVal)=ptr;
                }
#line 1539 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 24: /* FuncFParams: FuncFParam  */
#line 249 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"FuncFParams : FuncFParam"<<endl;
                    auto param=unique_ptr<AST_Base>((yyvsp[0].ast_baseVal));
                    auto ptr=new AST_Vec();
                    ptr->push(param);
                    (yyval.ast_vecVal)=ptr;
                }
#line 1551 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 25: /* FuncFParams: FuncFParams ',' FuncFParam  */
#line 257 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"FuncFParams : FuncFParams ',' FuncFParam"<<endl;
                    auto param=unique_ptr<AST_Base>((yyvsp[0].ast_baseVal));
                    auto ptr=(yyvsp[-2].ast_vecVal);
                    ptr->push(param);
                    (yyval.ast_vecVal)=ptr;
                }
#line 1563 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 26: /* FuncFParam: BType IDENT  */
#line 266 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"FuncFParam  : BType IDENT"<<endl;
                    auto ptr=new AST_FuncFParam();
                    ptr->tag=AST_FuncFParam::VARIABLE;
                    ptr->param_type=unique_ptr<string>((yyvsp[-1].str_val));
                    ptr->param_name=unique_ptr<string>((yyvsp[0].id_val).id);
                    (yyval.ast_baseVal)=ptr;
                }
#line 1576 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 27: /* FuncFParam: BType IDENT ArrayIndexList  */
#line 275 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"FuncFParam  : BType IDENT '[' ']'"<<endl;
                    auto ptr=new AST_FuncFParam();
                    ptr->tag=AST_FuncFParam::ARRAY;
                    ptr->param_type=unique_ptr<string>((yyvsp[-2].str_val));
                    ptr->param_name=unique_ptr<string>((yyvsp[-1].id_val).id);
                    ptr->ArrayIndexList=unique_ptr<AST_Vec>((yyvsp[0].ast_vecVal));
                    //ptr->is_zero=$3->is_zero;
                    (yyval.ast_baseVal)=ptr;
                }
#line 1591 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 28: /* ArrayIndexList: '[' ']'  */
#line 326 "D:/CompilerTools/code/minic/minic.y"
                    {
                        cout<<"ArrayIndexList : '['  ']'"<<endl;
                        auto ptr=new AST_Vec();
                        ptr->is_zero=true;
                        (yyval.ast_vecVal)=ptr;
                    }
#line 1602 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 29: /* ArrayIndexList: '[' ConstExp ']'  */
#line 333 "D:/CompilerTools/code/minic/minic.y"
                    {
                        cout<<"ArrayIndexList : '[' Exp ']'"<<endl;
                        auto exp=unique_ptr<AST_Base>((yyvsp[-1].ast_expVal));
                        auto ptr=new AST_Vec();
                        ptr->push(exp);
                        ptr->is_zero=false;
                        (yyval.ast_vecVal)=ptr;
                    }
#line 1615 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 30: /* ArrayIndexList: ArrayIndexList '[' ConstExp ']'  */
#line 342 "D:/CompilerTools/code/minic/minic.y"
                    {
                        cout<<"ArrayIndexList : ArrayIndexList '[' Exp ']'"<<endl;
                        auto ptr=(yyvsp[-3].ast_vecVal);
                        auto exp=unique_ptr<AST_Base>((yyvsp[-1].ast_expVal));
                        ptr->push(exp);
                        (yyval.ast_vecVal)=ptr;
                    }
#line 1627 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 31: /* Block: '{' BlockItemList '}'  */
#line 350 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout << "Block : '{' BlockItemList'}'" <<endl;
                    auto blocks=unique_ptr<AST_Vec>((yyvsp[-1].ast_vecVal));
                    auto ptr=new AST_Block(blocks);
                    (yyval.ast_baseVal)=ptr;
                }
#line 1638 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 32: /* Block: ';'  */
#line 357 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"Block : ;"<<endl;
                    auto ptr=new AST_Block();
                    (yyval.ast_baseVal)=ptr;
                }
#line 1648 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 33: /* BlockItemList: %empty  */
#line 363 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<< "BlockItemList   :"<<endl;
                    auto ptr=new AST_Vec();
                    (yyval.ast_vecVal)=ptr;
                }
#line 1658 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 34: /* BlockItemList: BlockItemList BlockItem  */
#line 369 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<< "BlockItemList   : BlockItemList BlockItem" <<endl;
                    auto blocks=(yyvsp[-1].ast_vecVal);
                    auto item=unique_ptr<AST_Base>((yyvsp[0].ast_baseVal));
                    blocks->push(item);
                    (yyval.ast_vecVal)=blocks;
                }
#line 1670 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 35: /* BlockItem: Decl  */
#line 377 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<< "------BlockItem : Decl------"<<endl;
                    auto decl=unique_ptr<AST_Base>((yyvsp[0].ast_baseVal));
                    auto ptr=new AST_BlockItem(decl,false);
                    (yyval.ast_baseVal)=ptr;
                }
#line 1681 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 36: /* BlockItem: Stmt  */
#line 384 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<< "------BlockItem : Stmt------"<<endl;
                    auto stmt=unique_ptr<AST_Base>((yyvsp[0].ast_baseVal));
                    auto ptr=new AST_BlockItem(stmt,true);
                    (yyval.ast_baseVal)=ptr;
                }
#line 1692 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 37: /* Stmt: MatchedStmt  */
#line 390 "D:/CompilerTools/code/minic/minic.y"
                             {
                    cout<<"Stmt:MatchedStmt"<<endl;
                    (yyval.ast_baseVal)=(yyvsp[0].ast_baseVal);
                }
#line 1701 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 38: /* Stmt: OpenStmt  */
#line 394 "D:/CompilerTools/code/minic/minic.y"
                          {
                    cout<<"Stmt:OpenStmt"<<endl;
                    (yyval.ast_baseVal)=(yyvsp[0].ast_baseVal);
                }
#line 1710 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 39: /* MatchedStmt: IF '(' Exp ')' MatchedStmt ELSE MatchedStmt  */
#line 398 "D:/CompilerTools/code/minic/minic.y"
                                                             {
                    cout<<"MatchedStmt : IF '(' Exp ')' MatchedStmt ELSE MatchedStmt"<<endl;
                    auto ptr =new AST_Stmt();
                    ptr->tag=AST_Stmt::IF;
                    ptr->cond=unique_ptr<AST_Exp>((yyvsp[-4].ast_expVal));
                    ptr->body=unique_ptr<AST_Base>((yyvsp[-2].ast_baseVal));
                    ptr->else_body=unique_ptr<AST_Base>((yyvsp[0].ast_baseVal));
                    (yyval.ast_baseVal)=ptr;
                }
#line 1724 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 40: /* MatchedStmt: SimpleStmt  */
#line 408 "D:/CompilerTools/code/minic/minic.y"
                          {
                    cout<<"MatchedStmt : SimpleStmt"<<endl;
                    (yyval.ast_baseVal)=(yyvsp[0].ast_baseVal);
                }
#line 1733 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 41: /* OpenStmt: IF '(' Exp ')' Stmt  */
#line 412 "D:/CompilerTools/code/minic/minic.y"
                                      {
                    cout<<"OpenStmt : IF '(' Exp ')' Stmt"<<endl;
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::IF;
                    ptr->cond=unique_ptr<AST_Exp>((yyvsp[-2].ast_expVal));
                    ptr->body=unique_ptr<AST_Base>((yyvsp[0].ast_baseVal));
                    (yyval.ast_baseVal)=ptr;
                }
#line 1746 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 42: /* OpenStmt: IF '(' Exp ')' MatchedStmt ELSE OpenStmt  */
#line 420 "D:/CompilerTools/code/minic/minic.y"
                                                           {
                    cout<<"OpenStmt : IF '(' Exp ')' MatchedStmt ELSE OpenStmt"<<endl;
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::IF;
                    ptr->cond=unique_ptr<AST_Exp>((yyvsp[-4].ast_expVal));
                    ptr->body=unique_ptr<AST_Base>((yyvsp[-2].ast_baseVal));
                    ptr->else_body=unique_ptr<AST_Base>((yyvsp[0].ast_baseVal));
                    (yyval.ast_baseVal)=ptr;
                }
#line 1760 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 43: /* SimpleStmt: LVal '=' Exp ';'  */
#line 430 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"SimpleStmt : LVal '=' Exp ';'"<<endl;
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::ASSIGN;
                    ptr->lval=unique_ptr<AST_Exp>((yyvsp[-3].ast_expVal));
                    ptr->exp=unique_ptr<AST_Exp>((yyvsp[-1].ast_expVal));
                    (yyval.ast_baseVal)=ptr;
                }
#line 1773 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 44: /* SimpleStmt: ';'  */
#line 439 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"SimpleStmt : ';'"<<endl;
                    //TODO ????????????????????
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::EXP;
                    (yyval.ast_baseVal)=ptr;
                }
#line 1785 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 45: /* SimpleStmt: Exp ';'  */
#line 447 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"SimpleStmt : Exp ';'"<<endl;
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::EXP;
                    ptr->exp=unique_ptr<AST_Exp>((yyvsp[-1].ast_expVal));
                    (yyval.ast_baseVal)=ptr;
                }
#line 1797 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 46: /* SimpleStmt: Block  */
#line 455 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"SimpleStmt : Block"<<endl;
                    //TODO ????????????????????
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::BLOCK;
                    //修改了类型
                    ptr->block=unique_ptr<AST_Base>((yyvsp[0].ast_baseVal));
                    (yyval.ast_baseVal)=ptr;

                }
#line 1812 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 47: /* SimpleStmt: WHILE '(' Cond ')' Stmt  */
#line 466 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"SimpleStmt : WHILE '(' Cond ')' Stmt"<<endl;
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::WHILE;
                    ptr->cond=unique_ptr<AST_Exp>((yyvsp[-2].ast_expVal));
                    ptr->body=unique_ptr<AST_Base>((yyvsp[0].ast_baseVal));
                    (yyval.ast_baseVal)=ptr;
                }
#line 1825 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 48: /* SimpleStmt: BREAK ';'  */
#line 475 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"BREAK ';'"<<endl;
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::BREAK;
                    (yyval.ast_baseVal)=ptr;
                }
#line 1836 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 49: /* SimpleStmt: CONT ';'  */
#line 482 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"CONT ';'"<<endl;
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::CONTINUE;
                    (yyval.ast_baseVal)=ptr;
                }
#line 1847 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 50: /* SimpleStmt: RET ';'  */
#line 489 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"RET ';'"<<endl;
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::RETURN;
                    (yyval.ast_baseVal)=ptr;
                }
#line 1858 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 51: /* SimpleStmt: RET Exp ';'  */
#line 496 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"RET Exp ';'"<<endl;
                    auto ptr=new AST_Stmt();
                    ptr->tag=AST_Stmt::RETURN;
                    ptr->exp=unique_ptr<AST_Exp>((yyvsp[-1].ast_expVal));
                    (yyval.ast_baseVal)=ptr;
                }
#line 1870 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 52: /* Exp: LOrExp  */
#line 504 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"Exp : LOrExp"<<endl;
                    auto lorExp=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_Exp1(lorExp);
                    (yyval.ast_expVal)=ptr;
                }
#line 1881 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 53: /* Cond: LOrExp  */
#line 511 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"Cond :LOrExp"<<endl;
                    //!!!需新建cond类
                    auto lorExp=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_Cond(lorExp);
                    (yyval.ast_expVal)=ptr;
                }
#line 1893 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 54: /* LVal: IDENT  */
#line 519 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"LVal : IDENT"<<endl;
                    auto ptr=new AST_LVal();
                    ptr->tag=AST_LVal::VARIABLE;
                    ptr->ident=unique_ptr<string>((yyvsp[0].id_val).id);
                    (yyval.ast_expVal)=ptr;
                }
#line 1905 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 55: /* LVal: IDENT ArrayIndexList  */
#line 527 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"LVal : IDENT ArrayIndexList"<<endl;
                    auto ptr=new AST_LVal();
                    ptr->tag=AST_LVal::ARRAY;
                    ptr->exps=unique_ptr<AST_Vec>((yyvsp[0].ast_vecVal));
                    ptr->ident=unique_ptr<string>((yyvsp[-1].id_val).id);
                    (yyval.ast_expVal)=ptr;
                }
#line 1918 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 56: /* PrimaryExp: '(' Exp ')'  */
#line 536 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"PrimaryExp  : '(' Exp ')'"<<endl;
                    auto ptr=new AST_Primary();
                    ptr->tag=AST_Primary::EXP;
                    ptr->exp=unique_ptr<AST_Exp>((yyvsp[-1].ast_expVal));
                    (yyval.ast_expVal)=ptr;
                }
#line 1930 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 57: /* PrimaryExp: LVal  */
#line 544 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"PrimaryExp  : LVal"<<endl;
                    auto ptr=new AST_Primary();
                    ptr->tag=AST_Primary::LVAL;
                    ptr->lval=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    (yyval.ast_expVal)=ptr;
                }
#line 1942 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 58: /* PrimaryExp: Number  */
#line 552 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"PrimaryExp  : Number"<<endl;
                    auto ptr=new AST_Primary();
                    ptr->tag=AST_Primary::NUM;
                    ptr->int_val= (yyvsp[0].val);
                    (yyval.ast_expVal)=ptr;

                }
#line 1955 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 59: /* Number: NUM  */
#line 561 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"Number : NUM"<<endl;
                    (yyval.val)=(yyvsp[0].int_val).val;
                }
#line 1964 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 60: /* UnaryExp: PrimaryExp  */
#line 567 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"UnaryExp :PrimaryExp"<<endl;
                    auto ptr=new AST_Unary();
                    ptr->tag=AST_Unary::ONLY_P;
                    ptr->primaryExp=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    (yyval.ast_expVal)=ptr;
                }
#line 1976 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 61: /* UnaryExp: IDENT '(' ')'  */
#line 575 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"UnaryExp : IDENT ( ) "<<endl;
                    auto funcName = unique_ptr<string>((yyvsp[-2].id_val).id);
                    auto ptr=new AST_FuncCall(funcName);
                    (yyval.ast_expVal)=ptr;
                }
#line 1987 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 62: /* UnaryExp: IDENT '(' FuncRParams ')'  */
#line 582 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"UnaryExp : IDENT ( FuncRParams )"<<endl;
                    auto funcName = unique_ptr<string>((yyvsp[-3].id_val).id);
                    auto funcRParams = unique_ptr<AST_Vec>((yyvsp[-1].ast_vecVal));
                    auto ptr=new AST_FuncCall(funcName,funcRParams);
                    (yyval.ast_expVal)=ptr;
                }
#line 1999 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 63: /* UnaryExp: UnaryOp UnaryExp  */
#line 590 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"UnaryExp :UnaryOp UnaryExp"<<endl;
                    auto ptr=new AST_Unary();
                    ptr->tag=AST_Unary::UU;
                    ptr->op=(yyvsp[-1].ast_op_type);
                    ptr->unaryExp=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    (yyval.ast_expVal)=ptr;
                }
#line 2012 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 64: /* UnaryExp: SelfOp LVal  */
#line 599 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"Unary : SelfOp LVal"<<endl;
                    auto ptr=new AST_Unary();
                    ptr->tag=AST_Unary::SELF;
                    if((yyvsp[-1].ast_op_type)==AST_OP_INCR)
                        ptr->op=AST_OP_LINC;
                    else
                        ptr->op=AST_OP_LDEC;
                    ptr->selfExp=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    (yyval.ast_expVal)=ptr;
                }
#line 2028 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 65: /* UnaryExp: LVal SelfOp  */
#line 611 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"Unary : LVal SelfOp"<<endl;
                    auto ptr=new AST_Unary();
                    ptr->tag=AST_Unary::SELF;
                    if((yyvsp[0].ast_op_type)==AST_OP_INCR)
                        ptr->op=AST_OP_RINC;
                    else
                        ptr->op=AST_OP_RDEC;
                    ptr->selfExp=unique_ptr<AST_Exp>((yyvsp[-1].ast_expVal));
                    (yyval.ast_expVal)=ptr;
                }
#line 2044 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 66: /* UnaryOp: '+'  */
#line 623 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"UnaryOp :'+'"<<endl;
                    (yyval.ast_op_type)=AST_OP_OPT;
                }
#line 2053 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 67: /* UnaryOp: '-'  */
#line 628 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"UnaryOp :'-'"<<endl;
                    (yyval.ast_op_type)=AST_OP_NEG;
                }
#line 2062 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 68: /* UnaryOp: '!'  */
#line 633 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"UnaryOp :'!'"<<endl;
                    (yyval.ast_op_type)=AST_OP_NOT;
                }
#line 2071 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 69: /* SelfOp: INCR  */
#line 638 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"SelfOp : INCR"<<endl;
                    (yyval.ast_op_type)=AST_OP_INCR;
                }
#line 2080 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 70: /* SelfOp: DECR  */
#line 643 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"SelfOp : DECR"<<endl;
                    (yyval.ast_op_type)=AST_OP_DECR;
                }
#line 2089 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 71: /* FuncRParams: Exp  */
#line 649 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"FuncRParams : Exp"<<endl;
                    auto paramVec=new AST_Vec();
                    auto exp=unique_ptr<AST_Base>((yyvsp[0].ast_expVal));
                    paramVec->push(exp);
                    (yyval.ast_vecVal)=paramVec;
                }
#line 2101 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 72: /* FuncRParams: FuncRParams ',' Exp  */
#line 657 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"FuncRParams : FuncRParams , Exp"<<endl;
                    auto paramVec = (yyvsp[-2].ast_vecVal);
                    auto exp=unique_ptr<AST_Base>((yyvsp[0].ast_expVal));
                    paramVec->push(exp);
                    (yyval.ast_vecVal)=paramVec; //???
                }
#line 2113 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 73: /* MulExp: UnaryExp  */
#line 665 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"MulExp :UnaryExp"<<endl;
                    auto unaryExp=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_MulExp(unaryExp);
                    (yyval.ast_expVal)=ptr;
                }
#line 2124 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 74: /* MulExp: MulExp '*' UnaryExp  */
#line 672 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"MulExp :MulExp '*' UnaryExp"<<endl;
                    auto mulExp=unique_ptr<AST_Exp>((yyvsp[-2].ast_expVal));
                    auto unaryExp=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_MulExp(AST_OP_MUL,mulExp,unaryExp);
                    (yyval.ast_expVal)=ptr;
                }
#line 2136 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 75: /* MulExp: MulExp '/' UnaryExp  */
#line 680 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"MulExp :MulExp '/' UnaryExp"<<endl;
                    auto mulExp=unique_ptr<AST_Exp>((yyvsp[-2].ast_expVal));
                    auto unaryExp=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_MulExp(AST_OP_DIV,mulExp,unaryExp);
                    (yyval.ast_expVal)=ptr;
                }
#line 2148 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 76: /* MulExp: MulExp '%' UnaryExp  */
#line 688 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"MulExp :MulExp '%' UnaryExp"<<endl;
                    auto mulExp=unique_ptr<AST_Exp>((yyvsp[-2].ast_expVal));
                    auto unaryExp=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_MulExp(AST_OP_MOD,mulExp,unaryExp);
                    (yyval.ast_expVal)=ptr;
                }
#line 2160 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 77: /* AddExp: MulExp  */
#line 696 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"AddExp :MulExp "<<endl;
                    auto mul=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_AddExp(mul);
                    (yyval.ast_expVal)=ptr;
                }
#line 2171 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 78: /* AddExp: AddExp '+' MulExp  */
#line 703 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"AddExp :AddExp '+' MulExp"<<endl;
                    auto add=unique_ptr<AST_Exp>((yyvsp[-2].ast_expVal));
                    auto mul=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_AddExp(AST_OP_ADD,add,mul);
                    (yyval.ast_expVal)=ptr;
                }
#line 2183 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 79: /* AddExp: AddExp '-' MulExp  */
#line 711 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"AddExp :AddExp '-' MulExp"<<endl;
                    auto add=unique_ptr<AST_Exp>((yyvsp[-2].ast_expVal));
                    auto mul=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_AddExp(AST_OP_SUB,add,mul);
                    (yyval.ast_expVal)=ptr;
                }
#line 2195 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 80: /* RelExp: AddExp  */
#line 719 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"RelExp :AddExp"<<endl;
                    auto add=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_RelExp(add);
                    (yyval.ast_expVal)=ptr;
                }
#line 2206 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 81: /* RelExp: RelExp '<' AddExp  */
#line 726 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout <<"RelExp :RelExp '<' AddExp"<<endl;
                    auto rel=unique_ptr<AST_Exp>((yyvsp[-2].ast_expVal));
                    auto add=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_RelExp(AST_OP_LT,rel,add);
                    (yyval.ast_expVal)=ptr;
                }
#line 2218 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 82: /* RelExp: RelExp '>' AddExp  */
#line 734 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout <<"RelExp :RelExp '>' AddExp"<<endl;
                    auto rel=unique_ptr<AST_Exp>((yyvsp[-2].ast_expVal));
                    auto add=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_RelExp(AST_OP_GT,rel,add);
                    (yyval.ast_expVal)=ptr;
                }
#line 2230 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 83: /* RelExp: RelExp LE AddExp  */
#line 742 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout <<"RelExp :RelExp '<=' AddExp"<<endl;
                    auto rel=unique_ptr<AST_Exp>((yyvsp[-2].ast_expVal));
                    auto add=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_RelExp(AST_OP_LE,rel,add);
                    (yyval.ast_expVal)=ptr;
                }
#line 2242 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 84: /* RelExp: RelExp GE AddExp  */
#line 750 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout <<"RelExp :RelExp '>=' AddExp"<<endl;
                    auto rel=unique_ptr<AST_Exp>((yyvsp[-2].ast_expVal));
                    auto add=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_RelExp(AST_OP_GE,rel,add);
                    (yyval.ast_expVal)=ptr;
                }
#line 2254 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 85: /* EqExp: RelExp  */
#line 758 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"EqExp :RelExp"<<endl;
                    auto rel=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_EqExp(rel);
                    (yyval.ast_expVal)=ptr;
                }
#line 2265 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 86: /* EqExp: EqExp EQ RelExp  */
#line 765 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"EqExp :EqExp EQ RelExp"<<endl;
                    auto eq=unique_ptr<AST_Exp>((yyvsp[-2].ast_expVal));
                    auto rel=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_EqExp(AST_OP_EQ,eq,rel);
                    (yyval.ast_expVal)=ptr;
                }
#line 2277 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 87: /* EqExp: EqExp NE RelExp  */
#line 773 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"EqExp :EqExp NE RelExp"<<endl;
                    auto eq=unique_ptr<AST_Exp>((yyvsp[-2].ast_expVal));
                    auto rel=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_EqExp(AST_OP_NE,eq,rel);
                    (yyval.ast_expVal)=ptr;

                }
#line 2290 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 88: /* LAndExp: EqExp  */
#line 782 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"LAndExp :EqExp"<<endl;
                    auto eq=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_LAnd(eq);
                    (yyval.ast_expVal)=ptr;
                }
#line 2301 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 89: /* LAndExp: LAndExp AND EqExp  */
#line 789 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"LAndExp :LAndExp AND EqExp"<<endl;
                    auto land=unique_ptr<AST_Exp>((yyvsp[-2].ast_expVal));
                    auto eq=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_LAnd(land,eq);
                    (yyval.ast_expVal)=ptr;
                }
#line 2313 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 90: /* LOrExp: LAndExp  */
#line 797 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"LOrExp :LAndExp"<<endl;
                    auto land=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_LOr(land);
                    (yyval.ast_expVal)=ptr;
                }
#line 2324 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 91: /* LOrExp: LOrExp OR LAndExp  */
#line 804 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"LOrExp :LOrExp OR LAndExp"<<endl;
                    auto land=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto lor=unique_ptr<AST_Exp>((yyvsp[-2].ast_expVal));
                    auto ptr=new AST_LOr(lor,land);
                    (yyval.ast_expVal)=ptr;
                }
#line 2336 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;

  case 92: /* ConstExp: Exp  */
#line 812 "D:/CompilerTools/code/minic/minic.y"
                {
                    cout<<"ConstExp :Exp"<<endl;
                    auto Exp=unique_ptr<AST_Exp>((yyvsp[0].ast_expVal));
                    auto ptr=new AST_ConstExp(Exp);
                    (yyval.ast_expVal)=ptr;
                }
#line 2347 "D:/CompilerTools/code/minic/minic_yacc.cpp"
    break;


#line 2351 "D:/CompilerTools/code/minic/minic_yacc.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (root, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, root);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, root);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (root, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, root);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, root);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 819 "D:/CompilerTools/code/minic/minic.y"


// 语法识别错误要调用函数的定义
void yyerror(unique_ptr<AST_Base> &ast, const char *s) {
  cerr << "error: " << s << endl;
}
