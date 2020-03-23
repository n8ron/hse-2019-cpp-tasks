#include <iostream>
#include <assert.h>
#include "my_array.h"


using namespace lab_13;

template <typename T, size_t N>
void test_my_array () {
    my_array<T, N> a;
    assert(!a.empty());
    assert(sizeof(a) == sizeof(T) * N);
    assert(a.size() == N);

    a.fill(14);

    assert(a[0] == 14 && a[N-1] == 14);
    if (N > 3) {
        a[3] = 3;
        assert(a[3] == 3);
        a.at(2) = 9;
        assert(a[2] == 9);
        a.at(3) = a[1];
        a[0] = a.at(3);
        assert(a.at(3) == 14);
        assert(a.at(0) == 14);
    }

    try {
        a.at(N + 3) = 4;
    }
    catch (const std::out_of_range & e) {
        std::cout << "Not bool tests passed\n";
        return;
    }

    assert(false);
}

template <size_t N>
void test_my_array_bool () {
    my_array<bool, N> a;
    my_array<bool, N> b;
    
    b[0] = true;
    for (size_t i = 1; i < N; i++) {
        b[i] = b[i - 1];
    }
    for (size_t i = 0; i < N; i++) {
        assert(b[i]);
    }
    for (size_t i = 0; i < N; i++) {
        b[i] = (i % 2 == 0) ? 0 : 1;
    }
    for (size_t i = 0; i < N; i++) {
        assert(b[i] == ((i % 2 == 0) ? 0 : 1));
    }
    for (size_t i = 0; i < N - 1; i++) {
        b[i] = b[i + 1];
    }

    for (size_t i = 0; i < N - 1; i++) {
        assert(b[i] == ((i % 2 == 0) ? 1 : 0));
    }
    assert(b[N - 1] == (((N - 1) % 2 == 0) ? 0 : 1));
    if (N > 11) {
        b[5] = true;
        b[7] = b[5];
        assert(b[5] == b[7]);
        assert(b[7] = true);
        b[3] = b[10] = b[4] = false;
        assert(b[3] == false);
        assert(b[10] == false);
        assert(b[4] == false);
    }
    assert(!a.empty());
    assert(sizeof(a) != sizeof(bool) * N);
    assert(sizeof(a) == sizeof(bool) * (N + 7) / 8);
    a.fill(true);
    assert(a.size() == N);
    assert(a[0] == true && a[N-1] == true);
    if (N > 3) {
        a[3] = false;
        assert(a[3] == false);
        a.at(2) = true;
        assert(a[2] == true);
        a.at(3) = a[1];
        assert(a.at(3) == true);
        a[1] = false;
        a[4] = a[5] = a[1]; 
        a[0] = a.at(3);
        assert(a.at(1) == false);
        assert(a.at(3) == true);
        assert(a[4] == false);
        assert(a.at(5) == false);
        assert(a.at(0) == true);
    }

    try {
        a.at(N + 3) = false;
    }
    catch (const std::out_of_range & e) {
        std::cout << "Bool tests passed\n";
        return;
    }
    assert(false);
}


int main() {
    std::cout.exceptions(std::cout.failbit | std::cout.badbit);
    std::cin.exceptions(std::cin.failbit | std::cin.badbit);
    try {
        test_my_array<int, 10>();
        test_my_array_bool <13>();
    }
    catch(std::ios_base::failure & fail) {
        return 1;
    } 
    return 0;
}