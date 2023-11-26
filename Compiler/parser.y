%{
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

%}

%union{
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
}

%token <node> INCLUDE HEADERFILE INT CHAR FLOAT STRING BOOL VOID RETURN INT_NUM FLOAT_NUM ID LEFTSHIFT RIGHTSHIFT LE GE EQ NE GT LT AND OR NOT ADD SUBTRACT DIVIDE MULTIPLY MODULO BITAND BITOR NEGATION XOR STR CHARACTER CC OC CS OS CF OF COMMA COLON SCOL OUTPUT INPUT SWITCH CASE BREAK DEFAULT IF ELIF ELSE WHILE FOR CONTINUE TYPEOF FLEN MAC RESET MACOP

%type <node> headerfileInclude Program func func_list func_prefix param_list param stmt_list stmt declaration return_stmt data_type func_data_type expr primary_expr unary_expr unary_op const assign if_stmt elif_stmt else_stmt switch_stmt case_stmt case_stmt_list while_loop_stmt for_loop_stmt postfix_expr func_call arg_list arg

%right ASSIGN
%left OR
%left AND
%left BITOR
%left XOR
%left BITAND
%left EQ NE
%left LE GE LT GT
%left LEFTSHIFT RIGHTSHIFT
%left ADD SUBTRACT
%left MULTIPLY DIVIDE MODULO
%left NEGATION

%%

Code            : headerfileInclude Program

headerfileInclude : INCLUDE HEADERFILE headerfileInclude 
                    |
                    ;

Program         :    func_list 
                    ;

func_list       :   func_list func {
    //printf("Hello");
}
                    |
                    ;

func            :   func_prefix OF
                    {
                        has_return_stmt = 0;
                        scope_history.push(++scope_counter);
                    } stmt_list CF 
                    {
                        if(func_table[curr_func_name].return_type != "void" && curr_func_name!="main" && has_return_stmt == 0){
                            sem_errors.push_back("Return stmt not there for function: " + curr_func_name);
                        }
                        scope_history.pop();
                        --scope_counter;
                        tac.push_back("end:\n");
                        has_return_stmt = 0;
                    }
 
func_prefix     :   func_data_type ID 
                    {   
                        if(func_table.find(string($2.lexeme)) != func_table.end()){
                            sem_errors.push_back("Error: Duplicate function name - " + string($2.lexeme));
                        }
                        tac.push_back(string($2.lexeme) + ": " + string($1.type)); 
                        curr_func_name = string($2.lexeme);
                        func_table[curr_func_name]=func_table["global"];
                        
                    } 
                    OC param_list CC {
                        func_table[curr_func_name].return_type = string($1.type);
                        func_table[curr_func_name].num_params = $5.nParams;
                    }

func_data_type  :   data_type {
                        strcpy($$.type, $1.type);
                        //printf("%s",string( $1.type));
                    }
                    | VOID {
                        sprintf($$.type, "void");
                        //printf("void");
                    }
                    ;
 
param_list      :   param {
                        func_table[curr_func_name].param_types.push_back(string($1.type));
                        func_table[curr_func_name].symbol_table[string($1.lexeme)] = { string($1.type), scope_counter+1, 0, 0, countn+1 };
                        tac.push_back("- arg " + string($1.type) + " " + string($1.lexeme));                       
                    }
                    COMMA param_list {
                        $$.nParams = $4.nParams + 1;
                        if($$.nParams>20) sem_errors.push_back("No. of parameters exceeded for " + curr_func_name);
                    }
                    | param {
                        $$.nParams = 1;
                        func_table[curr_func_name].param_types.push_back(string($1.type));
                        func_table[curr_func_name].symbol_table[string($1.lexeme)] = { string($1.type), scope_counter+1, 0, 0, countn+1 };
                        tac.push_back("- arg " + string($1.type) + " " + string($1.lexeme));
                    }
                    | {
                        $$.nParams = 0;
                    }
                    ;
 
param           :   data_type ID {
                        $$.nParams = 1;
                        strcpy($$.type, $1.type);
                        strcpy($$.lexeme, $2.lexeme);                   
                        }
                    ;
 
stmt_list       :   stmt stmt_list 
                    |
                    ;
 
stmt   		    :   declaration
                    | assign SCOL 
                    | expr SCOL 
                    | return_stmt SCOL 
                    | if_stmt
                    | while_loop_stmt 
                    | for_loop_stmt
                    | BREAK SCOL {
                        if(!loop_break.empty()){
                            tac.push_back("GOTO #L" + to_string(loop_break.top()));
                        }
                    }
                    | CONTINUE SCOL {
                        if(!loop_continue.empty()){
                            tac.push_back("GOTO #L" + to_string(loop_continue.top()));
                        }
                    }      
                    | switch_stmt
                    | INPUT OC ID CC SCOL  {
                        check_declaration($3.lexeme);
                        tac.push_back("input " + string($3.lexeme) + " " + func_table[curr_func_name].symbol_table[string($3.lexeme)].data_type);
                        // check_scope(string($3.lexeme));
                    }
                    | INPUT OC ID OS expr CS CC SCOL {
                        check_declaration($3.lexeme);
                        string temp = get_temp();
                        tac.push_back("input " + temp + " " + func_table[curr_func_name].symbol_table[string($3.lexeme)].data_type);
                        tac.push_back(string($3.lexeme) + " [ " + string($5.lexeme) + " ] = " + temp + " " + func_table[curr_func_name].symbol_table[string($3.lexeme)].data_type);
                        free_temp.push(temp);
                        // check_scope(string($3.lexeme));
                    }
                    | OUTPUT OC expr CC SCOL {
                        tac.push_back("output " + string($3.lexeme) + " " + string($3.type));
                    }
                    | OUTPUT OC STR CC SCOL {
                        tac.push_back("output " + string($3.lexeme) + " STRING");
                    }
                    | TYPEOF ID SCOL {
                        char dtype[256]; // Choose an appropriate size for the array
                        strcpy(dtype, func_table[curr_func_name].symbol_table[string($2.lexeme)].data_type.c_str());

                        // Print both the name of ID and its type
                        printf("Variable %s has type %s\n", $2.lexeme, dtype);
                    }


                    ;
 
