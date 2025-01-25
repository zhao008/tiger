CC = cc
CFLAGS = -g 
#DEBUG = 1

# ifeq ($(DEBUG), 1)
#     CFLAGS += -g -Wall  # 调试模式
# else
#     CFLAGS += -O2  # 发布模式，启用优化
# endif

a.out: main.o prog1.o slp.o util.o interpUtil.o
	$(CC) $(CFLAGS) main.o prog1.o slp.o util.o interpUtil.o

main.o: main.c slp.h util.h interpUtil.h prog1.h
	$(CC) $(CFLAGS) -c main.c

prog1.o: prog1.c slp.h util.h
	$(CC) $(CFLAGS) -c prog1.c

slp.o: slp.c slp.h util.h
	$(CC) $(CFLAGS) -c slp.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c

interpUtil.o: interpUtil.c slp.h util.h
	$(CC) $(CFLAGS) -c interpUtil.c

clean: 
	rm -f a.out util.o prog1.o slp.o main.o interpUtil.o