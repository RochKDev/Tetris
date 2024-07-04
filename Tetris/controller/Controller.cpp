#include "Controller.h"
#include <thread>
#include <mutex>

namespace Tetris {

    Controller::Controller(TetrisInterface &game, ConsoleView &view)
            : game_(game), view_(view), endGame(false)  {
        this->game_ = std::move(game);
    }

    void Controller::start() {
        view_.displayWelcomeMessage();
        while (!this->endGame) {
            this->gameType = askGameType();
            int width = checkWidth();
            int height =  checkHeight();
            int level = checkLevel();
            bool fillBoard = checkFillBoard();
            startGame(level, width, height, fillBoard);
            this->endGame = !wouldContinue();
        }
        view_.displayMessage("Thank you for playing!");
    }

    Movement Controller::getMovementFromUser(const std::string& move) {
        if (move == "left"){
            return Movement::LEFT;
        }else if (move == "right"){
            return Movement::RIGHT;
        }else if (move == "down"){
            return Movement::DOWN;
        }else if (move == "drop"){
            return Movement::DROP;
        }else if (move == "clock"){
            return Movement::CLOCKWISE;
        }else if (move == "counterclock"){
            return Movement::COUNTER_CLOCKWISE;
        }
    }

    int Controller::checkWidth() {
        int width;
        width = checkIfStringInt("What should be the width of your board?");
        while(width < 5){
            view_.displayMessage("The gaming board cannot be smaller than 5 in its width! ");
            width = checkIfStringInt("What should be the width of your board?");
        }
        return width;
    }

    int Controller::checkHeight() {
        int height;
        height = checkIfStringInt("What should be the height of your board?");
        while( height < 10 ){
            view_.displayMessage("The gaming board cannot be smaller than 10 in its height! ");
            height =  checkIfStringInt("What should be the height of your board?");
        }
        return height;
    }

    int Controller::checkLevel() {
        int level;
        level = checkIfStringInt("At which level would you like to start the game?");
        while( level > this->maxLevel || level < 1){
            view_.displayMessage("Incorrect level please enter a valid level.");
            view_.displayMessage("Max level allowed is : " + std::to_string(this->maxLevel));
            level =  checkIfStringInt("At which level would you like to start the game?");
        }
        return level;
    }

    bool Controller::checkFillBoard() {
        std::string fillBoardString = view_.askUserForString("Would you like to partially fill the board? Answer y for yes, n for no : ");
        while (fillBoardString != "n" && fillBoardString != "y"){
            view_.displayMessage("Incorrect answer please enter a valid answer");
            fillBoardString = view_.askUserForString("Would you like to partially fill the board? Answer y for yes, n for no : ");
        }
        return fillBoardString == "y";
    }

    bool Controller::wouldContinue() {
        std::string continueString = view_.askUserForString("Would you like to continue playing? Answer y for yes, n for no : ");
        while (continueString != "n" && continueString != "y"){
            view_.displayMessage("Incorrect answer please enter a valid answer");
            continueString = view_.askUserForString("Would you like to partially fill the board? Answer y for yes, n for no : ");
        }
        return continueString == "y";
    }

    int Controller::checkIfStringInt(const std::string& message) {
        int res;
        bool good{false};
        while(!good){
            try {
                res = std::stoi(view_.askUserForString(message));
                good = true;
            } catch (const std::exception &e) {
                view_.displayMessage("Please enter a valid number!");
            }
        }
        return res;
    }

    GameType Controller::askGameType() {
        GameType result;
        view_.displayMessage("What type of game would you like to play ? ");
        view_.displayMessage("You can choose from : ");
        view_.displayMessage("- Standard");
        view_.displayMessage("- Score (the game will end after you reach a certain score)");
        view_.displayMessage("- Lines (the game will end after you reach a certain number of accomplished lines");
        view_.displayMessage("- Survive (the game will end after a given amount of time");
        std::string type = checkIfStringOK("Enter the type : ");
        std::transform(type.begin(), type.end(), type.begin(), ::tolower);
        while(find(this->types.cbegin(), this->types.cend(), type) == this->types.cend()){
            view_.displayMessage("Please enter a valid type!");
            type = checkIfStringOK("Enter the type : ");
            std::transform(type.begin(), type.end(), type.begin(), ::tolower);
        }
        result = convertStringToGameType(type);
        return result;
    }

    std::string Controller::checkIfStringOK(const std::string& message) {
        std::string res;
        bool good{false};
        while(!good){
            try {
                res = view_.askUserForString(message);
                good = true;
            } catch (const std::exception &e) {
                view_.displayMessage("Please enter a valid type");
            }
        }
        return res;
    }

    GameType Controller::convertStringToGameType(const std::string &gameType) {
        if(gameType == "standard"){
            return GameType::STANDARD;
        }else if(gameType == "score"){
            return GameType::SCORE;
        }else if(gameType == "lines"){
            return GameType::LINES;
        }else if (gameType == "survive"){
            return GameType::SURVIVE;
        }else{
            return GameType::STANDARD;
        }
    }

    void Controller::startGame(int level, int width, int height, bool fillBoard) {
        switch (this->gameType) {
            case GameType::STANDARD : {
                startStandard(level, width, height, fillBoard);
                break;
            }
            case GameType::SCORE: {
                startScore(level, width, height, fillBoard);
                break;
            }
            case GameType::LINES : {
                startLines(level, width, height, fillBoard);
                break;
            }
            case GameType::SURVIVE : {
                startSurvive(level, width, height, fillBoard);
                break;
            }
        }
    }

    void Controller::startStandard(int level, int width, int height, bool fillBoard) {
        this->game_.start(level, width, height, fillBoard);
        game_.registerObserver(&view_);
        while (!this->game_.checkIfGameOver()) {
            this->game_.move(getMovementFromUser(view_.askUserForMovement()));
        }
    }

    void Controller::startScore(int level, int width, int height, bool fillBoard) {
        this->maxScore = checkIfStringInt("What will be your max score? : ");
        this->game_.start(level, width, height, fillBoard);
        game_.registerObserver(&view_);
        while (!this->game_.checkIfScoreGameOver(this->maxScore) && !this->game_.checkIfGameOver()) {
            this->game_.move(getMovementFromUser(view_.askUserForMovement()));
        }
        if (this->game_.checkIfScoreGameOver(this->maxScore)){
            view_.displayMessage("You Won!");
        }
    }

    void Controller::startLines(int level, int width, int height, bool fillBoard) {
        this->maxLines = checkIfStringInt("What will be your max of completed lines? : ");
        this->game_.start(level, width, height, fillBoard);
        game_.registerObserver(&view_);
        while (!this->game_.checkIfLinesGameOver(this->maxLines) && !this->game_.checkIfGameOver()) {
            this->game_.move(getMovementFromUser(view_.askUserForMovement()));
        }
        if (this->game_.checkIfLinesGameOver(this->maxLines)){
            view_.displayMessage("You Won!");
        }
    }

    void Controller::startSurvive(int level, int width, int height, bool fillBoard) {
        const int durationSec = checkIfStringInt("How mush time do you wish to survive? (in seconds) :");
        this->game_.start(level, width, height, fillBoard);
        game_.registerObserver(&view_);
        auto start = std::chrono::steady_clock::now();
        while(!this->game_.checkIfGameOver()){
            auto end = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
            this->game_.move(getMovementFromUser(view_.askUserForMovement()));
            if (duration.count() >= durationSec) {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

