/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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

#line 210 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
