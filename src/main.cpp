#include <iostream>
#include "Matrix.h"

int main() {

    std::vector<double> a = {2  , 1, 66, 1};
    std::vector<double> b = {323, 5, 4, 2};
    std::vector<double> c = {6  , 3, 2, 2};
    std::vector<double> d = {5  , 5, 1, 999};

    std::vector<std::vector<double>> m_values = {a, b, c, d};

    Matrix m1(m_values);
    m1.print();

}