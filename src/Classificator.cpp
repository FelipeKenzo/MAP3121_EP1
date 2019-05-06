#include "Classificator.h"

Classificator::Classificator(std::string filePath) :
    filePath(filePath) {
        //ctor
        a = new Matrix(filePath, 784);
    }

Classificator::~Classificator() {
    delete wd;
}

void Classificator::train(unsigned ndig_treino, unsigned p) {
    
    wd = nonNegativeFactorization(a, ndig_treino, p);
}

Matrix* Classificator::getWd() {
    return wd;
}