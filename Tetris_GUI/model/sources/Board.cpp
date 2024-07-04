#include "../headers/Board.h"
#include "../headers/Piece.h"
#include <algorithm>


namespace Tetris {

    Board::Board(int height, int width, Level level, bool isPartiallyFilled)
            : width_(width), height_(height), lines_(0), isBoardFull_(false), score_(0), drop_(0),
              oneMovementLines_(0) {
        this->level_ = std::make_unique<Level>(Level(level));
        this->bag_ = std::make_unique<Bag>(Bag());
        this->currentPieceCenter_ = std::make_pair(0, 0);
        buildBoard();
        this->boardCenter_ = this->board_.at(0).size() / 2;
        if (isPartiallyFilled) {
            partiallyFillBoard();
        }
        this->currentPiece_ = this->bag_->takePiece();
        this->nextPiece_ = this->bag_->takePiece();
        placeNewPiece();
    }

    void Board::buildBoard() {
        for (int i = 0; i < this->height_; i++) {
            this->board_.emplace_back(this->width_, 0);
        }
    }

    void Board::increaseLevel() {
        this->level_ = std::make_unique<Level>(Level(this->level_->number() + 1));
    }
    void Board::checkNextLevel() {
        if (this->lines_ != 0 && this->lines_ % 10 == 0){
            this->increaseLevel();
        }
    }

    Level* Board::level() const {
        return this->level_.get();
    }

    void Board::deleteLine(int line) {
        this->board_.erase(this->board_.cbegin() + line);
        this->board_.emplace_back(this->width_, 0);
        this->currentPieceCenter_.first -= 1;

        for (auto &row: this->currentPiecePositions_) {
            row.first -= 1;
        }
    }

    int Board::lines() const {
        return this->lines_;
    }

    bool Board::checkLine(int line) {
        for (int x: this->board_.at(line)) {
            if (x == 0) {
                return false;
            }
        }
        return true;
    }

    void Board::checkPossibleLines() {
        this->oneMovementLines_ = 0;
        for (int i = 0; i < this->board_.size(); i++) {
            if (checkLine(i)) {
                deleteLine(i);
                this->oneMovementLines_++;
                this->lines_++;
                checkNextLevel();
                i--;
            }
        }
    }

    int Board::score() const {
        return this->score_;
    }

    const std::vector<std::vector<int>> &Board::board() const {
        return this->board_;
    }

