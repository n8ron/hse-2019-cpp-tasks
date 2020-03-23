#include <cstdio>
#include <iostream>
#include "Test.h"

int Test::totalNum = 0;
int Test::failedNum = 0;

bool Test::showFinalResult() {
    std::cout << "Passed " << totalNum - failedNum << " of " << totalNum << " tests\n";
    return (failedNum == 0);
}

void Test::check(bool expr, const char * func, const char  * filename, size_t lineNum) {
    if (!expr) {
        std::cout << "Failed:Func " << func << " in file " << filename << ", line " << lineNum << '\n';
        failedNum++;
    }
    totalNum++;
}