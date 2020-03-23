#include "Figure.hpp"

class Rectangle : public Figure {
public:
    Rectangle(int id, int x, int y, int width, int height);
    void zoom(int factor) override;
    bool is_inside(int x, int y) const override;   
    void print() const override;

private:
    int height;
    int width;
};