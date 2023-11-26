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
#line 1 "parser.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <vector>
    #include <string.h>
    #include <queue>
    #include <set>

    #define add_tac($$, $1, $2, $3) {strcpy($$.type, $1.type);\
        sprintf($$.lexeme, get_temp().c_str());\
        string lt=string($1.type);\
        string rt=string($3.type);\
        if((lt == "CHAR" && rt == "INT") || (rt == "CHAR" && lt == "INT")){\
            strcpy($$.type, "INT");\
        }\
        else if((lt == "FLOAT" && rt == "INT") || (rt == "FLOAT" && lt == "INT")){\
            strcpy($$.type, "FLOAT");\
        }\
        else if((lt == "FLOAT" && rt == "FLOAT") || (lt == "INT" && rt == "INT") || (lt == "CHAR" && rt == "CHAR")){\
            strcpy($$.type, $1.type);\
        }\
        else{\
            strcpy($$.type, "STRING");\
        }}
    
    #include <iostream>
    #include <string>
    #include <unordered_map>
    #include<map>
    #include <stack>
    #include<algorithm>
    #include<fstream>

    using namespace std;

    void yyerror(const char *s);
    int yylex();
    int yywrap();
    int yytext();

    bool check_declaration(string variable);
    bool check_scope(string variable);
    bool multiple_declaration(string variable);
    bool is_reserved_word(string id);
    bool type_check(string type1, string type2);
    bool check_type(string l, string r);
    string get_temp();

    queue<string> free_temp;
    set<string> const_temps;
    void PrintStack(stack<int> s);

    struct var_info {
        string data_type;
        int scope;
        int size;   // for arrays
        int isArray;
        int line_number; 
        //string value;
    };

    vector<string> tac;
    map<string, string> temp_map;

    int variable_count = 0;
    int label_counter = 0;

    vector<string> sem_errors;

    int temp_index;
    int temp_label;

    stack<int> loop_continue, loop_break;
    stack<pair<string, vector<string>>> func_call_id;
    stack<int> scope_history;
    int scope_counter = 0;

    // for array declaration with initialization
    string curr_array;
    int arr_index=0;

    extern int countn;

    struct func_info{
        string return_type;
        int num_params;
        vector<string> param_types;
        unordered_map<string, struct var_info> symbol_table;
    };

    int has_return_stmt;

    unordered_map<string, struct func_info> func_table;
    unordered_map<string, string>string_info;
    string curr_func_name="global";
    vector<string> curr_func_param_type;

    vector<string> reserved = {"int", "float", "char", "bool","string", "void", "if", "elif", "else", "for", "while", "break", "continue", "main", "return", "switch", "case", "progin", "progout"};


