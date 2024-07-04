    #include "../headers/Matrix.h"


    namespace Tetris{

        const std::vector<std::vector<int>> & Matrix::matrix() const {
            return this->matrix_;
        }

        Matrix::Matrix(int width, int height)
        :width_(width), height_(height){
            this->matrix_ = std::vector<std::vector<int>> (width, std::vector<int> (height, 0));
        }

        void Matrix::setValue(int row, int col, int value) {
            if (row >= 0 && row < matrix_.size() && col >= 0 && col < matrix_[0].size()) {
                matrix_[row][col] = value;
            } else {
//TODO gerer
            }
        }


}



