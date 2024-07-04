#include "../headers/Level.h"


namespace Tetris{

    Level::Level(int number ) : number_(number) {
        switch (number) {
            case 1 : {
                this->rate_ = 60./60;
                break;
            }
            case 2 : {
                this->rate_ = 53./60;
                break;
            }
            case 3 : {
                this->rate_ = 49./60;
                break;
            }
            case 4 : {
                this->rate_ = 45./60;
                break;
            }
            case 5 : {
                this->rate_ = 41./60;
                break;
            }
            case 6 : {
                this->rate_ = 37./60;
                break;
            }
            case 7 : {
                this->rate_ = 33./60;
                break;
            }
            case 8 : {
                this->rate_ = 28./60;
                break;
            }
            case 9 : {
                this->rate_ = 23./60;
                break;
            }
            case 10 : {
                this->rate_ = 18./60;
                break;
            }
            case 11 : {
                this->rate_ = 13./60;
                break;
            }
            case 12 : {
                this->rate_ = 9./60;
                break;
            }
            case 13 : {
                this->rate_ = 8./60;
                break;
            }
            case 14 : {
                this->rate_ = 8./60;
                break;
            }
            case 15 : {
                this->rate_ = 7./60;
                break;
            }
            case 16 : {
                this->rate_ = 6./60;
                break;
            }
            case 17 : {
                this->rate_ = 5./60;
                break;
            }
            case 18 : {
                this->rate_ = 4./60;
                break;
            }
            case 19 : {
                this->rate_ = 3./60;
                break;
            }
            case 20 : {
                this->rate_ = 2./60;
                break;
            }
            default: {
                this->rate_ = 2./60;
                break;
            }


        }

    }

    double Level::rate() {
        return this->rate_;
    }

    int Level::number() {

        return this->number_;
    }

}