#line 173 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INCLUDE = 258,                 /* INCLUDE  */
    HEADERFILE = 259,              /* HEADERFILE  */
    INT = 260,                     /* INT  */
    CHAR = 261,                    /* CHAR  */
    FLOAT = 262,                   /* FLOAT  */
    STRING = 263,                  /* STRING  */
    BOOL = 264,                    /* BOOL  */
    VOID = 265,                    /* VOID  */
    RETURN = 266,                  /* RETURN  */
    INT_NUM = 267,                 /* INT_NUM  */
    FLOAT_NUM = 268,               /* FLOAT_NUM  */
    ID = 269,                      /* ID  */
    LEFTSHIFT = 270,               /* LEFTSHIFT  */
    RIGHTSHIFT = 271,              /* RIGHTSHIFT  */
    LE = 272,                      /* LE  */
    GE = 273,                      /* GE  */
    EQ = 274,                      /* EQ  */
    NE = 275,                      /* NE  */
    GT = 276,                      /* GT  */
    LT = 277,                      /* LT  */
    AND = 278,                     /* AND  */
    OR = 279,                      /* OR  */
    NOT = 280,                     /* NOT  */
    ADD = 281,                     /* ADD  */
    SUBTRACT = 282,                /* SUBTRACT  */
    DIVIDE = 283,                  /* DIVIDE  */
    MULTIPLY = 284,                /* MULTIPLY  */
    MODULO = 285,                  /* MODULO  */
    BITAND = 286,                  /* BITAND  */
    BITOR = 287,                   /* BITOR  */
    NEGATION = 288,                /* NEGATION  */
    XOR = 289,                     /* XOR  */
    STR = 290,                     /* STR  */
    CHARACTER = 291,               /* CHARACTER  */
    CC = 292,                      /* CC  */
    OC = 293,                      /* OC  */
    CS = 294,                      /* CS  */
    OS = 295,                      /* OS  */
    CF = 296,                      /* CF  */
    OF = 297,                      /* OF  */
    COMMA = 298,                   /* COMMA  */
    COLON = 299,                   /* COLON  */
    SCOL = 300,                    /* SCOL  */
    OUTPUT = 301,                  /* OUTPUT  */
    INPUT = 302,                   /* INPUT  */
    SWITCH = 303,                  /* SWITCH  */
    CASE = 304,                    /* CASE  */
    BREAK = 305,                   /* BREAK  */
    DEFAULT = 306,                 /* DEFAULT  */
    IF = 307,                      /* IF  */
    ELIF = 308,                    /* ELIF  */
    ELSE = 309,                    /* ELSE  */
    WHILE = 310,                   /* WHILE  */
    FOR = 311,                     /* FOR  */
    CONTINUE = 312,                /* CONTINUE  */
    TYPEOF = 313,                  /* TYPEOF  */
    FLEN = 314,                    /* FLEN  */
    MAC = 315,                     /* MAC  */
    RESET = 316,                   /* RESET  */
    MACOP = 317,                   /* MACOP  */
    ASSIGN = 318                   /* ASSIGN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INCLUDE 258
#define HEADERFILE 259
#define INT 260
#define CHAR 261
#define FLOAT 262
#define STRING 263
#define BOOL 264
#define VOID 265
#define RETURN 266
#define INT_NUM 267
#define FLOAT_NUM 268
#define ID 269
#define LEFTSHIFT 270
#define RIGHTSHIFT 271
#define LE 272
#define GE 273
#define EQ 274
#define NE 275
#define GT 276
#define LT 277
#define AND 278
#define OR 279
#define NOT 280
#define ADD 281
#define SUBTRACT 282
#define DIVIDE 283
#define MULTIPLY 284
#define MODULO 285
#define BITAND 286
#define BITOR 287
#define NEGATION 288
#define XOR 289
#define STR 290
#define CHARACTER 291
#define CC 292
#define OC 293
#define CS 294
#define OS 295
#define CF 296
#define OF 297
#define COMMA 298
#define COLON 299
#define SCOL 300
#define OUTPUT 301
#define INPUT 302
#define SWITCH 303
#define CASE 304
#define BREAK 305
#define DEFAULT 306
#define IF 307
#define ELIF 308
#define ELSE 309
#define WHILE 310
#define FOR 311
#define CONTINUE 312
#define TYPEOF 313
#define FLEN 314
#define MAC 315
#define RESET 316
#define MACOP 317
#define ASSIGN 318

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 103 "parser.y"

    struct node { 
        char lexeme[100];
        int line_number;
        char type[100];
        char if_body[5];
        char elif_body[5];
		char else_body[5];
        char loop_body[5];
        char parentNext[5];
        char case_body[5];
        char id[5];
        char temp[5];
        int nParams;
    } node;

#line 369 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INCLUDE = 3,                    /* INCLUDE  */
  YYSYMBOL_HEADERFILE = 4,                 /* HEADERFILE  */
  YYSYMBOL_INT = 5,                        /* INT  */
  YYSYMBOL_CHAR = 6,                       /* CHAR  */
  YYSYMBOL_FLOAT = 7,                      /* FLOAT  */
  YYSYMBOL_STRING = 8,                     /* STRING  */
  YYSYMBOL_BOOL = 9,                       /* BOOL  */
  YYSYMBOL_VOID = 10,                      /* VOID  */
  YYSYMBOL_RETURN = 11,                    /* RETURN  */
  YYSYMBOL_INT_NUM = 12,                   /* INT_NUM  */
  YYSYMBOL_FLOAT_NUM = 13,                 /* FLOAT_NUM  */
  YYSYMBOL_ID = 14,                        /* ID  */
  YYSYMBOL_LEFTSHIFT = 15,                 /* LEFTSHIFT  */
  YYSYMBOL_RIGHTSHIFT = 16,                /* RIGHTSHIFT  */
  YYSYMBOL_LE = 17,                        /* LE  */
  YYSYMBOL_GE = 18,                        /* GE  */
  YYSYMBOL_EQ = 19,                        /* EQ  */
  YYSYMBOL_NE = 20,                        /* NE  */
  YYSYMBOL_GT = 21,                        /* GT  */
  YYSYMBOL_LT = 22,                        /* LT  */
  YYSYMBOL_AND = 23,                       /* AND  */
  YYSYMBOL_OR = 24,                        /* OR  */
  YYSYMBOL_NOT = 25,                       /* NOT  */
  YYSYMBOL_ADD = 26,                       /* ADD  */
  YYSYMBOL_SUBTRACT = 27,                  /* SUBTRACT  */
  YYSYMBOL_DIVIDE = 28,                    /* DIVIDE  */
  YYSYMBOL_MULTIPLY = 29,                  /* MULTIPLY  */
  YYSYMBOL_MODULO = 30,                    /* MODULO  */
  YYSYMBOL_BITAND = 31,                    /* BITAND  */
  YYSYMBOL_BITOR = 32,                     /* BITOR  */
  YYSYMBOL_NEGATION = 33,                  /* NEGATION  */
  YYSYMBOL_XOR = 34,                       /* XOR  */
  YYSYMBOL_STR = 35,                       /* STR  */
  YYSYMBOL_CHARACTER = 36,                 /* CHARACTER  */
  YYSYMBOL_CC = 37,                        /* CC  */
  YYSYMBOL_OC = 38,                        /* OC  */
  YYSYMBOL_CS = 39,                        /* CS  */
  YYSYMBOL_OS = 40,                        /* OS  */
  YYSYMBOL_CF = 41,                        /* CF  */
  YYSYMBOL_OF = 42,                        /* OF  */
  YYSYMBOL_COMMA = 43,                     /* COMMA  */
  YYSYMBOL_COLON = 44,                     /* COLON  */
  YYSYMBOL_SCOL = 45,                      /* SCOL  */
  YYSYMBOL_OUTPUT = 46,                    /* OUTPUT  */
  YYSYMBOL_INPUT = 47,                     /* INPUT  */
  YYSYMBOL_SWITCH = 48,                    /* SWITCH  */
  YYSYMBOL_CASE = 49,                      /* CASE  */
  YYSYMBOL_BREAK = 50,                     /* BREAK  */
  YYSYMBOL_DEFAULT = 51,                   /* DEFAULT  */
  YYSYMBOL_IF = 52,                        /* IF  */
  YYSYMBOL_ELIF = 53,                      /* ELIF  */
  YYSYMBOL_ELSE = 54,                      /* ELSE  */
  YYSYMBOL_WHILE = 55,                     /* WHILE  */
  YYSYMBOL_FOR = 56,                       /* FOR  */
  YYSYMBOL_CONTINUE = 57,                  /* CONTINUE  */
  YYSYMBOL_TYPEOF = 58,                    /* TYPEOF  */
  YYSYMBOL_FLEN = 59,                      /* FLEN  */
  YYSYMBOL_MAC = 60,                       /* MAC  */
  YYSYMBOL_RESET = 61,                     /* RESET  */
  YYSYMBOL_MACOP = 62,                     /* MACOP  */
  YYSYMBOL_ASSIGN = 63,                    /* ASSIGN  */
  YYSYMBOL_YYACCEPT = 64,                  /* $accept  */
  YYSYMBOL_Code = 65,                      /* Code  */
  YYSYMBOL_headerfileInclude = 66,         /* headerfileInclude  */
  YYSYMBOL_Program = 67,                   /* Program  */
  YYSYMBOL_func_list = 68,                 /* func_list  */
  YYSYMBOL_func = 69,                      /* func  */
  YYSYMBOL_70_1 = 70,                      /* $@1  */
  YYSYMBOL_func_prefix = 71,               /* func_prefix  */
  YYSYMBOL_72_2 = 72,                      /* $@2  */
  YYSYMBOL_func_data_type = 73,            /* func_data_type  */
  YYSYMBOL_param_list = 74,                /* param_list  */
  YYSYMBOL_75_3 = 75,                      /* $@3  */
  YYSYMBOL_param = 76,                     /* param  */
  YYSYMBOL_stmt_list = 77,                 /* stmt_list  */
  YYSYMBOL_stmt = 78,                      /* stmt  */
  YYSYMBOL_declaration = 79,               /* declaration  */
  YYSYMBOL_arr_values = 80,                /* arr_values  */
  YYSYMBOL_81_4 = 81,                      /* $@4  */
  YYSYMBOL_82_5 = 82,                      /* $@5  */
  YYSYMBOL_return_stmt = 83,               /* return_stmt  */
  YYSYMBOL_data_type = 84,                 /* data_type  */
  YYSYMBOL_expr = 85,                      /* expr  */
  YYSYMBOL_postfix_expr = 86,              /* postfix_expr  */
  YYSYMBOL_unary_expr = 87,                /* unary_expr  */
  YYSYMBOL_primary_expr = 88,              /* primary_expr  */
  YYSYMBOL_unary_op = 89,                  /* unary_op  */
  YYSYMBOL_const = 90,                     /* const  */
  YYSYMBOL_assign = 91,                    /* assign  */
  YYSYMBOL_if_stmt = 92,                   /* if_stmt  */
  YYSYMBOL_93_6 = 93,                      /* $@6  */
  YYSYMBOL_94_7 = 94,                      /* $@7  */
  YYSYMBOL_95_8 = 95,                      /* $@8  */
  YYSYMBOL_96_9 = 96,                      /* $@9  */
  YYSYMBOL_elif_stmt = 97,                 /* elif_stmt  */
  YYSYMBOL_98_10 = 98,                     /* $@10  */
  YYSYMBOL_99_11 = 99,                     /* $@11  */
  YYSYMBOL_100_12 = 100,                   /* $@12  */
  YYSYMBOL_101_13 = 101,                   /* $@13  */
  YYSYMBOL_else_stmt = 102,                /* else_stmt  */
  YYSYMBOL_103_14 = 103,                   /* $@14  */
  YYSYMBOL_switch_stmt = 104,              /* switch_stmt  */
  YYSYMBOL_105_15 = 105,                   /* $@15  */
  YYSYMBOL_106_16 = 106,                   /* $@16  */
  YYSYMBOL_107_17 = 107,                   /* $@17  */
  YYSYMBOL_case_stmt_list = 108,           /* case_stmt_list  */
  YYSYMBOL_case_stmt = 109,                /* case_stmt  */
  YYSYMBOL_110_18 = 110,                   /* $@18  */
  YYSYMBOL_111_19 = 111,                   /* $@19  */
  YYSYMBOL_default_stmt = 112,             /* default_stmt  */
  YYSYMBOL_while_loop_stmt = 113,          /* while_loop_stmt  */
  YYSYMBOL_114_20 = 114,                   /* $@20  */
  YYSYMBOL_115_21 = 115,                   /* $@21  */
  YYSYMBOL_116_22 = 116,                   /* $@22  */
  YYSYMBOL_for_loop_stmt = 117,            /* for_loop_stmt  */
  YYSYMBOL_118_23 = 118,                   /* $@23  */
  YYSYMBOL_119_24 = 119,                   /* $@24  */
  YYSYMBOL_120_25 = 120,                   /* $@25  */
  YYSYMBOL_121_26 = 121,                   /* $@26  */
  YYSYMBOL_func_call = 122,                /* func_call  */
  YYSYMBOL_123_27 = 123,                   /* $@27  */
  YYSYMBOL_arg_list = 124,                 /* arg_list  */
  YYSYMBOL_arg = 125                       /* arg  */
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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   938

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  149
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  312

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   318


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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   139,   139,   141,   142,   145,   148,   151,   155,   154,
     170,   169,   184,   188,   194,   194,   203,   209,   214,   221,
     222,   225,   226,   227,   228,   229,   230,   231,   232,   237,
     242,   243,   248,   256,   259,   262,   273,   282,   292,   295,
     305,   314,   322,   333,   343,   344,   362,   377,   384,   388,
     391,   391,   399,   407,   407,   415,   426,   435,   440,   443,
     446,   449,   452,   455,   463,   469,   475,   505,   535,   547,
     553,   560,   566,   573,   579,   586,   592,   599,   605,   612,
     619,   629,   652,   675,   705,   711,   717,   740,   788,   836,
     841,   846,   850,   867,   873,   889,   906,   912,   934,   940,
     941,   942,   943,   946,   950,   954,   964,   987,  1001,  1003,
    1005,  1008,  1017,  1019,  1005,  1030,  1035,  1044,  1047,  1030,
    1054,  1057,  1057,  1058,  1061,  1066,  1070,  1061,  1080,  1084,
    1087,  1090,  1087,  1104,  1105,  1108,  1114,  1126,  1108,  1138,
    1142,  1156,  1161,  1138,  1173,  1173,  1195,  1203,  1211,  1214
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
  "\"end of file\"", "error", "\"invalid token\"", "INCLUDE",
  "HEADERFILE", "INT", "CHAR", "FLOAT", "STRING", "BOOL", "VOID", "RETURN",
  "INT_NUM", "FLOAT_NUM", "ID", "LEFTSHIFT", "RIGHTSHIFT", "LE", "GE",
  "EQ", "NE", "GT", "LT", "AND", "OR", "NOT", "ADD", "SUBTRACT", "DIVIDE",
  "MULTIPLY", "MODULO", "BITAND", "BITOR", "NEGATION", "XOR", "STR",
  "CHARACTER", "CC", "OC", "CS", "OS", "CF", "OF", "COMMA", "COLON",
  "SCOL", "OUTPUT", "INPUT", "SWITCH", "CASE", "BREAK", "DEFAULT", "IF",
  "ELIF", "ELSE", "WHILE", "FOR", "CONTINUE", "TYPEOF", "FLEN", "MAC",
  "RESET", "MACOP", "ASSIGN", "$accept", "Code", "headerfileInclude",
  "Program", "func_list", "func", "$@1", "func_prefix", "$@2",
  "func_data_type", "param_list", "$@3", "param", "stmt_list", "stmt",
  "declaration", "arr_values", "$@4", "$@5", "return_stmt", "data_type",
  "expr", "postfix_expr", "unary_expr", "primary_expr", "unary_op",
  "const", "assign", "if_stmt", "$@6", "$@7", "$@8", "$@9", "elif_stmt",
  "$@10", "$@11", "$@12", "$@13", "else_stmt", "$@14", "switch_stmt",
  "$@15", "$@16", "$@17", "case_stmt_list", "case_stmt", "$@18", "$@19",
  "default_stmt", "while_loop_stmt", "$@20", "$@21", "$@22",
  "for_loop_stmt", "$@23", "$@24", "$@25", "$@26", "func_call", "$@27",
  "arg_list", "arg", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-95)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-145)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      11,    39,    49,   -95,    11,   -95,   -95,   283,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,    22,    73,   -95,   -95,
     -95,   217,    51,    76,   291,   -95,   -95,    86,   -95,   -95,
     -95,   -95,   -95,   873,   199,    53,    57,   -95,    47,   -95,
     -95,    58,    55,    84,    82,    66,    87,   217,   -95,    88,
     116,     1,   -95,   -95,   -95,    24,   -95,    90,   -95,   -95,
     -95,   -95,   -95,   145,    54,    10,   -95,   601,   873,   873,
      93,   148,    98,    99,   104,   842,   123,   119,   -95,   120,
     124,   273,   -95,   128,   147,   139,   -95,   -95,   -95,    96,
     873,   873,   720,   749,   776,   780,   807,   811,   873,   873,
     900,   873,   873,   873,   873,   873,   873,   873,   -95,   873,
     -95,   -95,   -95,   149,   157,   184,   -95,   869,   873,   319,
     601,   873,   -95,   156,   160,   163,   170,   345,    21,   194,
     873,   873,   -95,   601,   164,   -95,   177,   -95,     3,   -95,
     838,   201,    85,    85,   180,    26,   181,    26,   182,   174,
     183,   174,   189,    26,   195,    26,   649,   626,   106,   -22,
     -22,   175,   175,   175,   722,   674,   697,   601,   -95,   196,
     -95,   187,   368,   405,   186,   601,   208,   203,   199,   -95,
     199,   193,   206,   207,   873,   -95,   431,   454,   -95,   197,
     218,   219,   228,   479,   211,   254,   256,   269,   270,   280,
     281,   145,   -95,   -95,   -95,   873,   -95,   873,   -95,   -95,
     -95,   -95,   -95,   516,   259,   -95,   -95,   873,   287,    80,
     234,    12,   -95,   -95,   265,   271,   275,   276,   277,   282,
     -95,   601,   -95,   284,   268,   278,   286,   541,   262,   -95,
     -95,   -95,   285,   288,   -95,   -95,   -95,   -95,   -95,   -95,
     299,   274,   -95,   -95,   -95,   -95,   307,   309,   -95,   -95,
     -95,   274,   217,   217,   273,   -95,   -95,   292,   304,   -95,
     290,   315,   320,    -2,   326,   318,   -95,   -95,   -95,   -95,
     217,   -95,   325,   338,   356,   -95,   -95,   347,   -95,   359,
     366,   363,   -95,   217,   217,   873,   -95,   365,   -95,   578,
     217,   -95,   -95,   367,   369,   -95,   -95,   217,   371,   -95,
     325,   -95
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     7,     4,     1,     2,     5,     3,    59,
      62,    60,    61,    63,    13,     6,     0,     0,    12,     8,
      10,    20,     0,     0,     0,   103,   104,    96,   101,    99,
     100,   102,   105,     0,     0,     0,     0,   124,     0,   110,
     135,     0,     0,     0,     0,     0,     0,    20,    21,     0,
       0,     0,    91,    89,    90,     0,    97,     0,    25,    30,
      26,    27,    93,    17,     0,    96,    57,    56,     0,     0,
       0,     0,    53,     0,    50,     0,     0,     0,    28,     0,
       0,     0,    29,     0,     0,     0,     9,    19,    24,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    23,     0,
      96,    95,    22,     0,    14,     0,    40,     0,     0,     0,
     106,   148,    98,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   109,   108,     0,    35,     0,    48,     0,    36,
       0,     0,    87,    88,     0,    69,     0,    71,     0,    77,
       0,    80,     0,    75,     0,    73,    81,    82,    92,    64,
      65,    67,    66,    83,    84,    85,    86,    68,    11,     0,
      18,     0,     0,     0,    94,   149,     0,   147,     0,    49,
       0,     0,     0,     0,     0,   125,     0,     0,   139,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,    41,    42,    94,     0,   145,   148,    54,    51,
      34,    33,    31,     0,     0,   111,   136,     0,     0,     0,
       0,     0,    43,    44,     0,     0,     0,     0,     0,     0,
      15,   107,   146,     0,     0,     0,     0,     0,     0,    45,
      46,    47,     0,     0,    70,    72,    78,    79,    76,    74,
       0,   129,   112,   137,   140,    38,     0,     0,    32,   130,
     126,   129,    20,    20,     0,    39,    37,     0,   134,   128,
       0,     0,     0,     0,     0,     0,   113,   138,   141,   131,
      20,   127,   120,     0,     0,   133,   115,   123,   142,     0,
       0,     0,   114,    20,    20,     0,   121,     0,   132,     0,
      20,   143,   116,     0,     0,   122,   117,    20,     0,   118,
     120,   119
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -95,   -95,   406,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     213,   -95,   -95,   -46,   -95,   -77,   -94,   -95,   -95,   -95,
      -4,   -24,   -95,   -95,   354,   -95,   -32,   -76,   -95,   -95,
     -95,   -95,   -95,   105,   -95,   -95,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   155,   -95,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     210,   -95
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     3,     6,     7,    15,    21,    16,    22,    17,
     113,   169,   114,    46,    47,    48,    73,   125,   123,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    79,
     235,   262,   282,   287,   290,   304,   307,   310,   292,   300,
      59,    77,   214,   268,   260,   261,   267,   284,   275,    60,
      80,   236,   263,    61,   217,   264,   283,   293,    62,    70,
     176,   177
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      67,    87,    74,    18,   132,   134,   102,   103,   104,    71,
      25,    26,   132,   141,     1,   190,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   242,   100,   101,   102,
     103,   104,   105,   106,    32,   107,    25,    26,   110,   191,
     109,    90,    91,     4,   119,   120,   108,   243,  -144,     5,
     118,   127,   100,   101,   102,   103,   104,   133,   183,   115,
      32,   184,    33,   109,    19,   133,   142,   143,   145,   147,
     149,   151,   153,   155,   156,   157,   159,   160,   161,   162,
     163,   164,   165,   166,   208,   167,   209,    20,   109,    63,
      64,    75,    78,   172,   173,    76,    81,   175,    83,   116,
      82,     9,    10,    11,    23,    13,   186,   187,    25,    26,
      27,   100,   101,   102,   103,   104,   193,   117,   -99,   -99,
      84,    28,    29,    30,  -144,   239,    68,    85,    86,    31,
      89,   121,    32,    88,    33,   112,   138,   128,    34,   -55,
     124,   139,   -99,   240,   -99,   -52,    74,   109,    74,    69,
       9,    10,    11,    12,    13,    44,    45,   129,   130,   140,
     213,   136,   131,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   135,   100,   101,   102,   103,   104,   105,
     106,   231,   107,   175,   137,   122,   168,   132,   272,    90,
      91,    92,    93,   237,   -16,    96,    97,   115,   170,   178,
     100,   101,   102,   103,   104,   179,   180,   181,   185,   188,
     109,    25,    26,    72,   189,   194,   270,   271,   195,   196,
     197,   198,     9,    10,    11,    23,    13,   199,    24,    25,
      26,    27,   202,   200,   285,    32,   109,   109,   210,   201,
     133,   279,    28,    29,    30,   206,   207,   297,   298,   205,
      31,   211,   212,    32,   303,    33,   223,   219,   220,    34,
     218,   308,   -58,    35,    36,    37,   221,    38,   224,    39,
     225,   299,    40,    41,    42,    43,    44,    45,     9,    10,
      11,    23,    13,   226,   227,    25,    26,    27,     9,    10,
      11,    12,    13,    14,   228,   229,   234,   241,    28,    29,
      30,   238,   244,    25,    26,    65,    31,   255,   245,    32,
     251,    33,   246,   247,   248,    34,    28,    29,    30,   249,
     252,   250,   256,   259,    31,   257,    66,    32,   253,    33,
     273,   276,    44,    45,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   258,   100,   101,   102,   103,   104,
     105,   106,   265,   107,   266,   274,   277,   278,   174,   281,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     280,   100,   101,   102,   103,   104,   105,   106,   286,   107,
     288,   109,   182,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   289,   100,   101,   102,   103,   104,   105,
     106,   291,   107,   294,   295,   296,   301,   109,   305,   111,
       8,   306,   309,   203,   230,   311,   269,   232,     0,     0,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     109,   100,   101,   102,   103,   104,   105,   106,     0,   107,
       0,     0,     0,     0,   204,     0,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,     0,   100,   101,   102,
     103,   104,   105,   106,     0,   107,     0,   109,   215,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,     0,
     100,   101,   102,   103,   104,   105,   106,     0,   107,     0,
       0,   216,     0,   109,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,     0,   100,   101,   102,   103,   104,
     105,   106,     0,   107,     0,     0,   109,     0,     0,     0,
       0,     0,     0,     0,   222,     0,     0,     0,     0,     0,
       0,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   109,   100,   101,   102,   103,   104,   105,   106,     0,
     107,     0,     0,     0,     0,   233,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,     0,   100,   101,   102,
     103,   104,   105,   106,     0,   107,     0,     0,   109,     0,
       0,     0,     0,     0,     0,     0,   254,     0,     0,     0,
       0,     0,     0,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   109,   100,   101,   102,   103,   104,   105,
     106,     0,   107,     0,     0,   302,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,     0,   100,   101,   102,
     103,   104,   105,   106,     0,   107,     0,     0,     0,     0,
     109,    90,    91,    92,    93,    94,    95,    96,    97,    98,
       0,     0,   100,   101,   102,   103,   104,   105,   106,     0,
     107,     0,     0,   109,    90,    91,    92,    93,    94,    95,
      96,    97,     0,     0,     0,   100,   101,   102,   103,   104,
     105,   106,     0,   107,     0,     0,     0,     0,   109,    90,
      91,    92,    93,    94,    95,    96,    97,     0,     0,     0,
     100,   101,   102,   103,   104,   105,     0,     0,   107,     0,
       0,   109,    90,    91,    92,    93,    94,    95,    96,    97,
       0,     0,     0,   100,   101,   102,   103,   104,   105,     0,
       0,     0,    25,    26,    65,     0,   109,    90,    91,    92,
      93,    94,    95,    96,    97,    28,    29,    30,   100,   101,
     102,   103,   104,    31,     0,     0,    32,     0,    33,   109,
       0,    25,    26,    65,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    28,    29,    30,     0,     0,   144,
       0,     0,    31,     0,   109,    32,     0,    33,    25,    26,
      65,     0,    25,    26,    65,     0,     0,     0,     0,     0,
       0,    28,    29,    30,     0,    28,    29,    30,   146,    31,
       0,     0,    32,    31,    33,     0,    32,     0,    33,    25,
      26,    65,     0,    25,    26,    65,     0,     0,     0,     0,
       0,     0,    28,    29,    30,   148,    28,    29,    30,   150,
      31,     0,     0,    32,    31,    33,     0,    32,     0,    33,
      25,    26,    65,     0,    25,    26,    65,     0,     0,     0,
       0,     0,     0,    28,    29,    30,   152,    28,    29,    30,
     154,    31,     0,     0,    32,    31,    33,   126,    32,     0,
      33,    25,    26,    65,     0,    25,    26,    65,     0,     0,
       0,     0,     0,     0,    28,    29,    30,   192,    28,    29,
      30,     0,    31,     0,   171,    32,    31,    33,     0,    32,
       0,    33,    25,    26,    65,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    28,   158,    30,     0,     0,
       0,     0,     0,    31,     0,     0,    32,     0,    33
};

