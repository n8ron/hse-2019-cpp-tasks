#include <iostream>
#include "BoardTest.h"

int main() {
    BoardTest bt;
    bt.runAllTests();
    if (bt.showFinalResult()) {
        return 0;
    }
    else {
        return 1;
    }
}