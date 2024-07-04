#ifndef GAME_H
#define GAME_H
#include <chrono>
#include <memory>
#include "Board.h"
#include "../../DP/observable.h"

namespace Tetris {
    class Level;
    enum class Movement;

    /**
     * Represents the game.
     */
    class Game : public he2b::esi::dev4::Observable{
        std::unique_ptr<Board> board_;
        std::chrono::duration<int> time_;

        /**
         * Checks if the game should increase the current level, abd does so if necessary.
         */
        void checkNextLevel();

    public:
        /**
         * The default constructor of \b Game.
         */
        Game();

        /**
         * The getter of the board.
         * @return the board of the game.
         */
        const Board &board() const;

        /**
         * The getter of \b isGameOver.
         * @return the boolean \b isGameOver.
         */
        bool isGameOver() const;

        /**
         * Starts a new \b Game.
         * @param level The level at which the \b Game starts.
         * @param fillBoar If true fills partially the board at the begin, else the board is empty.
         * @param width The width of the board of the \b Game.
         * @param height The height of the board of the \b Game.
         */
        void start(Level level, int width, int height, bool fillBoard = false);

        /**
         * Moves the current piece
         * @param movement The move to make.
         */
        void move(Movement movement);

        /**
         * Checks if the game is over.
         * @return True if the game is over, false otherwise.
         */
        bool checkIfGameOver();

        /**
         * The getter of \b isGameWin.
         * @return \b isGameWin.
         */
        bool isGameWin() const;

        void notifyObservers() const override;

        /**
         * The getter of \b score attribute.
         * @return the value of the \b score attribute.
         */
        int score() const;

        /**
         * The getter of \b lines attribute.
         * @return the value of the \b lines attribute.
         */
        int lines() const;
    };
}
#endif // GAME_H
