#ifndef INC_57998_58493_PROJETDEV4_TETRISFACADE_H
#define INC_57998_58493_PROJETDEV4_TETRISFACADE_H
#include "TetrisInterface.h"
#include "../../DP/observable.h"
#include "Level.h"
#include "Game.h"


namespace Tetris {
    enum class Movement;

    /**
     * It's the facade used to play the Tetris game.
     */
    class TetrisFacade : public TetrisInterface{
        Game game_;
    public :
        void start(Level level, int width, int height, bool fillBoard) override;
        virtual void move(Movement movement) override;
        bool checkIfGameOver() override;
        void registerObserver(he2b::esi::dev4::Observer * observer) override;
        bool checkIfScoreGameOver(int maxScore) override;
        bool checkIfLinesGameOver(int maxLines) override;
    };
}
#endif //INC_57998_58493_PROJETDEV4_TETRISFACADE_H
