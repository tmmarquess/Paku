%{
	#include "calc.tab.h" 
	#include <stdlib.h>
	void yyerror(char *s); 

	static int next_column = 1;
	int column = 1;

	#define HANDLE_COLUMN column = next_column; next_column += strlen(yytext)

	char *lineptr = NULL;
	size_t n = 0;
	size_t consumed = 0;
	size_t available = 0;

	size_t min(size_t a, size_t b);
	#define YY_INPUT(buf,result,max_size) {\
		if(available <= 0) {\
			consumed = 0;\
			available = getline(&lineptr, &n, yyin);\
			if (available < 0) {\
				if (ferror(yyin)) { perror("read error:"); }\
					available = 0;\
				}\
		}\
		result = min(available, max_size);\
		strncpy(buf, lineptr + consumed, result);\
		consumed += result;\
		available -= result;\
	}
%}

%option yylineno

%%

[0-9]+("."[0-9]+)? 					{ HANDLE_COLUMN; yylval.double_val = atof(yytext); return NUMBER; }
[\n]								{ HANDLE_COLUMN; next_column = 1; return EOL; }
[+]									{ HANDLE_COLUMN; return PLUS; }
[-]									{ HANDLE_COLUMN; return MINUS; }
[/]									{ HANDLE_COLUMN; return DIVIDE; }
[*]									{ HANDLE_COLUMN; return TIMES; }
[(]									{ HANDLE_COLUMN; return P_LEFT;}
[)]									{ HANDLE_COLUMN; return P_RIGHT;}
[%]									{ HANDLE_COLUMN; return MOD; }
(\*\*)								{ HANDLE_COLUMN; return POW; }
\"									{ HANDLE_COLUMN; return QUOTE; }
(int|float|double|char|string) 		{ HANDLE_COLUMN; yylval.str_val = strdup(yytext); return TYPE; }
("print_str")						{ HANDLE_COLUMN; return PRINT; }
[[:space:]]							{ HANDLE_COLUMN; }
("show")							{ HANDLE_COLUMN; return SHOW; }
(type)								{ HANDLE_COLUMN; return SHOW_TYPE; }
([a-zA-Z0-9]+)						{ HANDLE_COLUMN; yylval.str_val = strdup(yytext); return STRING; }	
[=]									{ HANDLE_COLUMN; return attribuition; }
.        							{ HANDLE_COLUMN; return yytext[0]; }

%%

int yywrap()
{
	return 1;
}

size_t min(size_t a, size_t b) {
    return b < a ? b : a;
}