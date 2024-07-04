#ifndef INC_57998_58493_PROJETDEV4_PIECE_H
#define INC_57998_58493_PROJETDEV4_PIECE_H
#include  <vector>
#include <memory>
#include "../headers/Matrix.h"
#include "../headers/Movement.h"

namespace Tetris {
    enum class Movement;
    /**
     * Represents a tetris \b Piece in a integer matrix with 4 different rotations.
     */
    class Piece{
        char id_;
        std::pair<int,int> center_;
        std::vector<std::unique_ptr<Matrix>> rotations_;
        int currentRotation_;

    public:
        /**
         * Creates a piece in a matrix.
         * @param id The id of the piece.
         */
        Piece(char id);

        /**
         * Getter for the \b rotations attribute.
         * @return the value of the \b rotations attribute.
         */
        const std::vector<std::unique_ptr<Matrix>> & getRotations() const;

        /**
         * Getter for the current rotation of the piece.
         * @return The current rotations of the piece in the \b rotations attribute.
         */
        const std::unique_ptr<Tetris::Matrix> &getCurrentRotation() const;

        /**
         * The getter for the \b center attribute.
         * @return the value of the \b center attribute.
         */
        const std::pair<int,int> center () const;

        /**
         * Rotates the piece in its matrix.
         * @param movement The movement of the rotation to make.
         */
        void rotate(Tetris::Movement movement);

    private:
        /**
         * Generates the 4 positions of the given piece.
         * @param id The id of the piece to generate the positions.
         * @return All the positions of the piece.
         */
        std::vector<std::vector<std::pair<int,int >>>piecePositions(char id);

        /**
         * Finds the center of the piece in its matrix.
         */
        void findCenter();

        /**
         * Initializes the positions of the piece in its matrix.
         * @param id The id of the piece.
         */
        void generateRotations(char id);
    };
}
#endif //INC_57998_58493_PROJETDEV4_PIECE_H
