# 编译文件为test.lex，生成了lex.out，随后使用clean清除lex.out和lex.yy.c

all: lex.out

lex.yy.c: test.lex
	lex test.lex

lex.out: lex.yy.c
	gcc -o lex.out lex.yy.c

clean:
	rm -f lex.out lex.yy.c