declaration     :   data_type ID SCOL { 
                        is_reserved_word(string($2.lexeme));
                        // if(multiple_declaration(string($2.lexeme))){
                        //     check_scope(string($2.lexeme));
                        // };
                        //if(string($1.lexeme)!="int")sem_errors.push_back(string($1.lexeme)+" "+string($2.lexeme));
                        tac.push_back("- " + string($1.type) + " " + string($2.lexeme));
                        func_table[curr_func_name].symbol_table[string($2.lexeme)] = { string($1.type), scope_counter, 0, 0, countn+1 };
                    }
                    | data_type ID ASSIGN FLEN OC STR CC SCOL {
                        string t0=get_temp();
                        func_table[curr_func_name].symbol_table[string($2.lexeme)] = { "INT", scope_counter, 0, 0, countn+1 };
                        string_info[string($2.lexeme)] = to_string(string($6.lexeme).length()-2);
                        tac.push_back(string($6.lexeme) + string_info[string($2.lexeme)]);
                        tac.push_back(t0+" = "+ string_info[string($2.lexeme)] + " INT ");
                        tac.push_back("- INT "+string($2.lexeme));
                        tac.push_back(string($2.lexeme) +" = " + t0 + " INT " );

                       }
                    | FLEN OC ID CC ASSIGN ID SCOL {
                        string_info[string($3.lexeme)] = string($6.lexeme);
                    }
                    | data_type ID ASSIGN FLEN OC ID CC SCOL{
                        string t0=get_temp();
                        //string_info[string($2.lexeme)] = string_info[string($6.lexeme)];
                        // tac.push_back(string($1.lexeme) + " "+ to_string(string_info[string($6.lexeme)]));
                        // tac.push_back(string($6.lexeme) + to_string(string_info[string($2.lexeme)]));
                        func_table[curr_func_name].symbol_table[string($2.lexeme)] = { "INT", scope_counter, 0, 0, countn+1 };
                        tac.push_back(t0+" = "+ string_info[string($6.lexeme)] + " INT ");
                        tac.push_back("- INT "+string($2.lexeme));
                        tac.push_back(string($2.lexeme) +" = " + t0 + " INT " );
                    }
                    | STRING ID SCOL { 
                        is_reserved_word(string($2.lexeme));
                        // if(multiple_declaration(string($2.lexeme))){
                        //     check_scope(string($2.lexeme));
                        // };
                        //if(string($1.lexeme)!="int")sem_errors.push_back(string($1.lexeme)+" "+string($2.lexeme));
                        tac.push_back("- " + string($1.type) + " " + string($2.lexeme));
                        func_table[curr_func_name].symbol_table[string($2.lexeme)] = { "STRING", scope_counter, 0, 0, countn+1 };
                    }
                    | STRING ID ASSIGN STR SCOL {
                        is_reserved_word(string($2.lexeme));
                        string_info[string($2.lexeme)]=to_string(string($4.lexeme).length()-2);
                        multiple_declaration(string($2.lexeme));
                        tac.push_back("- STRING " + string($2.lexeme));
                        tac.push_back(string($2.lexeme) + " = " + string($4.lexeme) + " STRING");
                        func_table[curr_func_name].symbol_table[string($2.lexeme)] = { "STRING", scope_counter, string($4.lexeme).length(), 0, countn+1 };
                    }
                    | STRING ID ASSIGN expr SCOL {
                        is_reserved_word(string($2.lexeme));
                        multiple_declaration(string($2.lexeme));
                        string_info[string($2.lexeme)]=string_info[string($4.lexeme)];
                        check_type(string($1.type), string($4.type));
                        tac.push_back("- " + string($1.type) + " " + string($2.lexeme));
                        tac.push_back(string($2.lexeme) + " = " + string($4.lexeme) + " " + "STRING");
                        func_table[curr_func_name].symbol_table[string($2.lexeme)] = { string($1.type), scope_counter, 0, 0, countn+1 };

                        if(const_temps.find(string($4.lexeme)) == const_temps.end() && $4.lexeme[0] == '@') free_temp.push(string($4.lexeme));
                    }
                    | data_type ID ASSIGN expr SCOL {
                        is_reserved_word(string($2.lexeme));
                        multiple_declaration(string($2.lexeme));
                        check_type(string($1.type), string($4.type));
                        tac.push_back("- " + string($1.type) + " " + string($2.lexeme));
                        tac.push_back(string($2.lexeme) + " = " + string($4.lexeme) + " " + string($1.type));
                        func_table[curr_func_name].symbol_table[string($2.lexeme)] = { string($1.type), scope_counter, 0, 0, countn+1 };

                        if(const_temps.find(string($4.lexeme)) == const_temps.end() && $4.lexeme[0] == '@') free_temp.push(string($4.lexeme));
                    }
                    | data_type ID assign ID SCOL
                    | data_type ID OS INT_NUM CS SCOL {
                        is_reserved_word(string($2.lexeme));
                        multiple_declaration(string($2.lexeme));
                        tac.push_back("- " + string($1.type) + " " + string($2.lexeme) + " [ " + string($4.lexeme) + " ] ");
                        func_table[curr_func_name].symbol_table[string($2.lexeme)] = { string($1.type), scope_counter, stoi(string($4.lexeme)), 1, countn+1 };
                    }
                    /* | data_type ID OS expr CS SCOL {
                        is_reserved_word(string($2.lexeme));
                        multiple_declaration(string($2.lexeme));
                        tac.push_back("- " + string($1.type) + " " + string($2.lexeme) + " [ " + string($4.lexeme) + " ] ");
                        func_table[curr_func_name].symbol_table[string($2.lexeme)] = { string($1.type), scope_counter, stoi(string($4.lexeme)), 1, countn+1 };
                    }
                    | data_type ID OS  CHARACTER CS SCOL {
                        is_reserved_word(string($2.lexeme));
                        multiple_declaration(string($2.lexeme));
                        tac.push_back("- " + string($1.type) + " " + string($2.lexeme) + " [ " + string($4.lexeme) + " ] ");
                        func_table[curr_func_name].symbol_table[string($2.lexeme)] = { string($1.type), scope_counter, stoi(string($4.lexeme)), 1, countn+1 };
                    } */
                    | data_type ID OS INT_NUM CS ASSIGN {
                        is_reserved_word(string($2.lexeme));
                        multiple_declaration(string($2.lexeme));
                        tac.push_back("- " + string($1.type) + " " + string($2.lexeme) + " [ " + string($4.lexeme) + " ] ");
                        func_table[curr_func_name].symbol_table[string($2.lexeme)] = { string($1.type), scope_counter, stoi(string($4.lexeme)), 1, countn+1 };
                        curr_array = string($2.lexeme);
                    }
                    /* | ID OS INT_NUM CS ASSIGN {
                        is_reserved_word(string($2.lexeme));
                        printf("Reached here!!");
                        //multiple_declaration(string($2.lexeme));
                        tac.push_back("- " + string($1.type) + " " + string($2.lexeme) + " [ " + string($4.lexeme) + " ] ");
                        func_table[curr_func_name].symbol_table[string($2.lexeme)] = { string($1.type), scope_counter, stoi(string($4.lexeme)), 1, countn+1 };
                        curr_array = string($2.lexeme);
                    } */
                    | data_type ID OS CHARACTER CS ASSIGN {
                        is_reserved_word(string($2.lexeme));
                        multiple_declaration(string($2.lexeme));
                        tac.push_back("- " + string($1.type) + " " + string($2.lexeme) + " [ " + string($4.lexeme) + " ] ");
                        func_table[curr_func_name].symbol_table[string($2.lexeme)] = { string($1.type), scope_counter, stoi(string($4.lexeme)), 1, countn+1 };
                        curr_array = string($2.lexeme);
                    }
                    | MAC RESET SCOL{
                        tac.push_back("MAC RESET");
                    }

                    | OF arr_values CF SCOL // array size must be a positive integer 
                    ;

