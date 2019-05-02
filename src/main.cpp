#include <iostream>
#include <cmath>
#include "Matrix.h"
#include "MatrixOp.h"


int main() {

/*
    std::vector<double> a = {2, 1,  1, -1,  1};
    std::vector<double> b = {0, 3,  0,  1,  2};
    std::vector<double> c = {0, 0,  2,  2, -1};
    std::vector<double> d = {0, 0, -1,  1,  2};
    std::vector<double> e = {0, 0,  0,  3,  1};

    std::vector<std::vector<double>> m_values = {a, b, c, d, e};

    Matrix m1(m_values);

    std::cout << "QR Factorization test: ";

    try {
    qrFactorization(m1);
    } catch (std::range_error* e) {
        std::cout << "Error: " << e->what() << "\n";
    }
*/

std::cout << "=====Primeira Tarefa=====\n";
std::cout << "a)\n";

Matrix w1(4, 5);
Matrix b1(4, 1);

for (unsigned i = 0; i < w1.getNumberOfLines(); i++) {
    b1.setValue(i, 0, 1);
    for (unsigned j = 0; j < w1.getNumberOfColumns(); j++) {
        double val = 0;
        if (i == j) 
            val = 2;
        else if (abs(i - j) == 1)
            val = 1;
        
        w1.setValue(i, j, val);
    }
}

std::cout << "W:";
w1.print();
std::cout << "b:";
b1.print();

Matrix x1 = solveLinearSystems(w1, b1);
std::cout << "x:";
x1.print();

std::cout << "W * x:";
(w1 * x1).print();

std::cout << "b)\n";

Matrix w2(20, 17);
Matrix b2(20, 1);

for (unsigned i = 1; i <= 20; i++) {
    b2.setValue(i-1, 0, i);
    for (unsigned j = 1; j <= 17; j++) {
        double val = 0;
        if (abs(i-j) <= 4)
            val = 1/double(i+j-1);
        w2.setValue(i-1, j-1, val);
    }
}

std::cout << "W:";
w2.print();
std::cout << "b:";
b2.print();

Matrix x2 = solveLinearSystems(w2, b2);

std::cout << "x:";
x2.print();

}