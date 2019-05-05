#include <iostream>
#include <cmath>
#include "Matrix.h"
#include "MatrixOp.h"


int main() {

/*
    std::vector<double> a = {2, 1,  1, -1};
    std::vector<double> b = {2, 3,  0,  1};
    std::vector<double> c = {0, 0,  2,  2};
    std::vector<double> d = {4, 0, -1,  1};
    std::vector<double> e = {0, 0,  0,  3};

    std::vector<std::vector<double>> m_values = {a, b, c, d, e};

    Matrix m1(m_values);
    double cos = 2 / sqrt(5);
    double sin = 1 / sqrt(5);

    std::cout << "QR Factorization test: ";

    try {
    qrFactorization(m1);

    } catch (std::range_error* e) {
        std::cout << "Error: " << e->what() << "\n";
    }
//*/

//*
std::cout << "==========[Primeira Tarefa]==========\n";
std::cout << "a)\n\n";

Matrix w_a(17, 17);
Matrix b_a(17, 1);

for (unsigned i = 0; i < w_a.getNumberOfLines(); i++) {
    b_a.setValue(i, 0, 1);
    for (unsigned j = 0; j < w_a.getNumberOfColumns(); j++) {
        double val = 0;
        if (i == j) 
            val = 2;
        else if (abs(i - j) == 1)
            val = 1;
        
        w_a.setValue(i, j, val);
    }
}

std::cout << "W_a:";
w_a.print();
std::cout << "b_a:";
b_a.print();

Matrix x_a = solveLinearSystems(w_a, b_a);
std::cout << "x_a:";
x_a.print();

std::cout << "W_a * x_a:";
(w_a * x_a).print();

std::cout << "b)\n\n";

Matrix w_b(20, 17);
Matrix b_b(20, 1);

for (unsigned i = 1; i <= w_b.getNumberOfLines(); i++) {
    b_b.setValue(i-1, 0, i);
    for (unsigned j = 1; j <= w_b.getNumberOfColumns(); j++) {
        double val = 0;
        if (abs(i-j) <= 4)
            val = 1/double(i+j-1);
        w_b.setValue(i-1, j-1, val);
    }
}

std::cout << "W_b:";
w_b.print();
std::cout << "b_b:";
b_b.print();

Matrix x_b = solveLinearSystems(w_b, b_b);

std::cout << "x_b:";
x_b.print();
std::cout << "W_b * x_b:";
(w_b * x_b).print();

}