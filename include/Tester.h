#ifndef TESTER_H
#define TESTER_H

#include <iostream>
#include <string>
#include <fstream>

#include "Classificator.h"
#include "Matrix.h"
#include "MatrixOp.h"

class Tester{
    public:
        Tester(std::string testFilePath, std::string verificationFilePath, Classificator* classificators[10]);
        ~Tester();

        void test(unsigned n_test, unsigned p);//Same p used in trainning
        
        void results();

    private:
        unsigned n_test;

        Matrix* a;
        std::vector<int>* mostProbableDigits;
        std::vector<double>* errors;

        Classificator** classificators;
        std::string testFilePath;
        std::string verificationFilePath;
        

};

#endif