static const yytype_int16 yycheck[] =
{
      24,    47,    34,     7,    81,    81,    28,    29,    30,    33,
      12,    13,    89,    89,     3,    12,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    14,    26,    27,    28,
      29,    30,    31,    32,    36,    34,    12,    13,    14,    36,
      62,    15,    16,     4,    68,    69,    45,    35,    38,     0,
      40,    75,    26,    27,    28,    29,    30,    81,    37,    63,
      36,    40,    38,    62,    42,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   178,   109,   180,    14,    62,    38,
      14,    38,    45,   117,   118,    38,    38,   121,    14,    45,
      45,     5,     6,     7,     8,     9,   130,   131,    12,    13,
      14,    26,    27,    28,    29,    30,   140,    63,    12,    13,
      38,    25,    26,    27,    38,    45,    40,    61,    41,    33,
      14,    38,    36,    45,    38,    45,    40,    14,    42,    41,
      41,    45,    36,    63,    38,    41,   178,    62,   180,    63,
       5,     6,     7,     8,     9,    59,    60,    38,    38,    63,
     184,    14,    38,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    45,    26,    27,    28,    29,    30,    31,
      32,   205,    34,   207,    45,    37,    37,   264,   264,    15,
      16,    17,    18,   217,    37,    21,    22,   201,    14,    43,
      26,    27,    28,    29,    30,    45,    43,    37,    14,    45,
      62,    12,    13,    14,    37,    14,   262,   263,    38,    38,
      38,    38,     5,     6,     7,     8,     9,    38,    11,    12,
      13,    14,    45,    38,   280,    36,    62,    62,    45,    43,
     264,   273,    25,    26,    27,    37,    43,   293,   294,    63,
      33,    45,    45,    36,   300,    38,    45,    39,    39,    42,
      63,   307,    45,    46,    47,    48,    38,    50,    14,    52,
      14,   295,    55,    56,    57,    58,    59,    60,     5,     6,
       7,     8,     9,    14,    14,    12,    13,    14,     5,     6,
       7,     8,     9,    10,    14,    14,    37,    63,    25,    26,
      27,    14,    37,    12,    13,    14,    33,    45,    37,    36,
      42,    38,    37,    37,    37,    42,    25,    26,    27,    37,
      42,    37,    37,    49,    33,    37,    35,    36,    42,    38,
      38,    41,    59,    60,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    45,    26,    27,    28,    29,    30,
      31,    32,    45,    34,    45,    51,    41,    37,    39,    41,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      44,    26,    27,    28,    29,    30,    31,    32,    53,    34,
      42,    62,    37,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    37,    26,    27,    28,    29,    30,    31,
      32,    54,    34,    44,    38,    42,    41,    62,    41,    55,
       4,    42,    41,    45,   201,   310,   261,   207,    -1,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      62,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      -1,    -1,    -1,    -1,    39,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    -1,    62,    37,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    -1,
      -1,    37,    -1,    62,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    -1,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    -1,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    62,    26,    27,    28,    29,    30,    31,    32,    -1,
      34,    -1,    -1,    -1,    -1,    39,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    -1,    -1,    62,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    62,    26,    27,    28,    29,    30,    31,
      32,    -1,    34,    -1,    -1,    37,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    -1,    -1,    -1,    -1,
      62,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    -1,    26,    27,    28,    29,    30,    31,    32,    -1,
      34,    -1,    -1,    62,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    -1,    -1,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    -1,    -1,    -1,    -1,    62,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    -1,    -1,
      26,    27,    28,    29,    30,    31,    -1,    -1,    34,    -1,
      -1,    62,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    -1,    -1,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    12,    13,    14,    -1,    62,    15,    16,    17,
      18,    19,    20,    21,    22,    25,    26,    27,    26,    27,
      28,    29,    30,    33,    -1,    -1,    36,    -1,    38,    62,
      -1,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    25,    26,    27,    -1,    -1,    59,
      -1,    -1,    33,    -1,    62,    36,    -1,    38,    12,    13,
      14,    -1,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,
      -1,    25,    26,    27,    -1,    25,    26,    27,    59,    33,
      -1,    -1,    36,    33,    38,    -1,    36,    -1,    38,    12,
      13,    14,    -1,    12,    13,    14,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    26,    27,    59,    25,    26,    27,    59,
      33,    -1,    -1,    36,    33,    38,    -1,    36,    -1,    38,
      12,    13,    14,    -1,    12,    13,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    25,    26,    27,    59,    25,    26,    27,
      59,    33,    -1,    -1,    36,    33,    38,    35,    36,    -1,
      38,    12,    13,    14,    -1,    12,    13,    14,    -1,    -1,
      -1,    -1,    -1,    -1,    25,    26,    27,    59,    25,    26,
      27,    -1,    33,    -1,    35,    36,    33,    38,    -1,    36,
      -1,    38,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    25,    26,    27,    -1,    -1,
      -1,    -1,    -1,    33,    -1,    -1,    36,    -1,    38
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    65,    66,     4,     0,    67,    68,    66,     5,
       6,     7,     8,     9,    10,    69,    71,    73,    84,    42,
      14,    70,    72,     8,    11,    12,    13,    14,    25,    26,
      27,    33,    36,    38,    42,    46,    47,    48,    50,    52,
      55,    56,    57,    58,    59,    60,    77,    78,    79,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,   104,
     113,   117,   122,    38,    14,    14,    35,    85,    40,    63,
     123,    85,    14,    80,    90,    38,    38,   105,    45,    93,
     114,    38,    45,    14,    38,    61,    41,    77,    45,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      26,    27,    28,    29,    30,    31,    32,    34,    45,    62,
      14,    88,    45,    74,    76,    84,    45,    63,    40,    85,
      85,    38,    37,    82,    41,    81,    35,    85,    14,    38,
      38,    38,    79,    85,    91,    45,    14,    45,    40,    45,
      63,    91,    85,    85,    59,    85,    59,    85,    59,    85,
      59,    85,    59,    85,    59,    85,    85,    85,    26,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    37,    75,
      14,    35,    85,    85,    39,    85,   124,   125,    43,    45,
      43,    37,    37,    37,    40,    14,    85,    85,    45,    37,
      12,    36,    59,    85,    14,    38,    38,    38,    38,    38,
      38,    43,    45,    45,    39,    63,    37,    43,    80,    80,
      45,    45,    45,    85,   106,    37,    37,   118,    63,    39,
      39,    38,    45,    45,    14,    14,    14,    14,    14,    14,
      74,    85,   124,    39,    37,    94,   115,    85,    14,    45,
      63,    63,    14,    35,    37,    37,    37,    37,    37,    37,
      37,    42,    42,    42,    45,    45,    37,    37,    45,    49,
     108,   109,    95,   116,   119,    45,    45,   110,   107,   108,
      77,    77,    91,    38,    51,   112,    41,    41,    37,    90,
      44,    41,    96,   120,   111,    77,    53,    97,    42,    37,
      98,    54,   102,   121,    44,    38,    42,    77,    77,    85,
     103,    41,    37,    77,    99,    41,    42,   100,    77,    41,
     101,    97
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    64,    65,    66,    66,    67,    68,    68,    70,    69,
      72,    71,    73,    73,    75,    74,    74,    74,    76,    77,
      77,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      81,    80,    80,    82,    80,    80,    83,    83,    83,    84,
      84,    84,    84,    84,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    86,    86,    87,    88,    88,    88,    89,
      89,    89,    89,    90,    90,    90,    91,    91,    91,    91,
      93,    94,    95,    96,    92,    98,    99,   100,   101,    97,
      97,   103,   102,   102,   105,   106,   107,   104,   108,   108,
     110,   111,   109,   112,   112,   114,   115,   116,   113,   118,
     119,   120,   121,   117,   123,   122,   124,   124,   124,   125
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     3,     0,     1,     2,     0,     0,     5,
       0,     6,     1,     1,     0,     4,     1,     0,     2,     2,
       0,     1,     2,     2,     2,     1,     1,     1,     2,     2,
       1,     5,     8,     5,     5,     3,     3,     8,     7,     8,
       3,     5,     5,     5,     5,     6,     6,     6,     3,     4,
       0,     4,     1,     0,     4,     1,     2,     2,     0,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       6,     3,     6,     3,     6,     3,     6,     3,     6,     6,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     3,     1,     4,     2,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     6,     1,     1,
       0,     0,     0,     0,    13,     0,     0,     0,     0,    12,
       0,     0,     5,     0,     0,     0,     0,    11,     2,     0,
       0,     0,     8,     3,     0,     0,     0,     0,    10,     0,
       0,     0,     0,    15,     0,     5,     3,     1,     0,     1
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
        yyerror (YY_("syntax error: cannot back up")); \
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
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
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
yyparse (void)
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
  case 6: /* func_list: func_list func  */
#line 148 "parser.y"
                                   {
    //printf("Hello");
}
#line 1817 "y.tab.c"
    break;

  case 8: /* $@1: %empty  */
#line 155 "parser.y"
                    {
                        has_return_stmt = 0;
                        scope_history.push(++scope_counter);
                    }
#line 1826 "y.tab.c"
    break;

  case 9: /* func: func_prefix OF $@1 stmt_list CF  */
#line 159 "parser.y"
                    {
                        if(func_table[curr_func_name].return_type != "void" && curr_func_name!="main" && has_return_stmt == 0){
                            sem_errors.push_back("Return stmt not there for function: " + curr_func_name);
                        }
                        scope_history.pop();
                        --scope_counter;
                        tac.push_back("end:\n");
                        has_return_stmt = 0;
                    }
#line 1840 "y.tab.c"
    break;

  case 10: /* $@2: %empty  */
#line 170 "parser.y"
                    {   
                        if(func_table.find(string((yyvsp[0].node).lexeme)) != func_table.end()){
                            sem_errors.push_back("Error: Duplicate function name - " + string((yyvsp[0].node).lexeme));
                        }
                        tac.push_back(string((yyvsp[0].node).lexeme) + ": " + string((yyvsp[-1].node).type)); 
                        curr_func_name = string((yyvsp[0].node).lexeme);
                        func_table[curr_func_name]=func_table["global"];
                        
                    }
#line 1854 "y.tab.c"
    break;

  case 11: /* func_prefix: func_data_type ID $@2 OC param_list CC  */
#line 179 "parser.y"
                                     {
                        func_table[curr_func_name].return_type = string((yyvsp[-5].node).type);
                        func_table[curr_func_name].num_params = (yyvsp[-1].node).nParams;
                    }
#line 1863 "y.tab.c"
    break;

  case 12: /* func_data_type: data_type  */
#line 184 "parser.y"
                              {
                        strcpy((yyval.node).type, (yyvsp[0].node).type);
                        //printf("%s",string( $1.type));
                    }
#line 1872 "y.tab.c"
    break;

  case 13: /* func_data_type: VOID  */
#line 188 "parser.y"
                           {
                        sprintf((yyval.node).type, "void");
                        //printf("void");
                    }
#line 1881 "y.tab.c"
    break;

  case 14: /* $@3: %empty  */
#line 194 "parser.y"
                          {
                        func_table[curr_func_name].param_types.push_back(string((yyvsp[0].node).type));
                        func_table[curr_func_name].symbol_table[string((yyvsp[0].node).lexeme)] = { string((yyvsp[0].node).type), scope_counter+1, 0, 0, countn+1 };
                        tac.push_back("- arg " + string((yyvsp[0].node).type) + " " + string((yyvsp[0].node).lexeme));                       
                    }
#line 1891 "y.tab.c"
    break;

  case 15: /* param_list: param $@3 COMMA param_list  */
#line 199 "parser.y"
                                     {
                        (yyval.node).nParams = (yyvsp[0].node).nParams + 1;
                        if((yyval.node).nParams>20) sem_errors.push_back("No. of parameters exceeded for " + curr_func_name);
                    }
#line 1900 "y.tab.c"
    break;

  case 16: /* param_list: param  */
#line 203 "parser.y"
                            {
                        (yyval.node).nParams = 1;
                        func_table[curr_func_name].param_types.push_back(string((yyvsp[0].node).type));
                        func_table[curr_func_name].symbol_table[string((yyvsp[0].node).lexeme)] = { string((yyvsp[0].node).type), scope_counter+1, 0, 0, countn+1 };
                        tac.push_back("- arg " + string((yyvsp[0].node).type) + " " + string((yyvsp[0].node).lexeme));
                    }
#line 1911 "y.tab.c"
    break;

  case 17: /* param_list: %empty  */
#line 209 "parser.y"
                      {
                        (yyval.node).nParams = 0;
                    }
#line 1919 "y.tab.c"
    break;

  case 18: /* param: data_type ID  */
#line 214 "parser.y"
                                 {
                        (yyval.node).nParams = 1;
                        strcpy((yyval.node).type, (yyvsp[-1].node).type);
                        strcpy((yyval.node).lexeme, (yyvsp[0].node).lexeme);                   
                        }
#line 1929 "y.tab.c"
    break;

  case 28: /* stmt: BREAK SCOL  */
#line 232 "parser.y"
                                 {
                        if(!loop_break.empty()){
                            tac.push_back("GOTO #L" + to_string(loop_break.top()));
                        }
                    }
#line 1939 "y.tab.c"
    break;

  case 29: /* stmt: CONTINUE SCOL  */
#line 237 "parser.y"
                                    {
                        if(!loop_continue.empty()){
                            tac.push_back("GOTO #L" + to_string(loop_continue.top()));
                        }
                    }
#line 1949 "y.tab.c"
    break;

  case 31: /* stmt: INPUT OC ID CC SCOL  */
#line 243 "parser.y"
                                           {
                        check_declaration((yyvsp[-2].node).lexeme);
                        tac.push_back("input " + string((yyvsp[-2].node).lexeme) + " " + func_table[curr_func_name].symbol_table[string((yyvsp[-2].node).lexeme)].data_type);
                        // check_scope(string($3.lexeme));
                    }
#line 1959 "y.tab.c"
    break;

  case 32: /* stmt: INPUT OC ID OS expr CS CC SCOL  */
#line 248 "parser.y"
                                                     {
                        check_declaration((yyvsp[-5].node).lexeme);
                        string temp = get_temp();
                        tac.push_back("input " + temp + " " + func_table[curr_func_name].symbol_table[string((yyvsp[-5].node).lexeme)].data_type);
                        tac.push_back(string((yyvsp[-5].node).lexeme) + " [ " + string((yyvsp[-3].node).lexeme) + " ] = " + temp + " " + func_table[curr_func_name].symbol_table[string((yyvsp[-5].node).lexeme)].data_type);
                        free_temp.push(temp);
                        // check_scope(string($3.lexeme));
                    }
#line 1972 "y.tab.c"
    break;

  case 33: /* stmt: OUTPUT OC expr CC SCOL  */
#line 256 "parser.y"
                                             {
                        tac.push_back("output " + string((yyvsp[-2].node).lexeme) + " " + string((yyvsp[-2].node).type));
                    }
#line 1980 "y.tab.c"
    break;

  case 34: /* stmt: OUTPUT OC STR CC SCOL  */
#line 259 "parser.y"
                                            {
                        tac.push_back("output " + string((yyvsp[-2].node).lexeme) + " STRING");
                    }
#line 1988 "y.tab.c"
    break;

  case 35: /* stmt: TYPEOF ID SCOL  */
#line 262 "parser.y"
                                     {
                        char dtype[256]; // Choose an appropriate size for the array
                        strcpy(dtype, func_table[curr_func_name].symbol_table[string((yyvsp[-1].node).lexeme)].data_type.c_str());

                        // Print both the name of ID and its type
                        printf("Variable %s has type %s\n", (yyvsp[-1].node).lexeme, dtype);
                    }
#line 2000 "y.tab.c"
    break;

  case 36: /* declaration: data_type ID SCOL  */
#line 273 "parser.y"
                                      { 
                        is_reserved_word(string((yyvsp[-1].node).lexeme));
                        // if(multiple_declaration(string($2.lexeme))){
                        //     check_scope(string($2.lexeme));
                        // };
                        //if(string($1.lexeme)!="int")sem_errors.push_back(string($1.lexeme)+" "+string($2.lexeme));
                        tac.push_back("- " + string((yyvsp[-2].node).type) + " " + string((yyvsp[-1].node).lexeme));
                        func_table[curr_func_name].symbol_table[string((yyvsp[-1].node).lexeme)] = { string((yyvsp[-2].node).type), scope_counter, 0, 0, countn+1 };
                    }
#line 2014 "y.tab.c"
    break;

  case 37: /* declaration: data_type ID ASSIGN FLEN OC STR CC SCOL  */
#line 282 "parser.y"
                                                              {
                        string t0=get_temp();
                        func_table[curr_func_name].symbol_table[string((yyvsp[-6].node).lexeme)] = { "INT", scope_counter, 0, 0, countn+1 };
                        string_info[string((yyvsp[-6].node).lexeme)] = to_string(string((yyvsp[-2].node).lexeme).length()-2);
                        tac.push_back(string((yyvsp[-2].node).lexeme) + string_info[string((yyvsp[-6].node).lexeme)]);
                        tac.push_back(t0+" = "+ string_info[string((yyvsp[-6].node).lexeme)] + " INT ");
                        tac.push_back("- INT "+string((yyvsp[-6].node).lexeme));
                        tac.push_back(string((yyvsp[-6].node).lexeme) +" = " + t0 + " INT " );

                       }
#line 2029 "y.tab.c"
    break;

  case 38: /* declaration: FLEN OC ID CC ASSIGN ID SCOL  */
#line 292 "parser.y"
                                                   {
                        string_info[string((yyvsp[-4].node).lexeme)] = string((yyvsp[-1].node).lexeme);
                    }
#line 2037 "y.tab.c"
    break;

  case 39: /* declaration: data_type ID ASSIGN FLEN OC ID CC SCOL  */
#line 295 "parser.y"
                                                            {
                        string t0=get_temp();
                        //string_info[string($2.lexeme)] = string_info[string($6.lexeme)];
                        // tac.push_back(string($1.lexeme) + " "+ to_string(string_info[string($6.lexeme)]));
                        // tac.push_back(string($6.lexeme) + to_string(string_info[string($2.lexeme)]));
                        func_table[curr_func_name].symbol_table[string((yyvsp[-6].node).lexeme)] = { "INT", scope_counter, 0, 0, countn+1 };
                        tac.push_back(t0+" = "+ string_info[string((yyvsp[-2].node).lexeme)] + " INT ");
                        tac.push_back("- INT "+string((yyvsp[-6].node).lexeme));
                        tac.push_back(string((yyvsp[-6].node).lexeme) +" = " + t0 + " INT " );
                    }
#line 2052 "y.tab.c"
    break;

  case 40: /* declaration: STRING ID SCOL  */
#line 305 "parser.y"
                                     { 
                        is_reserved_word(string((yyvsp[-1].node).lexeme));
                        // if(multiple_declaration(string($2.lexeme))){
                        //     check_scope(string($2.lexeme));
                        // };
                        //if(string($1.lexeme)!="int")sem_errors.push_back(string($1.lexeme)+" "+string($2.lexeme));
                        tac.push_back("- " + string((yyvsp[-2].node).type) + " " + string((yyvsp[-1].node).lexeme));
                        func_table[curr_func_name].symbol_table[string((yyvsp[-1].node).lexeme)] = { "STRING", scope_counter, 0, 0, countn+1 };
                    }
#line 2066 "y.tab.c"
    break;

  case 41: /* declaration: STRING ID ASSIGN STR SCOL  */
#line 314 "parser.y"
                                                {
                        is_reserved_word(string((yyvsp[-3].node).lexeme));
                        string_info[string((yyvsp[-3].node).lexeme)]=to_string(string((yyvsp[-1].node).lexeme).length()-2);
                        multiple_declaration(string((yyvsp[-3].node).lexeme));
                        tac.push_back("- STRING " + string((yyvsp[-3].node).lexeme));
                        tac.push_back(string((yyvsp[-3].node).lexeme) + " = " + string((yyvsp[-1].node).lexeme) + " STRING");
                        func_table[curr_func_name].symbol_table[string((yyvsp[-3].node).lexeme)] = { "STRING", scope_counter, string((yyvsp[-1].node).lexeme).length(), 0, countn+1 };
                    }
#line 2079 "y.tab.c"
    break;

  case 42: /* declaration: STRING ID ASSIGN expr SCOL  */
#line 322 "parser.y"
                                                 {
                        is_reserved_word(string((yyvsp[-3].node).lexeme));
                        multiple_declaration(string((yyvsp[-3].node).lexeme));
                        string_info[string((yyvsp[-3].node).lexeme)]=string_info[string((yyvsp[-1].node).lexeme)];
                        check_type(string((yyvsp[-4].node).type), string((yyvsp[-1].node).type));
                        tac.push_back("- " + string((yyvsp[-4].node).type) + " " + string((yyvsp[-3].node).lexeme));
                        tac.push_back(string((yyvsp[-3].node).lexeme) + " = " + string((yyvsp[-1].node).lexeme) + " " + "STRING");
                        func_table[curr_func_name].symbol_table[string((yyvsp[-3].node).lexeme)] = { string((yyvsp[-4].node).type), scope_counter, 0, 0, countn+1 };

                        if(const_temps.find(string((yyvsp[-1].node).lexeme)) == const_temps.end() && (yyvsp[-1].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-1].node).lexeme));
                    }
