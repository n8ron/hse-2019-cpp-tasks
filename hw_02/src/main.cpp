#include <iostream>
#include <cstring>
#include "Board.h"
#include "BoardView.h"
#include "StdioBoardView.h"
#include "GameController.h"
#include "NcursesBoardView.h"
#include <memory>

int main(int argc, char * argv[]) {
    std::unique_ptr<BoardView> view;
    Board cur_board;
    std::cout.exceptions(std::cout.failbit | std::cout.badbit);
    std::cin.exceptions(std::cin.failbit | std::cin.badbit);
    try {
        if (argc == 2) {
            if (!strcmp("silent", argv[1])) {
                view.reset(new StdioBoardView(cur_board, GameMode::SILENT));

            }
            else if (!strcmp("curses", argv[1])) {
                view.reset(new NcursesBoardView(cur_board));

            }
            else {
                std::cout << "Incorrect command\n";
                return 0;
            }
        }
        else {
            view.reset(new StdioBoardView(cur_board, GameMode::DEFAULT));
        }    
        GameController cur_game(*view, cur_board);
        cur_game.run_game();
    }
    catch(std::ios_base::failure & fail) {
        return 1;
    }
    return 0;
}