    std::pair<bool, std::vector<std::pair<int, int>>> Board::checkIfValidMovement(Movement movement) {

        switch (movement) {
            case Movement::LEFT : {


                std::vector<std::pair<int, int>> positions = currentPiecePositions_;
                std::vector<std::pair<int, int>> positionsAfterMove;


                for (const auto &pos: positions) {
                    int newRow = pos.first;
                    int newCol = pos.second - 1;


                    if ((newCol < 0 || board_[newRow][newCol] == -1)) {


                        return {false, currentPiecePositions_};
                    }


                    positionsAfterMove.emplace_back(newRow, newCol);


                }
                return {true, positionsAfterMove};
            }

            case Movement::RIGHT : {

                std::vector<std::pair<int, int>> positions = currentPiecePositions_;
                std::vector<std::pair<int, int>> positionsAfterMove;


                for (const auto &pos: positions) {
                    int newRow = pos.first;
                    int newCol = pos.second + 1;


                    if ((newCol >=board_[0].size() || board_[newRow][newCol] == -1)) {


                        return {false, currentPiecePositions_};
                    }


                    positionsAfterMove.emplace_back(newRow, newCol);


                }

                return {true, positionsAfterMove};
            }

            case Movement::DOWN : {

                std::vector<std::pair<int, int>> positions = currentPiecePositions_;
                std::vector<std::pair<int, int>> positionsAfterMove;


                for (const auto &pos: positions) {
                    int newRow = pos.first - 1;
                    int newCol = pos.second;

                        if (newRow < 0 ||board_[newRow][newCol] == -1) {
                            return {false, currentPiecePositions_};
                        }


                    positionsAfterMove.emplace_back(newRow, newCol);
                }
                return {true, positionsAfterMove};
            }

            case Movement::CLOCKWISE : {


                int rowCenter = currentPiece_->center().first;
                int colCenter = currentPiece_->center().second;

                std::vector<std::pair<int, int>> positionsAfterMove;
                std::vector<std::pair<int, int>> positions = currentPiecePositions_;

                rotatePiece(Movement::CLOCKWISE);

                int rowMax = this->currentPiece_->getCurrentRotation()->matrix().size();
                int colMax = this->currentPiece_->getCurrentRotation()->matrix()[0].size();

                int rowPiece = 0;
                int colPiece = 0;

                int rowCenterBoard = 0;
                int colCenterBoard = 0;

                int row = 0;
                int col = 0;

                for (int i = 0; i < rowMax; i++) {
                    for (int j = 0; j < colMax; j++) {


                        if (currentPiece_->getCurrentRotation()->matrix()[i][j] == 1 ||
                            currentPiece_->getCurrentRotation()->matrix()[i][j] == 2) {


                            rowPiece = i -rowCenter ;
                            colPiece = j - colCenter;

                            rowCenterBoard = currentPieceCenter_.first;
                            colCenterBoard = currentPieceCenter_.second;

                            row = rowCenterBoard + rowPiece;
                            col = colCenterBoard + colPiece;
                        } else {
                            continue;
                        }

                        if ((row < 0 || row >= board_.size()) || (col < 0 || col >= board_[0].size()) ||
                            (board_[row][col]) == -1) {

                            return {false, positions};
                        }
                        positionsAfterMove.emplace_back(row, col);
                    }
                }
                return {true, positionsAfterMove};
            }

            case Movement::COUNTER_CLOCKWISE : {

                int rowCenter = currentPiece_->center().first;
                int colCenter = currentPiece_->center().second;

                std::vector<std::pair<int, int>> positionsAfterMove;
                std::vector<std::pair<int, int>> positions = currentPiecePositions_;

                rotatePiece(Movement::COUNTER_CLOCKWISE);

                int rowMax = this->currentPiece_->getCurrentRotation()->matrix().size();
                int colMax = this->currentPiece_->getCurrentRotation()->matrix()[0].size();

                int rowPiece = 0;
                int colPiece = 0;

                int rowCenterBoard = 0;
                int colCenterBoard = 0;

                int row = 0;
                int col = 0;

                for (int i = 0; i < rowMax; i++) {
                    for (int j = 0; j < colMax; j++) {


                        if (currentPiece_->getCurrentRotation()->matrix()[i][j] == 1 ||
                            currentPiece_->getCurrentRotation()->matrix()[i][j] == 2) {


                            rowPiece = i - rowCenter;
                            colPiece = j - colCenter;

                            rowCenterBoard = currentPieceCenter_.first;
                            colCenterBoard = currentPieceCenter_.second;

                            row = rowCenterBoard + rowPiece;
                            col = colCenterBoard + colPiece;


                        } else {
                            continue;
                        }


                        if ((row < 0 || row >= board_.size()) || (col < 0 || col >= board_[0].size()) ||
                            (board_[row][col]) == -1) {

                            return {false, positions};
                        }


                        positionsAfterMove.emplace_back(row, col);


                    }


                }
                return {true, positionsAfterMove};
            }

            default: {
                return {false, currentPiecePositions_};
            }
        }
    }

