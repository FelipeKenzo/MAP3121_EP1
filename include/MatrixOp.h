#ifndef MATRIXOP_H
#define MATRIXOP_H

/*
    Definitions for the Matrix Operations package
*/

#include <chrono>

#include "Matrix.h"

    /** Returns cos and sin parameters used in Givens rotation linear operator **/
    double* getRGParameters(Matrix* w, unsigned i, unsigned j, unsigned k); 
    
    void rotGivens(Matrix* w, unsigned i, unsigned j, double c, double s); 

    /** Returns R matrix produced by QR factorization */
    void qrFactorization(Matrix* w);

    // Returns an R matrix which is the best solution for W * X = B
    Matrix* solveLinearSystems(Matrix* w, Matrix* a);

    Matrix* nonNegativeFactorization(Matrix* a, unsigned m, unsigned p);

#endif