#ifndef CLASSIFICATOR_H
#define CLASSIFICATOR_H

#include <string>
#include <iostream>

#include "Matrix.h"
#include "MatrixOp.h"

class Classificator {
public:
    Classificator(std::string filePath);
    ~Classificator();

    void train(unsigned ndig_treino, unsigned p);

    Matrix* getWd();

private:
    Matrix* a;
    Matrix* wd = NULL;
    std::string filePath;
    int dig;
};

#endif