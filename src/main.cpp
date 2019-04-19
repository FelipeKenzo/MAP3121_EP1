#include <iostream>
#include "Matrix.h"

int main() {
    Matrix m1(2, 3);
    Matrix m2(3, 4, 2);
    Matrix m3(4, 3, 3);

    m1.print();
    m2.print();
    m3.print();

    std::vector<double> row = {3, 4, 2, 1};
    m1.setRow(2, row);

    m1.print();

    Matrix* m4 = m1.transpose();

    m4->print();
}