arr_values      :   const {
                        check_type(func_table[curr_func_name].symbol_table[curr_array].data_type, string($1.type));
                        tac.push_back(curr_array + " [ " + to_string(arr_index++) + " ] = " + string($1.lexeme) + " " + func_table[curr_func_name].symbol_table[curr_array].data_type);
                        if(arr_index > func_table[curr_func_name].symbol_table[curr_array].size){
                            sem_errors.push_back("Line no: " + to_string(func_table[curr_func_name].symbol_table[curr_array].line_number) + " error: too many initializers for "+curr_array+ "[" + to_string(func_table[curr_func_name].symbol_table[curr_array].size) + "]");
                        }
                    } 
                    COMMA arr_values
                    | const {
                        check_type(func_table[curr_func_name].symbol_table[curr_array].data_type, string($1.type));
                        tac.push_back(curr_array + " [ " + to_string(arr_index++) + " ] = " + string($1.lexeme) + " " + func_table[curr_func_name].symbol_table[curr_array].data_type);
                        if(arr_index > func_table[curr_func_name].symbol_table[curr_array].size){
                            sem_errors.push_back("Line no: " + to_string(func_table[curr_func_name].symbol_table[curr_array].line_number) + " error: too many initializers for "+curr_array+ "[" + to_string(func_table[curr_func_name].symbol_table[curr_array].size) + "]");
                        }
                        arr_index=0;
                    } |
                    ID {
                        check_type(func_table[curr_func_name].symbol_table[curr_array].data_type, string($1.type));
                        tac.push_back(curr_array + " [ " + to_string(arr_index++) + " ] = " + string($1.lexeme) + " " + func_table[curr_func_name].symbol_table[curr_array].data_type);
                        if(arr_index > func_table[curr_func_name].symbol_table[curr_array].size){
                            sem_errors.push_back("Line no: " + to_string(func_table[curr_func_name].symbol_table[curr_array].line_number) + " error: too many initializers for "+curr_array+ "[" + to_string(func_table[curr_func_name].symbol_table[curr_array].size) + "]");
                        }
                    } 
                    COMMA arr_values
                    | ID {
                        check_type(func_table[curr_func_name].symbol_table[curr_array].data_type, string($1.type));
                        tac.push_back(curr_array + " [ " + to_string(arr_index++) + " ] = " + string($1.lexeme) + " " + func_table[curr_func_name].symbol_table[curr_array].data_type);
                        if(arr_index > func_table[curr_func_name].symbol_table[curr_array].size){
                            sem_errors.push_back("Line no: " + to_string(func_table[curr_func_name].symbol_table[curr_array].line_number) + " error: too many initializers for "+curr_array+ "[" + to_string(func_table[curr_func_name].symbol_table[curr_array].size) + "]");
                        }
                        arr_index=0;
                    }
                    
                    ;
                   
