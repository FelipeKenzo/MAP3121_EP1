#include "MatrixOp.h"


std::vector<double> getRGParameters(Matrix w, unsigned i, unsigned j, unsigned k)
{
    if(i > (w.getRowDimension() - 1 )|| j > (w.getColumnDimension() - 1) )
       throw new std::range_error("Input values i, j are out of range");

    double tal, c, s;  
    std::vector<double> rgParameters;  

    if(  abs(w.getValue(i,k)) > abs(w.getValue(j,k)) ){
        tal = (- w.getValue(j,k)) / w.getValue(i,k);
        c = 1 / sqrt(1 + (tal * tal));
        s = c * tal;
    } else{
        tal = (- w.getValue(i,k)) / w.getValue(j,k);
        s = 1 / sqrt(1 + (tal * tal));
        c = s * tal;
    }

    rgParameters[0] = c; //Sets cos at position 0
    rgParameters[1] = s; //Sets sin at position 1

    return rgParameters;
}

Matrix rotGivens(Matrix w, unsigned n, unsigned m, unsigned i, unsigned j, double c, double s)
{
    double aux;

    for (unsigned it = 0; it < n; it++){
        aux = c * w.getValue(i, it) - s * w.getValue(j, it);
        w.setValue(j, it, s * w.getValue(i,it) + c * w.getValue(j, it));
        w.setValue(i, it, aux);
    }

    return w;
}

Matrix qrFactorization(Matrix w)
{
    double c, s, n, m;
    unsigned i, j;

    n = w.getColumnDimension();
    m = w.getRowDimension();

    for(unsigned k = 1; k <= m; k++){
        for(j = n; j >= k+1; k--){
            i = j - 1;
            if(w.getValue(j, k) != 0){
                c = (getRGParameters(w, i, j, k))[0];
                s = (getRGParameters(w, i, j, k))[1];
                w = rotGivens(w, n, m, i, j, c, s);
            }
        }
    }
    return w;
}