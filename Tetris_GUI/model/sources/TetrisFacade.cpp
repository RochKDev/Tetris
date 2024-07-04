#include "../headers/TetrisFacade.h"
#include "../headers/Movement.h"

namespace Tetris {

    void TetrisFacade::start(Level level, int width, int height, bool fillBoard) {
        this->game_ = Game();
        game_.start(level, width, height, fillBoard);
    }

    void TetrisFacade::move(Tetris::Movement movement) {
        game_.move(movement);
        game_.notifyObservers();
    }

    bool TetrisFacade::checkIfGameOver() {
        return this->game_.checkIfGameOver();
    }

    void TetrisFacade::registerObserver(he2b::esi::dev4::Observer *observer) {
        this->game_.registerObserver(observer);
        game_.notifyObservers();
    }

    bool TetrisFacade::checkIfScoreGameOver(int maxScore) {
        return this->game_.score() >= maxScore;
    }

    bool TetrisFacade::checkIfLinesGameOver(int maxLines) {
        return this->game_.lines() >= maxLines;
    }

    const Piece *TetrisFacade::getNextPiece() const{
        return game_.getNextPiece();
    }
}// end namespace Tetris