#line 2095 "y.tab.c"
    break;

  case 43: /* declaration: data_type ID ASSIGN expr SCOL  */
#line 333 "parser.y"
                                                    {
                        is_reserved_word(string((yyvsp[-3].node).lexeme));
                        multiple_declaration(string((yyvsp[-3].node).lexeme));
                        check_type(string((yyvsp[-4].node).type), string((yyvsp[-1].node).type));
                        tac.push_back("- " + string((yyvsp[-4].node).type) + " " + string((yyvsp[-3].node).lexeme));
                        tac.push_back(string((yyvsp[-3].node).lexeme) + " = " + string((yyvsp[-1].node).lexeme) + " " + string((yyvsp[-4].node).type));
                        func_table[curr_func_name].symbol_table[string((yyvsp[-3].node).lexeme)] = { string((yyvsp[-4].node).type), scope_counter, 0, 0, countn+1 };

                        if(const_temps.find(string((yyvsp[-1].node).lexeme)) == const_temps.end() && (yyvsp[-1].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-1].node).lexeme));
                    }
#line 2110 "y.tab.c"
    break;

  case 45: /* declaration: data_type ID OS INT_NUM CS SCOL  */
#line 344 "parser.y"
                                                      {
                        is_reserved_word(string((yyvsp[-4].node).lexeme));
                        multiple_declaration(string((yyvsp[-4].node).lexeme));
                        tac.push_back("- " + string((yyvsp[-5].node).type) + " " + string((yyvsp[-4].node).lexeme) + " [ " + string((yyvsp[-2].node).lexeme) + " ] ");
                        func_table[curr_func_name].symbol_table[string((yyvsp[-4].node).lexeme)] = { string((yyvsp[-5].node).type), scope_counter, stoi(string((yyvsp[-2].node).lexeme)), 1, countn+1 };
                    }
#line 2121 "y.tab.c"
    break;

  case 46: /* declaration: data_type ID OS INT_NUM CS ASSIGN  */
