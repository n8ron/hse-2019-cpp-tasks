#include <assert.h>
#include "Board.h"

const std::vector < std::pair <int, int> > Board::directions({{0, 1}, {1, 0}, {1, 1}, {1, -1}});

Board::Board() {
    for (int i = 0; i < size_; i++) { 
        for (int j = 0; j < size_; j++) {
            game_field[i][j] = FieldState::E;
        }
    }
}

int Board::get_size() const {
    return size_;
}

bool Board::is_out_of_field(int x, int y) const{
    if (x < 0 || y < 0 || x >= size_ || y >= size_) {
        return true;
    }
    return false;
}

Board::FieldState Board::get_cell(int x, int y) const{
    assert(!is_out_of_field(x, y));
    return (game_field[x][y]);
}

bool Board::is_cell_win(int x, int y) const {
    bool win = false;
    for (const auto[dx, dy] : directions) {
        win |= (check_row(x, y, dx, dy));
    }
    return win;
}

bool Board::check_row(int x, int y, int dx, int dy) const{
    int cell_in_a_row =  count_after_cell(x, y, dx, dy);
    if (cell_in_a_row + 1 >= number_in_a_row) {
        return true;
    }
    return false;
}

int Board::count_after_cell(int x, int y, int dx, int dy) const{
    FieldState cur_player = game_field[x][y];
    int temp_x = x;
    int temp_y = y;
    int cell_in_a_row = 0;
    while (game_field[temp_x][temp_y] == cur_player && 
         !is_out_of_field(temp_x + dx, temp_y + dy)) {

        temp_x += dx;
        temp_y += dy;
        if (game_field[temp_x][temp_y] == cur_player) {
             cell_in_a_row++;
        }
    }
    return cell_in_a_row;
}

Board::GameState Board::get_state() const {
    int number_of_x = 0;
    int number_of_o = 0;
    for (int x = 0; x < size_; x++) {
        for (int y = 0; y < size_; y++) {
            if (game_field[x][y] == FieldState::X) {
                number_of_x++;  
            }
            if (game_field[x][y] == FieldState::O) {
                number_of_o++;
            }
            if (game_field[x][y] != FieldState::E) {
                if (is_cell_win(x, y)) {
                    return (game_field[x][y] == FieldState::X) ? GameState::x_win : GameState::o_win;
                }
            }
        }
    }
    
    assert(abs(number_of_x - number_of_o) <= 1);
    assert(number_of_o >= 0 && number_of_x >= 0);

    if (number_of_x + number_of_o == size_ * size_) {
        return GameState::draw;
    }
    return (number_of_o > number_of_x) ? GameState::turn_x : GameState::turn_o;
}

bool Board::can_move(int x, int y, Player player) const {
    if (is_out_of_field(x, y)) {
        return false;
    }
    GameState temp_game_state = (player == Player::X) ? GameState::turn_x : GameState::turn_o;
    if (temp_game_state == get_state() && game_field[x][y] == FieldState::E) {
         return true;
    }
    return false;
}

void Board::move(int x, int y, Player player) {
    game_field[x][y] = (player == Player::O) ? FieldState::O : FieldState::X;    
}
