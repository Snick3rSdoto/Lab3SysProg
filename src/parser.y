%{
#include "ast.hpp"
#include <iostream>

extern int yylex();
void yyerror(const char* message);

std::shared_ptr<ProgramNode> root;
%}

%code requires {
    #include "ast.hpp"
}

%union {
    double number;
    std::string* str;
    Node* node;
    ProgramNode* program;
}

%token INT FLOAT RETURN
%token <number> NUMBER
%token <str> IDENTIFIER

%token EQ NE LE GE

%type <node> expression statement
%type <program> statements

%left '+' '-'
%left '*' '/'

%start program

%%

program:
    statements {
        root = std::shared_ptr<ProgramNode>($1);
    }
;

statements:
    statement {
        $$ = new ProgramNode();
        $$->add(NodePtr($1));
    }
    |
    statements statement {
        $1->add(NodePtr($2));
        $$ = $1;
    }
;

statement:
    INT IDENTIFIER '=' expression ';' {
        $$ = new DeclarationNode(
            "int", *$2, NodePtr($4)
        );
        delete $2;
    }
    |
    FLOAT IDENTIFIER '=' expression ';' {
        $$ = new DeclarationNode(
            "float", *$2, NodePtr($4)
        );
        delete $2;
    }
    |
    IDENTIFIER '=' expression ';' {
        $$ = new AssignmentNode(
            *$1, NodePtr($3)
        );
        delete $1;
    }
    |
    RETURN expression ';' {
        $$ = new ReturnNode(NodePtr($2));
    }
;

expression:
    NUMBER {
        $$ = new NumberNode($1);
    }
    |
    IDENTIFIER {
        $$ = new VariableNode(*$1);
        delete $1;
    }
    |
    expression '+' expression {
        $$ = new BinaryNode("+", NodePtr($1), NodePtr($3));
    }
    |
    expression '-' expression {
        $$ = new BinaryNode("-", NodePtr($1), NodePtr($3));
    }
    |
    expression '*' expression {
        $$ = new BinaryNode("*", NodePtr($1), NodePtr($3));
    }
    |
    expression '/' expression {
        $$ = new BinaryNode("/", NodePtr($1), NodePtr($3));
    }
    |
    '(' expression ')' {
        $$ = $2;
    }
;

%%

void yyerror(const char* message) {
    std::cerr << "Syntax error: " << message << '\n';
}
