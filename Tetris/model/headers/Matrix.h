#ifndef INC_57998_58493_PROJETDEV4_MATRIX_H
#define INC_57998_58493_PROJETDEV4_MATRIX_H
#include <vector>

namespace Tetris {
    /**
     * Represents a \b Matrix in a 2D vector of int. A 0 means there is nothing in it, and a 1 means it is occupied.
     */
    class Matrix{
       std::vector<std::vector<int>> matrix_;
        int width_;
        int height_;

    public:
        /**
         * The constructor of the \b Matrix.
         * @param width the width of the \b Matrix.
         * @param height the height of the \b Matrix.
         */
        Matrix(int width, int height);

        /**
         * The getter of the matrix.
         * @return a std::vector<std::vector<int>> that represents the matrix.
         */
        const std::vector<std::vector<int>> &matrix() const;

        /**
         * This method allow to set a value on the matrix
         * @param row represent the row of the Matrix.
         * @param col represent the column of the Matrix.
         * @param value adds 1 to a square to indicate that it is occupied .
         */
        void setValue(int row, int col, int value = 1);
    };
}
#endif //INC_57998_58493_PROJETDEV4_MATRIX_H
