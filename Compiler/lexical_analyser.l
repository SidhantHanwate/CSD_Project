%{
#include "y.tab.h"
#include <string.h>

int countn=0;
// extern int verbose_flag;
int verbose_flag = 1;

%}

%option yylineno

alpha [a-zA-Z_]
digit [0-9]

%%

"include"                       { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
                             printf("Processing include: %s\n", yytext);
    }return INCLUDE; }
"int"                       { strcpy(yylval.node.lexeme, yytext);if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    } return INT; }
"char"                      { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return CHAR; }
"float"                     { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return FLOAT; }
"string"                    { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return STRING; }
"bool"                      { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return BOOL; }
"void"                      { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return VOID; }
"return"                    { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return RETURN; }
"progin"                     { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return INPUT; }
"progout"                    { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return OUTPUT; }
"switch"                    { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return SWITCH; }
"case"                      { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return CASE; }
"break"                     { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return BREAK; }
"continue"                  { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return CONTINUE; }
"default"                   { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return DEFAULT; }
"if"                        { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return IF; }
"elif"                      { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return ELIF; }
"else"                      { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return ELSE; }
"while"                     { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return WHILE; }
"for"                       { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return FOR; }
"len"                       { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return FLEN; }
"typeof"                    { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return TYPEOF; }
"mac"                       { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
                             printf("Processing include: %s\n", yytext);
    }return MAC; }
"reset"                       { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
                             printf("Processing include: %s\n", yytext);
    }return RESET; }

{digit}+                    { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return INT_NUM; }
{digit}*\.{digit}+          { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return FLOAT_NUM;}
{alpha}({alpha}|{digit})*   { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return ID; }


"<<"			            { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return LEFTSHIFT; }
">>"			            { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return RIGHTSHIFT; }


"<="                        { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return LE; }
">="                        { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return GE; }
"=="                        { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return EQ; }
"!="                        { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return NE; }
">"	                        { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return GT; }
"<"	                        { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return LT; }
"&&"	                    { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return AND; }
"||"	                    { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return OR; }


"+"                         { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return ADD; }
"-"                         { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return SUBTRACT; }
"/"                         { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return DIVIDE; }
"%"                         { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return MODULO;}
"*"                         { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return MULTIPLY; }
"="                         { strcpy(yylval.node.lexeme, yytext); return ASSIGN; }


"&"			                { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return BITAND; }
"|"			                { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return BITOR; }
"~"			                { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return NEGATION; }
"^"			                { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return XOR; }

"!"					        { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return NOT;}
";"                         { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return SCOL;}
","                         { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return COMMA;}
":"                         { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return COLON;}
"{"                         { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return OF;}
"("                         { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return OC;}
"["                         { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return OS;}
"}"                         { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return CF;}
")"                         { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return CC;}
"]"                         { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return CS;}
"@"                       { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
                             printf("Processing include: %s\n", yytext);
    }return MACOP; }

\/\/.*                      { ; }
\/\*(.*\n)*.*\*\/           { ; } 
[ \t]*                      { ; }
[\n]                        { countn++; }
["].*["]                   { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return STR; }
['][\\][nb][']|['].[']      { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return CHARACTER; }
[<].*[>]                    { strcpy(yylval.node.lexeme, yytext); if (verbose_flag) {
        printf("Processing include: %s\n", yytext);
    }return HEADERFILE; }
.                           { ; }

%%

int yywrap() {
    return 1;
}