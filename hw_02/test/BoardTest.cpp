#include <cstdio>
#include <iostream>
#include "BoardTest.h"

static constexpr const auto X = Board::Player::X;
static constexpr const auto O = Board::Player::O;

void BoardTest::test_move_out_of_field() {
    Board b;
    DO_CHECK(!b.can_move(-1, 5, O));
}


void BoardTest::test_move_incorrect_player() {
    Board b;
    DO_CHECK(!b.can_move(1, 5, X));
}

void BoardTest::test_move_not_empty_cell() {
    Board b;
    b.move(1, 0, O);	
    DO_CHECK(!b.can_move(1, 0, X));
}

void BoardTest::test_move_double_move() {
    Board b;
    b.move(3, 5, O);
    DO_CHECK(!b.can_move(4, 3, O));
}

void BoardTest::test_move_correct_move() {
    Board b;
    b.move(9, 9, O);
    DO_CHECK(b.can_move(0, 0, X));
}

void BoardTest::test_get_state_o_win() {
    Board b;
    b.move(0, 0, O);
    b.move(0, 1, X);
    b.move(1, 0, O);
    b.move(1, 1, X);
    b.move(2, 0, O);
    b.move(2, 1, X);
    b.move(3, 0, O);
    b.move(3, 1, X);
    b.move(4, 0, O);
    DO_CHECK(b.get_state() == Board::GameState::o_win);
}

void BoardTest::test_get_state_x_win() {
    Board b;
    b.move(0, 0, O);
    b.move(0, 1, X);
    b.move(1, 0, O);
    b.move(1, 1, X);
    b.move(2, 0, O);
    b.move(2, 1, X);
    b.move(3, 0, O);
    b.move(3, 1, X);
    b.move(5, 0, O);
    b.move(4, 1, X);
    DO_CHECK(b.get_state() == Board::GameState::x_win);
}

void BoardTest::test_get_state_o_turn() {
    Board b;
    DO_CHECK(b.get_state() == Board::GameState::turn_o);
}

void BoardTest::test_get_state_x_turn() {
    Board b;
    b.move(1, 3, O);
    DO_CHECK(b.get_state() == Board::GameState::turn_x);
}

void BoardTest::draw_line_right(Board & b, int i) {
    for (int j = 0; j < b.get_size(); j++) {
        if (j % 2 == 0) {
            b.move(i, j, O);
        }
        else {
            b.move(i, j, X);
        }
    }
}

void BoardTest::draw_line_left(Board & b, int i) {
     for (int j = b.get_size() - 1; j >= 0; j--) {
        if (j % 2 != 0) {
            b.move(i, j, O);
        }
        else {
            b.move(i, j, X);
        }
    }
}

void BoardTest::test_get_state_draw() {
    Board b;
    for (int i = 0; i < b.get_size(); i += 2) {
        if (i % 4 == 0) {
            draw_line_right(b, i);
            draw_line_right(b, i + 1);      
        }
        else {
            draw_line_left(b, i);
            draw_line_left(b, i + 1); 
            
        }
    }
    DO_CHECK(b.get_state() == Board::GameState::draw);

}

void BoardTest::test_is_out_of_field_true() {
     Board b;
     DO_CHECK(b.is_out_of_field(10, 10));    
}

void BoardTest::test_is_out_of_field_false() {
     Board b;
     DO_CHECK(!b.is_out_of_field(1, 5));    
}

void BoardTest::test_get_size() {
     Board b;
     DO_CHECK(b.get_size() == 10);    
}

void BoardTest::test_get_cell_X() {
     Board b;
     b.move(1, 1, O);
     b.move(2, 3, X);
     DO_CHECK(b.get_cell(2, 3) == Board::FieldState::X);    
}

void BoardTest::test_get_cell_O() {
     Board b;
     b.move(1, 1, O);
     DO_CHECK(b.get_cell(1, 1) == Board::FieldState::O);     
}

void BoardTest::test_get_cell_E() {
     Board b;
     DO_CHECK(b.get_cell(1, 1) == Board::FieldState::E);    
}

void BoardTest::runAllTests() {
    test_move_out_of_field();
    test_move_incorrect_player();
    test_move_not_empty_cell();
    test_move_double_move();
    test_move_correct_move();
    test_get_state_o_win();
    test_get_state_x_win();
    test_get_state_o_turn();
    test_get_state_x_turn();
    test_get_state_draw();
    test_is_out_of_field_true();
    test_is_out_of_field_false();
    test_get_size();
    test_get_cell_X();
    test_get_cell_O();
    test_get_cell_E();
}