#line 362 "parser.y"
                                                        {
                        is_reserved_word(string((yyvsp[-4].node).lexeme));
                        multiple_declaration(string((yyvsp[-4].node).lexeme));
                        tac.push_back("- " + string((yyvsp[-5].node).type) + " " + string((yyvsp[-4].node).lexeme) + " [ " + string((yyvsp[-2].node).lexeme) + " ] ");
                        func_table[curr_func_name].symbol_table[string((yyvsp[-4].node).lexeme)] = { string((yyvsp[-5].node).type), scope_counter, stoi(string((yyvsp[-2].node).lexeme)), 1, countn+1 };
                        curr_array = string((yyvsp[-4].node).lexeme);
                    }
#line 2133 "y.tab.c"
    break;

  case 47: /* declaration: data_type ID OS CHARACTER CS ASSIGN  */
#line 377 "parser.y"
                                                          {
                        is_reserved_word(string((yyvsp[-4].node).lexeme));
                        multiple_declaration(string((yyvsp[-4].node).lexeme));
                        tac.push_back("- " + string((yyvsp[-5].node).type) + " " + string((yyvsp[-4].node).lexeme) + " [ " + string((yyvsp[-2].node).lexeme) + " ] ");
                        func_table[curr_func_name].symbol_table[string((yyvsp[-4].node).lexeme)] = { string((yyvsp[-5].node).type), scope_counter, stoi(string((yyvsp[-2].node).lexeme)), 1, countn+1 };
                        curr_array = string((yyvsp[-4].node).lexeme);
                    }
#line 2145 "y.tab.c"
    break;

  case 48: /* declaration: MAC RESET SCOL  */
#line 384 "parser.y"
                                    {
                        tac.push_back("MAC RESET");
                    }
#line 2153 "y.tab.c"
    break;

  case 50: /* $@4: %empty  */
#line 391 "parser.y"
                          {
                        check_type(func_table[curr_func_name].symbol_table[curr_array].data_type, string((yyvsp[0].node).type));
                        tac.push_back(curr_array + " [ " + to_string(arr_index++) + " ] = " + string((yyvsp[0].node).lexeme) + " " + func_table[curr_func_name].symbol_table[curr_array].data_type);
                        if(arr_index > func_table[curr_func_name].symbol_table[curr_array].size){
                            sem_errors.push_back("Line no: " + to_string(func_table[curr_func_name].symbol_table[curr_array].line_number) + " error: too many initializers for "+curr_array+ "[" + to_string(func_table[curr_func_name].symbol_table[curr_array].size) + "]");
                        }
                    }
#line 2165 "y.tab.c"
    break;

  case 52: /* arr_values: const  */
#line 399 "parser.y"
                            {
                        check_type(func_table[curr_func_name].symbol_table[curr_array].data_type, string((yyvsp[0].node).type));
                        tac.push_back(curr_array + " [ " + to_string(arr_index++) + " ] = " + string((yyvsp[0].node).lexeme) + " " + func_table[curr_func_name].symbol_table[curr_array].data_type);
                        if(arr_index > func_table[curr_func_name].symbol_table[curr_array].size){
                            sem_errors.push_back("Line no: " + to_string(func_table[curr_func_name].symbol_table[curr_array].line_number) + " error: too many initializers for "+curr_array+ "[" + to_string(func_table[curr_func_name].symbol_table[curr_array].size) + "]");
                        }
                        arr_index=0;
                    }
#line 2178 "y.tab.c"
    break;

  case 53: /* $@5: %empty  */
#line 407 "parser.y"
                       {
                        check_type(func_table[curr_func_name].symbol_table[curr_array].data_type, string((yyvsp[0].node).type));
                        tac.push_back(curr_array + " [ " + to_string(arr_index++) + " ] = " + string((yyvsp[0].node).lexeme) + " " + func_table[curr_func_name].symbol_table[curr_array].data_type);
                        if(arr_index > func_table[curr_func_name].symbol_table[curr_array].size){
                            sem_errors.push_back("Line no: " + to_string(func_table[curr_func_name].symbol_table[curr_array].line_number) + " error: too many initializers for "+curr_array+ "[" + to_string(func_table[curr_func_name].symbol_table[curr_array].size) + "]");
                        }
                    }
#line 2190 "y.tab.c"
    break;

  case 55: /* arr_values: ID  */
#line 415 "parser.y"
                         {
                        check_type(func_table[curr_func_name].symbol_table[curr_array].data_type, string((yyvsp[0].node).type));
                        tac.push_back(curr_array + " [ " + to_string(arr_index++) + " ] = " + string((yyvsp[0].node).lexeme) + " " + func_table[curr_func_name].symbol_table[curr_array].data_type);
                        if(arr_index > func_table[curr_func_name].symbol_table[curr_array].size){
                            sem_errors.push_back("Line no: " + to_string(func_table[curr_func_name].symbol_table[curr_array].line_number) + " error: too many initializers for "+curr_array+ "[" + to_string(func_table[curr_func_name].symbol_table[curr_array].size) + "]");
                        }
                        arr_index=0;
                    }
#line 2203 "y.tab.c"
    break;

  case 56: /* return_stmt: RETURN expr  */
#line 426 "parser.y"
                                {
                        //sem_errors.push_back($2.type);
                        check_type(func_table[curr_func_name].return_type, string((yyvsp[0].node).type));
                        tac.push_back("return " + string((yyvsp[0].node).lexeme) + " " + func_table[curr_func_name].return_type);
                        has_return_stmt = 1;

                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));
                    }
#line 2216 "y.tab.c"
    break;

  case 57: /* return_stmt: RETURN STR  */
#line 435 "parser.y"
                               {
                        has_return_stmt = 1;
                        tac.push_back("return " + string((yyvsp[0].node).lexeme) + " " + func_table[curr_func_name].return_type);
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));
                    }
#line 2226 "y.tab.c"
    break;

  case 59: /* data_type: INT  */
#line 443 "parser.y"
                        {
                        strcpy((yyval.node).type, "INT");
                    }
#line 2234 "y.tab.c"
    break;

  case 60: /* data_type: FLOAT  */
#line 446 "parser.y"
                            {
                        strcpy((yyval.node).type, "FLOAT");
                    }
#line 2242 "y.tab.c"
    break;

  case 61: /* data_type: STRING  */
#line 449 "parser.y"
                            {
                        strcpy((yyval.node).type, "STRING");
                    }
#line 2250 "y.tab.c"
    break;

  case 62: /* data_type: CHAR  */
#line 452 "parser.y"
                           {
                        strcpy((yyval.node).type, "CHAR");
                    }
#line 2258 "y.tab.c"
    break;

  case 63: /* data_type: BOOL  */
#line 455 "parser.y"
                           {
                        strcpy((yyval.node).type, "BOOL");
                    }
#line 2266 "y.tab.c"
    break;

  case 64: /* expr: expr ADD expr  */
#line 463 "parser.y"
                                      {
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[-2].node).lexeme) + " " + string((yyvsp[-1].node).lexeme) + " " + string((yyvsp[0].node).lexeme) + " " + string((yyval.node).type));
                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));
                    }
#line 2277 "y.tab.c"
    break;

  case 65: /* expr: expr SUBTRACT expr  */
#line 469 "parser.y"
                                         {
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[-2].node).lexeme) + " " + string((yyvsp[-1].node).lexeme) + " " + string((yyvsp[0].node).lexeme) + " " + string((yyval.node).type));
                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));
                    }
#line 2288 "y.tab.c"
    break;

  case 66: /* expr: expr MULTIPLY expr  */
#line 475 "parser.y"
                                         {
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        string t0=get_temp();
                        string t1=get_temp();
                        string t2=get_temp();
                        string a = string((yyval.node).lexeme);
                        string b = string((yyvsp[-2].node).lexeme);
                        string c = string((yyvsp[0].node).lexeme);
                        string dtype = string((yyval.node).type);
                        
                        tac.push_back(a + " = 0 " + dtype);
                        tac.push_back(t0 + " = 0 " + dtype);
                        tac.push_back(t2 + " = 1 " + dtype);
                        tac.push_back("#L" + to_string(++label_counter) + ":");
                        tac.push_back(t1 + " = " + t0 + " < " + c +  "  " + dtype);
                        tac.push_back("if " + t1 + " GOTO " + "#L" + to_string(label_counter+1) + " else GOTO " + "#L" + to_string(label_counter+2));
                        tac.push_back("#L" + to_string(++label_counter) + ":");
                        tac.push_back(a + " = " + a + " + " + b +  "  " + dtype);
                        tac.push_back(t0 + " = " + t0 + " + " + t2 +  "  " + dtype);
                        tac.push_back("GOTO #L" + to_string(label_counter-1));
                        tac.push_back("#L" + to_string(++label_counter) + ":");

                        free_temp.push(t0);
                        free_temp.push(t1);
                        free_temp.push(t2);
                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));

                        label_counter++;
                    }
#line 2323 "y.tab.c"
    break;

  case 67: /* expr: expr DIVIDE expr  */
#line 505 "parser.y"
                                       {
                       //if(atoi($3.lexeme)==0)  sem_errors.push_back("Line no " + to_string(countn+1) +" : " +" Divide by zero error"); 
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        string t0=get_temp();
                        string t1=get_temp();
                        string t2=get_temp();
                        string a = string((yyval.node).lexeme);
                        string b = string((yyvsp[-2].node).lexeme);
                        string c = string((yyvsp[0].node).lexeme);
                        string dtype = string((yyval.node).type);
                        
                        tac.push_back(a + " = 0 " + dtype);
                        tac.push_back(t0 + " = " + b + " " + dtype);
                        tac.push_back(t2 + " = 1 " + dtype);
                        tac.push_back("#L" + to_string(++label_counter) + ":");
                        tac.push_back(t1 + " = " + t0 + " >= " + c +  "  " + dtype);
                        tac.push_back("if " + t1 + " GOTO " + "#L" + to_string(label_counter+1) + " else GOTO " + "#L" + to_string(label_counter+2));
                        tac.push_back("#L" + to_string(++label_counter) + ":");
                        tac.push_back(a + " = " + a + " + " + t2 +  "  " + dtype);
                        tac.push_back(t0 + " = " + t0 + " - " + c +  "  " + dtype);
                        tac.push_back("GOTO #L" + to_string(label_counter-1));
                        tac.push_back("#L" + to_string(++label_counter) + ":");
                        free_temp.push(t0);
                        free_temp.push(t1);
                        free_temp.push(t2);
                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));

                        label_counter++;
                    }
#line 2358 "y.tab.c"
    break;

  case 68: /* expr: expr MACOP expr  */
#line 535 "parser.y"
                                      {
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        if(string((yyvsp[-2].node).type)!="INT" || string((yyvsp[0].node).type)!="INT") sem_errors.push_back("MAC instruction expects only int values");
                        tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[-2].node).lexeme) + " " + string((yyvsp[-1].node).lexeme) + " " + string((yyvsp[0].node).lexeme) + " " + string((yyval.node).type));
                        
                        // printf("%s",string($$.lexeme));
                        // printf("%s",string($1.lexeme));
                        // printf("%s",string($2.lexeme));
                        // printf("%s",string($3.lexeme));
                        // if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        // if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));
                    }
#line 2375 "y.tab.c"
    break;

  case 69: /* expr: expr LE expr  */
#line 547 "parser.y"
                                   {
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[-2].node).lexeme) + " " + string((yyvsp[-1].node).lexeme) + " " + string((yyvsp[0].node).lexeme) + " " + string((yyval.node).type));
                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));
                    }
#line 2386 "y.tab.c"
    break;

  case 70: /* expr: expr LE FLEN OC ID CC  */
#line 553 "parser.y"
                                            {
                        add_tac((yyval.node), (yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-1].node))
                        string t0 = get_temp();
                        tac.push_back(t0+" = "+string_info[(yyvsp[-1].node).lexeme]+" INT");
                        tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[-5].node).lexeme) + " " + string((yyvsp[-4].node).lexeme) + " " + t0 + " " + "INT");

                    }
#line 2398 "y.tab.c"
    break;

  case 71: /* expr: expr GE expr  */
#line 560 "parser.y"
                                   {
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[-2].node).lexeme) + " " + string((yyvsp[-1].node).lexeme) + " " + string((yyvsp[0].node).lexeme) + " " + string((yyval.node).type));
                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));
                    }
#line 2409 "y.tab.c"
    break;

  case 72: /* expr: expr GE FLEN OC ID CC  */
#line 566 "parser.y"
                                            {
                        add_tac((yyval.node), (yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-1].node))
                        string t0 = get_temp();
                        tac.push_back(t0+" = "+string_info[(yyvsp[-1].node).lexeme]+" INT");
                        tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[-5].node).lexeme) + " " + string((yyvsp[-4].node).lexeme) + " " + t0 + " " + "INT");

                    }
#line 2421 "y.tab.c"
    break;

  case 73: /* expr: expr LT expr  */
#line 573 "parser.y"
                                   {
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[-2].node).lexeme) + " " + string((yyvsp[-1].node).lexeme) + " " + string((yyvsp[0].node).lexeme) + " " + string((yyval.node).type));
                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));
                    }
#line 2432 "y.tab.c"
    break;

  case 74: /* expr: expr LT FLEN OC ID CC  */
#line 579 "parser.y"
                                            {
                        add_tac((yyval.node), (yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-1].node))
                        string t0 = get_temp();
                        tac.push_back(t0+" = "+string_info[(yyvsp[-1].node).lexeme]+" INT");
                        tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[-5].node).lexeme) + " " + string((yyvsp[-4].node).lexeme) + " " + t0 + " " + "INT");

                    }
