#ifndef LAB11_STDIOBOARDVIEW_H_INCLUDED
#define LAB11_STDIOBOARDVIEW_H_INCLUDED
#include "BoardView.h"

class Board;

class StdioBoardView final: public BoardView {
public:
    StdioBoardView(Board &, GameMode);
    Point read_input() override;
    void draw_field() override;
    void write_status() override;
private:
    Board & cur_board;
    GameMode mode_;
};

#endif  