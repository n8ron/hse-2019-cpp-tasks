#include <iostream>
#include <cstring>
#include <assert.h>

#include "my_vector.h"

namespace product {

class Product {
public:
    Product(const char* name, int quantity, double price) : quantity_(quantity), price_(price) {
        assert(name != nullptr);
        name_ = new char[sizeof(name)];
        strcpy(name_, name);
    }

    Product(const Product& other) : Product(other.name_, other.quantity_, other.price_) {}

    ~Product() {
        delete [] name_;
    }
    bool operator== (Product product) {
        return strcmp(name_, product.name_) == 0 
               && quantity_ == product.quantity_
               && price_ == product.price_;

    }
    std::ostream& operator>> (std::ostream& os) const {
        os << name_ << ' ' << quantity_ << ' ' << price_;
        return os;
    }
private:
    char* name_; 
    int quantity_;
    double price_;
};

std::ostream& operator<< (std::ostream& os, const Product & product) {
    return product >> os;
}

void print(const my_vector::my_vector<Product>& v) {
    std::cout << v << std::endl;
}

}  // namespace product

template < typename T >
void test_my_vector (T first, T second) {
    my_vector::my_vector<T> a1;
    
    assert(a1.empty());
    assert(a1.size() == 0);
    assert(a1.capacity() == 0);

    a1.push_back(first);

    assert(a1.capacity() == 1);
    assert(a1.size() == 1);
    assert(!a1.empty());  

    a1.push_back(second);

    assert(a1.capacity() == 2);
    assert(a1.size() == 2);

    a1.push_back(second);

    assert(a1.capacity() == 4);
    assert(a1.size() == 3);

    a1.pop_back();

    assert(a1.capacity() == 4);
    assert(a1.size() == 2);

    a1.push_back(second);
    assert(a1.capacity() == 4);
    assert(a1.size() == 3);

    my_vector::my_vector<T> a2 = a1;

    a1.reserve(15);
    assert(a1.capacity() == 16);
    assert(a1.size() == 3);
    assert(a2.capacity() == 4);
    assert(a1.size() == 3);
    
    my_vector::my_vector<T> a3;
    a3 = a1; 
    a2.push_back(second);
    a1.clear();

    assert(a1.capacity() == 16);
    assert(a1.size() == 0);
    assert(a2.capacity() == 4);
    assert(a2.size() == 4);
    assert(a3.capacity() == 4);
    assert(a3.size() == 3);

    my_vector::my_vector<T> a4 = std::move(a1);

    assert(a4.capacity() == 16);
    assert(a4.size() == 0);
    a4.push_back(second);
    assert(a4[0] == second);

    a4 = std::move(a2);
    assert(a4.capacity() == 4);
    assert(a4.size() == 4);
    

    std::cout << "All tests passed\n";
}

template < typename T >
void test_my_vector_default_constructible (T first, T second) {
    my_vector::my_vector<T> a1;
    a1.resize(17);

    assert(a1.capacity() == 32);
    assert(a1.size() == 17);
    
    my_vector::my_vector<T> a2(12);
    a1.push_back(first);
    a1.push_back(second);

    assert(a1.capacity() == 32);
    assert(a1.size() == 19);
    assert(a2.capacity() == 16);
    assert(a2.size() == 12);

    a2.resize(7);
    assert(a2.capacity() == 16);
    assert(a2.size() == 7);

    a2.resize(7);
    assert(a2.capacity() == 16);
    assert(a2.size() == 7);
    a2[4] = 5;
    assert(a2[4] == 5);
    my_vector::my_vector<T> a3 = std::move(a2);
    assert(a3[4] == 5);
    a3[6] = 7;
    assert(a3[6] == 7);

    std::cout << "All default constructible passed\n";
}

int main() {
    std::cout.exceptions(std::cout.failbit | std::cout.badbit);
    std::cin.exceptions(std::cin.failbit | std::cin.badbit);

    try {
        test_my_vector<int>(5, 10);
        test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));
        test_my_vector_default_constructible <int>(5, 10);
    }
    catch (const std::bad_alloc& e) {
        std::cout << "Unable to allocate memory.\n";
        return 1;
    }
    catch(std::ios_base::failure & fail) {
        return 1;
    } 
    return 0;
}