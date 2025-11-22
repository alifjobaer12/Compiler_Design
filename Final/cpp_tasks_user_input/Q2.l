%option noyywrap

%{
#include <stdio.h>
#include "Q2.tab.h"
extern long long yylval;
%}

%%

[ \t\r\n]+                ;
-?[0-9]+                  {
                             yylval = atoll(yytext);
                             return NUMBER;
                          }

/* single-char tokens/operators */
"("                       { return '('; }
")"                       { return ')'; }
"+"                       { return '+'; }
"-"                       { return '-'; }
"*"                       { return '*'; }
"/"                       { return '/'; }

.                         {return yytext[0]; }

%%
