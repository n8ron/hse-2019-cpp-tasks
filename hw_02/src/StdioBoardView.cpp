#include <iostream>
#include <sstream>
#include "StdioBoardView.h"
#include "Board.h"

StdioBoardView::StdioBoardView(Board & board, GameMode mode): cur_board(board), mode_(mode) {}

void StdioBoardView::draw_field() {
    if ((mode_ != GameMode::SILENT) || 
        (cur_board.get_state() != Board::GameState::turn_x &&
        cur_board.get_state() != Board::GameState::turn_o)) {
                        
        for (int i = 0; i < cur_board.get_size(); i++) {
            std::cout<<'\n';
            for (int j = 0; j < cur_board.get_size(); j++) {
                Board::FieldState cell = cur_board.get_cell(i, j);
                switch (cell) {
                    case Board::FieldState::X:
                        std::cout << 'X';
                        break;
                    case Board::FieldState::O:
                        std::cout << 'O';
                        break;
                    case Board::FieldState::E:
                        std::cout << '.';
                        break;
                }
            }
        }
        std::cout << '\n';
    }
}

void StdioBoardView::write_status() {
    switch (cur_board.get_state()) {
        case Board::GameState::x_win:
            std::cout << "X wins!\n";
            break;
        case Board::GameState::o_win:
            std::cout << "O wins!\n";
            break;
        case Board::GameState::draw:
            std::cout << "Draw.\n";
            break;
        case Board::GameState::turn_x:
            std::cout << "X move: ";
            break;
        case Board::GameState::turn_o:
            std::cout << "O move: ";
            break;
    }
}

BoardView::Point StdioBoardView::read_input() {
    int x = -2, y = -2;
    std::string buff;
    char c, c2;
    Board::Player cur_player = (cur_board.get_state() == Board::GameState::turn_x) ? Board::Player::X : Board::Player::O;
    bool correct_read = false;
    while (!correct_read) {
        std::getline(std::cin, buff);
        int pos = buff.size() - 1;
        while (buff[pos] == ' ' && pos >= 0) {
            buff.pop_back();
            pos--;
        }
        int x_buf, y_buf;
        int numb = sscanf(buff.c_str(), "%d%c%d%c", &x_buf, &c, &y_buf, &c2);
        if (c == ' ' && numb == 3) {
            x = x_buf; y = y_buf;
        }
        
        if (!cur_board.can_move(x, y, cur_player) && !(x == exit_code.x_ && y == exit_code.y_)) {
            std::cout << "Bad move!" << '\n';
            std::cout << ((cur_board.get_state() == Board::GameState::turn_x) ? "X" : "O") << " move: ";
        }
        else {
            correct_read = true;
        }
    }
    BoardView::Point cur_point;
    cur_point.x_ = x;
    cur_point.y_ = y; 
    return cur_point;
}