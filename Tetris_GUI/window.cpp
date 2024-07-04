#include "window.h"
#include "./ui_window.h"
#include "model/headers/Level.h"
#include <QGridLayout>
#include <iostream>
#include <QtUiTools/QUiLoader>
#include <QFile>
#include "model/headers/Piece.h"
#include "view/headers/ColoredSquare.h"
#include <QKeyEvent>
#include <QMessageBox>
#include "model/headers/Movement.h"


MaClasse::MaClasse(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MaClasse), timer(new QTimer), timerSurvive(new QTimer), lvl(Tetris::Level(1)) {
    ui->setupUi(this);
    ui->levelSpinBox->setMinimum(1);
    ui->levelSpinBox->setMaximum(20);
    for (const auto &gameType: gameTypes) {
        ui->gameTypeComboBox->addItem(QString::fromStdString(gameType));
    }
    connect(ui->gameTypeComboBox, &QComboBox::currentTextChanged, this, &MaClasse::onGameTypeChanged);
    connect(timer, &QTimer::timeout, this, &MaClasse::action_timer);
    connect(timerSurvive, &QTimer::timeout, this, &MaClasse::action_timerSurvive);
    this->game = new Tetris::TetrisFacade();
    this->ui->stackedWidget->setCurrentIndex(0);
}

MaClasse::~MaClasse() {
    delete ui;
    delete game;
    delete timer;
    delete timerSurvive;
}

void MaClasse::start() {
    if(canStart()){
        int level = ui->levelSpinBox->value();
        int width = ui->widthSpinBox->value();
        int height = ui->heightSpinBox->value();
        bool partially_fill_board = ui->isPartially->isChecked();
        std::string gameType = ui->gameTypeComboBox->currentText().toStdString();

        this->gameType = gameType;
        lvl = Tetris::Level(level);
        this->game->start(lvl, width, height, partially_fill_board);

        this->game->registerObserver(this);
        startGame(gameType);
        ui->stackedWidget->setCurrentIndex(1);
    }else{
        QMessageBox::warning(this, "Cannot start game", "The board must be at least 10x5.");
    }
}


void MaClasse::action_timer() {
    cpt++;
    ui->lcdNumber->display(cpt);
    displayNextPiece();
    this->game->move(Tetris::Movement::DOWN);
    this->checkIfGameOver();
}

void MaClasse::on_pushButton_clicked() {
    start();
}

void MaClasse::update(const Tetris::Board *observable, int score, Tetris::Level level, int lines) {
    QGridLayout *layout = qobject_cast<QGridLayout *>(this->ui->TetrisGrid);
    if (!layout) return;
    while (QLayoutItem * item = layout->takeAt(0)) {
        if (QWidget * widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
    int boardSize = observable->board().size();
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < observable->board().at(i).size(); ++j) {
            QColor color;
            switch (observable->board().at(i).at(j)) {
                case -1:
                    color = Qt::green;
                    break;
                case 0:
                    color = Qt::white;
                    break;
                case 1:
                    color = Qt::red;
                    break;
                default:
                    color = Qt::black;
            }
            Tetris::ColoredSquare *square = new Tetris::ColoredSquare(this, color);
            layout->addWidget(square, boardSize - i, j);
        }
    }
    this->ui->LevelLabel->setText(QString::number(level.number()));
    if (this->lvl.number() < level.number()) {
        this->lvl = level;
        int rateInMilliseconds = static_cast<int>(lvl.rate() * 1000);
        timer->start(rateInMilliseconds);
    }

    this->ui->LinesLabel->setText(QString::number(lines));
    this->ui->ScoreLabel->setText(QString::number(score));
}

void MaClasse::on_pushButton_2_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
    this->resetMainPage();
}

