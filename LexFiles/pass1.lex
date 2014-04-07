%{
	int tabc = 0;
	void indent();
%}
%%

\{ { printf("{"); tabc++; }

\} { printf("}"); tabc--; }

.+ { indent(); printf("%s", yytext); }


%%

void indent() {
	int i;
	for(i = 0; i < tabc; i++)
		printf("\t");
}


int main() {
	yylex();
	return 0;
}
