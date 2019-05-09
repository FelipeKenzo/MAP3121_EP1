#ifndef TESTER_H
#define TESTER_H

#include <iostream>
#include <string>

#include "Classificator.h"
#include "Matrix.h"
#include "MatrixOp.h"

class Tester{
    public:
        Tester(std::string testFilePath, std::string verificationFilePath, Classificator* classificators[10]);
        ~Tester();

        void test(unsigned n_test, unsigned p);//Same p used in trainning

    private:

        Matrix* a;
        std::vector<int>* mostProbableDigits;
        std::vector<double>* errors;

        Classificator** classificators;
        std::string testFilePath;
        std::string verificationFilePath;
        

};

#endif