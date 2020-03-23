#include <ncurses.h>
#include "NcursesBoardView.h"

NcursesBoardView::NcursesBoardView(Board & board) : cur_board(board) {
    initscr();
    keypad(stdscr, TRUE);
}

NcursesBoardView::~NcursesBoardView() {
    endwin();
}

void NcursesBoardView::draw_field() {
    move(0, 0);
    for (int i = 0; i < cur_board.get_size(); i++) {
        for (int j = 0; j < cur_board.get_size(); j++) {
            Board::FieldState cell = cur_board.get_cell(i, j);
            switch (cell) {
                case Board::FieldState::X:
                    printw("X");
                    break;
                case Board::FieldState::O:
                    printw("O");
                    break;
                case Board::FieldState::E:
                    printw(".");
                    break;
            }
        }
        printw("\n");
    }
}

void NcursesBoardView::write_status() {
    switch (cur_board.get_state()) {
        case Board::GameState::x_win:
            printw("X wins!\n");
            game_final = true;
            break;
        case Board::GameState::o_win:
            printw("O wins!\n");
            game_final = true;
            break;
        case Board::GameState::draw:
            printw("Draw.\n");
            game_final = true;
            break;
        case Board::GameState::turn_x:
            printw("X move ");
            break;
        case Board::GameState::turn_o:
            printw("O move ");
            break;
    }
    move(cur_y, cur_x);
    refresh();
    if (game_final) {
        getch();
    }
}

void NcursesBoardView::move_cursor(int dx, int dy) {
    if (!cur_board.is_out_of_field(cur_x + dx, cur_y + dy)) {
        cur_y += dy;
        cur_x += dx;
    }

}

BoardView::Point NcursesBoardView::read_input() {
    bool correct_read = false;
    noecho();
    BoardView::Point cur_point;
    while(!correct_read) {
        int key = getch();
        switch (key) {
            case KEY_RIGHT:
                move_cursor(1, 0);
                break;
            case KEY_LEFT:
                move_cursor(-1, 0);
                break;
            case KEY_DOWN:
                move_cursor(0, 1);
                break;
            case KEY_UP:
                move_cursor(0, -1);
                break; 
            case ' ':
                cur_point.x_ = cur_y;
                cur_point.y_ = cur_x;
                correct_read = true;
                break;
            case 'x':
                cur_point.x_ = -1;
                cur_point.y_ = -1;
                correct_read = true;
        }
        if (!correct_read) {
            draw_field();
            write_status(); 
        }
    }
    return cur_point;
}