return_stmt     :   RETURN expr {
                        //sem_errors.push_back($2.type);
                        check_type(func_table[curr_func_name].return_type, string($2.type));
                        tac.push_back("return " + string($2.lexeme) + " " + func_table[curr_func_name].return_type);
                        has_return_stmt = 1;

                        if(const_temps.find(string($2.lexeme)) == const_temps.end() && $2.lexeme[0] == '@') free_temp.push(string($2.lexeme));
                    }  
                    |
                    RETURN STR {
                        has_return_stmt = 1;
                        tac.push_back("return " + string($2.lexeme) + " " + func_table[curr_func_name].return_type);
                        if(const_temps.find(string($2.lexeme)) == const_temps.end() && $2.lexeme[0] == '@') free_temp.push(string($2.lexeme));
                    }
                    |
                    ;

data_type       :   INT {
                        strcpy($$.type, "INT");
                    }
                    | FLOAT {
                        strcpy($$.type, "FLOAT");
                    }
                    | STRING{
                        strcpy($$.type, "STRING");
                    }
                    | CHAR {
                        strcpy($$.type, "CHAR");
                    }
                    | BOOL {
                        strcpy($$.type, "BOOL");
                    }
                    
                    ;
               
 
/* Expressions */
expr      	    :   expr ADD expr {
                        add_tac($$, $1, $2, $3)
                        tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + string($3.lexeme) + " " + string($$.type));
                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));
                    }
                    | expr SUBTRACT expr {
                        add_tac($$, $1, $2, $3)
                        tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + string($3.lexeme) + " " + string($$.type));
                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));
                    }
                    | expr MULTIPLY expr {
                        add_tac($$, $1, $2, $3)
                        string t0=get_temp();
                        string t1=get_temp();
                        string t2=get_temp();
                        string a = string($$.lexeme);
                        string b = string($1.lexeme);
                        string c = string($3.lexeme);
                        string dtype = string($$.type);
                        
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
                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));

                        label_counter++;
                    }
                    | expr DIVIDE expr {
                       //if(atoi($3.lexeme)==0)  sem_errors.push_back("Line no " + to_string(countn+1) +" : " +" Divide by zero error"); 
                        add_tac($$, $1, $2, $3)
                        string t0=get_temp();
                        string t1=get_temp();
                        string t2=get_temp();
                        string a = string($$.lexeme);
                        string b = string($1.lexeme);
                        string c = string($3.lexeme);
                        string dtype = string($$.type);
                        
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
                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));

                        label_counter++;
                    }
                    | expr MACOP expr {
                        add_tac($$, $1, $2, $3)
                        if(string($1.type)!="INT" || string($3.type)!="INT") sem_errors.push_back("MAC instruction expects only int values");
                        tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + string($3.lexeme) + " " + string($$.type));
                        
                        // printf("%s",string($$.lexeme));
                        // printf("%s",string($1.lexeme));
                        // printf("%s",string($2.lexeme));
                        // printf("%s",string($3.lexeme));
                        // if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        // if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));
                    }
                    | expr LE expr {
                        add_tac($$, $1, $2, $3)
                        tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + string($3.lexeme) + " " + string($$.type));
                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));
                    }
                    | expr LE FLEN OC ID CC {
                        add_tac($$, $1, $2, $5)
                        string t0 = get_temp();
                        tac.push_back(t0+" = "+string_info[$5.lexeme]+" INT");
                        tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + t0 + " " + "INT");

                    }
                    | expr GE expr {
                        add_tac($$, $1, $2, $3)
                        tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + string($3.lexeme) + " " + string($$.type));
                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));
                    }
                    | expr GE FLEN OC ID CC {
                        add_tac($$, $1, $2, $5)
                        string t0 = get_temp();
                        tac.push_back(t0+" = "+string_info[$5.lexeme]+" INT");
                        tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + t0 + " " + "INT");

                    }
                    | expr LT expr {
                        add_tac($$, $1, $2, $3)
                        tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + string($3.lexeme) + " " + string($$.type));
                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));
                    }
                    | expr LT FLEN OC ID CC {
                        add_tac($$, $1, $2, $5)
                        string t0 = get_temp();
                        tac.push_back(t0+" = "+string_info[$5.lexeme]+" INT");
                        tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + t0 + " " + "INT");

                    }
                    | expr GT expr {
                        add_tac($$, $1, $2, $3)
                        tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + string($3.lexeme) + " " + string($$.type));
                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));
                    }
                    | expr GT FLEN OC ID CC {
                        add_tac($$, $1, $2, $5)
                        string t0 = get_temp();
                        tac.push_back(t0+" = "+string_info[$5.lexeme]+" INT");
                        tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + t0 + " " + "INT");

                    }
                    | expr EQ expr {
                        add_tac($$, $1, $2, $3)
                        tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + string($3.lexeme) + " " + string($$.type));
                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));
                    }
                    | expr EQ FLEN OC ID CC {
                        add_tac($$, $1, $2, $5)
                        string t0 = get_temp();
                        tac.push_back(t0+" = "+string_info[$5.lexeme]+" INT");
                        tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + t0 + " " + "INT");

                    }
                    | expr NE FLEN OC ID CC {
                        add_tac($$, $1, $2, $5)
                        string t0 = get_temp();
                        tac.push_back(t0+" = "+string_info[$5.lexeme]+" INT");
                        tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + t0 + " " + "INT");

                    }
                    | expr NE expr {
                        add_tac($$, $1, $2, $3)
                        string temp = get_temp();
                        tac.push_back(temp + " = " + string($1.lexeme) + " == " + string($3.lexeme) + " " + string($$.type));
                        tac.push_back(string($$.lexeme) + " = ~ " + temp + " " + string($$.type)); 

                        free_temp.push(temp);
                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));
                    }
                    | expr AND expr {
                        add_tac($$, $1, $2, $3)
                        string l0 = "#L" + to_string(++label_counter);
                        string l1 = "#L" + to_string(++label_counter);
                        string l2 = "#L" + to_string(++label_counter);
                        string l3 = "#L" + to_string(++label_counter);
                        string dtype = string($$.type);

                        tac.push_back("if " + string($1.lexeme) + " GOTO " + l3 + " else GOTO " + l1);
                        tac.push_back(l3 + ":");
                        tac.push_back("if " + string($3.lexeme) + " GOTO " + l0 + " else GOTO " + l1);
                        tac.push_back(l0 + ":");
                        tac.push_back(string($$.lexeme) + " = 1 " + dtype);
                        tac.push_back("GOTO " + l2);
                        tac.push_back(l1 + ":");
                        tac.push_back(string($$.lexeme) + " = 0 " + dtype);
                        tac.push_back(l2 + ":");

                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));

                        label_counter++;
                    }
                    | expr OR expr {
                        add_tac($$, $1, $2, $3)
                        string l0 = "#L" + to_string(++label_counter);
                        string l1 = "#L" + to_string(++label_counter);
                        string l2 = "#L" + to_string(++label_counter);
                        string l3 = "#L" + to_string(++label_counter);
                        string dtype = string($$.type);

                        tac.push_back("if " + string($1.lexeme) + " GOTO " + l0 + " else GOTO " + l3);
                        tac.push_back(l3 + ":");
                        tac.push_back("if " + string($3.lexeme) + " GOTO " + l0 + " else GOTO " + l1);
                        tac.push_back(l0 + ":");
                        tac.push_back(string($$.lexeme) + " = 1 " + dtype);
                        tac.push_back("GOTO " + l2);
                        tac.push_back(l1 + ":");
                        tac.push_back(string($$.lexeme) + " = 0 " + dtype);
                        tac.push_back(l2 + ":");

                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));

                        label_counter++;
                    }
                    | expr MODULO expr {
                        add_tac($$, $1, $2, $3)
                        string t0=get_temp();
                        string t1=get_temp();
                        string t2=get_temp();
                        string a = string($$.lexeme);
                        string b = string($1.lexeme);
                        string c = string($3.lexeme);
                        string dtype = string($$.type);
                        
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
                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));

                        label_counter++;
                    }
                    | expr BITAND expr {
                        add_tac($$, $1, $2, $3)
                        tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + string($3.lexeme) + " " + string($$.type));
                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));
                    }
                    | expr BITOR expr {
                        add_tac($$, $1, $2, $3)
                        tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + string($3.lexeme) + " " + string($$.type));
                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));
                    }
                    | expr XOR expr {
                        add_tac($$, $1, $2, $3)
                        string a = string($$.lexeme);
                        string b = string($1.lexeme);
                        string b_= get_temp();
                        string c = string($3.lexeme);
                        string c_= get_temp();

                        tac.push_back(b_ + " = ~ " + b + " " + string($1.type));
                        tac.push_back(c_ + " = ~ " + c + " " + string($3.type));
                        string t1=get_temp();
                        string t2=get_temp();
                        tac.push_back(t1 + " = " + b + " & " + c_ + " " + string($$.type));
                        tac.push_back(t2 + " = " + b_ + " & " + c + " " + string($$.type));
                        tac.push_back(a + " = " + t1 + " | " + t2 + " " + string($$.type));

                        free_temp.push(b_);
                        free_temp.push(c_);
                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));

                        label_counter++;
                    }
                    | expr LEFTSHIFT expr {
                        add_tac($$, $1, $2, $3)
                        string d = string($3.lexeme);
                        string t3 = get_temp();
                        string t4 = get_temp();
                        string l0 = "#L" + to_string(++label_counter);
                        string l1 = "#L" + to_string(++label_counter);
                        string l2 = "#L" + to_string(++label_counter);

                        string t0= get_temp();
                        string t1= get_temp();
                        string t2= get_temp();
                        string a = string($$.lexeme);
                        string b = string($1.lexeme);
                        string c = get_temp();
                        tac.push_back(c + " = 2 INT");
                        string dtype = string($$.type);
                        
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
                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));

                        label_counter++;
                    }
                    | expr RIGHTSHIFT expr {
                        add_tac($$, $1, $2, $3)
                        string d = string($3.lexeme);
                        string t3 = get_temp();
                        string t4 = get_temp();
                        string l0 = "#L" + to_string(++label_counter);
                        string l1 = "#L" + to_string(++label_counter);
                        string l2 = "#L" + to_string(++label_counter);

                        string t0=get_temp();
                        string t1=get_temp();
                        string t2=get_temp();
                        string a = string($$.lexeme);
                        string b = string($1.lexeme);
                        string c = get_temp();
                        tac.push_back(c + " = 2 INT");
                        string dtype = string($$.type);
                        
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
                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));

                        label_counter++;
                    }
                    | unary_expr {
                        strcpy($$.type, $1.type);
                        strcpy($$.type, $1.type);
                        sprintf($$.lexeme, "%s", $1.lexeme);
                    }
                    | primary_expr {
                        strcpy($$.type, $1.type);
                        strcpy($$.type, $1.type);
                        strcpy($$.lexeme, $1.lexeme);
                    }
                    | postfix_expr {
                        strcpy($$.type, $1.type);
                        sprintf($$.lexeme, "%s", $1.lexeme);
                    }
                    | expr ADD ADD{
                        // add_tac($$, $1, $2, $3)
                        string t0=get_temp();
                        string t1=get_temp();
                        string t2=get_temp();
                        string a = string($1.lexeme);
                        tac.push_back(t1 + " = 1 "+ string($$.type));
                        tac.push_back(t2 + " = "+a+ " + " + t1+ " " +string($$.type));
                        tac.push_back(a+" = "+t2+ " " +string($$.type));
                        // tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + "1" + " " + string($$.type));
                        if(const_temps.find(string($1.lexeme)) == const_temps.end() && $1.lexeme[0] == '@') free_temp.push(string($1.lexeme));
                        free_temp.push(t0);
                        free_temp.push(t1);
                        free_temp.push(t2);
                    }
                    

