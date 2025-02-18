#include "../include/Tester.h"

Tester::Tester(std::string testFilePath, std::string verificationFilePath, Classificator* classificators[10]) :
    testFilePath(testFilePath), verificationFilePath(verificationFilePath), classificators(classificators) {
        //constructor
        a = new Matrix(testFilePath, 784);
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
    
    Matrix* a_test = new Matrix(784, n_test); //Cópia de A contendo apenas as n_test colunas necessárias
    
    Matrix* Wd_test = new Matrix (784, p);

    //Copia a_test da a
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

        //Esse processo modifica h e a
        h = solveLinearSystems(Wd_test, a_test);

        //Recopia a matriz a_teste
        for(unsigned i = 1; i <= 784; i++){
            for(unsigned j = 1 ; j <= n_test; j++){
                a_test->setValue(i,j, a->at(i,j)); 
            }
        }

        Matrix* Wdh = (*(classificators[k]->getWd())) * h;
        c = (*a_test) - Wdh;

        delete Wdh;

        for(unsigned j = 1; j <= n_test; j++ ){

            for(unsigned i = 1; i <= 784; i++){
                c_norm += (c->at(i, j)) * (c->at(i, j));
            }
            c_norm = sqrt(c_norm);

            if(k == 0){ 
                errors->at(j-1) = c_norm;
            }else if(c_norm < errors->at(j-1)){
                errors->at(j-1) = c_norm;
                mostProbableDigits->at(j-1) = (int)k;
            }
        }

    }

    delete h;
    delete c;
    delete a_test;
}

void Tester::results()
{    
    std::ifstream input;
    input.open(verificationFilePath);
    
    double hits[10];
    double quantity[10];

    for (unsigned i = 0; i < 10; i++) {
        hits[i] = 0;
        quantity[i] = 0;
    }

    int din;
    double totalHits = 0;
    for (unsigned i = 0; i < n_test; i++) {
        input >> din;
        quantity[din]++;
        if ((*mostProbableDigits)[i] == din) {
            hits[din]++;
            totalHits++;
        }
    }

    input.close();

    std::cout << "Taxa de acertos total: " << 100 * totalHits / double(n_test) << "%\n";

    for (unsigned i = 0; i < 10; i++) {
        std::cout << "Taxa de acertos do dig. " << i << ": ";
        if(double(quantity[i]) >= 1.0) 
            std::cout << 100 * double(hits[i]) / double(quantity[i]) << "%\n";
        else
            std::cout << "Nenhum dig. testado\n";
    }

}
    
void Tester::results(const std::string& filePath)
{
    std::ifstream input;
    input.open(verificationFilePath);

    
    double hits[10];
    double quantity[10];

    for (unsigned i = 0; i < 10; i++) {
        hits[i] = 0;
        quantity[i] = 0;
    }

    int din;
    double totalHits = 0;
    for (unsigned i = 0; i < n_test; i++) {
        input >> din;
        quantity[din]++;
        if ((*mostProbableDigits)[i] == din) {
            hits[din]++;
            totalHits++;
        }
    }

    input.close();

    std::ofstream output;
    output.open(filePath);

    output << "Taxa de acertos total: " << 100 * totalHits / double(n_test) << "%\n";
    std::cout << "Taxa de acertos total: " << 100 * totalHits / double(n_test) << "%\n";

    for (unsigned i = 0; i < 10; i++) {
        output << "Taxa de acertos dig. " << i << ": ";
        std::cout << "Taxa de acertos dig. " << i << ": ";

        if(double(quantity[i]) >= 1.0) { 
            output << 100 * double(hits[i]) / double(quantity[i]) << "%\n";
            std::cout << 100 * double(hits[i]) / double(quantity[i]) << "%\n";

        }
        else {
            output << "No digit tested\n";
            std::cout << "No digit tested\n";
        }
    }
}