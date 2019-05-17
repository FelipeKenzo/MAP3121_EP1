#ifndef TESTER_H
#define TESTER_H

#include <iostream>
#include <string>
#include <fstream>
#include <thread>

#include "../include/Classificator.h"
#include "../include/Matrix.h"
#include "../include/MatrixOp.h"

class Tester{
    public:
        Tester(std::string testFilePath, std::string verificationFilePath, Classificator* classificators[10]);
        ~Tester();

        void test(unsigned n_test, unsigned p);//Same p used in trainning
        
        void results();
        void results(const std::string& filePath);

    private:
        unsigned n_test = 0;

        Matrix* a;
        std::vector<int>* mostProbableDigits;
        std::vector<double>* errors;

        Classificator** classificators;
        std::string testFilePath;
        std::string verificationFilePath;
        

};

#endif