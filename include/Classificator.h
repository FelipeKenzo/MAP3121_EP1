#ifndef CLASSIFICATOR_H
#define CLASSIFICATOR_H

#include <string>
#include <iostream>
#include <fstream>

#include "../include/Matrix.h"
#include "../include/MatrixOp.h"

class Classificator {
public:
    Classificator(std::string filePath, int dig);
    ~Classificator();

    void train(unsigned ndig_treino, unsigned p, bool multithreading);
    void saveParameterMatrix(const std::string& filePath, unsigned p);

    Matrix* getWd();

private:
    Matrix* a;
    Matrix* wd = NULL;
    std::string filePath;
    int dig;
};

#endif