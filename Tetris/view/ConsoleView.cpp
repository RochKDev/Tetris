#include "ConsoleView.h"
#include <iostream>
#include "keyboard.hpp"
#include <algorithm>

namespace Tetris{
    using namespace std;
    void ConsoleView::displayBoard(const Board *board){
        const auto& boardData = board->board();

        for (int i = boardData.size() - 1; i >= 0; i--) {
            for (const int & col : boardData.at(i)) {
                if (col == -1){
                    cout<< "|" << "1";
                }else{
                    cout<< "|" << col;
                }
            }
            cout << "|"<< endl;
        }
    }

    void ConsoleView::displayWelcomeMessage() {
        cout << "Welcome in our Tetris game!" << endl;
        cout << "To play this game you will have basic commands at your disposition." << endl;
        cout << "Such as : " << endl;
        cout << "   - Left " << endl;
        cout << "   - Right " << endl;
        cout << "   - Down " << endl;
        cout << "   - Drop " << endl;
        cout << "   - Clock " << endl;
        cout << "   - CounterClock " << endl;
    }

    string ConsoleView::askUserForMovement() {
        string move;
        move = checkIfStringOK("Please enter your movement : ");
        std::transform(move.begin(), move.end(), move.begin(), ::tolower);
        while(find(this->validMoves.cbegin(), this->validMoves.cend(), move) == this->validMoves.cend()){// string not in vector
            cout << "Please enter a valid move : " << endl ;
            move = checkIfStringOK("Please enter your movement : ");
        }
        return move;
    }

    string ConsoleView::checkIfStringOK(const std::string& message) {
        string res;
        bool good{false};
        while(!good){
            try {
                cout << message << endl;
                res = he2b::esi::dev4::lineFromKbd<string>();
                good = true;
            } catch (const std::exception &e) {
                displayMessage("Please enter a valid move!");
            }
        }
        return res;
    }

    string ConsoleView::askUserForString(const string& message) {
        cout << message << endl;
        return he2b::esi::dev4::lineFromKbd<string>();
    }

    void ConsoleView::displayMessage(const string& message) {
        cout << message << endl;
    }

    void ConsoleView::update(const Board * observable, int score, int level, int lines) {
        cout << "Score : " << score << ", Level : " << level << ", Lines : " << lines << endl;
            this->displayBoard(observable);
    }



    ConsoleView::~ConsoleView() = default;

}