postfix_expr    :   func_call {
                        //sem_errors.push_back("Hi");
                        strcpy($$.type, $1.type);
                        sprintf($$.lexeme, "%s", $1.lexeme);
                    }
                    |
                    ID OS expr CS {
                        bool isString =0;
                        string dtype = func_table[curr_func_name].symbol_table[string($1.lexeme)].data_type;
                        if(dtype=="STRING"|| dtype=="STRING") isString=1;
                        if(check_declaration(string($1.lexeme)) && !isString && func_table[curr_func_name].symbol_table[string($1.lexeme)].isArray == 0) { 
                            sem_errors.push_back("Line no " + to_string(countn+1) +" : " +string($1.lexeme)+ " Variable is not an array from expr" + dtype ); 
                        }
                        check_scope(string($1.lexeme));
                        strcpy($$.type, func_table[curr_func_name].symbol_table[string($1.lexeme)].data_type.c_str());
                        sprintf($$.lexeme, get_temp().c_str());
                        tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " [ " + string($3.lexeme) + " ] " + string($$.type));
                        
                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));
                    }
                    ;
 
unary_expr      :   unary_op primary_expr {
                        strcpy($$.type, $2.type);
                        sprintf($$.lexeme, get_temp().c_str());
                        if(string($1.lexeme) == "~" || string($1.lexeme) == "-"){
                            tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($2.lexeme) + " " + string($$.type));
                        }
                        else if(string($1.lexeme) == "+"){
                            tac.push_back(string($$.lexeme) + " = " + string($2.lexeme) + " " + string($$.type));
                        }
                        else{
                            tac.push_back(string($$.lexeme) + " = ~ " + string($2.lexeme) + " " + string($$.type));
                        }

                        if(const_temps.find(string($2.lexeme)) == const_temps.end() && $2.lexeme[0] == '@') free_temp.push(string($2.lexeme));
                    }
                    ;
 
