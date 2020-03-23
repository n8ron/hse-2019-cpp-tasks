#include "algorithm.h"
#include "util.h"
#include "io.h"

int doComputation(int a, double b) {
    int c = max(3, 4);    
    int d = (int)(a + b);
    c += d;
    logDebug('d');
    return c;
}
