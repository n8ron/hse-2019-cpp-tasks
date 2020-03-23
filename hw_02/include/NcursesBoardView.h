#ifndef LAB11_NCURSESBOARDVIEW_H_INCLUDED
#define LAB11_NCURSESBOARDVIEW_H_INCLUDED

#include "BoardView.h"
#include "Board.h"

class NcursesBoardView final: public BoardView {
public:
    NcursesBoardView(Board &);
    ~NcursesBoardView();
    Point read_input() override;
    void draw_field() override;
    void write_status() override;
private:
    Board & cur_board;
    void move_cursor(int dx, int dy);
    int cur_x = 0;
    int cur_y = 0;
    bool game_final = false;
};

#endif