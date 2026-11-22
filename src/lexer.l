%option noyywrap
%option yylineno

%{
#include "parser.tab.hpp"
#include <cstdlib>
#include <string>
%}

%%

"int"       { return INT; }
"float"     { return FLOAT; }
"return"    { return RETURN; }

[0-9]+      {
                yylval.number = std::atof(yytext);
                return NUMBER;
            }

[a-zA-Z_][a-zA-Z0-9_]* {
                yylval.str = new std::string(yytext);
                return IDENTIFIER;
            }

"=="        { return EQ; }
"!="        { return NE; }
"<="        { return LE; }
">="        { return GE; }

[+\-*/=<>]  { return yytext[0]; }

[(){};,]    { return yytext[0]; }

[ \t\r\n]+  { /* Ігноруємо пробіли */ }

.           {
                std::cerr << "Unknown character: " << yytext
                          << " at line " << yylineno << '\n';
                return yytext[0];
            }

%%