#line 2444 "y.tab.c"
    break;

  case 75: /* expr: expr GT expr  */
#line 586 "parser.y"
                                   {
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[-2].node).lexeme) + " " + string((yyvsp[-1].node).lexeme) + " " + string((yyvsp[0].node).lexeme) + " " + string((yyval.node).type));
                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));
                    }
#line 2455 "y.tab.c"
    break;

  case 76: /* expr: expr GT FLEN OC ID CC  */
#line 592 "parser.y"
                                            {
                        add_tac((yyval.node), (yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-1].node))
                        string t0 = get_temp();
                        tac.push_back(t0+" = "+string_info[(yyvsp[-1].node).lexeme]+" INT");
                        tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[-5].node).lexeme) + " " + string((yyvsp[-4].node).lexeme) + " " + t0 + " " + "INT");

                    }
#line 2467 "y.tab.c"
    break;

  case 77: /* expr: expr EQ expr  */
#line 599 "parser.y"
                                   {
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[-2].node).lexeme) + " " + string((yyvsp[-1].node).lexeme) + " " + string((yyvsp[0].node).lexeme) + " " + string((yyval.node).type));
                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));
                    }
#line 2478 "y.tab.c"
    break;

  case 78: /* expr: expr EQ FLEN OC ID CC  */
#line 605 "parser.y"
                                            {
                        add_tac((yyval.node), (yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-1].node))
                        string t0 = get_temp();
                        tac.push_back(t0+" = "+string_info[(yyvsp[-1].node).lexeme]+" INT");
                        tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[-5].node).lexeme) + " " + string((yyvsp[-4].node).lexeme) + " " + t0 + " " + "INT");

                    }
#line 2490 "y.tab.c"
    break;

  case 79: /* expr: expr NE FLEN OC ID CC  */
#line 612 "parser.y"
                                            {
                        add_tac((yyval.node), (yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-1].node))
                        string t0 = get_temp();
                        tac.push_back(t0+" = "+string_info[(yyvsp[-1].node).lexeme]+" INT");
                        tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[-5].node).lexeme) + " " + string((yyvsp[-4].node).lexeme) + " " + t0 + " " + "INT");

                    }
#line 2502 "y.tab.c"
    break;

  case 80: /* expr: expr NE expr  */
#line 619 "parser.y"
                                   {
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        string temp = get_temp();
                        tac.push_back(temp + " = " + string((yyvsp[-2].node).lexeme) + " == " + string((yyvsp[0].node).lexeme) + " " + string((yyval.node).type));
                        tac.push_back(string((yyval.node).lexeme) + " = ~ " + temp + " " + string((yyval.node).type)); 

                        free_temp.push(temp);
                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));
                    }
#line 2517 "y.tab.c"
    break;

  case 81: /* expr: expr AND expr  */
#line 629 "parser.y"
                                    {
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        string l0 = "#L" + to_string(++label_counter);
                        string l1 = "#L" + to_string(++label_counter);
                        string l2 = "#L" + to_string(++label_counter);
                        string l3 = "#L" + to_string(++label_counter);
                        string dtype = string((yyval.node).type);

                        tac.push_back("if " + string((yyvsp[-2].node).lexeme) + " GOTO " + l3 + " else GOTO " + l1);
                        tac.push_back(l3 + ":");
                        tac.push_back("if " + string((yyvsp[0].node).lexeme) + " GOTO " + l0 + " else GOTO " + l1);
                        tac.push_back(l0 + ":");
                        tac.push_back(string((yyval.node).lexeme) + " = 1 " + dtype);
                        tac.push_back("GOTO " + l2);
                        tac.push_back(l1 + ":");
                        tac.push_back(string((yyval.node).lexeme) + " = 0 " + dtype);
                        tac.push_back(l2 + ":");

                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));

                        label_counter++;
                    }
#line 2545 "y.tab.c"
    break;

  case 82: /* expr: expr OR expr  */
#line 652 "parser.y"
                                   {
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        string l0 = "#L" + to_string(++label_counter);
                        string l1 = "#L" + to_string(++label_counter);
                        string l2 = "#L" + to_string(++label_counter);
                        string l3 = "#L" + to_string(++label_counter);
                        string dtype = string((yyval.node).type);

                        tac.push_back("if " + string((yyvsp[-2].node).lexeme) + " GOTO " + l0 + " else GOTO " + l3);
                        tac.push_back(l3 + ":");
                        tac.push_back("if " + string((yyvsp[0].node).lexeme) + " GOTO " + l0 + " else GOTO " + l1);
                        tac.push_back(l0 + ":");
                        tac.push_back(string((yyval.node).lexeme) + " = 1 " + dtype);
                        tac.push_back("GOTO " + l2);
                        tac.push_back(l1 + ":");
                        tac.push_back(string((yyval.node).lexeme) + " = 0 " + dtype);
                        tac.push_back(l2 + ":");

                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));

                        label_counter++;
                    }
#line 2573 "y.tab.c"
    break;

  case 83: /* expr: expr MODULO expr  */
#line 675 "parser.y"
                                       {
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        string t0=get_temp();
                        string t1=get_temp();
                        string t2=get_temp();
                        string a = string((yyval.node).lexeme);
                        string b = string((yyvsp[-2].node).lexeme);
                        string c = string((yyvsp[0].node).lexeme);
                        string dtype = string((yyval.node).type);
                        
                        tac.push_back(a + " = 0 " + dtype);
                        tac.push_back(t0 + " = " + b + " " + dtype);
                        tac.push_back(t2 + " = 1 " + dtype);
                        tac.push_back("#L" + to_string(++label_counter) + ":");
                        tac.push_back(t1 + " = " + t0 + " >= " + c +  "  " + dtype);
                        tac.push_back("if " + t1 + " GOTO " + "#L" + to_string(label_counter+1) + " else GOTO " + "#L" + to_string(label_counter+2));
                        tac.push_back("#L" + to_string(++label_counter) + ":");
                        tac.push_back(t0 + " = " + t0 + " - " + c +  "  " + dtype);
                        tac.push_back("GOTO #L" + to_string(label_counter-1));
                        tac.push_back("#L" + to_string(++label_counter) + ":");
                        tac.push_back(a + " = " + t0 +  "  " + dtype);

                        free_temp.push(t0);
                        free_temp.push(t1);
                        free_temp.push(t2);
                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));

                        label_counter++;
                    }
#line 2608 "y.tab.c"
    break;

  case 84: /* expr: expr BITAND expr  */
#line 705 "parser.y"
                                       {
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[-2].node).lexeme) + " " + string((yyvsp[-1].node).lexeme) + " " + string((yyvsp[0].node).lexeme) + " " + string((yyval.node).type));
                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));
                    }
#line 2619 "y.tab.c"
    break;

  case 85: /* expr: expr BITOR expr  */
#line 711 "parser.y"
                                      {
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[-2].node).lexeme) + " " + string((yyvsp[-1].node).lexeme) + " " + string((yyvsp[0].node).lexeme) + " " + string((yyval.node).type));
                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));
                    }
#line 2630 "y.tab.c"
    break;

  case 86: /* expr: expr XOR expr  */
#line 717 "parser.y"
                                    {
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        string a = string((yyval.node).lexeme);
                        string b = string((yyvsp[-2].node).lexeme);
                        string b_= get_temp();
                        string c = string((yyvsp[0].node).lexeme);
                        string c_= get_temp();

                        tac.push_back(b_ + " = ~ " + b + " " + string((yyvsp[-2].node).type));
                        tac.push_back(c_ + " = ~ " + c + " " + string((yyvsp[0].node).type));
                        string t1=get_temp();
                        string t2=get_temp();
                        tac.push_back(t1 + " = " + b + " & " + c_ + " " + string((yyval.node).type));
                        tac.push_back(t2 + " = " + b_ + " & " + c + " " + string((yyval.node).type));
                        tac.push_back(a + " = " + t1 + " | " + t2 + " " + string((yyval.node).type));

                        free_temp.push(b_);
                        free_temp.push(c_);
                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));

                        label_counter++;
                    }
#line 2658 "y.tab.c"
    break;

  case 87: /* expr: expr LEFTSHIFT expr  */
#line 740 "parser.y"
                                          {
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        string d = string((yyvsp[0].node).lexeme);
                        string t3 = get_temp();
                        string t4 = get_temp();
                        string l0 = "#L" + to_string(++label_counter);
                        string l1 = "#L" + to_string(++label_counter);
                        string l2 = "#L" + to_string(++label_counter);

                        string t0= get_temp();
                        string t1= get_temp();
                        string t2= get_temp();
                        string a = string((yyval.node).lexeme);
                        string b = string((yyvsp[-2].node).lexeme);
                        string c = get_temp();
                        tac.push_back(c + " = 2 INT");
                        string dtype = string((yyval.node).type);
                        
                        tac.push_back(t3 + " = 0 INT");
                        tac.push_back(l2 + ":");
                        tac.push_back(t4 + " = " + t3 + " < " + d + " INT");
                        tac.push_back("\nif " + t4 + " GOTO " + l0 + " else GOTO " + l1);
                        tac.push_back(l0 + ":");
                        tac.push_back(a + " = 0 " + dtype);
                        tac.push_back(t0 + " = 0 " + dtype);
                        tac.push_back(t2 + " = 1 " + dtype);
                        tac.push_back("#L" + to_string(++label_counter) + ":");
                        tac.push_back(t1 + " = " + t0 + " < " + c +  "  " + dtype);
                        tac.push_back("if " + t1 + " GOTO " + "#L" + to_string(label_counter+1) + " else GOTO " + "#L" + to_string(label_counter+2));
                        tac.push_back("#L" + to_string(++label_counter) + ":");
                        tac.push_back(a + " = " + a + " + " + b +  "  " + dtype);
                        tac.push_back(t0 + " = " + t0 + " + " + t2 +  "  " + dtype);
                        tac.push_back("GOTO #L" + to_string(label_counter-1));
                        tac.push_back("#L" + to_string(++label_counter) + ":");
                        tac.push_back("GOTO " + l2);
                        tac.push_back(l1 + ":");

                        free_temp.push(t0);
                        free_temp.push(t1);
                        free_temp.push(t2);
                        free_temp.push(t3);
                        free_temp.push(t4);
                        free_temp.push(c);
                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));

                        label_counter++;
                    }
#line 2711 "y.tab.c"
    break;

  case 88: /* expr: expr RIGHTSHIFT expr  */
#line 788 "parser.y"
                                           {
                        add_tac((yyval.node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node))
                        string d = string((yyvsp[0].node).lexeme);
                        string t3 = get_temp();
                        string t4 = get_temp();
                        string l0 = "#L" + to_string(++label_counter);
                        string l1 = "#L" + to_string(++label_counter);
                        string l2 = "#L" + to_string(++label_counter);

                        string t0=get_temp();
                        string t1=get_temp();
                        string t2=get_temp();
                        string a = string((yyval.node).lexeme);
                        string b = string((yyvsp[-2].node).lexeme);
                        string c = get_temp();
                        tac.push_back(c + " = 2 INT");
                        string dtype = string((yyval.node).type);
                        
                        tac.push_back(t3 + " = 0 INT");
                        tac.push_back(l2 + ":");
                        tac.push_back(t4 + " = " + t3 + " < " + d + " INT");
                        tac.push_back("\nif " + t4 + " GOTO " + l0 + " else GOTO " + l1);
                        tac.push_back(l0 + ":");
                        tac.push_back(a + " = 0 " + dtype);
                        tac.push_back(t0 + " = " + b + " " + dtype);
                        tac.push_back(t2 + " = 1 " + dtype);
                        tac.push_back("#L" + to_string(++label_counter) + ":");
                        tac.push_back(t1 + " = " + t0 + " >= " + c +  "  " + dtype);
                        tac.push_back("if " + t1 + " GOTO " + "#L" + to_string(label_counter+1) + " else GOTO " + "#L" + to_string(label_counter+2));
                        tac.push_back("#L" + to_string(++label_counter) + ":");
                        tac.push_back(a + " = " + a + " + " + t2 +  "  " + dtype);
                        tac.push_back(t0 + " = " + t0 + " - " + c +  "  " + dtype);
                        tac.push_back("GOTO #L" + to_string(label_counter-1));
                        tac.push_back("#L" + to_string(++label_counter) + ":");
                        tac.push_back("GOTO " + l2);
                        tac.push_back(l1 + ":");

                        free_temp.push(t0);
                        free_temp.push(t1);
                        free_temp.push(t2);
                        free_temp.push(t3);
                        free_temp.push(t4);
                        free_temp.push(c);
                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));

                        label_counter++;
                    }
#line 2764 "y.tab.c"
    break;

  case 89: /* expr: unary_expr  */
#line 836 "parser.y"
                                 {
                        strcpy((yyval.node).type, (yyvsp[0].node).type);
                        strcpy((yyval.node).type, (yyvsp[0].node).type);
                        sprintf((yyval.node).lexeme, "%s", (yyvsp[0].node).lexeme);
                    }
#line 2774 "y.tab.c"
    break;

  case 90: /* expr: primary_expr  */
#line 841 "parser.y"
                                   {
                        strcpy((yyval.node).type, (yyvsp[0].node).type);
                        strcpy((yyval.node).type, (yyvsp[0].node).type);
                        strcpy((yyval.node).lexeme, (yyvsp[0].node).lexeme);
                    }
#line 2784 "y.tab.c"
    break;

  case 91: /* expr: postfix_expr  */
