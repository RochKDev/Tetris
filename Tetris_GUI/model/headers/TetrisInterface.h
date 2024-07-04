#ifndef INC_57998_58493_PROJETDEV4_TETRISINTERFACE_H
#define INC_57998_58493_PROJETDEV4_TETRISINTERFACE_H
#include "../../DP/observer.h"
namespace Tetris{
    class Level;
    enum class Movement;

    /**
     * Abstract class that represents the Tetris Interface.
     */
    class TetrisInterface{
    public:
        /**
        * Starts a new \b Game.
        * @param level The level at which the \b Game starts.
        * @param fillBoar If true fills partially the board at the begin, else the board is empty.
        * @param width The width of the board of the \b Game.
        * @param height The height of the board of the \b Game.
        */
        virtual void start(Level level, int width, int height, bool fillBoard = false) = 0;
        /**
         * Moves the current piece
         * @param movement The move to make.
         */
        virtual void move(Movement movement) = 0;
        /**
         * Checks if the game is over.
         * @return True if the game is over, false otherwise.
         */
        virtual bool checkIfGameOver() = 0;

        /**
         * Checks if the game is over based on the score given.
         * @param maxScore The max score to reach during the game.
         * @return True if the score is greater or equal to maxScore, false otherwise.
         */
        virtual bool checkIfScoreGameOver(int maxScore) = 0;

        /**
        * Checks if the game is over based on the number of maxLines given.
        * @param maxLines The max number of lines to reach during the game.
        * @return True if the number of completed lines is greater or equal to maxLines, false otherwise.
        */
        virtual bool checkIfLinesGameOver(int maxLines) = 0;

        virtual void registerObserver(he2b::esi::dev4::Observer * observer) = 0;
    };
}

#endif //INC_57998_58493_PROJETDEV4_TETRISINTERFACE_H
