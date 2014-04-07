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

{typed}\ {alpha}{alphanum}*\_*{alphanum}*\(({single}(\,\ {single})*)?\) {
//	printf("seen a function");
	int i, j;
	i = j = 0;
//------------------------------------------
//Extraction of the name of the function	
	while(yytext[i] != ' ') i++;
	i++;
	char name[100], vars[100];
	while(yytext[i] != '(') {
		name[j] = yytext[i];
		j++;
		i++;
	}
	name[j] = '\0';
//	printf("\nname : %s", name);
	memset(vars, '\0', sizeof vars);
//------------------------------------------
	
//------------------------------------------	
// Extraction of the function arguments
	if(yytext[i+1] != ')') {
		i++;
		memset(vars, '#', sizeof vars);
		j = 0; // for variables
	label1:	printf("");
		int k = 0, l = 0;
		char temp[50];
		while(yytext[i] != ',' && yytext[i] != ')') {
			temp[k] = yytext[i];
			i++; k++;
		}
		temp[k] = '\0';
//		printf("\ntemp : %s", temp);
		k = 0;
		while(temp[k] != ' ') k++;
		k++;
		while(temp[k] != '\0') {
			vars[j] = temp[k];
			j++; k++;	
		}
		j++;
		if(yytext[i] == ',') {
			i += 2;
			goto label1;
		} else {
			vars[j-1] = '\0';
		}
					
	}
//	printf("\nvars : %s", vars);
//------------------------------------------

//------------------------------------------
	printf("def %s(", name);
	i = 0;
	while(vars[i] != '\0') {
		if(vars[i] == '#')
			printf(", ");
		else
			printf("%c", vars[i]);
		i++;
	}
	printf(")");	
	
//------------------------------------------

}

{typed}\ ({varn})(\,\ {varn})*\; ;


\|\| { printf("or");
}

\&\& {
	printf("and");
}

\! {
	printf("not");
}


%%
int main() {
	yylex();
	return 1;
}
