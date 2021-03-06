%{
#include <string.h>
%}
typed char|float|int|double|long
alpha [a-zA-Z]
numeric [0-9]
alphanum [a-zA-Z0-9]
alphanumeric {alpha}({alpha}|{numeric})*
varn {alpha}{alphanum}*\_*{alphanum}*
single {typed}\ {varn}

ps \,{varn}
ps2 \,\&{varn}

%%
\#include\<[a-z0-9]+\.h\> ;


scanf\(\"[^;)"]+\"{ps2}+\); {
	int i = 0, j = -1, k = 0;
	while (yytext[i] != '"') i++; i++;
	while (yytext[i] != '"') i++;
	i += 2;
	char names[100][100]; memset(names, '\0', sizeof names);
	while (yytext[i] != ')') {
		if (yytext[i] == '&') {
			j++; k = 0;
		}
		if (yytext[i] != '&' && yytext[i] != ',') {
			names[j][k++] = yytext[i];
		}
		i++;
	}
	for( i = 0; i <= j-1; i++) 
		printf("%s = input();\n", names[i]);
	printf("%s = input();",names[j]);
}

printf\(\".*\"{ps}*\) {
//	printf("\n Getting matched");
	int i = 0, j = 0;
	while(yytext[i] != '"') i++;
	i++;
	char content[100]; 
	while(yytext[i] != '"') {
		content[j] = yytext[i];
		i++;
		j++;
	}
	content[j] = '\0';
	printf("print(\"%s\")", content);
	if(yytext[i+1] == ',') {
		i+=2;
		putchar('%');
		putchar('(');
//		printf("\%(");
		while(yytext[i] != ')') {
			printf("%c", yytext[i]);
			i++;
		}
		printf(")");
	}
}


%%
int main() {
	yylex();
	return 0;
}
