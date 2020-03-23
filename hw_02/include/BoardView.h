#ifndef LAB11_BOARDVIEW_H_INCLUDED
#define LAB11_BOARDVIEW_H_INCLUDED

enum GameMode{
    DEFAULT,
    SILENT,
    NCURSE
};


class BoardView {
public:
    struct Point {
        int x_, y_;
    };
    virtual ~BoardView() = default;
    virtual Point read_input() = 0;
    virtual void draw_field() = 0;
    virtual void write_status() = 0;
};

constexpr static BoardView::Point exit_code = {-1, -1};

#endif