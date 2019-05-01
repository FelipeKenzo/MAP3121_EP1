#include "MatrixOp.h"
#define eps 1e-6

double* getRGParameters(Matrix w, unsigned i, unsigned j, unsigned k)
{
    if(i > (w.getRowDimension() - 1 )|| j > (w.getColumnDimension() - 1) )
       throw new std::range_error("Input values i, j are out of range");

    double tau, c, s;
    static double rgParameters[2];  

    if(  abs(w.at(i,k)) > abs(w.at(j,k)) ){
        tau = -(w.at(j,k) / w.at(i,k));
        c = 1 / sqrt(1 + (tau * tau));
        s = c * tau;
    } else{
        tau = -(w.at(i,k) / w.at(j,k));
        s = 1 / sqrt(1 + (tau * tau));
        c = s * tau;
    }

    rgParameters[0] = c; //Sets cos at position 0
    rgParameters[1] = s; //Sets sin at position 1

    return rgParameters;
}

Matrix rotGivens(Matrix w, unsigned n, unsigned m, unsigned i, unsigned j, double c, double s)
{
    double aux;

    for (unsigned r = 0; r < m; r++){
        aux = c * w.at(i, r) - s * w.at(j, r);
        w.setValue(j, r, ((s * w.at(i,r)) + (c * w.at(j, r))));
        w.setValue(i, r, aux);
    }

    return w;
}

Matrix qrFactorization(Matrix w)
{

    double c, s;
    unsigned n, m, i, j;

    n = w.getColumnDimension();
    m = w.getRowDimension();

    Matrix r(w.getValues());
    r.print();

    for(unsigned k = 0; k < m; k++){
        for(j = n-1; j > k; j--){
            i = j - 1;
            if(fabs(r.at(j, k)) > eps){
                std::cout << "rotGivens para zerar r(" << j << ", " << k << ")\n";
                double* params = getRGParameters(w, i, j, k);
                c = params[0];
                s = params[1];
                r = rotGivens(r, n, m, i, j, c, s);
                r.print();
            }
        }
    }
    return r;
}