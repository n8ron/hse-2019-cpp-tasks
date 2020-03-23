#include <cmath>
#include <cstdio>
#include "Rectangle.hpp"

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure (id, x, y) {
    this->width = width;
    this->height = height;
}

void Rectangle::zoom(int factor) {
    if (factor < 0) {
        printf("ERROR: wrong factor\n");
        return;
    }
    width *= factor;
    height *= factor;
} 

bool Rectangle::is_inside(int x, int y) const {
    return 2 * abs(this->x - x) <= width && 2 * abs(this->y - y) <= height;
}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, x, y, width, height);
}
