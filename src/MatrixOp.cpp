#include "MatrixOp.h"


double* getRGParameters(Matrix w, unsigned i, unsigned j, unsigned k)
{
    if(i > (w.getRowDimension() - 1 )|| j > (w.getColumnDimension() - 1) )
       throw new std::range_error("Input values i, j are out of range");

    double tal, c, s;  
    static double rgParameters[2];  

    if(  abs(w.at(i,k)) > abs(w.at(j,k)) ){
        tal = (- w.at(j,k)) / w.at(i,k);
        c = 1 / sqrt(1 + (tal * tal));
        s = c * tal;
    } else{
        tal = (- w.at(i,k)) / w.at(j,k);
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

    for (unsigned it = 1; it <= n; it++){
        aux = c * (w.at(i, it)) - (s * w.at(j, it));
        w.setValue(j, it, s * w.at(i,it) + c * w.at(j, it));
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

    Matrix r(w.getValues());

    for(unsigned k = 0; k < m; k++){
        for(j = n-1; j > k; j--){
            i = j - 1;
            if(r.at(j, k) != 0){
                double* params = getRGParameters(w, i, j, k);
                c = params[0];
                s = params[1];
                r = rotGivens(r, n, m, i, j, c, s);
            }
        }
    }
    return r;
}