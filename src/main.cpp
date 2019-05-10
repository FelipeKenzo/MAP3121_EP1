#include <iostream>
#include <string>
#include <cmath>
#include <chrono>
#include <stdexcept>

#include "Classificator.h"
#include "Matrix.h"
#include "MatrixOp.h"
#include "Tester.h"
//#include "MatrixPersistence.h"

int main() {
    //*
   //*
    auto p_start = std::chrono::high_resolution_clock::now();

    //*
    std::vector<double>* a = new std::vector<double>{2, 1,  1, -1,  1};
    std::vector<double>* b = new std::vector<double>{0, 3,  0,  1,  2};
    std::vector<double>* c = new std::vector<double>{0, 0,  2,  2, -1};
    std::vector<double>* d = new std::vector<double>{0, 0, -1,  1,  2};
    std::vector<double>* e = new std::vector<double>{0, 0,  0,  3,  1};

    std::vector<std::vector<double>*>* m_values = new std::vector<std::vector<double>*>{a, b, c, d, e};

    Matrix* m1 = new Matrix(m_values);

    std::cout << "QR Factorization test: \n\n" << "W:";

    m1->print();

    try {
    qrFactorization(m1);

    } catch (std::range_error* e) {
        std::cout << "Error: " << e->what() << "\n";
    }

    std::cout << "R:";

    m1->print();

    auto qr_finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> qr_elapsed = qr_finish - p_start;
    
    std::cout << "QR elapsed time: " << qr_elapsed.count() << "\n\n";
    
    
    std::cout << "==========[Primeira Tarefa]==========\n";

    auto t1_start = std::chrono::high_resolution_clock::now();

    std::cout << "a)\n\n";

    Matrix* w_a = new Matrix(64, 64);
    Matrix* b_a = new Matrix(64, 1);

    for (unsigned i = 1; i <= w_a->getNumberOfLines(); i++) {
        b_a->setValue(i, 1, 1);
        for (unsigned j = 1; j <= w_a->getNumberOfColumns(); j++) {
            double val = 0;
            if (i == j) 
                val = 2;
            else if (abs(i - j) == 1)
                val = 1;
            
            w_a->setValue(i, j, val);
        }
    }


    //std::cout << "W_a:";
    //w_a->print();
    //std::cout << "b_a:";
    //b_a->print();

    Matrix* x_a = solveLinearSystems(w_a, b_a);
    std::cout << "x_a:";
    x_a->print();

    delete w_a;
    delete b_a;
    delete x_a;

    //std::cout << "W_a * x_a:";
    //(w_a * x_a)->print();

    std::cout << "b)\n\n";

    Matrix* w_b = new Matrix(20, 17);
    Matrix* b_b = new Matrix(20, 1);

    for (unsigned i = 1; i <= w_b->getNumberOfLines(); i++) {
        b_b->setValue(i, 1, i);
        for (unsigned j = 1; j <= w_b->getNumberOfColumns(); j++) {
            double val = 0;
            if (abs(i-j) <= 4)
                val = 1/double(i+j-1);
            w_b->setValue(i, j, val);
        }
    }

    //std::cout << "W_b:";
    //w_b->print();
    //std::cout << "b_b:";
    //b_b->print();

    Matrix* x_b = solveLinearSystems(w_b, b_b);

    std::cout << "x_b:";
    x_b->print();

    //std::cout << "W_b * x_b:";
    //(w_b * x_b)->print();

    std::cout << "c)\n\n";

    Matrix* w_c = new Matrix(64, 64);
    Matrix* b_c = new Matrix(64, 3);

    for (unsigned i = 1; i <= w_c->getNumberOfLines(); i++) {
        b_c->setValue(i, 1, 1);
        b_c->setValue(i, 2, i);
        b_c->setValue(i, 3, (2*i)-1);
        for (unsigned j = 1; j <= w_c->getNumberOfColumns(); j++) {
            double val = 0;
            if (i == j) 
                val = 2;
            else if (abs(i - j) == 1)
                val = 1;
            w_c->setValue(i, j, val);
        }
    }

    Matrix* x_c = solveLinearSystems(w_c, b_c);
    std::cout << "x_c:";
    x_c->print();

    std::cout << "d)\n\n";

    Matrix* w_d = new Matrix(20, 17);
    Matrix* b_d = new Matrix(20, 3);

    for (unsigned i = 1; i <= w_d->getNumberOfLines(); i++) {
        b_d->setValue(i, 1, 1);
        b_d->setValue(i, 2, i);
        b_d->setValue(i, 3, (2*i)-1);
        for (unsigned j = 1; j <= w_d->getNumberOfColumns(); j++) {
            double val = 0;
            if (abs(i-j) <= 4)
                val = 1/double(i+j-1);
            w_d->setValue(i, j, val);
        }
    }

    Matrix* x_d = solveLinearSystems(w_d, b_d);
    std::cout << "x_d:";
    x_d->print();

    auto t1_finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> t1_elapsed = t1_finish - t1_start;

    std::cout << "Tarefa 1 elapsed time: " << t1_elapsed.count() << "\n\n";

 
    std::cout << "======== [Segunda Tarefa] =========\n";
    auto t2_start = std::chrono::high_resolution_clock::now();

    Matrix* at2 = new Matrix(3, 3);
    Matrix* w = new Matrix(3, 2);


    std::vector<double>* a1 = new std::vector<double>{3.0/10.0, 3.0/5.0, 0};
    std::vector<double>* a2 = new std::vector<double>{1.0/2.0 ,   0, 1};
    std::vector<double>* a3 = new std::vector<double>{4.0/10.0, 4.0/5.0, 0};

    at2->setRow(1, a1);
    at2->setRow(2, a2);
    at2->setRow(3, a3);

    std::cout << "Matriz A:\n";
    at2->print();

    std::cout << "Matriz W:\n";
    w = (nonNegativeFactorization(at2, 3, 2));
    w->print();

    auto t2_finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> t2_elapsed = t2_finish - t2_start;

    std::cout << "Tarefa 2 elapsed time: " << t2_elapsed.count() << "\n\n";
    
    //*/

    //*
    std::cout << "======== [Tarefa Principal] =========\n";
    auto tp_start = std::chrono::high_resolution_clock::now();

    Classificator* classificators[10];
    //MatrixPersistence* persistence = new MatrixPersistence();

        for (unsigned i = 0; i < 10; i++){
            std::cout << "Inicializando classificador d " << i << "...\n";
            
            classificators[i] = new Classificator("../dados_mnist/train_dig" + std::to_string(i) + ".txt");
            std::cout << "classificador d" << i << " inicializado.\n";
            
            std::cout << "Iniciando treinamento d " << i << "...\n";
            
            auto train_start = std::chrono::high_resolution_clock::now();
            try {
                classificators[i]->train(100, 10);
            } catch (std::invalid_argument* e) {
                std::cout << "Erro: " << e->what() << "\n";
            }
            auto train_finish = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> train_elapsed = train_finish - train_start;
            std::cout << "Treinou.\nTraining elapsed time: " << train_elapsed.count() <<"\n\n";

            /*
            std::cout << "Salvando matrix do classificador...\n";
            persistence->save("classificator_100_5_" + std::to_string(i) + ".txt", classificators[i]->getWd());
            
            auto save_finish = std::chrono::high_resolution_clock::now();
            train_elapsed = train_finish - save_finish;

            std::cout << "Salvou.\nSaving elapsed time: " << train_elapsed.count() << "\n\n\n";
            //*/
        }

    Tester tester("../dados_mnist/test_images.txt", "../dados_mnist/test_index.txt", classificators);

    try {
        tester.test(1000, 5);
    } catch (std::invalid_argument* e) {
        std::cout << "Erro: " << e->what() << "\n";
    }

    tester.results();


    auto tp_finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tp_elapsed = tp_finish - tp_start;
    
    std::cout << "\nTarefa Principal elapsed time: " << tp_elapsed.count() << "\n";    
    //*/

    
    auto p_finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> p_elapsed = p_finish - p_start;
    
    std::cout << "\nTotal elapsed time: " << p_elapsed.count() << "\n";
    
    return 0;
}