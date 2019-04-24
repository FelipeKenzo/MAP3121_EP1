#include <iostream>
#include "Matrix.h"
#include "MatrixOp.h"

int main() {

    std::vector<double> a = {2, 1,  1, -1,  1};
    std::vector<double> b = {0, 3,  0,  1,  2};
    std::vector<double> c = {0, 0,  2,  2, -1};
    std::vector<double> d = {0, 0, -1,  1,  2};
    std::vector<double> e = {0, 0,  0,  3,  1};

    std::vector<std::vector<double>> m_values = {a, b, c, d, e};

    Matrix m1(m_values);
    m1.print();

    std::cout << "QR Factorization: ";

    try {
    qrFactorization(m1).print();
    } catch (std::range_error* e) {
        std::cout << "Error: " << e->what() << "\n";
    }
}