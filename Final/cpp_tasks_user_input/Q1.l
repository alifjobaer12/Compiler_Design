%option noyywrap

%{
#include <stdio.h>
#include "Q1.tab.h" 
%}

%%
[ \t\r\n]+               ;
[a-zA-Z][a-zA-Z0-9]*     { return VARIABLE; }
[0-9]+                   { return NUMBER; }
"="                      { return '='; }
"("                      { return '('; }
")"                      { return ')'; }
"+"                      { return '+'; }
"-"                      { return '-'; }
"*"                      { return '*'; }
"/"                      { return '/'; }
"%"                      { return '%'; }
.                        { return yytext[0]; }
%%
