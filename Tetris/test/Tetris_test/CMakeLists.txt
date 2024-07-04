cmake_minimum_required(VERSION 3.5)

project(Tetris_test LANGUAGES CXX)


enable_testing()
set(CMAKE_PREFIX_PATH "C:/Qt/6.6.1/mingw_64/lib/cmake/Qt6")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Tetris_test BoardTest.cpp
     ../../model/headers/Game.h ../../model/sources/Game.cpp ../../model/headers/Board.h ../../model/sources/Board.cpp
            ../../model/sources/Bag.cpp ../../model/headers/Bag.h ../../model/sources/Piece.cpp ../../model/headers/Piece.h ../../model/sources/Matrix.cpp
            ../../model/headers/Matrix.h ../../model/sources/Level.cpp ../../model/headers/Level.h
        ../../model/sources/TetrisFacade.cpp ../../model/headers/TetrisFacade.h ../../model/headers/TetrisInterface.h

            ../../DP/observable.h
            ../../DP/observer.h
            ../../DP/observable.cpp


)
add_test(NAME Tetris_test COMMAND Tetris_test)

target_link_libraries(Tetris_test PRIVATE Qt${QT_VERSION_MAJOR}::Test)

