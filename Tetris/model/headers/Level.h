#ifndef INC_57998_58493_PROJETDEV4_LEVEL_H
#define INC_57998_58493_PROJETDEV4_LEVEL_H
namespace Tetris{
/**
 * The class that represents a \b Level.
 */
class Level {

    int number_;
    double rate_;

public:

    /**
     * The default constructor of \b Level.
     */
    Level(int number) ;
    /**
     * The getter of the rate of the level.
     * @return the rate of the \b Level.
     */
    double rate();

    /**
    The getter of the number of the level.
     * @return the number of the \b Level.
     */
    int number();
};
}
#endif //INC_57998_58493_PROJETDEV4_LEVEL_H
