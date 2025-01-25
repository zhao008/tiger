#include "interpUtil.h"
#include <stdio.h> 
#include <string.h>

int getPrintArgs(A_stm stm){
  
  int printArgs = 1;
  A_expList expList = stm->u.print.exps;
  
  while(expList->kind != A_lastExpList){
      printArgs ++; 
      expList = expList->u.pair.tail;
  }

  return printArgs;
}

int maxargs(A_stm stm){
    int printMaxArg = 0;
    int printMaxArgStm1 = 0;
    int printMaxArgStm2 = 0;
    A_expList expList;
    
    if(stm->kind == A_printStm){

        printMaxArg = getPrintArgs(stm);
                
    }
    
    if(stm->kind == A_compoundStm){
        printMaxArgStm1 = maxargs(stm->u.compound.stm1);
        if(printMaxArgStm1 > printMaxArg)
            printMaxArg = printMaxArgStm1;
        printMaxArgStm2 = maxargs(stm->u.compound.stm2); 
        if(printMaxArgStm2 > printMaxArg)
            printMaxArg = printMaxArgStm2;        
    }

    if(stm->kind == A_assignStm){
        if(stm->u.assign.exp->kind == A_eseqExp)
            if(stm->u.assign.exp->u.eseq.stm->kind == A_printStm){
                
                printMaxArg = getPrintArgs(stm->u.assign.exp->u.eseq.stm);
                
            }  
    }
    return printMaxArg;
}

table Table(string id, int value){
    table t = checked_malloc(sizeof *t);
    t->id = id; t->value = value; t->left = NULL; t->right = NULL;
    return t;
}

table update(table t, string id, int value){
    if(t == NULL)
        t = Table(id, value);
    else if(strcmp(id, t->id) < 0)
        t->left = update(t->left, id, value);
    else if(strcmp(id, t->id) > 0)
        t->right = update(t->right, id, value);
    else if(strcmp(id, t->id) == 0)
        t->value = value;
    return t;   
}

void printTable(table t){
    if(t != NULL){
        printTable(t->left);
        printf("%s %d\n", t->id, t->value);
        printTable(t->right);
    }
}   

int lookup(table t, string id){
    int value = 0;
    
    if(t != NULL){
        if(strcmp(id, t->id) == 0)
            value = t->value;
        else if(strcmp(id, t->id) < 0)
            value = lookup(t->left, id);
        else if(strcmp(id, t->id) > 0)
            value = lookup(t->right, id);
    }

    return value;
}

table interpStm(A_stm s, table t){

    intAndTable iAt;
    A_expList   expList;
    A_exp       exp;

    if ( s->kind ==  A_compoundStm)
    {
        t = interpStm(s->u.compound.stm1, t);
        t = interpStm(s->u.compound.stm2, t);
    }
    
     if ( s->kind ==  A_assignStm)
    {
        iAt = interpExp(s->u.assign.exp, t);
        t = update(iAt.t, s->u.assign.id, iAt.i);
    }   

    if ( s->kind ==  A_printStm)
    {
        expList = s->u.print.exps;

        if( expList->kind == A_lastExpList )
            iAt = interpExp(expList->u.last, t);
        else
            iAt = interpExp(expList->u.pair.head, t);
        printf("%d ", iAt.i);

        while(expList->kind != A_lastExpList){
            expList = expList->u.pair.tail;
            
            if( expList->kind == A_lastExpList )
                iAt = interpExp(expList->u.last, t);
            else
                iAt = interpExp(expList->u.pair.head, t);
            
            printf("%d ", iAt.i);
            
        }

        printf("\n");
    }

    return t;    

}

intAndTable interpExp(A_exp e, table t){
    
    intAndTable iAt;
    intAndTable iAt_l;
    intAndTable iAt_r;

    if(e->kind == A_idExp){
        iAt.t = t;
        iAt.i = lookup(t, e->u.id);
    }

    if(e->kind == A_numExp){
        iAt.t = t;
        iAt.i = e->u.num;
    }

    if(e->kind == A_opExp){
        iAt.t = t;
        iAt_l = interpExp(e->u.op.left, t);
        iAt_r = interpExp(e->u.op.right, t);
        
        if(e->u.op.oper == A_plus) 
            iAt.i = iAt_l.i + iAt_r.i;
        else if(e->u.op.oper == A_minus)
            iAt.i = iAt_l.i - iAt_r.i;
        else if(e->u.op.oper == A_times)
            iAt.i = iAt_l.i * iAt_r.i;
        else if(e->u.op.oper == A_div)
            iAt.i = iAt_l.i / iAt_r.i;
    }

    if(e->kind == A_eseqExp){
        t = interpStm(e->u.eseq.stm, t);
        iAt = interpExp(e->u.eseq.exp, t);
    }

    return iAt;

}