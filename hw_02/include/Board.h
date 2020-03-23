#ifndef LAB11_BOARD_H_INCLUDED
#define LAB11_BOARD_H_INCLUDED
#include <array>
#include <vector>

class Board final {
public:
    Board();
    enum class GameState {
        x_win, o_win, draw, turn_x, turn_o
    };

    enum class Player {
        X, O
    };

    enum class FieldState {
        X, O, E
    };

    bool can_move(int x, int y, Player player) const; 
    void move(int x, int y, Player player); 
    GameState get_state() const;
    
    FieldState get_cell(int x, int y) const; 
    int get_size() const;
    bool is_out_of_field(int x, int y) const;

private:
    static const std::vector < std::pair <int, int> > directions;
    constexpr static int size_ = 10;
    constexpr static int number_in_a_row = 5;
    std::array<std::array<FieldState, size_>, size_> game_field;
    bool is_cell_win(int x, int y) const;
    bool check_row(int x, int y, int dx, int dy) const;
    int  count_after_cell(int x, int y, int dx, int dy) const;
};

#endif