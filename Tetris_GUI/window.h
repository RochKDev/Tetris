#ifndef MACLASSE_H
#define MACLASSE_H

#include <QMainWindow>
#include "model/headers/TetrisFacade.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "DP/observer.h"
#include "model/headers/Level.h"
#include <QLayout>
#include <QTimer>
#include <vector>


QT_BEGIN_NAMESPACE
namespace Ui { class MaClasse; }
QT_END_NAMESPACE

class MaClasse : public QMainWindow, public he2b::esi::dev4::Observer {
    Q_OBJECT

public:
    /**
    * Constructor for the MaClasse class.
    * @param parent The parent QWidget object.
    */
    MaClasse(QWidget *parent = nullptr);

    /**
    * Destructor for the MaClasse class.
    */
    ~MaClasse();

    /**
    * Starts the game by initializing the game parameters and switching to the game view.
    */
    void start();

    /**
    * Updates the game view based on the current state of the game.
    * @param observable The observable Board object.
    * @param score The current score.
    * @param level The current level.
    * @param lines The current number of lines.
    */
    void update(const Tetris::Board *observable, int score, Tetris::Level level, int lines) override;


private
    slots:
    /**
    * Slot for handling the click event of the start button.
    */
    void on_pushButton_clicked();

    /**
    * Slot for handling the change event of the game type combo box.
    * @param gameType The selected game type.
    */
    void onGameTypeChanged(const QString &gameType);

    /**
    * Slot for handling the click event of the reset button.
    */
    void on_pushButton_2_clicked();


    /**
    * Handles the key press events for controlling the game.
    * @param event The QKeyEvent object.
    */
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MaClasse *ui;
    Tetris::TetrisFacade *game;
    QTimer *timer;
    QTimer *timerSurvive;
    std::vector<std::string> gameTypes{"standard", "lines", "score", "survive"};

    int cpt;
    int cptSurvive;
    int maxLines;
    int maxScore;
    int survivalTime;
    Tetris::Level lvl;
    std::string gameType;

    /**
     * the method to be executed when the main timer is triggered.
     */
    void action_timer();

    /**
     * the method to be executed when the survive timer is triggered.
     */
    void action_timerSurvive();

    /**
    * Starts the game based on the selected game type.
    * @param gameType The selected game type.
    */
    void startGame(std::string gameType);

    /**
    * Starts the standard game mode.
    */
    void startStandardGame();

    /**
    * Starts the lines game mode.
     */
    void startLinesGame();

    /**
    * Starts the score game mode.
    */
    void startScoreGame();

    /**
    * Starts the survive game mode.
    */
    void startSurviveGame();

    /**
    * Checks if the game is over based on the game mode and game state.
    */
    void checkIfGameOver();

    /**
    * Displays the end message based on the game mode and game state.
    */
    void displayEndMessage();

    /**
    * Resets the main page to the initial state.
    */
    void resetMainPage();

    /**
    * Checks if the game can start based on the board size.
    * @return True if the game can start, false otherwise.
    */
    bool canStart();

    /**
    * Displays the next piece in the game.
    */
    void displayNextPiece();
};
#endif // MACLASSE_H