#line 846 "parser.y"
                                   {
                        strcpy((yyval.node).type, (yyvsp[0].node).type);
                        sprintf((yyval.node).lexeme, "%s", (yyvsp[0].node).lexeme);
                    }
#line 2793 "y.tab.c"
    break;

  case 92: /* expr: expr ADD ADD  */
#line 850 "parser.y"
                                  {
                        // add_tac($$, $1, $2, $3)
                        string t0=get_temp();
                        string t1=get_temp();
                        string t2=get_temp();
                        string a = string((yyvsp[-2].node).lexeme);
                        tac.push_back(t1 + " = 1 "+ string((yyval.node).type));
                        tac.push_back(t2 + " = "+a+ " + " + t1+ " " +string((yyval.node).type));
                        tac.push_back(a+" = "+t2+ " " +string((yyval.node).type));
                        // tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + "1" + " " + string($$.type));
                        if(const_temps.find(string((yyvsp[-2].node).lexeme)) == const_temps.end() && (yyvsp[-2].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-2].node).lexeme));
                        free_temp.push(t0);
                        free_temp.push(t1);
                        free_temp.push(t2);
                    }
#line 2813 "y.tab.c"
    break;

  case 93: /* postfix_expr: func_call  */
#line 867 "parser.y"
                              {
                        //sem_errors.push_back("Hi");
                        strcpy((yyval.node).type, (yyvsp[0].node).type);
                        sprintf((yyval.node).lexeme, "%s", (yyvsp[0].node).lexeme);
                    }
#line 2823 "y.tab.c"
    break;

  case 94: /* postfix_expr: ID OS expr CS  */
#line 873 "parser.y"
                                  {
                        bool isString =0;
                        string dtype = func_table[curr_func_name].symbol_table[string((yyvsp[-3].node).lexeme)].data_type;
                        if(dtype=="STRING"|| dtype=="STRING") isString=1;
                        if(check_declaration(string((yyvsp[-3].node).lexeme)) && !isString && func_table[curr_func_name].symbol_table[string((yyvsp[-3].node).lexeme)].isArray == 0) { 
                            sem_errors.push_back("Line no " + to_string(countn+1) +" : " +string((yyvsp[-3].node).lexeme)+ " Variable is not an array from expr" + dtype ); 
                        }
                        check_scope(string((yyvsp[-3].node).lexeme));
                        strcpy((yyval.node).type, func_table[curr_func_name].symbol_table[string((yyvsp[-3].node).lexeme)].data_type.c_str());
                        sprintf((yyval.node).lexeme, get_temp().c_str());
                        tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[-3].node).lexeme) + " [ " + string((yyvsp[-1].node).lexeme) + " ] " + string((yyval.node).type));
                        
                        if(const_temps.find(string((yyvsp[-1].node).lexeme)) == const_temps.end() && (yyvsp[-1].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-1].node).lexeme));
                    }
#line 2842 "y.tab.c"
    break;

  case 95: /* unary_expr: unary_op primary_expr  */
#line 889 "parser.y"
                                          {
                        strcpy((yyval.node).type, (yyvsp[0].node).type);
                        sprintf((yyval.node).lexeme, get_temp().c_str());
                        if(string((yyvsp[-1].node).lexeme) == "~" || string((yyvsp[-1].node).lexeme) == "-"){
                            tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[-1].node).lexeme) + " " + string((yyvsp[0].node).lexeme) + " " + string((yyval.node).type));
                        }
                        else if(string((yyvsp[-1].node).lexeme) == "+"){
                            tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[0].node).lexeme) + " " + string((yyval.node).type));
                        }
                        else{
                            tac.push_back(string((yyval.node).lexeme) + " = ~ " + string((yyvsp[0].node).lexeme) + " " + string((yyval.node).type));
                        }

                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));
                    }
#line 2862 "y.tab.c"
    break;

  case 96: /* primary_expr: ID  */
#line 906 "parser.y"
                       {
                        check_declaration(string((yyvsp[0].node).lexeme));
                        // check_scope(string($1.lexeme));
                        strcpy((yyval.node).type, func_table[curr_func_name].symbol_table[string((yyvsp[0].node).lexeme)].data_type.c_str());
                        strcpy((yyval.node).lexeme, (yyvsp[0].node).lexeme);
                    }
#line 2873 "y.tab.c"
    break;

  case 97: /* primary_expr: const  */
#line 912 "parser.y"
                            {
                        strcpy((yyval.node).type, (yyvsp[0].node).type);

                        string t=get_temp();
                        sprintf((yyval.node).lexeme, t.c_str());
                        tac.push_back(string((yyval.node).lexeme) + " = " + string((yyvsp[0].node).lexeme) + " " + string((yyval.node).type)); 
                        temp_map[string((yyvsp[0].node).lexeme)] = string((yyval.node).lexeme);

                        const_temps.insert(t);
                        // if(temp_map[string($1.lexeme)] == ""){
                        //     string t=get_temp();
                        //     sprintf($$.lexeme, t.c_str());
                        //     tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($$.type)); 
                        //     temp_map[string($1.lexeme)] = string($$.lexeme);

                        //     const_temps.insert(t);
                        // }
                        // else{
                        //     //tac.push_back(temp_map[string($1.lexeme)] + " = " + string($1.lexeme) + " " + string($$.type)); 
                        //     strcpy($$.lexeme, temp_map[string($1.lexeme)].c_str());
                        // }
                    }
#line 2900 "y.tab.c"
    break;

  case 98: /* primary_expr: OC expr CC  */
#line 934 "parser.y"
                                 {
                        strcpy((yyval.node).type, (yyvsp[-1].node).type);
                        strcpy((yyval.node).lexeme, (yyvsp[-1].node).lexeme);
                    }
#line 2909 "y.tab.c"
    break;

  case 103: /* const: INT_NUM  */
#line 946 "parser.y"
                            {
                        strcpy((yyval.node).type, "INT");
                        strcpy((yyval.node).lexeme, (yyvsp[0].node).lexeme);
                    }
#line 2918 "y.tab.c"
    break;

  case 104: /* const: FLOAT_NUM  */
#line 950 "parser.y"
                                {
                        strcpy((yyval.node).type, "FLOAT");
                        strcpy((yyval.node).lexeme, (yyvsp[0].node).lexeme);
                    }
#line 2927 "y.tab.c"
    break;

  case 105: /* const: CHARACTER  */
#line 954 "parser.y"
                                {
                        // printf("CHAR");
                        // printf("\n");
                        // printf($1.lexeme);
                        // printf("\n");
                        strcpy((yyval.node).type, "CHAR");
                        strcpy((yyval.node).lexeme, (yyvsp[0].node).lexeme);
                    }
#line 2940 "y.tab.c"
    break;

  case 106: /* assign: ID ASSIGN expr  */
#line 964 "parser.y"
                                   {
                        // printf($1.lexeme);
                        // printf($3.lexeme);
                        bool k= check_declaration(string((yyvsp[-2].node).lexeme));
                        if(k) {
                        if(func_table[curr_func_name].symbol_table.find(string((yyvsp[-2].node).lexeme))!=func_table[curr_func_name].symbol_table.end()){
                            char dtype[256]; // Choose an appropriate size for the array

                        // Then copy the C-string into the array
                        strcpy(dtype, func_table[curr_func_name].symbol_table[string((yyvsp[-2].node).lexeme)].data_type.c_str());

                            // printf(dtype);
                            // printf(string($3.type).c_str());
                        check_type(func_table[curr_func_name].symbol_table[string((yyvsp[-2].node).lexeme)].data_type, string((yyvsp[0].node).type));
                        check_scope(string((yyvsp[-2].node).lexeme));
                        tac.push_back(string((yyvsp[-2].node).lexeme) + " = " + string((yyvsp[0].node).lexeme) + " " + func_table[curr_func_name].symbol_table[string((yyvsp[-2].node).lexeme)].data_type);

                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));
                        }
                        }
                        
                    }
#line 2967 "y.tab.c"
    break;

  case 107: /* assign: ID OS expr CS ASSIGN expr  */
#line 987 "parser.y"
                                              {
                        check_type(func_table[curr_func_name].symbol_table[string((yyvsp[-5].node).lexeme)].data_type, string((yyvsp[0].node).type));
                        bool isString =0;
                        string dtype = func_table[curr_func_name].symbol_table[string((yyvsp[-5].node).lexeme)].data_type;
                        if(dtype=="STRING"|| dtype=="STRING") isString=1;
                        if(check_declaration(string((yyvsp[-5].node).lexeme)) && !isString && func_table[curr_func_name].symbol_table[string((yyvsp[-5].node).lexeme)].isArray == 0) { 
                            sem_errors.push_back("Line no " + to_string(countn+1) +" : " +string((yyvsp[-5].node).lexeme)+ " Variable is not an array from assign expr" + dtype); 
                        }
                        check_scope(string((yyvsp[-5].node).lexeme));
                        tac.push_back(string((yyvsp[-5].node).lexeme) + " [ " + string((yyvsp[-3].node).lexeme) + " ] = " + string((yyvsp[0].node).lexeme) + " " + func_table[curr_func_name].symbol_table[string((yyvsp[-5].node).lexeme)].data_type);

                        if(const_temps.find(string((yyvsp[0].node).lexeme)) == const_temps.end() && (yyvsp[0].node).lexeme[0] == '@') free_temp.push(string((yyvsp[0].node).lexeme));
                    }
#line 2985 "y.tab.c"
    break;

  case 110: /* $@6: %empty  */
#line 1005 "parser.y"
                        {
                        sprintf((yyvsp[0].node).parentNext, "#L%d", label_counter++);
                    }
#line 2993 "y.tab.c"
    break;

  case 111: /* $@7: %empty  */
#line 1008 "parser.y"
                               { 
                        tac.push_back("if " + string((yyvsp[-1].node).lexeme) + " GOTO #L" + to_string(label_counter) + " else GOTO #L" + to_string(label_counter+1));
                        sprintf((yyvsp[-1].node).if_body, "#L%d", label_counter++);
                        sprintf((yyvsp[-1].node).else_body, "#L%d", label_counter++); 
                        tac.push_back(string((yyvsp[-1].node).if_body) + ":");

                        if(const_temps.find(string((yyvsp[-1].node).lexeme)) == const_temps.end() && (yyvsp[-1].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-1].node).lexeme));
                    }
#line 3006 "y.tab.c"
    break;

  case 112: /* $@8: %empty  */
#line 1017 "parser.y"
                    {
                      scope_history.push(++scope_counter);  
                    }
#line 3014 "y.tab.c"
    break;

  case 113: /* $@9: %empty  */
#line 1019 "parser.y"
                                   {  
                        scope_history.pop(); 
                        --scope_counter;
                        tac.push_back("GOTO " + string((yyvsp[-9].node).parentNext));
                        tac.push_back(string((yyvsp[-6].node).else_body) + ":");
                    }
#line 3025 "y.tab.c"
    break;

  case 114: /* if_stmt: IF $@6 OC expr CC $@7 OF $@8 stmt_list CF $@9 elif_stmt else_stmt  */
#line 1025 "parser.y"
                                         {   
                        tac.push_back(string((yyvsp[-12].node).parentNext) + ":");
                    }
#line 3033 "y.tab.c"
    break;

  case 115: /* $@10: %empty  */
#line 1030 "parser.y"
                         {
                        string str = tac[tac.size()-2].substr(5);
                        char* hold = const_cast<char*>(str.c_str());
                        sprintf((yyvsp[0].node).parentNext, "%s", hold);
                    }
#line 3043 "y.tab.c"
    break;

  case 116: /* $@11: %empty  */
#line 1035 "parser.y"
                               {
                        tac.push_back("if " + string((yyvsp[-1].node).lexeme) + " GOTO #L" + to_string(label_counter) + " else GOTO #L" + to_string(label_counter+1));
                        sprintf((yyvsp[-1].node).if_body, "#L%d", label_counter++);
                        sprintf((yyvsp[-1].node).else_body, "#L%d", label_counter++); 
                        tac.push_back(string((yyvsp[-1].node).if_body) + ":");

                        if(const_temps.find(string((yyvsp[-1].node).lexeme)) == const_temps.end() && (yyvsp[-1].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-1].node).lexeme));
                    }
#line 3056 "y.tab.c"
    break;

  case 117: /* $@12: %empty  */
#line 1044 "parser.y"
                    {
                        scope_history.push(++scope_counter);
                    }
#line 3064 "y.tab.c"
    break;

  case 118: /* $@13: %empty  */
#line 1047 "parser.y"
                                 {
                        scope_history.pop();
                        --scope_counter;
                        tac.push_back("GOTO " + string((yyvsp[-9].node).parentNext));
                        tac.push_back(string((yyvsp[-6].node).else_body) + ":");
                    }
#line 3075 "y.tab.c"
    break;

  case 121: /* $@14: %empty  */
#line 1057 "parser.y"
                            {scope_history.push(++scope_counter);}
#line 3081 "y.tab.c"
    break;

  case 122: /* else_stmt: ELSE OF $@14 stmt_list CF  */
#line 1057 "parser.y"
                                                                               {scope_history.pop(); --scope_counter;}
#line 3087 "y.tab.c"
    break;

  case 124: /* $@15: %empty  */
#line 1061 "parser.y"
                           {
                        int temp_label = label_counter;
                        loop_break.push(temp_label);
                        sprintf((yyvsp[0].node).parentNext, "#L%d", label_counter++);
                    }
#line 3097 "y.tab.c"
    break;

  case 125: /* $@16: %empty  */
