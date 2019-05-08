#include "Tester.h"

Tester::Tester(std::string filePath, Classificator* classificators[10]) :
    filePath(filePath), classificators(classificators) {
        //constructor
        a = new Matrix(filePath, 784);
    }

Tester::~Tester(){
    delete a;
    delete mostProbableDigits;
}

void Tester::test(unsigned n_test, unsigned p){

    mostProbableDigits = new std::vector<int>(n_test);
    errors = new std::vector<double>(n_test);
    Matrix* h = new Matrix(p, n_test);
    Matrix* c = new Matrix(748, n_test);


    double c_norm;

    Matrix* classifiers[10];

    for(unsigned k = 0; k < 10; k++){
        c_norm = 0;

        //wd matrix
        classifiers[k] = new Matrix(classificators[k]->getWd()->getValues());

        //Altera o valor de A e de wd, precisa fazer cópias
        h = solveLinearSystems(classifiers[k], this->a);
        c = a - ((classifiers[k]) * h);

        for(unsigned j = 1; j <= n_test; j++ ){

            for(unsigned i = 1; i <= 748; i++){
                c_norm += (c->at(i, j)) * (c->at(i, j));
            }
            c_norm = sqrt(c_norm);

            if(c_norm < errors->at(j)){
                errors->at(j) = c_norm;
                mostProbableDigits->at(j) = (int)k;
            }
        }

    }

    delete h;
    delete c;
}