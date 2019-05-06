#include <iostream>
#include <string>
#include <cmath>
#include <chrono>

#include "Matrix.h"
#include "MatrixOp.h"

int main() {

    auto p_start = std::chrono::high_resolution_clock::now();


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

    /*
    std::cout << "==========[Primeira Tarefa]==========\n";
    std::cout << "a)\n\n";

    Matrix* w_a = new Matrix(63, 63);
    Matrix* b_a = new Matrix(63, 1);

    for (unsigned i = 1; i <= w_a->getNumberOfLines(); i++) {
        b_a->setValue(i, 1, 1);
        for (unsigned j = 1; j <= w_a->getNumberOfColumns(); j++) {
            double val = 0;
            if (i == j) 
                val = 2;
            else if (abs(i - j) == 1)
                val = 1;
            
            w_a->setValue(i, j, val);
        }
    }


    //std::cout << "W_a:";
    //w_a->print();
    //std::cout << "b_a:";
    //b_a->print();

    Matrix* x_a = solveLinearSystems(w_a, b_a);
    std::cout << "x_a:";
    x_a->print();

    delete w_a;
    delete b_a;
    delete x_a;

    //std::cout << "W_a * x_a:";
    //(w_a * x_a)->print();

    std::cout << "b)\n\n";

    Matrix* w_b = new Matrix(20, 17);
    Matrix* b_b = new Matrix(20, 1);

    for (unsigned i = 1; i <= w_b->getNumberOfLines(); i++) {
        b_b->setValue(i, 1, i);
        for (unsigned j = 1; j <= w_b->getNumberOfColumns(); j++) {
            double val = 0;
            if (abs(i-j) <= 4)
                val = 1/double(i+j-1);
            w_b->setValue(i, j, val);
        }
    }

    //std::cout << "W_b:";
    //w_b->print();
    //std::cout << "b_b:";
    //b_b->print();

    Matrix* x_b = solveLinearSystems(w_b, b_b);

    std::cout << "x_b:";
    x_b->print();

    //std::cout << "W_b * x_b:";
    //(w_b * x_b)->print();

    std::cout << "c)\n\n";

    Matrix* w_c = new Matrix(63, 63);
    Matrix* b_c = new Matrix(63, 3);

    for (unsigned i = 1; i <= w_c->getNumberOfLines(); i++) {
        b_c->setValue(i, 1, 1);
        b_c->setValue(i, 2, i);
        b_c->setValue(i, 3, (2*i)-1);
        for (unsigned j = 1; j <= w_c->getNumberOfColumns(); j++) {
            double val = 0;
            if (i == j) 
                val = 2;
            else if (abs(i - j) == 1)
                val = 1;
            w_c->setValue(i, j, val);
        }
    }

    Matrix* x_c = solveLinearSystems(w_c, b_c);
    std::cout << "x_c:";
    x_c->print();

    std::cout << "d)\n\n";

    Matrix* w_d = new Matrix(20, 17);
    Matrix* b_d = new Matrix(20, 3);

    for (unsigned i = 1; i <= w_d->getNumberOfLines(); i++) {
        b_d->setValue(i, 1, 1);
        b_d->setValue(i, 2, i);
        b_d->setValue(i, 3, (2*i)-1);
        for (unsigned j = 1; j <= w_d->getNumberOfColumns(); j++) {
            double val = 0;
            if (abs(i-j) <= 4)
                val = 1/double(i+j-1);
            w_d->setValue(i, j, val);
        }
    }

    Matrix* x_d = solveLinearSystems(w_d, b_d);
    std::cout << "x_d:";
    x_d->print();

    //*/

    /*
    std::cout << "======== [Segunda Tarefa] =========\n";

    Matrix* a = new Matrix(3, 3);
    Matrix* w = new Matrix(3, 2);


    std::vector<double>* a1 = new std::vector<double>{3.0/10.0, 3.0/5.0, 0};
    std::vector<double>* a2 = new std::vector<double>{1.0/2.0 ,   0, 1};
    std::vector<double>* a3 = new std::vector<double>{4.0/10.0, 4.0/5.0, 0};

    a->setRow(1, a1);
    a->setRow(2, a2);
    a->setRow(3, a3);

    std::cout << "Matriz A:\n";
    a->print();

    w = (nonNegativeFactorization(a, 2));
    //*/

    Matrix* a = new Matrix("train_dig0.txt", 784);
    std::cout << a->at(784, 5923) << "\n";

    auto p_finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> p_elapsed = p_finish - p_start;
    std::cout << "Total elapsed time: " << p_elapsed.count() << "\n";

    return 0;
}