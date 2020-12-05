
#include <iostream>
#include "MatrixObject.hpp"

int main() {
    std::vector<unsigned> sizes = {3, 3, 8};
    auto mat = create_matrix<double>(sizes.size(), sizes);
    double val = 0;
    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat[i].size(); ++j) {
            for (int k = 0; k < mat[i][j].size(); ++k) {
                mat[i][j][k] = Object<double>(val);
                val += 1;
            }
        }
    }
    std::cout << mat << std::endl;
    return 0;
}
