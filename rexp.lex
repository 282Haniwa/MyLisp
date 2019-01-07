%{
int linecounter = 1;
%}
%option nounput
%%
-?[0-9]+			{ return(INTEGER); }
-?[0-9]+"."[0-9]+	{ return(REAL); }
"("					{ return(LPAR); }
")"					{ return(RPAR); }
"."					{ return(DOT); }
"\n"				{ linecounter++; }
"\r\n"				{ linecounter++; }
"\r"				{ linecounter++; }
" "|"\t"			{ }
"#".*				{ linecounter++; }
[^ \t\r\n().#]*		{ return(ATOMIC_SYMBOL); }
%%
int yywrap(void) {
	return(1);
}
