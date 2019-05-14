#include <iostream>
#include <string>
#include <cmath>
#include <chrono>
#include <stdexcept>
#include <thread>
//#include <stdlib.h>

#include "../include/Classificator.h"
#include "../include/Matrix.h"
#include "../include/MatrixOp.h"
#include "../include/Tester.h"

///***-------------------------------------------------------***///
///***------------- FUNCTIONS DECLARATIONS ------------------***///
///***------------ Main function at line 234 ----------------***///
///***-------------------------------------------------------***///

void primeiraTarefa(){

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

    //w_a->print(0);

    Matrix* x_a = solveLinearSystems(w_a, b_a);
    std::cout << "x_a:";
    x_a->print(5);

    delete w_a;
    delete b_a;
    delete x_a;

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

    Matrix* x_b = solveLinearSystems(w_b, b_b);

    std::cout << "x_b:";
    x_b->print(5);

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
    x_c->print(5);

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
    x_d->print(5);

    auto t1_finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> t1_elapsed = t1_finish - t1_start;

    std::cout << "Tarefa 1 elapsed time: " << t1_elapsed.count() << "\n\n";

}

void segundaTarefa(){

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
    at2->print(5);

    std::cout << "Matriz W:\n";
    w = (nonNegativeFactorization(at2, 3, 2));
    w->print(5);

    auto t2_finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> t2_elapsed = t2_finish - t2_start;

    std::cout << "Tarefa 2 elapsed time: " << t2_elapsed.count() << "\n\n";
    
}

void tarefaPrincipal(unsigned n_digTreino, unsigned n_test, unsigned p, bool multithreading){

    std::cout << "======== [Tarefa Principal] =========\n\n";
    auto tp_start = std::chrono::high_resolution_clock::now();

    Classificator* classificators[10];

    std::cout << "======================================\n"
              << "n_digTreino: " << n_digTreino <<", p: " << p << ", n_test: " << n_test << "\n"
              << "multi_threading: " << std::boolalpha << multithreading << "\n"
              << "======================================\n";

    //*** Training Phase ***//

    auto train_start = std::chrono::high_resolution_clock::now();
    std::cout << "Training started...\n";

    std::thread t[10];
    
    for (unsigned i = 0; i < 10; i++) {

        classificators[i] = new Classificator("../dados_mnist/train_dig" + std::to_string(i) + ".txt", i);
            
        if (multithreading) {    
            t[i] = std::thread(&Classificator::train, classificators[i], n_digTreino, p, multithreading);
        }
        else {
            classificators[i]->train(n_digTreino, p, multithreading);
            std::cout<< "Training progress: " << (i+1) * 10 <<"%\n";
        }
    }
    
    if (multithreading) {
        for (unsigned i = 0; i < 10; i++) {
            t[i].join();
        }
    }

    auto train_finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> train_elapsed = train_finish - train_start;
    std::cout << "Finished. Elapsed time: " << train_elapsed.count() <<"\n\n";

    //*** classification Phase ***//

    auto test_start = std::chrono::high_resolution_clock::now();
    std::cout << "Classification started...\n";
    Tester tester("../dados_mnist/test_images.txt", "../dados_mnist/test_index.txt", classificators);

    try {
        tester.test(n_test, p);
    } catch (std::invalid_argument* e) {
        std::cout << "Erro: " << e->what() << "\n";
    }

    auto test_finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> test_elapsed = test_finish - test_start;
    
    std::cout << "Finished. Elapsed time: " << test_elapsed.count() <<"\n";
    
    std::cout << "---Results: \n";

    tester.results();

    auto tp_finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tp_elapsed = tp_finish - tp_start;
    std::cout << "\nTarefa Principal elapsed time: " << tp_elapsed.count() << "\n";    
    
}

///***---------------- MAIN ----------------***///

int main(int argc, char* argv[]) {

    bool arg = false;
    bool multi = false;
    unsigned n_digTreino, n_test, p;
    bool arguments[3] = {false, false, false};

    if (argc > 1) {
        arg = true;
        for (int i = 1; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "-nt") {
                if (i + 1 < argc) {
                    arguments[0] = true;
                    n_digTreino = std::stoi(argv[++i], nullptr, 0);
                }
            }
            else if (arg == "-nc") {
                if (i + 1 < argc) {
                    arguments[1] = true;
                    n_test = std::stoi(argv[++i], nullptr, 0);
                }
            }
            else if (arg == "-p") {
                if (i + 1 < argc) {
                    arguments[2] = true;
                    p = std::stoi(argv[++i], nullptr, 0);
                }
            }
            else if (arg == "-mt" || arg == "multithreading") {
                multi = true;
            }
            else {
                std::cerr << "invalid argument(s)." << std::endl;
                return 1;
            }
        }
    }



    auto t_start = std::chrono::high_resolution_clock::now();

    primeiraTarefa();

    segundaTarefa();

    if (!(arguments[0] && arguments [1] && arguments[2])) {
        std::cout << "======= Dados para a Tarefa Principal =======\n";
    }
    if (!arguments[0]) {
        std::cout << "Insira o numero de imagens usadas no treino: ";
        std::cin >> n_digTreino;
    }
    if (!arguments[1]) {
        std::cout << "\nInsira o numero de imagens a serem classificadas: ";
        std::cin >> n_test;
    }
    if (!arguments[2]) {
        std::cout << "\nInsira a precisao (p): ";
        std::cin >> p;
    }

    tarefaPrincipal(n_digTreino, n_test, p, multi);

    auto t_finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> t_elapsed = t_finish - t_start;

    std::cout << "\n\nTempo total de execução do programa: " << t_elapsed.count() << "\n\n";
 


    return 0;
}