primary_expr    :   ID {
                        check_declaration(string($1.lexeme));
                        // check_scope(string($1.lexeme));
                        strcpy($$.type, func_table[curr_func_name].symbol_table[string($1.lexeme)].data_type.c_str());
                        strcpy($$.lexeme, $1.lexeme);
                    }
                    | const {
                        strcpy($$.type, $1.type);

                        string t=get_temp();
                        sprintf($$.lexeme, t.c_str());
                        tac.push_back(string($$.lexeme) + " = " + string($1.lexeme) + " " + string($$.type)); 
                        temp_map[string($1.lexeme)] = string($$.lexeme);

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
                    | OC expr CC {
                        strcpy($$.type, $2.type);
                        strcpy($$.lexeme, $2.lexeme);
                    }
                    ;
 
unary_op        :   ADD 
                    | SUBTRACT 
                    | NOT
                    | NEGATION
                    ;
 
const           :   INT_NUM {
                        strcpy($$.type, "INT");
                        strcpy($$.lexeme, $1.lexeme);
                    }
                    | FLOAT_NUM {
                        strcpy($$.type, "FLOAT");
                        strcpy($$.lexeme, $1.lexeme);
                    }
                    | CHARACTER {
                        // printf("CHAR");
                        // printf("\n");
                        // printf($1.lexeme);
                        // printf("\n");
                        strcpy($$.type, "CHAR");
                        strcpy($$.lexeme, $1.lexeme);
                    }
                    ;
                   
assign          :   ID ASSIGN expr {
                        // printf($1.lexeme);
                        // printf($3.lexeme);
                        bool k= check_declaration(string($1.lexeme));
                        if(k) {
                        if(func_table[curr_func_name].symbol_table.find(string($1.lexeme))!=func_table[curr_func_name].symbol_table.end()){
                            char dtype[256]; // Choose an appropriate size for the array

                        // Then copy the C-string into the array
                        strcpy(dtype, func_table[curr_func_name].symbol_table[string($1.lexeme)].data_type.c_str());

                            // printf(dtype);
                            // printf(string($3.type).c_str());
                        check_type(func_table[curr_func_name].symbol_table[string($1.lexeme)].data_type, string($3.type));
                        check_scope(string($1.lexeme));
                        tac.push_back(string($1.lexeme) + " = " + string($3.lexeme) + " " + func_table[curr_func_name].symbol_table[string($1.lexeme)].data_type);

                        if(const_temps.find(string($3.lexeme)) == const_temps.end() && $3.lexeme[0] == '@') free_temp.push(string($3.lexeme));
                        }
                        }
                        
                    }
                    |
                    ID OS expr CS ASSIGN expr {
                        check_type(func_table[curr_func_name].symbol_table[string($1.lexeme)].data_type, string($6.type));
                        bool isString =0;
                        string dtype = func_table[curr_func_name].symbol_table[string($1.lexeme)].data_type;
                        if(dtype=="STRING"|| dtype=="STRING") isString=1;
                        if(check_declaration(string($1.lexeme)) && !isString && func_table[curr_func_name].symbol_table[string($1.lexeme)].isArray == 0) { 
                            sem_errors.push_back("Line no " + to_string(countn+1) +" : " +string($1.lexeme)+ " Variable is not an array from assign expr" + dtype); 
                        }
                        check_scope(string($1.lexeme));
                        tac.push_back(string($1.lexeme) + " [ " + string($3.lexeme) + " ] = " + string($6.lexeme) + " " + func_table[curr_func_name].symbol_table[string($1.lexeme)].data_type);

                        if(const_temps.find(string($6.lexeme)) == const_temps.end() && $6.lexeme[0] == '@') free_temp.push(string($6.lexeme));
                    }
                    |
                    expr
                    |
                    declaration

if_stmt         :   IF  {
                        sprintf($1.parentNext, "#L%d", label_counter++);
                    } 
                    OC expr CC { 
                        tac.push_back("if " + string($4.lexeme) + " GOTO #L" + to_string(label_counter) + " else GOTO #L" + to_string(label_counter+1));
                        sprintf($4.if_body, "#L%d", label_counter++);
                        sprintf($4.else_body, "#L%d", label_counter++); 
                        tac.push_back(string($4.if_body) + ":");

                        if(const_temps.find(string($4.lexeme)) == const_temps.end() && $4.lexeme[0] == '@') free_temp.push(string($4.lexeme));
                    } 
                    OF
                    {
                      scope_history.push(++scope_counter);  
                    } stmt_list CF {  
                        scope_history.pop(); 
                        --scope_counter;
                        tac.push_back("GOTO " + string($1.parentNext));
                        tac.push_back(string($4.else_body) + ":");
                    } 
                    elif_stmt  else_stmt {   
                        tac.push_back(string($1.parentNext) + ":");
                    }
                    ;        

elif_stmt       :   ELIF {
                        string str = tac[tac.size()-2].substr(5);
                        char* hold = const_cast<char*>(str.c_str());
                        sprintf($1.parentNext, "%s", hold);
                    } 
                    OC expr CC {
                        tac.push_back("if " + string($4.lexeme) + " GOTO #L" + to_string(label_counter) + " else GOTO #L" + to_string(label_counter+1));
                        sprintf($4.if_body, "#L%d", label_counter++);
                        sprintf($4.else_body, "#L%d", label_counter++); 
                        tac.push_back(string($4.if_body) + ":");

                        if(const_temps.find(string($4.lexeme)) == const_temps.end() && $4.lexeme[0] == '@') free_temp.push(string($4.lexeme));
                    } 
                    OF
                    {
                        scope_history.push(++scope_counter);
                    } 
                    stmt_list CF {
                        scope_history.pop();
                        --scope_counter;
                        tac.push_back("GOTO " + string($1.parentNext));
                        tac.push_back(string($4.else_body) + ":");
                    } 
                    elif_stmt  
                    |
                    ;

else_stmt       :   ELSE OF {scope_history.push(++scope_counter);} stmt_list CF{scope_history.pop(); --scope_counter;}
                    |
                    ;       

switch_stmt     :   SWITCH {
                        int temp_label = label_counter;
                        loop_break.push(temp_label);
                        sprintf($1.parentNext, "#L%d", label_counter++);
                    } 
                    OC ID {
                        temp_index = variable_count;
                        tac.push_back("@t" + to_string(variable_count++) + " = " + string($4.lexeme) + " " + func_table[curr_func_name].symbol_table[string($4.lexeme)].data_type);
                    } 
                    CC OF case_stmt_list {
                        // strcpy($8.id, $4.lexeme);
                        // strcpy($8.parentNext, $1.parentNext);
                    }
                    default_stmt CF {
                        tac.push_back(string($1.parentNext) + ":");
                        loop_break.pop();
                    }
                    ;

case_stmt_list  :   case_stmt case_stmt_list {
                        strcpy($1.id, $$.id);
                        strcpy($1.parentNext, $$.parentNext);
                    }
                    |
                    ;

case_stmt       :   CASE {
                        // tac.push_back(string($4.if_body) + ":");
                    } 
                    OC const {
                        char* hold = const_cast<char*>(to_string(variable_count).c_str());
                        sprintf($4.temp, "%s", hold);
                        tac.push_back("@t" + to_string(variable_count++) + " = " + string($4.lexeme) + " " + string($4.type));
                        tac.push_back("@t" + to_string(variable_count++) + " = " + "@t" + to_string(temp_index) + " == " + "@t" + string($4.temp) + " INT");
                        tac.push_back("if @t" + to_string(variable_count-1) + " GOTO #L" + to_string(label_counter) + " else GOTO #L" + to_string(label_counter+1));
                        tac.push_back("#L" + to_string(label_counter) + ":");
                        sprintf($4.case_body, "#L%d", label_counter++);
                        sprintf($4.parentNext, "#L%d", label_counter++);
                    }
                    CC COLON stmt_list {
                        tac.push_back(string($4.parentNext) + ":");
                    } 

default_stmt    :   DEFAULT COLON stmt_list
                    |
                    ;                       

while_loop_stmt :   WHILE {
                        sprintf($1.loop_body, "#L%d", label_counter); 
                        loop_continue.push(label_counter++);
                        tac.push_back("\n" + string($1.loop_body) + ":");
                    } 
                    OC expr CC 
                    {
                        sprintf($4.if_body, "#L%d", label_counter++); 

                        loop_break.push(label_counter);
                        sprintf($4.else_body, "#L%d", label_counter++); 

                        tac.push_back("\nif " + string($4.lexeme) + " GOTO " + string($4.if_body) + " else GOTO " + string($4.else_body));
                        tac.push_back("\n" + string($4.if_body) + ":");

                        if(const_temps.find(string($4.lexeme)) == const_temps.end() && $4.lexeme[0] == '@') free_temp.push(string($4.lexeme));
                        
                    } 
                    OF{
                        scope_history.push(++scope_counter);
                    } stmt_list CF    
                    {
                        scope_history.pop();
                        --scope_counter;
                        tac.push_back("GOTO " + string($1.loop_body));
                        tac.push_back("\n" + string($4.else_body) + ":");
                        loop_continue.pop();
                        loop_break.pop();
                    }

for_loop_stmt   :   FOR OC assign SCOL {
                        sprintf($1.loop_body, "#L%d", label_counter++); 
                        tac.push_back("\n" + string($1.loop_body) + ":");
                    } 
                    expr SCOL {  
                        sprintf($6.if_body, "#L%d", label_counter++); 

                        loop_break.push(label_counter);
                        sprintf($6.else_body, "#L%d", label_counter++); 

                        tac.push_back("\nif " + string($6.lexeme) + " GOTO " + string($6.if_body) + " else GOTO " + string($6.else_body));

                        sprintf($6.loop_body, "#L%d", label_counter); 
                        loop_continue.push(label_counter++);
                        tac.push_back("\n" + string($6.loop_body) + ":");

                        if(const_temps.find(string($6.lexeme)) == const_temps.end() && $6.lexeme[0] == '@') free_temp.push(string($6.lexeme));
                    }
                    assign CC {
                        tac.push_back("GOTO " + string($1.loop_body));
                        tac.push_back("\n" + string($6.if_body) + ":");
                    }
                    OF
                    {
                        scope_history.push(++scope_counter);
                    }
                    stmt_list CF {
                        scope_history.pop();
                        --scope_counter;
                        tac.push_back("GOTO " + string($6.loop_body));
                        tac.push_back("\n" + string($6.else_body) + ":");
                        loop_continue.pop();
                        loop_break.pop();
                    }

func_call       :   ID {
                        func_call_id.push({string($1.lexeme), func_table[string($1.lexeme)].param_types});
                    } 
                    OC arg_list CC  {
                        // char dtype[256]; // Choose an appropriate size for the array

                        // // Then copy the C-string into the array
                        // strcpy(dtype, func_table[curr_func_name].symbol_table[string($1.lexeme)].data_type.c_str());
                        // char debugInfo[] = "from func call";

                        // // Use sprintf to format and print the combined string
                        // char result[256]; // Choose a size that can hold the combined string
                        // sprintf(result, "%s %s\n", dtype, debugInfo);
                        // printf("%s", result);
                        strcpy($$.type, func_table[string($1.lexeme)].return_type.c_str());
                        func_call_id.pop();
                        sprintf($$.lexeme, get_temp().c_str());

                        tac.push_back(string($$.lexeme) + " = @call " + string($1.lexeme) + " " + func_table[string($1.lexeme)].return_type + " " + to_string(func_table[string($1.lexeme)].num_params));
                    }
                    ;

arg_list        :   arg COMMA arg_list {
                        int sz = func_call_id.top().second.size();
                        string type = func_call_id.top().second[sz-1];
                        func_call_id.top().second.pop_back();
                        if(type_check(string($1.type), type)) {
                            sem_errors.push_back("datatype for argument not matched in line " + to_string(countn+1));
                        }
                    }
                    | arg {
                        int sz = func_call_id.top().second.size();
                        string type = func_call_id.top().second[sz-1];
                        func_call_id.top().second.pop_back();
                        if(type_check(string($1.type), type)) {
                            sem_errors.push_back("datatype for argument not matched in line " + to_string(countn+1));
                        }
                    }
                    | 
                    ;

arg             :   expr {
                        tac.push_back("param " + string($1.lexeme) + " " + string($1.type));
                    }
                    ;

%%

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

