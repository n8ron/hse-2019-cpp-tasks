#include <cstring>
#include <cstdio>
#include <assert.h>
#include "Circle.hpp"

Circle::Circle(int id, int x, int y, int radius, const char* label) : Figure (id, x, y) {
	assert(label != nullptr);
    this->radius = radius;
    this->label = new char[strlen(label) + 1];
    strcpy(this->label, label);     
}

void Circle::zoom(int factor) {
    if (factor < 0) {
        printf("ERROR: wrong factor\n");
        return;
    }
    radius *= factor;
} 

bool Circle::is_inside(int x, int y) const {
    int x0 = this->x;
    int y0 = this->y; 
    return (x0 - x) * (x0 - x) + (y0 - y) * (y0 - y) <= radius * radius;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, x, y, radius, label);
}

Circle::~Circle() {
    if (label != nullptr) {
        delete[] label;
    }
}