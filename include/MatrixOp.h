#ifndef MATRIXOP_H
#define MATRIXOP_H

/*
    Definitions for the Matrix Operations package
*/

#include "Matrix.h"

    /** Returns cos and sin parameters used at Givens rotation linear operator **/
    std::vector<double> getRGParameters(Matrix w, unsigned i, unsigned j, unsigned k); 
    
    Matrix rotGivens(Matrix w, unsigned n, unsigned m, unsigned i, unsigned j, double c, double s); 

#endif