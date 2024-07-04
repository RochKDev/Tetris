#include <QtTest>
#include "../../model/headers/Board.h"
#include "../../model/headers/Level.h"
class BoardTest : public QObject, protected Tetris::Board
{
    Q_OBJECT

public:
    BoardTest()
        :Tetris::Board(10,10, Tetris::Level{1})
    {

    }

private slots:

void init(){
    this->score_ = 0;
    level_ = std::make_unique<Tetris::Level>(Tetris::Level{1});
    bag_ = std::make_unique<Tetris::Bag>(Tetris::Bag());
    currentPieceCenter_ = std::make_pair(0, 0);
    currentPiecePositions_.clear();
    oneMovementLines_ = 0;
    drop_ = 0;
    isBoardFull_ = false;
}

        void testCheckLine();
        void testCheckLineNotFull();
        void testDeleteLine();
        void testIncreaseLevel();
        void test0PossibleLines();
        void test1PossibleLines();
        void test2PossibleLines();
        void test3PossibleLines();
        void testCalculateScore900Points();
        void testCalculateScore16Points();
        void testCalculateScore14418Points();
        void testCalculateScore0Points();
        void testFixPiece();



};


void BoardTest::testCheckLine(){
    this->board_.at(0) = std::vector<int>(10,-1);
    QVERIFY(this->checkLine(0));
}

void BoardTest::testCheckLineNotFull(){
    this->board_.at(0) = std::vector<int>(10,-1);
    this->board_.at(0).at(0) = 0;
    QVERIFY(!this->checkLine(0));
}

void BoardTest::testDeleteLine(){
    deleteLine(0);
    QCOMPARE(this->board_.size(), 10);
    QVERIFY(!checkLine(9));
}

void BoardTest::testIncreaseLevel(){
    increaseLevel();

    QCOMPARE(this->level_.get()->number(), Tetris::Level{2}.number());
}

void BoardTest::test0PossibleLines(){
    checkPossibleLines();
    QCOMPARE(this->oneMovementLines_, 0);
}

void BoardTest::test1PossibleLines(){
    this->board_.at(0) = std::vector<int>(10,-1);
    checkPossibleLines();
    QCOMPARE(this->oneMovementLines_, 1);
}

void BoardTest::test2PossibleLines(){
    this->board_.at(0) = std::vector<int>(10,-1);
    this->board_.at(1) = std::vector<int>(10,-1);
    checkPossibleLines();
    QCOMPARE(this->oneMovementLines_, 2);
}

void BoardTest::test3PossibleLines(){
    this->board_.at(0) = std::vector<int>(10,-1);
    this->board_.at(1) = std::vector<int>(10,-1);
    this->board_.at(2) = std::vector<int>(10,-1);
    checkPossibleLines();
    QCOMPARE(this->oneMovementLines_, 3);
}

void BoardTest::testCalculateScore900Points(){
    this->oneMovementLines_ = 3;
    this->drop_ = 0;
    this->calculateScore();
    QCOMPARE(this->score_, 900);

}

void BoardTest::testCalculateScore16Points(){
    this->oneMovementLines_ = 0;
    this->drop_ = 8;
    this->level_ = std::make_unique<Tetris::Level>(Tetris::Level{2});
    this->calculateScore();
    QCOMPARE(this->score_, 16);

}

void BoardTest::testCalculateScore14418Points(){
    this->oneMovementLines_ = 4;
    this->drop_ = 6;
    this->level_ = std::make_unique<Tetris::Level>(Tetris::Level{3});
    this->calculateScore();
    QCOMPARE(this->score_, 14418);

}

void BoardTest::testCalculateScore0Points(){
    this->oneMovementLines_ = 0;
    this->drop_ = 0;
    this->level_ = std::make_unique<Tetris::Level>(Tetris::Level{1});
    this->calculateScore();
    QCOMPARE(this->score_, 0);

}

void BoardTest::testFixPiece(){
    std::vector<std::pair<int, int>> expected;
    this->currentPiecePositions_.emplace_back(std::make_pair(0,1));
    this->currentPiecePositions_.emplace_back(std::make_pair(0,2));
    this->currentPiecePositions_.emplace_back(std::make_pair(0,3));
    this->currentPiecePositions_.emplace_back(std::make_pair(1,2));
    expected = this->currentPiecePositions_;
    fixPiece();

    std::vector<std::pair<int,int>> res;
    for (int i{0}; i < this->board_.size(); i++) {
        for (int j {0}; j < this->board_.at(i).size(); j++) {
            if (this->board_.at(i).at(j) == -1){
                 res.emplace_back(std::make_pair(i, j));
            }
        }

    }
    QCOMPARE(expected, res);
}










QTEST_APPLESS_MAIN(BoardTest)

#include "BoardTest.moc"