#line 1066 "parser.y"
                          {
                        temp_index = variable_count;
                        tac.push_back("@t" + to_string(variable_count++) + " = " + string((yyvsp[0].node).lexeme) + " " + func_table[curr_func_name].symbol_table[string((yyvsp[0].node).lexeme)].data_type);
                    }
#line 3106 "y.tab.c"
    break;

  case 126: /* $@17: %empty  */
#line 1070 "parser.y"
                                         {
                        // strcpy($8.id, $4.lexeme);
                        // strcpy($8.parentNext, $1.parentNext);
                    }
#line 3115 "y.tab.c"
    break;

  case 127: /* switch_stmt: SWITCH $@15 OC ID $@16 CC OF case_stmt_list $@17 default_stmt CF  */
#line 1074 "parser.y"
                                    {
                        tac.push_back(string((yyvsp[-10].node).parentNext) + ":");
                        loop_break.pop();
                    }
#line 3124 "y.tab.c"
    break;

  case 128: /* case_stmt_list: case_stmt case_stmt_list  */
#line 1080 "parser.y"
                                             {
                        strcpy((yyvsp[-1].node).id, (yyval.node).id);
                        strcpy((yyvsp[-1].node).parentNext, (yyval.node).parentNext);
                    }
#line 3133 "y.tab.c"
    break;

  case 130: /* $@18: %empty  */
#line 1087 "parser.y"
                         {
                        // tac.push_back(string($4.if_body) + ":");
                    }
#line 3141 "y.tab.c"
    break;

  case 131: /* $@19: %empty  */
#line 1090 "parser.y"
                             {
                        char* hold = const_cast<char*>(to_string(variable_count).c_str());
                        sprintf((yyvsp[0].node).temp, "%s", hold);
                        tac.push_back("@t" + to_string(variable_count++) + " = " + string((yyvsp[0].node).lexeme) + " " + string((yyvsp[0].node).type));
                        tac.push_back("@t" + to_string(variable_count++) + " = " + "@t" + to_string(temp_index) + " == " + "@t" + string((yyvsp[0].node).temp) + " INT");
                        tac.push_back("if @t" + to_string(variable_count-1) + " GOTO #L" + to_string(label_counter) + " else GOTO #L" + to_string(label_counter+1));
                        tac.push_back("#L" + to_string(label_counter) + ":");
                        sprintf((yyvsp[0].node).case_body, "#L%d", label_counter++);
                        sprintf((yyvsp[0].node).parentNext, "#L%d", label_counter++);
                    }
#line 3156 "y.tab.c"
    break;

  case 132: /* case_stmt: CASE $@18 OC const $@19 CC COLON stmt_list  */
#line 1100 "parser.y"
                                       {
                        tac.push_back(string((yyvsp[-4].node).parentNext) + ":");
                    }
#line 3164 "y.tab.c"
    break;

  case 135: /* $@20: %empty  */
#line 1108 "parser.y"
                          {
                        sprintf((yyvsp[0].node).loop_body, "#L%d", label_counter); 
                        loop_continue.push(label_counter++);
                        tac.push_back("\n" + string((yyvsp[0].node).loop_body) + ":");
                    }
#line 3174 "y.tab.c"
    break;

  case 136: /* $@21: %empty  */
#line 1114 "parser.y"
                    {
                        sprintf((yyvsp[-1].node).if_body, "#L%d", label_counter++); 

                        loop_break.push(label_counter);
                        sprintf((yyvsp[-1].node).else_body, "#L%d", label_counter++); 

                        tac.push_back("\nif " + string((yyvsp[-1].node).lexeme) + " GOTO " + string((yyvsp[-1].node).if_body) + " else GOTO " + string((yyvsp[-1].node).else_body));
                        tac.push_back("\n" + string((yyvsp[-1].node).if_body) + ":");

                        if(const_temps.find(string((yyvsp[-1].node).lexeme)) == const_temps.end() && (yyvsp[-1].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-1].node).lexeme));
                        
                    }
#line 3191 "y.tab.c"
    break;

  case 137: /* $@22: %empty  */
#line 1126 "parser.y"
                      {
                        scope_history.push(++scope_counter);
                    }
#line 3199 "y.tab.c"
    break;

  case 138: /* while_loop_stmt: WHILE $@20 OC expr CC $@21 OF $@22 stmt_list CF  */
#line 1129 "parser.y"
                    {
                        scope_history.pop();
                        --scope_counter;
                        tac.push_back("GOTO " + string((yyvsp[-9].node).loop_body));
                        tac.push_back("\n" + string((yyvsp[-6].node).else_body) + ":");
                        loop_continue.pop();
                        loop_break.pop();
                    }
#line 3212 "y.tab.c"
    break;

  case 139: /* $@23: %empty  */
#line 1138 "parser.y"
                                       {
                        sprintf((yyvsp[-3].node).loop_body, "#L%d", label_counter++); 
                        tac.push_back("\n" + string((yyvsp[-3].node).loop_body) + ":");
                    }
#line 3221 "y.tab.c"
    break;

  case 140: /* $@24: %empty  */
#line 1142 "parser.y"
                              {  
                        sprintf((yyvsp[-1].node).if_body, "#L%d", label_counter++); 

                        loop_break.push(label_counter);
                        sprintf((yyvsp[-1].node).else_body, "#L%d", label_counter++); 

                        tac.push_back("\nif " + string((yyvsp[-1].node).lexeme) + " GOTO " + string((yyvsp[-1].node).if_body) + " else GOTO " + string((yyvsp[-1].node).else_body));

                        sprintf((yyvsp[-1].node).loop_body, "#L%d", label_counter); 
                        loop_continue.push(label_counter++);
                        tac.push_back("\n" + string((yyvsp[-1].node).loop_body) + ":");

                        if(const_temps.find(string((yyvsp[-1].node).lexeme)) == const_temps.end() && (yyvsp[-1].node).lexeme[0] == '@') free_temp.push(string((yyvsp[-1].node).lexeme));
                    }
#line 3240 "y.tab.c"
    break;

  case 141: /* $@25: %empty  */
#line 1156 "parser.y"
                              {
                        tac.push_back("GOTO " + string((yyvsp[-9].node).loop_body));
                        tac.push_back("\n" + string((yyvsp[-4].node).if_body) + ":");
                    }
#line 3249 "y.tab.c"
    break;

  case 142: /* $@26: %empty  */
#line 1161 "parser.y"
                    {
                        scope_history.push(++scope_counter);
                    }
#line 3257 "y.tab.c"
    break;

  case 143: /* for_loop_stmt: FOR OC assign SCOL $@23 expr SCOL $@24 assign CC $@25 OF $@26 stmt_list CF  */
#line 1164 "parser.y"
                                 {
                        scope_history.pop();
                        --scope_counter;
                        tac.push_back("GOTO " + string((yyvsp[-9].node).loop_body));
                        tac.push_back("\n" + string((yyvsp[-9].node).else_body) + ":");
                        loop_continue.pop();
                        loop_break.pop();
                    }
#line 3270 "y.tab.c"
    break;

  case 144: /* $@27: %empty  */
#line 1173 "parser.y"
                       {
                        func_call_id.push({string((yyvsp[0].node).lexeme), func_table[string((yyvsp[0].node).lexeme)].param_types});
                    }
#line 3278 "y.tab.c"
    break;

  case 145: /* func_call: ID $@27 OC arg_list CC  */
#line 1176 "parser.y"
                                    {
                        // char dtype[256]; // Choose an appropriate size for the array

                        // // Then copy the C-string into the array
                        // strcpy(dtype, func_table[curr_func_name].symbol_table[string($1.lexeme)].data_type.c_str());
                        // char debugInfo[] = "from func call";

                        // // Use sprintf to format and print the combined string
                        // char result[256]; // Choose a size that can hold the combined string
                        // sprintf(result, "%s %s\n", dtype, debugInfo);
                        // printf("%s", result);
                        strcpy((yyval.node).type, func_table[string((yyvsp[-4].node).lexeme)].return_type.c_str());
                        func_call_id.pop();
                        sprintf((yyval.node).lexeme, get_temp().c_str());

                        tac.push_back(string((yyval.node).lexeme) + " = @call " + string((yyvsp[-4].node).lexeme) + " " + func_table[string((yyvsp[-4].node).lexeme)].return_type + " " + to_string(func_table[string((yyvsp[-4].node).lexeme)].num_params));
                    }
#line 3300 "y.tab.c"
    break;

  case 146: /* arg_list: arg COMMA arg_list  */
#line 1195 "parser.y"
                                       {
                        int sz = func_call_id.top().second.size();
                        string type = func_call_id.top().second[sz-1];
                        func_call_id.top().second.pop_back();
                        if(type_check(string((yyvsp[-2].node).type), type)) {
                            sem_errors.push_back("datatype for argument not matched in line " + to_string(countn+1));
                        }
                    }
#line 3313 "y.tab.c"
    break;

  case 147: /* arg_list: arg  */
#line 1203 "parser.y"
                          {
                        int sz = func_call_id.top().second.size();
                        string type = func_call_id.top().second[sz-1];
                        func_call_id.top().second.pop_back();
                        if(type_check(string((yyvsp[0].node).type), type)) {
                            sem_errors.push_back("datatype for argument not matched in line " + to_string(countn+1));
                        }
                    }
#line 3326 "y.tab.c"
    break;

  case 149: /* arg: expr  */
#line 1214 "parser.y"
                         {
                        tac.push_back("param " + string((yyvsp[0].node).lexeme) + " " + string((yyvsp[0].node).type));
                    }
#line 3334 "y.tab.c"
    break;


#line 3338 "y.tab.c"

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
      yyerror (YY_("syntax error"));
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
                      yytoken, &yylval);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1219 "parser.y"


int main(int argc, char *argv[]) {
    /* yydebug = 1; */
    yyparse();
    for(auto item: sem_errors){
        cout << item << endl;
    }
    if(sem_errors.size() > 0)
        exit(0);
    for(auto x: tac)
        cout << x << endl;
    
}

bool check_declaration(string variable){
    bool a = func_table[curr_func_name].symbol_table.find(variable) == func_table[curr_func_name].symbol_table.end();
    bool b = func_table["global"].symbol_table.find(variable) == func_table["global"].symbol_table.end();
    if(a&&b){
        sem_errors.push_back(variable + " Variable not declared in line " + to_string(countn+1) + " before usage.");
        return false;
    }
    return true;
}

bool check_scope(string variable){
    bool a = func_table[curr_func_name].symbol_table.find(variable) == func_table[curr_func_name].symbol_table.end();
    bool b = func_table["global"].symbol_table.find(variable) == func_table["global"].symbol_table.end();
    if(a&&b){
        sem_errors.push_back(variable + " Variable not declared in line " + to_string(countn+1) + " before usage.");
        return false;
    }
    if(curr_func_name=="global") return 1;
    int var_scope = func_table[curr_func_name].symbol_table[variable].scope;
    // int curr_scope = scope_counter;
    stack<int> temp_stack(scope_history);
    // cout << "variable: " << variable << endl;
    // cout << "var_scope: " << var_scope << endl;
    //PrintStack(temp_stack);
    //printf("\n");
    // cout << endl;
    while(!temp_stack.empty()){
        if(temp_stack.top() == var_scope){
            return true;
        }
        temp_stack.pop();
    }
    sem_errors.push_back("Scope of variable '" + variable +"' not matching in line " + to_string(countn+1) + ".");
    return true;
}

bool multiple_declaration(string variable){
    if((func_table[curr_func_name].symbol_table.find(variable) != func_table[curr_func_name].symbol_table.end())){
        sem_errors.push_back("redeclaration of '" + variable + "' in line " + to_string(countn+1));
        return true;
    }
    return false;
}

bool check_type(string l, string r){
    // if(r == "FLOAT" && l == "CHAR"){
    //     sem_errors.push_back("Cannot convert type FLOAT to CHAR in line " + to_string(countn+1));
    //     return false;
    // }
    // if(l == "FLOAT" && r == "CHAR"){
    //     sem_errors.push_back("Cannot convert typr CHAR to FLOAT in line " + to_string(countn+1));
    //     return false;
    // }
    return 0;
}

bool is_reserved_word(string id){
    for(auto &item: id){
        item = tolower(item);
    }
    auto iterator = find(reserved.begin(), reserved.end(), id);
    if(iterator != reserved.end()){
        sem_errors.push_back("Reserved keyword used: '" + id + "' in line " + to_string(countn+1));
        return true;
    }
    return false;
}

bool type_check(string type1, string type2) {
    // if((type1 == "FLOAT" and type2 == "CHAR") or (type1 == "CHAR" and type2 == "FLOAT")) {
    //     return true;
    // }
    // return false;
    return 0;
}

void yyerror(const char* msg) {
    sem_errors.push_back("syntax error in line " + to_string(countn+1));
    for(auto item: sem_errors)
        cout << item << endl;
    // fprintf(stderr, "%s\n", msg);
    cout << msg << endl;  // Print the actual error message

    exit(1);
}

string get_temp(){
    if(free_temp.empty()){
        return "@t" + to_string(variable_count++);
    }
    string t=free_temp.front();
    free_temp.pop(); 
    return t; 
}
void PrintStack(stack<int> s)
{
    if (s.empty())
        return;
    int x = s.top();
    s.pop();
    cout << x << ' ';
    PrintStack(s);
    s.push(x);
}


// check if void functions has return type
// deal with scope for function arguments
// deal with scope for arrays
// scope in switch statement

//Write documentation for the above code
//Write documentation for the above code
//The above code takes lexemes from the lexer and parses it to check for syntax errors and semantic errors
//

