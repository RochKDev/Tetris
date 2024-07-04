#include "../headers/Game.h"
#include "../../DP/observer.h"

namespace Tetris{
    Game::Game()
    {}

    void Game::start(Level level, int width, int height, bool fillBoard) {
        this->board_ = std::make_unique<Board>(Board(height, width, level, fillBoard));
    }

    const Board &Game::board() const {
        return *this->board_;
    }

    void Game::move(Movement movement) {
        this->board_->move(movement);
        checkNextLevel();
    }

    bool Game::checkIfGameOver() {
        return this->board_->isBoardFull();
    }

    void Game::checkNextLevel() {
        if (this->board_->lines() != 0 && this->board_->lines() % 10 == 0){
            this->board_->increaseLevel();
        }
    }

    void Game::notifyObservers() const{
        for (he2b::esi::dev4::Observer * observer : observers_)
        {
            observer->update(this->board_.get(), this->board_.get()->score(), this->board_.get()->level(), this->board_->lines());
        }
    }

    int Game::score() const {
        return this->board_->score();
    }

    int Game::lines() const {
        return this->board_->lines();
    }
}