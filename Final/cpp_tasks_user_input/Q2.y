%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
extern long long yylval;
%}

%union {
    long long ival;
}

%token <ival> NUMBER

%type <ival> expr

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

input:
      expr    { printf("\nResult = %lld\n", $1); exit(0); }
    ;

expr:
      expr '+' expr   { $$ = $1 + $3; }
    | expr '-' expr   { $$ = $1 - $3; }
    | expr '*' expr   { $$ = $1 * $3; }
    | expr '/' expr   {
                        if ($3 == 0) yyerror("division by zero");
                        $$ = $1 / $3;
                      }
    | '-' expr %prec UMINUS  { $$ = -$2; }
    | '(' expr ')'     { $$ = $2; }
    | NUMBER           { $$ = $1; }
    ;

%%

int main(void)
{
    printf("Enter arithmetic expression:\n");
    fflush(stdout);
    yyparse();

    return 0;
}

void yyerror(const char *s)
{
    printf("\nError: %s\n", s);
    exit(0);
}
