#ifndef LAB11_GAMECONTROLLER_H_INCLUDED
#define LAB11_GAMECONTROLLER_H_INCLUDED

class BoardView;
class Board;

class GameController final {
public:
    explicit GameController(BoardView &, Board &);
    void run_game();
private:
    BoardView & view;
    Board & cur_board;
};

#endif