#include "Classificator.h"

Classificator::Classificator(std::string filePath) :
    filePath(filePath) {
        //ctor
        a = new Matrix(filePath, 784);
    }

Classificator::~Classificator() {
    delete wd;
    delete a;
}

void Classificator::train(unsigned ndig_treino, unsigned p) {
    
    //std::cout << "Antes do nmf.\n";
    wd = nonNegativeFactorization(a, ndig_treino, p);
    //std::cout << "Depois do nmf.\n";
}

Matrix* Classificator::getWd() {
    return wd;
}