void MaClasse::keyPressEvent(QKeyEvent *event) {
    if(ui->stackedWidget->currentIndex() != 1){
        return;
    }
    switch (event->key()) {
        case Qt::Key_Down:
            game->move(Tetris::Movement::DOWN);
            break;
        case Qt::Key_Left:
            game->move(Tetris::Movement::LEFT);
            break;
        case Qt::Key_Right:
            game->move(Tetris::Movement::RIGHT);
            break;
        case Qt::Key_Space:
            game->move(Tetris::Movement::DROP);
            break;
        case Qt::Key_Q:
            game->move(Tetris::Movement::LEFT);
            break;
        case Qt::Key_D:
            game->move(Tetris::Movement::RIGHT);
            break;
        case Qt::Key_S:
            game->move(Tetris::Movement::DOWN);
            break;
        case Qt::Key_A:
            game->move(Tetris::Movement::COUNTER_CLOCKWISE);
            break;
        case Qt::Key_E:
            game->move(Tetris::Movement::CLOCKWISE);
            break;
        default:
            break;
    }
    this->checkIfGameOver();
}

void MaClasse::startGame(std::string gameType) {

    if (gameType == "standard") {
        startStandardGame();
    } else if (gameType == "lines") {
        startLinesGame();
    } else if (gameType == "score") {
        startScoreGame();
    } else if (gameType == "survive") {
        startSurviveGame();
    }
}

void MaClasse::startStandardGame() {
    this->gameType = "standard";
    cpt = 0;
    this->ui->lcdNumber->display(cpt);
    int rateInMilliseconds = static_cast<int>(lvl.rate() * 1000);
    timer->start(rateInMilliseconds);
}

void MaClasse::startLinesGame() {
    cpt = 0;
    this->ui->lcdNumber->display(cpt);
    int rateInMilliseconds = static_cast<int>(lvl.rate() * 1000);
    timer->start(rateInMilliseconds);

    QLayoutItem* item = ui->additionalInfos->itemAt(1);
    if (item) {
        QSpinBox* spinBox = qobject_cast<QSpinBox*>(item->widget());
        if (spinBox) {
            int spinBoxValue = spinBox->value();
            this->maxLines = spinBoxValue;
        }
    }
}

void MaClasse::startScoreGame() {
    cpt = 0;
    this->ui->lcdNumber->display(cpt);
    int rateInMilliseconds = static_cast<int>(lvl.rate() * 1000);
    timer->start(rateInMilliseconds);

    QLayoutItem* item = ui->additionalInfos->itemAt(1);
    if (item) {
        QSpinBox* spinBox = qobject_cast<QSpinBox*>(item->widget());
        if (spinBox) {
            int spinBoxValue = spinBox->value();
            this->maxScore = spinBoxValue;
        }
    }
}

void MaClasse::startSurviveGame() {
    cpt = 0;
    this->ui->lcdNumber->display(cpt);
    int rateInMilliseconds = static_cast<int>(lvl.rate() * 1000);
    timer->start(rateInMilliseconds);
    cptSurvive = 0;
    QLayoutItem* item = ui->additionalInfos->itemAt(1);
    if (item) {
        QSpinBox* spinBox = qobject_cast<QSpinBox*>(item->widget());
        if (spinBox) {
            int spinBoxValue = spinBox->value();
            this->survivalTime = spinBoxValue;
        }
    }
    timerSurvive->start(1000);
}

void MaClasse::checkIfGameOver() {
    if (this->gameType == "standard") {
        if (this->game->checkIfGameOver()) {
            timer->stop();
            this->displayEndMessage();
            this->ui->stackedWidget->setCurrentIndex(2);
        }
    } else if (this->gameType == "lines") {
        if (this->game->checkIfGameOver() || this->game->checkIfLinesGameOver(this->maxLines)) {
            timer->stop();
            this->displayEndMessage();
            this->ui->stackedWidget->setCurrentIndex(2);
        }
    } else if (this->gameType == "score") {
        if (this->game->checkIfGameOver() || this->game->checkIfScoreGameOver(this->maxScore)) {
            timer->stop();
            this->displayEndMessage();
            this->ui->stackedWidget->setCurrentIndex(2);
        }
    } else if (this->gameType == "survive") {
        if (this->game->checkIfGameOver()) {
            timer->stop();
            timerSurvive->stop();
            this->displayEndMessage();
            this->ui->stackedWidget->setCurrentIndex(2);
        }
    }
}

