#DEBUG_YACC = -t
#DEBUG_LEX = -d

all: 
	bison $(DEBUG_YACC) -d yacc.y
	flex $(DEBUG_LEX) lex.l
	gcc -g main.c yacc.tab.c lex.yy.c func.c output.c  -o cgraph2vcg

clean:
	rm -f cgraph2vcg lex.yy.c yacc.tab.c yacc.tab.h yacc.output
