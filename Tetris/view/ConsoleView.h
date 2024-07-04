#ifndef TETRIS_CONSOLEVIEW_H
#define TETRIS_CONSOLEVIEW_H

#include "../model/headers/Board.h"
#include <string>
#include <vector>
#include "../DP/observer.h"
#include "../model/headers/TetrisFacade.h"

namespace Tetris {
    /**
     * The view of the Tetris game.
     */
    class ConsoleView : public he2b::esi::dev4::Observer {
        std::vector<std::string> validMoves{"left", "right", "down", "drop", "clock", "counterclock"};

    public:
        ConsoleView() = default;

        ~ConsoleView();

        void update(const Board *observable, int score, int level, int lines) override;

        /**
         * Displays the board in the console.
         * @param board The board to display.
         */
        void displayBoard(const Board *board);

        /**
         * Displays the a welcoming message to the console.
         */
        static void displayWelcomeMessage();

        /**
         * Asks robustly the user for a movement.
         * @return the string value of the movement.
         */
        std::string askUserForMovement();

        /**
         * Displays the given message to the console.
         * @param message the message to display.
         */
        static void displayMessage(const std::string &message);

        /**
         * Displays the given message to the console and reads the input.
         * @param message The message to display.
         * @return The string read in the input.
         */
        static std::string askUserForString(const std::string &message);

        /**
         * Checks if a string is correct.
         * @param message the message to display to the console.
         * @return the correct string.
         */
        std::string checkIfStringOK(const std::string &message);
    };
}
#endif //TETRIS_CONSOLEVIEW_H
