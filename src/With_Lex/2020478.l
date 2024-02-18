%{
#include <stdio.h>
%}
%option noyywrap

%%
int|float|char|bool         {printf("TOKEN: Datatype, LEXEME: %s\n", yytext);}
print|true|false|if|else         {printf("TOKEN: Keyword, LEXEME: %s\n", yytext);}

"="	                        {printf("TOKEN: Assignment, LEXEME: %s\n", yytext);}
";"	                        {printf("TOKEN: Delimiter, LEXEME: %s\n", yytext);}

[A-Za-z][_a-zA-Z0-9]*	    {printf("TOKEN: IDENTIFIER, LEXEME: %s\n", yytext);}

['"][A-Z a-z_]*['"]		    {printf("TOKEN: STRING_VALUE, LEXEME: %s\n", yytext);}
[0-9]+	                    {printf("TOKEN: INTEGER_VALUE, LEXEME: %s\n", yytext);}
[0-9]+[.][0-9]+	            {printf("TOKEN: DECIMAL_VALUE, LEXEME: %s\n", yytext);}

[*+-/]                      {printf("TOKEN: OPERATOR, LEXEME: %s\n", yytext);}

[(){}]                      {printf("TOKEN: PARENTHESIS, LEXEME: %s\n", yytext);}

[ \t\n]					     ;

[0-9][_a-zA-Z0-9]*			{printf("INVALID TOKEN, LEXEME: %s\n", yytext);}
.							{printf("INVALID TOKEN, LEXEME: %s\n", yytext);}
%%

int main() {;
    yylex();
    return 0;
}