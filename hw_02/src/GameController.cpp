#include "GameController.h"
#include "StdioBoardView.h"
#include "Board.h"

GameController::GameController(BoardView & bw, Board & cb) : view(bw), cur_board(cb) {}

void GameController::run_game() {
    bool is_game_end = false;
    BoardView::Point point;
    while (!is_game_end) {
        view.draw_field();
        view.write_status();
        Board::GameState cur_state = cur_board.get_state();
        if (cur_state == Board::GameState::turn_x || 
            cur_state == Board::GameState::turn_o ) {
            Board::Player cur_player = (cur_state == Board::GameState::turn_x) ? Board::Player::X : Board::Player::O;

            point = view.read_input();
            while (!cur_board.can_move(point.x_, point.y_, cur_player) && 
                          !(point.x_ == exit_code.x_ && point.y_ == exit_code.x_)) {

                point = view.read_input();  
            }
            if (point.x_ == exit_code.x_ && point.y_ == exit_code.x_) {
                is_game_end = true;
            }
            else {
                cur_board.move(point.x_, point.y_, cur_player);    
            }
        }
        else {
            is_game_end = true;
        }
    }
}