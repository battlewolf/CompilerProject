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

%%

for\([^\);]*\;[^\);]*\;[^\);]*\) {
	char var_name[10], start[10], limit[10], counter[10];
	int i = 4, j = 0;
	while(yytext[i] != ' ') {
		var_name[j] = yytext[i];
		i++; j++;
	}
	var_name[j] = '\0';
	j = 0;
	while(!(yytext[i] >= '0' && yytext[i] <= '9'))i++;
	while(yytext[i] != ';') {
		start[j] = yytext[i];
		i++; j++;
	}
	start[j] = '\0';
	j = 0;
	while(!(yytext[i] >= '0' && yytext[i] <= '9')) i++;
	while(yytext[i] != ';') {
		limit[j] = yytext[i];
		j++; i++;
	}
	limit[j] = '\0';
	i++;

	while(!(yytext[i] == '+' || yytext[i] == '-')) i++;
//	printf("\n sybmol %c", yytext[i]);
	counter[0] = yytext[i];
//	printf("\n counter[0] %c\n", counter[0]);
	j=1; i+=2;
	while(yytext[i] != ')') {
//		printf("yytextdd[i] : %c", yytext[i]);
		counter[j] = yytext[i];
		i++;
		j++;
	}
	counter[j] = '\0';
	printf("for %s in range(%s, %s, %s):", var_name, start, limit, counter);


}


while\([^;\)]+\) {
	printf("%s:", yytext);
}

def\ {varn}\([^;\)]*\) {
	printf("%s:", yytext);
}


else\ if\([^;\)]*\) {
	int i = 7, j = 0;
	char cond[100];
	while (yytext[i] != ')') {
		cond[j] = yytext[i];
		i++; j++;
	}
	cond[j] = yytext[i]; j++;
	cond[j] = '\0';
	printf("elif%s:",cond);
}

else {
	printf("else:");
}


if\([^;\)]*\) {
//	printf(" I get seen : %s", yytext);	
	printf("%s:",yytext);
}

\{ ;
\} ;

%%

int main() {
	yylex();
	return 0;
}
