#include "../headers/Bag.h"
#include "../headers/Piece.h"
#include <iostream>
#include <algorithm>



namespace Tetris{

    Bag::Bag() : gen(std::random_device()()){
        pieces.push_back(std::shared_ptr<Piece>{std::make_shared<Piece>('a')});
        pieces.push_back(std::shared_ptr<Piece>{std::make_shared<Piece>('b')});
        pieces.push_back(std::shared_ptr<Piece>{std::make_shared<Piece>('c')});
        pieces.push_back(std::shared_ptr<Piece>{std::make_shared<Piece>('d')});
        pieces.push_back(std::shared_ptr<Piece>{std::make_shared<Piece>('e')});
        pieces.push_back(std::shared_ptr<Piece>{std::make_shared<Piece>('f')});
        pieces.push_back(std::shared_ptr<Piece>{std::make_shared<Piece>('g')});
        shufflePieces();

    }

    Piece * Bag::takePiece() {

        if (pieceIndex >= pieces.size()) {
            shufflePieces();
            this->pieceIndex = 0;
        }

        Piece *returnPiece = pieces[pieceIndex].get();
        this->pieceIndex++;

        return returnPiece;
    }


    void Bag::shufflePieces() {
        std::shuffle(pieces.begin(), pieces.end(), gen);
    }
}