    void Board::move(Movement movement) {


        switch (movement) {

            case Movement::DOWN: {
                std::pair<bool, std::vector<std::pair<int, int>>> isValid = checkIfValidMovement(Movement::DOWN);

                if (isValid.first) {

                    this->currentPieceCenter_.first --;

                    for (const auto &pos: currentPiecePositions_) {
                        int row = pos.first;
                        int col = pos.second;
                        board_[row][col] = 0;
                    }

                    this->currentPiecePositions_ = isValid.second;
                    for (const auto &newPos: this->currentPiecePositions_) {
                        int row = newPos.first;
                        int col = newPos.second;
                        board_[row][col] = 1;
                    }


                } else {
                    fixPiece();
                }

                break;
            }


            case Movement::LEFT : {

                std::pair<bool, std::vector<std::pair<int, int>>> isValid = checkIfValidMovement(Movement::LEFT);

                if (isValid.first) {

                    for (const auto &pos: currentPiecePositions_) {
                        int row = pos.first;
                        int col = pos.second;
                        board_[row][col] = 0;
                    }

                    this->currentPiecePositions_ = isValid.second;
                    this->currentPieceCenter_.second--;
                    for (const auto &newPos: this->currentPiecePositions_) {
                        int row = newPos.first;
                        int col = newPos.second;
                        board_[row][col] = 1;
                    }
                }
                move(Movement::DOWN);
                break;
            }

            case Movement::RIGHT: {
                std::pair<bool, std::vector<std::pair<int, int>>> isValid = checkIfValidMovement(Movement::RIGHT);

                if (isValid.first) {

                    for (const auto &pos: currentPiecePositions_) {
                        int row = pos.first;
                        int col = pos.second;
                        board_[row][col] = 0;
                    }
                    this->currentPiecePositions_ = isValid.second;
                    this->currentPieceCenter_.second++;
                    for (const auto &newPos: isValid.second) {
                        int row = newPos.first;
                        int col = newPos.second;
                        board_[row][col] = 1;
                    }
                }
                move(Movement::DOWN);
                break;
            }

            case Movement::CLOCKWISE: {
                std::pair<bool, std::vector<std::pair<int, int>>> isValid = checkIfValidMovement(Movement::CLOCKWISE);

                if (isValid.first) {

                    for (const auto &pos: currentPiecePositions_) {
                        int row = pos.first;
                        int col = pos.second;
                        board_[row][col] = 0;
                    }

                    currentPiecePositions_ = isValid.second;
                    for (const auto &newPos: currentPiecePositions_) {
                        int row = newPos.first;
                        int col = newPos.second;
                        board_[row][col] = 1;
                    }
                }

                break;
            }


            case Movement::COUNTER_CLOCKWISE: {
                std::pair<bool, std::vector<std::pair<int, int>>> isValid = checkIfValidMovement(
                        Movement::COUNTER_CLOCKWISE);

                if (isValid.first) {

                    for (const auto &pos: currentPiecePositions_) {
                        int row = pos.first;
                        int col = pos.second;
                        board_[row][col] = 0;
                    }

                    currentPiecePositions_ = isValid.second;

                    for (const auto &newPos: currentPiecePositions_) {
                        int row = newPos.first;
                        int col = newPos.second;
                        board_[row][col] = 1;
                    }
                }

                break;
            }

            case Movement::DROP: {
                std::pair<bool, std::vector<std::pair<int, int>>> isValid = checkIfValidMovement(
                        Movement::DOWN);

                while (isValid.first) {
                    move(Movement::DOWN);
                    this->drop_++;
                    isValid = checkIfValidMovement(Movement::DOWN);
                }
                move(Movement::DOWN);
                break;
            }
        }
    }

    void Board::calculateScore() {
        switch (this->oneMovementLines_) {
            case 1 : {
                this->score_ += (40 * 1 + this->drop_) * this->level_->number();
                break;
            }
            case 2: {
                this->score_ += (100 * 2 + this->drop_) * this->level_->number();
                break;
            }
            case 3: {
                this->score_ += (300 * 3 + this->drop_) * this->level_->number();
                break;
            }
            case 4: {
                this->score_ += (1200 * 4 + this->drop_) * this->level_->number();
                break;
            }
            default: {
                this->score_ += (40 * 0 + this->drop_) * this->level_->number();
            }
        }
    }

    void Board::fixPiece() {
        for (auto &pos: this->currentPiecePositions_) {
            this->board_.at(pos.first).at(pos.second) = -1;
        }
        checkPossibleLines();
        calculateScore();
        this->currentPiece_ = this->nextPiece_;
        this->nextPiece_ = this->bag_->takePiece();
        this->placeNewPiece();
    }

