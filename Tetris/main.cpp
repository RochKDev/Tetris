#include "controller/Controller.h"
#include "view/ConsoleView.h"

using namespace std;

int main()
{
    Tetris::TetrisFacade facade = Tetris::TetrisFacade();
    Tetris::TetrisInterface &interface = facade;
    Tetris::ConsoleView view = Tetris::ConsoleView();
    Tetris::Controller controller = Tetris::Controller(interface, view);
    controller.start();

    return 0;
}
