
#include <iostream>
#include "MatrixObject.hpp"

int main() {
    std::vector<unsigned> sizes = {2, 2};
    Object mat(sizes);
    for (int i = 0 ; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            mat[i][j] = Object("1");
//
    Object mat2(sizes);
    for (int i = 0 ; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            mat2[i][j] = Object("2");

    std::cout << (mat + mat2)  <<  std::endl;
    return 0;
}
