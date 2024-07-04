cmake_minimum_required(VERSION 3.5)

project(Tetris LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "C:/Qt/6.6.1/mingw_64/lib/cmake/Qt6")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -pedantic-errors")




set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# Inclusion des répertoires de Qt
include_directories(${Qt6Test_INCLUDE_DIRS})




add_executable(Tetris main.cpp model/headers/Game.h model/sources/Game.cpp model/headers/Board.h model/sources/Board.cpp
        model/sources/Bag.cpp model/headers/Bag.h model/sources/Piece.cpp model/headers/Piece.h model/sources/Matrix.cpp
        model/headers/Matrix.h model/sources/Level.cpp model/headers/Level.h
    model/sources/TetrisFacade.cpp model/headers/TetrisFacade.h model/headers/TetrisInterface.h
        controller/Controller.cpp
        controller/Controller.h
        view/ConsoleView.cpp
        view/ConsoleView.h
        view/keyboard.hpp
        view/stringConvert.hpp
        DP/observable.h
        DP/observer.h
        DP/observable.cpp
        model/headers/GameType.h

)



install(TARGETS Tetris
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
