#include <stdio.h>
#include "slp.h"
#include "util.h"
#include "prog1.h"
#include "interpUtil.h"

int main(){
    table t = NULL;
    A_stm stm = prog();
    t = interpStm(stm, t);
    
    // table t = NULL;
    // t = update(t, "d", 10);
    // t = update(t, "b", 80);
    // t = update(t, "f", 5);
    // t = update(t, "z", 5);
    // t = update(t, "c", 5);
    // t = update(t, "ca", 5);
    // t = update(t, "aa", 5);
    // printTable(t);

    return 0;
}