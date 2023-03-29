%{
#include "calc.tab.h" 
#include <stdlib.h>

void yyerror(char *s); 
%}

%%

[0-9]+("."[0-9]+)? 					{ yylval.double_val = atof(yytext); return NUMBER; }
[\n]								{ return EOL; }
[+]									{ return PLUS; }
[-]									{ return MINUS; }
[/]									{ return DIVIDE; }
[*]									{ return TIMES; }
[(]									{ return P_LEFT;}
[)]									{ return P_RIGHT;}
[%]									{ return MOD; }
(\*\*)								{ return POW; }
\"									{ return QUOTE; }
(int|float|double|char|string) 		{ yylval.str_val = strdup(yytext); return TYPE; }
("print_str")						{ return PRINT; }
[[:space:]]							;
("show")							{ return SHOW; }
([a-zA-Z0-9]+)						{ yylval.str_val = strdup(yytext); return STRING; }	
[=]									{ return attribuition; }
.									{ yyerror("Undefined token\n"); }

%%

int yywrap()
{
	return 1;
}

