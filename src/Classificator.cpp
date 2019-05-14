#include "../include/Classificator.h"

Classificator::Classificator(std::string filePath, int dig) :
    filePath(filePath), dig(dig) {
        //ctor
    }

Classificator::~Classificator() {
    delete wd;
    delete a;
}

void Classificator::train(unsigned ndig_treino, unsigned p, bool multithreading) {
    
    a = new Matrix(filePath, 784);
    wd = nonNegativeFactorization(a, ndig_treino, p);
    if (multithreading) {
        std::cout << "Treinou digito " << dig << ".\n";
    }
    delete a;
}

Matrix* Classificator::getWd() {
    return wd;
}