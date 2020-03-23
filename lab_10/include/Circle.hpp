#pragma once

#include "Figure.hpp"

class Circle : public Figure {
public:
    Circle(int id, int x, int y, int radius, const char * label);
    ~Circle();
    void zoom(int factor) override;
    bool is_inside(int x, int y) const override;   
    void print() const override;

private:
    char * label;
    int radius;
};