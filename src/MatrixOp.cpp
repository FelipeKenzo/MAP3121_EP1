#include "MatrixOp.h"
#define eps 1e-5
#define itmax 100

double* getRGParameters(Matrix w, unsigned i, unsigned j, unsigned k)
{
    if (j > (w.getNumberOfLines() -1) || k > (w.getNumberOfColumns() -1)) {
       std::cout << i << " " << j << "\n";
       throw new std::range_error("Input values i, j, k are out of range");
    }

    double tau, c, s;
    double* rgParameters = new double[2];  

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

Matrix rotGivens(Matrix w, unsigned i, unsigned j, double c, double s)
{
    double aux;
    unsigned m = w.getNumberOfColumns();

    for (unsigned r = 0; r < m; r++){
        //std::cout << "Acessando w[" << i << "][" << r
        //          << "] e w[" << j << "][" << r << "]\n";
        aux = c * w.at(i, r) - s * w.at(j, r);
        w.setValue(j, r, ((s * w.at(i,r)) + (c * w.at(j, r))));
        w.setValue(i, r, aux);
    }

    //std::cout << "rotGivens completo.\n";
    return w;
}

Matrix qrFactorization(Matrix w)
{

    double c, s;
    unsigned n, m, i, j;

    n = w.getNumberOfLines();
    m = w.getNumberOfColumns();

    Matrix r(w.getValues());
    r.print();

    for(unsigned k = 0; k < m; k++){
        for(j = n-1; j > k; j--){
            i = j - 1;
            if(fabs(r.at(j, k)) > eps){
                std::cout << "rotGivens para zerar r(" << j << ", " << k << ")\n";
                double* params = getRGParameters(r, i, j, k);
                c = params[0];
                s = params[1];
                std::cout << "parametros: c = " << c << ", s = " << s <<"\n";
                r = rotGivens(r, i, j, c, s);
                delete params;
                r.print();
            }
        }
    }
    return r;
}

Matrix solveLinearSystems(Matrix w, Matrix b) { //W * x = b
    double c, s;

    Matrix r(w.getValues());
    Matrix newB(b.getValues());
    Matrix x(w.getNumberOfColumns(), b.getNumberOfColumns());

    for(unsigned k = 0; k < w.getNumberOfColumns(); k++){
        for(unsigned j = w.getNumberOfLines()-1; j > k; j--){
            unsigned i = j - 1;
            //std::cout << "r[" << j << "][" << k << "]\n";
            if(fabs(r.at(j, k)) > eps){
                double* params = getRGParameters(r, i, j, k);
                c = params[0];
                s = params[1];
                r = rotGivens(r, i, j, c, s);
                newB = rotGivens(newB, i, j, c, s);
                delete params;
            }
        }
    }

    //std::cout << "Matriz R:";
    //r.print();
    //std::cout << "Matriz blinha:";
    //newB.print();

    for (int k = int(x.getNumberOfLines()-1); k >= 0; k--) {
        for (unsigned j = 0; j < x.getNumberOfColumns(); j++) {
            double aux = 0;
            for (int i = k + 1; i < x.getNumberOfLines(); i++) {
                //std::cout << "k: " << k << " j: " << j << " i: " << i << "\n";
                aux += r.at(k, i) * x.at(i, j);
            }
            double x_k_j = (newB.at(k, j) - aux)/r.at(k, k);
            x.setValue(k, j, x_k_j);
        }
    }

    return x;
}

Matrix nonNegativeFactorization(Matrix a, unsigned p)
{
    Matrix w(a.getNumberOfLines(), p);

    for (unsigned i = 0; i < w.getNumberOfLines(); i++) {
        for (unsigned j = 0; j < w. getNumberOfColumns(); j++) {
            double random = double(rand() % 9 +1);
            w.setValue(i, j, random);
        }
    }

    if (p < a.getNumberOfColumns() || p < a.getNumberOfLines())
        throw new std::invalid_argument("invalid inner dimension");
    
    return w;
}