#ifndef LAB11_BOARDTEST_H_INCLUDED
#define LAB11_BOARDTEST_H_INCLUDED

#include <cstdio>

#include "Board.h"
#include "Test.h"


class BoardTest final : public Test {
private:
    void test_move_out_of_field();
    void test_move_incorrect_player();
    void test_move_not_empty_cell();
    void test_move_double_move();
    void test_move_correct_move();
    void test_get_state_o_win();
    void test_get_state_x_win();
    void test_get_state_o_turn();
    void test_get_state_x_turn();
    void test_get_state_draw();
    void test_is_out_of_field_true();
    void test_is_out_of_field_false();
    void test_get_size();
    void test_get_cell_X();
    void test_get_cell_O();
    void test_get_cell_E();

    void draw_line_right(Board &, int);
    void draw_line_left(Board &, int);
public:
    void runAllTests() override;
};  

#endif