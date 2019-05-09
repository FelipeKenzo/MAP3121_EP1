#include "Tester.h"

Tester::Tester(std::string filePath, Classificator* classificators[10]) :
    testfilePath(testfilePath), verificationFilePath(verificationFilePath) classificators(classificators) {
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
    //Copy of a containing only the n_test relevant columns
    Matrix* a_test = new Matrix(748, n_test);

    //Copies the a_test from a
        for(unsigned i = 1; i <= 748; i++){
            for(unsigned j = 1 ; j <= n_test; j++){
                a_test->setValue(i,j, a->at(i,j)); 
            }
        }

    double c_norm;

    for(unsigned k = 0; k < 10; k++){
       
        c_norm = 0;        

        //Modifies wd and a_test 
        h = solveLinearSystems(classificators[k]->getWd(), a_test);
                /*---!!! FALTA FAZER A CÓPIA DE WD  !!!---*/

        //Copies the a_test again due to modification
        for(unsigned i = 1; i <= 748; i++){
            for(unsigned j = 1 ; j <= n_test; j++){
                a_test->setValue(i,j, a->at(i,j)); 
            }
        }

        c = (*a_test) - ((*(classificators[k]->getWd())) * h);

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
    delete a_test;

    std::cout << "Test is over\n";
}