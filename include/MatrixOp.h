#ifndef MATRIXOP_H
#define MATRIXOP_H

/*
    Definições para o pacote de operações MatrixOp
*/

#include <chrono>
#include <iostream>

#include "../include/Matrix.h"

    /** Retorna os parâmetros cosseno e seno usados na Rotação de Givens **/
    double* getRGParameters(Matrix* w, unsigned i, unsigned j, unsigned k); 
    
    void rotGivens(Matrix* w, unsigned i, unsigned j, double c, double s); 

    /** Retorna a matriz R produzida pela fatoração QR **/
    void qrFactorization(Matrix* w);

    /** Retorna a matriz R que é a melhor solução para W * X = B **/
    Matrix* solveLinearSystems(Matrix* w, Matrix* a);

    Matrix* nonNegativeFactorization(Matrix* a, unsigned m, unsigned p);

#endif