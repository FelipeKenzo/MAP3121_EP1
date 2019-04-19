#include <iostream>
#include "Matrix.h"

int main() {
    Matrix m1(3, 4, 1);
    Matrix m2(4, 3, 22);
    Matrix m3(3, 4, 333);

    std::vector<double> a = {1, 1, 1, 1};

    m1 = m1 * 3 * m2;
    m1.print();

}