    void Board::partiallyFillBoard() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 1);
        int maxFillHeight = this->board_.size()/4;
        for (int i = 0; i < maxFillHeight; i++) {
            for (int j = 0; j < this->board_.at(i).size(); j++) {
                int random_number = dis(gen);
                if(random_number == 1){
                    this->board_.at(i).at(j) = -1;
                }
            }
        }
    }

    void Board::placeNewPiece() {
        this->currentPiecePositions_.clear();
        this->oneMovementLines_ = 0;
        this->drop_ = 0;
        int boardSize = this->board_.size();
        std::vector<int> goodLines = nonZeroHorizontalPieceLines();
        int bottomLine = this->board_.size() - goodLines.size();

        int pieceCurrentLine = goodLines.at(0);
        int goodLinesIndex{0};

        for (int i = bottomLine; i < boardSize && pieceCurrentLine <= goodLines.at(goodLinesIndex); i++) {

            int xAxisPieceCenter = this->currentPiece_->center().second;

            for (int j = this->boardCenter_; j < this->width_ &&
                                             xAxisPieceCenter <
                                             this->currentPiece_->getCurrentRotation()->matrix().size(); j++) { //check right
                if (this->currentPiece_->getCurrentRotation()->matrix().at(pieceCurrentLine).at(xAxisPieceCenter) !=
                    0) {
                    if (this->board_.at(i).at(j) == -1) {//piece already there
                        this->isBoardFull_ = true;
                        return;
                    } else if (this->currentPiece_->getCurrentRotation()->matrix().at(pieceCurrentLine).at(
                            xAxisPieceCenter) == 2) {
                        this->board_.at(i).at(j) = 1;
                        this->currentPieceCenter_.first = i;
                        this->currentPieceCenter_.second = j;
                        currentPiecePositions_.emplace_back(i, j);
                    } else {
                        this->board_.at(i).at(j) = 1;
                        currentPiecePositions_.emplace_back(i, j);
                    }
                }

                xAxisPieceCenter++;
            }

            xAxisPieceCenter = this->currentPiece_->center().second - 1;

            for (int j = this->boardCenter_ - 1; j >= 0 &&
                                                 xAxisPieceCenter >= 0; j--) {//check left
                if (this->currentPiece_->getCurrentRotation()->matrix().at(pieceCurrentLine).at(xAxisPieceCenter) !=
                    0) {
                    if (this->board_.at(i).at(j) == -1) {//piece already there
                        this->isBoardFull_ = true;
                        return;
                    } else if (this->currentPiece_->getCurrentRotation()->matrix().at(pieceCurrentLine).at(
                            xAxisPieceCenter) == 2) {
                        this->board_.at(i).at(j) = 1;
                        this->currentPieceCenter_.first = i;
                        this->currentPieceCenter_.second = j;
                        currentPiecePositions_.emplace_back(i, j);
                    } else {
                        this->board_.at(i).at(j) = 1;
                        currentPiecePositions_.emplace_back(i, j);
                    }
                }
                xAxisPieceCenter--;
            }
            pieceCurrentLine++;
            goodLinesIndex++;
        }
    }

    std::vector<int> Board::nonZeroHorizontalPieceLines() {
        std::vector<int> res;
        for (int i = 0; i < this->currentPiece_->getCurrentRotation()->matrix().size(); i++) {
            if (!isLineEmpty(this->currentPiece_->getCurrentRotation()->matrix().at(i))) {
                res.push_back(i);
            }
        }
        return res;
    }

    bool Board::isLineEmpty(const std::vector<int> &line) {
        for (int x: line) {
            if (x != 0) {
                return false;
            }
        }
        return true;
    }

    void Board::rotatePiece(Tetris::Movement movement) {
        this->currentPiece_->rotate(movement);
    }

    bool Board::isBoardFull() const {
        return this->isBoardFull_;
    }

    const Piece *Board::nextPiece() const{
        return this->nextPiece_;
    }
}