void MaClasse::displayEndMessage() {
    if (this->gameType == "standard") {
        this->ui->endMessageLabel->setText("Game Over");
    } else if (this->gameType == "lines") {
        if(this->game->checkIfGameOver()) {
            this->ui->endMessageLabel->setText("Game Over");
        } else {
            this->ui->endMessageLabel->setText("Congratulations you reached " + QString::number(this->maxLines) + " lines");
        }
    } else if (this->gameType == "score") {
        if(this->game->checkIfGameOver()) {
            this->ui->endMessageLabel->setText("Game Over");
        } else {
            this->ui->endMessageLabel->setText("Congratulations you reached " + QString::number(this->maxScore) + " points");
        }
    } else if (this->gameType == "survive") {
        if(this->game->checkIfGameOver()) {
            this->ui->endMessageLabel->setText("Game Over");
        } else {
            this->ui->endMessageLabel->setText("Congratulations you survived " + QString::number(cptSurvive) + " seconds");
        }
    }
}

void MaClasse::onGameTypeChanged(const QString &gameType) {
    QLayoutItem* item;
    while ((item = ui->additionalInfos->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    if (gameType.toStdString() == "score") {
            QSpinBox *spinBox = new QSpinBox(this);
            spinBox->setMinimum(1);
            spinBox->setMaximum(99999);
            QLabel *label = new QLabel("Score", this);
            ui->additionalInfos->addWidget(label);
            ui->additionalInfos->addWidget(spinBox);
        } else
    if (gameType.toStdString() == "lines") {
        QSpinBox *spinBox = new QSpinBox(this);
        spinBox->setMinimum(1);
        spinBox->setMaximum(99999);
        QLabel *label = new QLabel("Lines", this);
        ui->additionalInfos->addWidget(label);
        ui->additionalInfos->addWidget(spinBox);
    } else  if(gameType.toStdString() == "survive"){
        QSpinBox *spinBox = new QSpinBox(this);
        spinBox->setMinimum(1);
        spinBox->setMaximum(99999);
        QLabel *label = new QLabel("Time", this);
        ui->additionalInfos->addWidget(label);
        ui->additionalInfos->addWidget(spinBox);
    }
}

void MaClasse::resetMainPage() {
    ui->levelSpinBox->setValue(1);
    ui->widthSpinBox->setValue(0);
    ui->heightSpinBox->setValue(0);
    ui->isPartially->setChecked(false);
    ui->gameTypeComboBox->setCurrentIndex(0);
    QLayoutItem* item;
    while ((item = ui->additionalInfos->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}

bool MaClasse::canStart() {
    return ui->widthSpinBox->value() >= 5 && ui->heightSpinBox->value() >= 10;
}

void MaClasse::action_timerSurvive() {
    cptSurvive++;
    if (cptSurvive >= this->survivalTime) {
        timerSurvive->stop();
        timer->stop();
        this->displayEndMessage();
        this->cptSurvive = 0;
        this->ui->stackedWidget->setCurrentIndex(2);
    }
}

void MaClasse::displayNextPiece() {
    const Tetris::Piece *piece = this->game->getNextPiece();
    QGridLayout *layout = qobject_cast<QGridLayout *>(this->ui->nextPieceGrid);
    if (!layout) return;
    while (QLayoutItem * item = layout->takeAt(0)) {
        if (QWidget * widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
    for (int i = 0; i < piece->getCurrentRotation()->matrix().size(); ++i) {
        for (int j = 0; j < piece->getCurrentRotation()->matrix().at(i).size(); ++j) {
            QColor color;
            switch (piece->getCurrentRotation()->matrix().at(i).at(j)) {
                case 0:
                    color = Qt::white;
                    break;
                case 1:
                    color = Qt::red;
                    break;
                default:
                    color = Qt::red;
            }
            Tetris::ColoredSquare *square = new Tetris::ColoredSquare(this, color);
            layout->addWidget(square, piece->getCurrentRotation()->matrix().size() - i, j);
        }
    }
}
