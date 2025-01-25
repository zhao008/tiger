#include "slp.h"
#include "util.h"

#ifndef INTERPUTIL_H
#define INTERPUTIL_H

int getPrintArgs(A_stm stm);
int maxargs(A_stm stm);

//目前这一版将state table更新为二叉树结构
//树的左孩子小于根节点
typedef struct table_ *table;
struct table_ {string id; int value; table left; table right;};
table Table(string id, int value);
//目前写出的程序对于t是有副作用的，不知道有没有办法解决
table update(table t, string id, int value);
//当前打印二叉树的顺序为：中、左、右。
void printTable(table t);
int lookup(table t, string id);

typedef struct intAndTable { int i; table t;} intAndTable;
table interpStm(A_stm s, table t);
intAndTable interpExp(A_exp e, table t);

#endif