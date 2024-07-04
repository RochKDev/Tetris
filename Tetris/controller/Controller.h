#ifndef TETRIS_CONTROLLER_H
#define TETRIS_CONTROLLER_H
#include "../view/ConsoleView.h"
#include "../model/headers/TetrisInterface.h"
#include "../model/headers/Movement.h"
#include "../model/headers/GameType.h"
#include <string>

namespace Tetris{
    enum class GameType;
    /**
     * The controller class of the Tetris Game.
     */
    class Controller{
        TetrisInterface &game_;
        ConsoleView view_;
        bool endGame;
        int maxLevel {20};
        GameType gameType;
        std::vector<std::string> types{"standard", "score", "lines", "survive"};
        int maxScore;
        int maxLines;

        /**
         * Asks robustly the user for the width of the board.
         * @return The width of the Board.
         */
        int checkWidth();

        /**
         * Asks robustly the user for the height of the board.
         * @return The height of the Board.
         */
        int checkHeight();

        /**
        * Asks robustly the user for the level of the board.
        * @return The level of the Board.
        */
        int checkLevel();

        /**
        * Asks robustly the user if he wants to partially fill the Board.
        * @return The answer of the user.
        */
        bool checkFillBoard();

        /**
        * Asks robustly the user if he wants to continue playing.
        * @return The answer of the user.
        */
        bool wouldContinue();

        /**
         * Checks if the string read from input is in fact a int.
         * @param message The message to display.
         * @return The transformed int from the string.
         */
        int checkIfStringInt(const std::string& message);

        /**
         * Asks robustly the user for the type of game he wants to play.
         * @return The \GameType that the user chose.
         */
        GameType askGameType();

        /**
         * Checks if the string from input is a correct string.
         * @param message The message to display to the user.
         * @return The correct string.
         */
        std::string checkIfStringOK(const std::string& message);

        /**
         * Converts a given string to a \GameType.
         * @param gameType The string to be converted.
         * @return The converted \bGameType.
         */
        GameType convertStringToGameType(const std::string &gameType);

        /**
         * Asks robustly the user for a movement.
         * @param move The movement to make.
         * @return The Converted \Movement from the string.
         */
        static Movement getMovementFromUser(const std::string& move);

        /**
         * Starts a game.
         * @param level The level at which to start.
         * @param width The width of the board.
         * @param height The height of the board.
         * @param fillBoard Fill or don't fill partially the board.
         */
        void startGame(int level, int width, int height, bool fillBoard);

        /**
        * Starts a standard game.
        * @param level The level at which to start.
        * @param width The width of the board.
        * @param height The height of the board.
        * @param fillBoard Fill or don't fill partially the board.
        */
        void startStandard(int level, int width, int height, bool fillBoard);

        /**
        * Starts a game where the player wins by reaching a certain score.
        * @param level The level at which to start.
        * @param width The width of the board.
        * @param height The height of the board.
        * @param fillBoard Fill or don't fill partially the board.
        */
        void startScore(int level, int width, int height, bool fillBoard);

        /**
        * Starts a game where the player wins by reaching a certain number of completed lines.
        * @param level The level at which to start.
        * @param width The width of the board.
        * @param height The height of the board.
        * @param fillBoard Fill or don't fill partially the board.
        */
        void startLines(int level, int width, int height, bool fillBoard);

        /**
        * Starts a game where the player wins by surviving certain amount of time.
        * @param level The level at which to start.
        * @param width The width of the board.
        * @param height The height of the board.
        * @param fillBoard Fill or don't fill partially the board.
        */
        void startSurvive(int level, int width, int height, bool fillBoard);

    public:
        Controller(TetrisInterface &game, ConsoleView &view);

        /**
         * Starts the game.
         */
        void start();
    };
}
#endif //TETRIS_CONTROLLER_H
