#ifndef INC_57998_58493_PROJETDEV4_BOARD_H
#define INC_57998_58493_PROJETDEV4_BOARD_H
#include <memory>
#include <vector>
#include "../headers/Bag.h"
#include "../headers/Level.h"

namespace Tetris {
    class Piece;
    enum class Movement;
    /**
     * Represents the board on which the game takes place.
     */
    class Board{
    protected:

        int width_;
        int height_;
        Piece* currentPiece_;
        Piece* nextPiece_;
        std::vector<std::vector<int>> board_;
        int lines_;
        bool isBoardFull_;
        int score_;
        int drop_;
        int oneMovementLines_;
        int boardCenter_;
        std::unique_ptr<Bag> bag_;
        std::unique_ptr<Level> level_;
        std::pair<int,int>currentPieceCenter_;
        std::vector<std::pair<int,int>>currentPiecePositions_;

        /**
         * Checks if the movement is a valid one.
         * @param movement The movement to check.
         * @return true if the movement is a valid one, false otherwise.
         */
        std::pair<bool,std::vector<std::pair<int,int>>> checkIfValidMovement(Movement movement);

        /**
         * Checks if there are any completed lines. If there are, calculates the score, updates it
         * and deletes any completed lines.
         */
        void checkPossibleLines();

        /**
         * Checks if the given line is completed. If it is, it deletes the line.
         * @param line The line to check.
         * @return True if a line was formed and deleted.
         */
        bool checkLine(int line);

        /**
         * Deletes the given line from the \b Board.
         * @param line the line to delete.
         */
        void deleteLine(int line);

        /**
         * Calculates the score of the \b Board.
         */
        void calculateScore();

        /**
         * Builds the board itself.
         * @param isPartiallyFilled Fills partially the board if true, else the board will be empty.
         */
        void buildBoard();

        /**
         * Partially fills the board with random pieces.
         */
        void partiallyFillBoard();

        /**
         * Places a new \b Piece on top of the \b Board.
         */
        void placeNewPiece();

        /**
         * Checks for lines in the current piece matrix that aren't empty.
         * @return The lines in the current piece that are occupied by the piece.
         */
        std::vector<int> nonZeroHorizontalPieceLines();

        /**
         * Checks if a line is only made of 0, so empty.
         * @param line The line to check.
         * @return True if the line is empty, false otherwise.
         */
        bool isLineEmpty(const std::vector<int>& line);

        /**
         * Fixes the current piece in place in the \b Board.
         */
        void fixPiece();

        /**
         * Rotates the current piece in the given movement.
         * @param movement the movement for the rotation.
         */
        void rotatePiece(Tetris::Movement movement);

        /**
         * Checks if the game should increase the current level, abd does so if necessary.
         */
        void checkNextLevel();

    public:
        /**
         * The constructor of the gaming \b Board.
         * @param width The width of the \b Board.
         * @param height The height of the \b Board.
         * @param level The \b Level at which the \b Board will start.
         * @param isBoardFull This param will be true when the \b board  is full but defaults to true
         * @param isPartiallyFilled_ The \b Board will be partially filled is true, else it will be empty.
         */
        Board(int height, int width, Level level, bool isPartiallyFilled = false);

        /**
         * Moves the current piece in the given movement.
         * @param movement The movement of the current piece.
         */
        void move(Movement movement);

        /**
         * Gets the lines completed on the \b Board.
         * @return The number of lines completed.
         */
        int lines() const;

        /**
         * Gets the score of the \b Board.
         * @return the score of the \b Board.
         */
        int score() const;

        /**
         * Gets the board represented by a 2D vector.
         * @return the board of the \b Board.
         */
        const std::vector<std::vector<int>> &board() const;

        /**
         * Gets the current level of the \b Board.
         * @return the current level of the \b Board.
         */
        Level* level() const;

        /**
         * Increases the current level by one.
         */
        void increaseLevel();

        /**
         * The getter for the isBoardFull attribute.
         * @return the value of isBoardFull.
         */
        bool isBoardFull () const;

        /**
         * The getter for the nextPiece attribute.
         * @return the value of NextPiece.
         */
        const Piece* nextPiece() const;
    };

}
#endif //INC_57998_58493_PROJETDEV4_BOARD_H
