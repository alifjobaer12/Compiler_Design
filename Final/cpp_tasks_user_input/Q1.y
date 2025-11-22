%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
%}

%token NUMBER VARIABLE

%left '+' '-'
%left '*' '/' '%'

%%

input:
      stmt
    ;

stmt:
      VARIABLE '=' expr   { printf("\naccepted\n\n"); exit(0); }
    | expr                { printf("\naccepted (expression)\n\n"); exit(0); }
    ;

expr:
      expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '%' expr
    | '(' expr ')'
    | NUMBER
    | VARIABLE
    ;

%%

int main(void){
    printf("\nEnter Any Arithmetic Expression:\n");
    yyparse();
    return 0;
}

void yyerror(const char *s){
    printf("\nrejected\n\n");
    exit(0);
}
