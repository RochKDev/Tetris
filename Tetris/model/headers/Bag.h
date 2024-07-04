#ifndef INC_57998_58493_PROJETDEV4_BAG_H
#define INC_57998_58493_PROJETDEV4_BAG_H
#include <vector>
#include <memory>
#include <random>

namespace Tetris {

class Piece;
    /**
     * Represents a \b Bag containing the pieces of the game.
     */
    class Bag {
        std::vector<std::shared_ptr<Piece>> pieces;
        int pieceIndex = 0;
        std::mt19937 gen;

    public:
        /**
         * The default constructor of \b Bag.
         */
        Bag();

        /**
         * Takes a piece out of the \b Bag.
         */
         Piece* takePiece();

        /**
       * Shuffles the pieces of the bag.
       */
        void shufflePieces();
    };
}
#endif //INC_57998_58493_PROJETDEV4_BAG_H
