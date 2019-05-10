#include "Classificator.h"

Classificator::Classificator(std::string filePath) :
    filePath(filePath) {
        //ctor
    }

Classificator::~Classificator() {
    delete wd;
    delete a;
}

void Classificator::train(unsigned ndig_treino, unsigned p) {
    
    a = new Matrix(filePath, 784);
    //std::cout << "Antes do nmf.\n";
    wd = nonNegativeFactorization(a, ndig_treino, p);
    //std::cout << "Depois do nmf.\n";
    delete a;
}

Matrix* Classificator::getWd() {
    return wd;
}