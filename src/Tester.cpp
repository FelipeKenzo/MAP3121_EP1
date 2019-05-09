#include "Tester.h"

Tester::Tester(std::string testFilePath, std::string verificationFilePath, Classificator* classificators[10]) :
    testFilePath(testFilePath), verificationFilePath(verificationFilePath), classificators(classificators) {
        //constructor
        a = new Matrix(testFilePath, 7483);
    }

Tester::~Tester(){
    delete a;
    delete mostProbableDigits;
}

void Tester::test(unsigned n_test, unsigned p){

    this->n_test = n_test;

    mostProbableDigits = new std::vector<int>(n_test);
    errors = new std::vector<double>(n_test);
    Matrix* h = new Matrix(p, n_test);
    Matrix* c = new Matrix(784, n_test);
    
    Matrix* a_test = new Matrix(784, n_test); //Copy of A containing only the n_test relevant columns
    
    Matrix* Wd_test = new Matrix (784, p);

    //Copies the a_test from a
        for(unsigned i = 1; i <= 784; i++){
            for(unsigned j = 1 ; j <= n_test; j++){
                a_test->setValue(i,j, a->at(i,j)); 
            }
        }


    double c_norm;

    for(unsigned k = 0; k < 10; k++){
        
        for(unsigned i = 1; i <= 784; i++){
            for(unsigned j = 1 ; j <= p; j++){
                    Wd_test->setValue(i,j, classificators[k]->getWd()->at(i,j)); 
            }
        }
       
        c_norm = 0;        

        //Modifies wd and a_test 
        h = solveLinearSystems(Wd_test, a_test);

        //Copies the a_test again due to modification
        for(unsigned i = 1; i <= 784; i++){
            for(unsigned j = 1 ; j <= n_test; j++){
                a_test->setValue(i,j, a->at(i,j)); 
            }
        }

        //std::cout << "  Wd eh " << Wd_test->getNumberOfLines() << " x " << Wd_test->getNumberOfColumns() << "\n";
        //std::cout << "   H eh " << h->getNumberOfLines() << " x " << h->getNumberOfColumns() << "\n";

        Matrix* Wdh = (*(classificators[k]->getWd())) * h;
        
        
        //std::cout << "Wd*H eh " << Wdh->getNumberOfLines() << " x " << Wdh->getNumberOfColumns() << "\n";
        //std::cout << "   A eh " << a_test->getNumberOfLines() << " x " << a_test->getNumberOfColumns() << "\n";
        c = (*a_test) - Wdh;

        //std::cout << "   C eh " << a_test->getNumberOfLines() << " x " << a_test->getNumberOfColumns() << "\n";

        delete Wdh;

        for(unsigned j = 1; j <= n_test; j++ ){

            for(unsigned i = 1; i <= 784; i++){
                c_norm += (c->at(i, j)) * (c->at(i, j));
            }
            c_norm = sqrt(c_norm);

            if(c_norm < errors->at(j-1)){
                errors->at(j-1) = c_norm;
                mostProbableDigits->at(j-1) = (int)k;
            }
        }

    }

    delete h;
    delete c;
    delete a_test;

    std::cout << "Test is over\n";
}

void Tester::results() {
    
    std::ifstream input;
    input.open(verificationFilePath);
    
    double percentages[10];
    double hits[10];
    double quantity[10];

    for (unsigned i = 0; i < 10; i++) {
        hits[i] = 0;
        quantity[i] = 0;
        percentages[i] = 0;
    }

    int din;
    for (unsigned i = 0; i < n_test; i++) {
        input >> din;
        std::cout << "[" << din << ", " << (*mostProbableDigits)[i] << "] ";
        quantity[din]++;
        if ((*mostProbableDigits)[i] == din) {
            hits[din]++;
        }
    }
    std::cout << "\n";

    input.close();

    for (unsigned i = 0; i < 10; i++) {
        std::cout << "Accuracy for digit " << i << ": ";
        std::cout << 100 * double(hits[i]) / double(quantity[i]) << "%\n";
    }
}