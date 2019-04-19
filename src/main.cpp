#include <iostream>
#include "Matrix.h"

int main() {
    Matrix m1(3, 4, 1);
    Matrix m2(3, 4, 22);
    Matrix m3(3, 4, 333);

    std::vector<double> a = {1, 1, 1, 1};

    m1.print();
    m2.print();
    m3.print();

    m2.setRow(1, a);

    m2.print();
}