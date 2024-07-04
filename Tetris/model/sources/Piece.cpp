#include "../headers/Piece.h"



namespace Tetris {


    Piece::Piece(char id) : id_(id), currentRotation_(0) {
        generateRotations(id);
        findCenter();
    }

/**
 * a = Brick I , b= Brick square , c = Brick T,  d = Brick J ,  e = Brick L,
 *  f = Brick Z ,  g = Brick S.
 * @param id this parm allows you to know exactly which piece it is
 * @return
 */
    std::vector<std::vector<std::pair<int, int>>> Piece::piecePositions(char id) {

        std::vector<std::vector<std::pair<int, int>>> relativePositions;
        switch (id) {
            case ('a'):
                relativePositions.push_back({{2, 3},
                                             {2, 2},
                                             {2, 1},
                                             {2, 0},
                                             {2, 1}}); // Rotation 0
                relativePositions.push_back({{0, 1},
                                             {1, 1},
                                             {2, 1},
                                             {3, 1},
                                             {2, 1}}); // Rotation 1
                relativePositions.push_back({{1, 3},
                                             {1, 2},
                                             {1, 1},
                                             {1, 0},
                                             {1, 1}}); // Rotation 2
                relativePositions.push_back({{0, 2},
                                             {1, 2},
                                             {2, 2},
                                             {3, 2},
                                             {2,2}}); // Rotation 3
                this->currentRotation_ = 0;
                break;

            case ('b'):

                relativePositions.push_back({{2, 3},
                                             {3, 3},
                                             {2, 2},
                                             {3, 2},
                                             {2,2}}); // Rotation 0
                relativePositions.push_back({{2, 3},
                                             {3, 3},
                                             {2, 2},
                                             {3, 2},
                                             {2,2}}); // Rotation 1
                relativePositions.push_back({{2, 3},
                                             {3, 3},
                                             {2, 2},
                                             {3, 2},
                                             {2,2}}); // Rotation 2
                relativePositions.push_back({{2, 3},
                                             {3, 3},
                                             {2, 2},
                                             {3, 2},
                                             {2,2}}); // Rotation 3
                this->currentRotation_ = 0;
                break;

            case ('c'):

                relativePositions.push_back({{2, 3},
                                             {2, 2},
                                             {1, 2},
                                             {3, 2},
                                             {2,2}}); // Rotation 0
                relativePositions.push_back({{1, 2},
                                             {2, 2},
                                             {2, 3},
                                             {2, 1},
                                             {2,2}}); // Rotation 1
                relativePositions.push_back({{2, 1},
                                             {2, 2},
                                             {1, 2},
                                             {3, 2},
                                             {2,2}}); // Rotation 2
                relativePositions.push_back({{3, 2},
                                             {2, 2},
                                             {2, 3},
                                             {2, 1},
                                             {2,2}}); // Rotation 3

                this->currentRotation_ = 0;
                break;

            case ('d'):
                relativePositions.push_back({{3, 1},
                                             {2, 1},
                                             {2, 2},
                                             {2, 3},
                                             {2,2}}); // Rotation 0
                relativePositions.push_back({{3, 2},
                                             {3, 3},
                                             {2, 2},
                                             {1, 2},
                                             {2,2}}); // Rotation 1
                relativePositions.push_back({{2, 1},
                                             {2, 2},
                                             {2, 3},
                                             {1, 3},
                                             {2,2}}); // Rotation 2
                relativePositions.push_back({{3, 2},
                                             {2, 2},
                                             {1, 2},
                                             {1, 1},
                                             {2,2}}); // Rotation 3
                this->currentRotation_ = 0;
                break;

            case ('e'):
                relativePositions.push_back({{2, 1},
                                             {2, 2},
                                             {2, 3},
                                             {3, 3},
                                             {2,2}}); // Rotation 0
                relativePositions.push_back({{3, 2},
                                             {2, 2},
                                             {1, 2},
                                             {1, 3},
                                             {2,2}}); // Rotation 1
                relativePositions.push_back({{1, 1},
                                             {2, 1},
                                             {2, 2},
                                             {2, 3},
                                             {2,2}}); // Rotation 2
                relativePositions.push_back({{3, 1},
                                             {3, 2},
                                             {2, 2},
                                             {1, 2},
                                             {2,2}}); // Rotation 3
                this->currentRotation_ = 0;
                break;

            case ('f'):
                relativePositions.push_back({{1, 2},
                                             {2, 2},
                                             {2, 1},
                                             {3, 1},
                                             {2,2}}); // Rotation 0
                relativePositions.push_back({{3, 3},
                                             {3, 2},
                                             {2, 2},
                                             {2, 1},
                                             {2,2}}); // Rotation 1
                relativePositions.push_back({{1, 3},
                                             {2, 3},
                                             {2, 2},
                                             {3, 2},
                                             {2,2}}); // Rotation 2
                relativePositions.push_back({{2, 3},
                                             {2, 2},
                                             {1, 2},
                                             {1, 1},
                                             {2,2}}); // Rotation 3

                this->currentRotation_ = 0;
                break;

            case ('g'):

                relativePositions.push_back({{1, 2},
                                             {2, 2},
                                             {2, 3},
                                             {3, 3},
                                             {2,2}}); // Rotation 0
                relativePositions.push_back({{1, 3},
                                             {1, 2},
                                             {2, 2},
                                             {2, 1},
                                             {2,2}}); // Rotation 1
                relativePositions.push_back({{3, 2},
                                             {2, 2},
                                             {2, 1},
                                             {1, 1},
                                             {2,2}}); // Rotation 2
                relativePositions.push_back({{3, 1},
                                             {3, 2},
                                             {2, 2},
                                             {2, 3},
                                             {2,2}}); // Rotation 3
                this->currentRotation_ = 0;
                break;

        }
        return relativePositions;
    }


    void Piece::generateRotations(char id) {

        std::vector<std::vector<std::pair<int, int>>> relativePositions = Piece::piecePositions(id);
        for (const auto &positions: relativePositions) {

            std::unique_ptr<Matrix> rotation = std::make_unique<Matrix>(5, 5);

            for (const auto &pos: positions) {
                rotation->setValue(pos.first, pos.second, 1);
            }
            rotation->setValue(positions.at(positions.size()-1).first, positions.at(positions.size()-1).second, 2);
            rotations_.push_back(std::move(rotation));


        }


    }

    const std::vector<std::unique_ptr<Matrix>> &Piece::getRotations() const {

        return this->rotations_;

    }

    const std::unique_ptr<Matrix> &Piece::getCurrentRotation() const {

        return rotations_[currentRotation_];

    }

    void Piece::rotate(Tetris::Movement movement) {

        switch (movement) {
            case Movement::CLOCKWISE : {

                currentRotation_++;
                if (this->currentRotation_ == 4) {
                    this->currentRotation_ = 0;
                }
                break;
            }

            case Movement::COUNTER_CLOCKWISE : {

                currentRotation_--;
                if (this->currentRotation_ == -1) {

                    this->currentRotation_ = 3;
                }
                break;
            }
            default: {
            }
        }
        findCenter();

    }


    const std::pair<int, int> Piece::center() const {
        return this->center_;
    }

    void Piece::findCenter() {
        for (int i = 0; i < this->rotations_.at(this->currentRotation_).get()->matrix().size(); i++) {
            for (int j = 0; j < this->rotations_.at(this->currentRotation_).get()->matrix().at(1).size(); j++) {
                if (this->rotations_.at(this->currentRotation_).get()->matrix().at(i).at(j) == 2){
                    this->center_.first = i;
                    this->center_.second = j;
                }
            }
        }
    }
}






