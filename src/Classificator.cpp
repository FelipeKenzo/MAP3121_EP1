#include "../include/Classificator.h"

Classificator::Classificator(std::string filePath, int dig) :
    filePath(filePath), dig(dig) {
        //ctor
    }

Classificator::~Classificator() {
    delete wd;
    delete a;
}

void Classificator::train(unsigned ndig_treino, unsigned p, bool multithreading)
{    
    a = new Matrix(filePath, 784);
    wd = nonNegativeFactorization(a, ndig_treino, p);
    if (multithreading) {
        std::cout << "Treinou digito " << dig << ".\n";
        //wd->print(4);
    }
    delete a;
}

Matrix* Classificator::getWd() {
    return wd;
}

void Classificator::saveParameterMatrix(const std::string& filePath, unsigned p)
{
    std::ofstream output;
    output.open(filePath);

    output << "P2\n";
    output << "28 28\n";
    output << "65535\n";

    for (unsigned i = 0; i < 28; i++) {
        for (unsigned j = 0; j < 28; j++) {
            //std::cout << "[" << i*28 + j << "][" << p << "]\n";
            output <<  65535 - abs(65535 * (wd->at((i * 28 + j) + 1, p + 1))) << " ";
        }
        output << "\n";
    }

    output.close();
}