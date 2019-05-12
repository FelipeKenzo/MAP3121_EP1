#include "../include/MatrixOp.h"
#define eps 1e-5
#define itmax 100

double* getRGParameters(Matrix* w, unsigned i, unsigned j, unsigned k)
{
    if (j > (w->getNumberOfLines()) || k > (w->getNumberOfColumns())) {
       std::cout << i << " " << j << "\n";
       throw new std::range_error("Input values i, j, k are out of range");
    }

    double tau, c, s;
    double* rgParameters = new double[2];  

    if(  abs(w->at(i,k)) > abs(w->at(j,k)) ){
        tau = -(w->at(j,k) / w->at(i,k));
        c = 1 / sqrt(1 + (tau * tau));
        s = c * tau;
    } else{
        tau = -(w->at(i,k) / w->at(j,k));
        s = 1 / sqrt(1 + (tau * tau));
        c = s * tau;
    }

    rgParameters[0] = c; //Sets cos at position 0
    rgParameters[1] = s; //Sets sin at position 1

    return rgParameters;
}

void rotGivens(Matrix* w, unsigned i, unsigned j, double c, double s)
{
    double aux;
    unsigned m = w->getNumberOfColumns();

    for (unsigned r = 1; r <= m; r++){
        //std::cout << "Acessando w[" << i << "][" << r
        //          << "] e w[" << j << "][" << r << "]\n";
        aux = c * w->at(i, r) - s * w->at(j, r);
        w->setValue(j, r, ((s * w->at(i,r)) + (c * w->at(j, r))));
        w->setValue(i, r, aux);
    }

    //std::cout << "rotGivens completo->\n";
    return;
}

void qrFactorization(Matrix* w)
{

    double c, s;
    unsigned n, m, i, j;

    n = w->getNumberOfLines();
    m = w->getNumberOfColumns();

    for(unsigned k = 1; k <= m; k++){
        for(j = n; j >= k + 1; j--){
            i = j - 1;
            if(fabs(w->at(j, k)) > eps){
                //std::cout << "rotGivens para zerar r(" << j << ", " << k << ")\n";
                double* params = getRGParameters(w, i, j, k);
                c = params[0];
                s = params[1];
                //std::cout << "parametros: c = " << c << ", s = " << s <<"\n";
                rotGivens(w, i, j, c, s);
                delete params;
                //w->print();
            }
        }
    }
    return;
}

Matrix* solveLinearSystems(Matrix* w, Matrix* a) { //W * H = A
    double c, s;

    unsigned n = w->getNumberOfLines();
    unsigned m = a->getNumberOfColumns();
    unsigned p = w->getNumberOfColumns();

    Matrix* h = new Matrix(p, m);

    for(unsigned k = 1; k <= p; k++){
        for(unsigned j = n; j >= k + 1; j--){
            unsigned i = j - 1;
            //std::cout << "r[" << j << "][" << k << "]\n";
            if(fabs(w->at(j, k)) > eps){
                double* params = getRGParameters(w, i, j, k);
                c = params[0];
                s = params[1];
                rotGivens(w, i, j, c, s);
                rotGivens(a, i, j, c, s);
                delete params;
            }
        }
    }

    //std::cout << "Matriz R:";
    //r->print();
    //std::cout << "Matriz blinha:";
    //newB->print();

    for (unsigned k = p; k >= 1; k--) {
        for (unsigned j = 1; j <= m; j++) {
            double aux = 0;
            for (unsigned i = k + 1; i <= p; i++) {
                //std::cout << "k: " << k << " j: " << j << " i: " << i << "\n";
                aux += w->at(k, i) * h->at(i, j);
            }
            
            h->setValue(k, j, (a->at(k, j) - aux)/w->at(k, k));
        }
    }

    return h;
}

Matrix* nonNegativeFactorization(Matrix* a, unsigned m, unsigned p)
{
    if (p > a->getNumberOfColumns() || p > a->getNumberOfLines())
        throw new std::invalid_argument("invalid inner dimension");

    if (m > a->getNumberOfColumns())
        throw new std::invalid_argument("m > colunas(a)");
    
    unsigned n = a->getNumberOfLines();

    Matrix* w  = new Matrix(n, p);
    Matrix* h;  // must be deleted;
    Matrix* wt; // must be deleted;
    Matrix* a2 = new Matrix(n, m); // must be deleted

    for (unsigned i = 1; i <= w->getNumberOfLines(); i++) {
        for (unsigned j = 1; j <= w->getNumberOfColumns(); j++) {
            double random = double(rand() % 9 +1);
            w->setValue(i, j, random);
        }        
    }

    unsigned it = 0;

    while (it < 100) {
        /*------! Criando uma cópia de A !-----*/
        
        //*
        //std::cout << "b\n";
        for(unsigned i = 1; i <= n; i++){
            for(unsigned j = 1; j <= m; j++){
                a2->setValue(i,j, a->at(i,j));
            }
        }
        //*/
        
        /*-------!  Normalização W  !---------*/
        //*
        //std::cout << "c\n";
        for (unsigned j = 1; j <= w->getNumberOfColumns(); j++) {
            double aux = 0;
            
            for (unsigned i = 1; i <= w->getNumberOfLines(); i++) {
                aux += w->at(i, j) * w->at(i, j);
            }
            for (unsigned i = 1; i <= w->getNumberOfLines(); i++) {
                w->setValue(i, j, w->at(i, j)/sqrt(aux));
            }          
        }

        //*/

        /*-----!    MMQ para determinar h     !-----*/
        //std::cout << "d\n";
        h = solveLinearSystems(w, a2);

        /*-----!      Redefinição de h       !------*/
        //*
        //std::cout << "e\n";
        for (unsigned i = 1; i <= h->getNumberOfLines(); i++){
            for(unsigned j = 1; j <= h->getNumberOfColumns(); j++){                
                if(h->at(i,j) < -eps){                
                    h->setValue(i, j, 0); 
                }
            }                
        }
        //*/

        /*-----! Computação de A original transposta  !-----*/
        //reseta os valores de a2 aos da matriz original.
        
        //*
        //std::cout << "f\n";
        for(unsigned i = 1; i <= n; i++){
            for(unsigned j = 1; j <= m; j++){
                a2->setValue(i,j, a->at(i,j));
            }
        }
        //*/

        //std::cout << "g\n";
        a2->transpose();
        
        /*
        Matrix* ht = new Matrix (p, m);
        
        for(unsigned i = 1; i <= p; i++){
            for(unsigned j = 1; j <= m; j++){
                ht->setValue(i,j, h->at(i,j));
            }
        }
        
        ht->transpose();

        //*/

        /*-----!      MMQ das Transpostas    !-----*/
        
        //std::cout << "h\n";
        h->transpose();

        //std::cout << "i\n";
        wt = solveLinearSystems(h, a2);

        //delete ht;
        //delete a2;
        delete h;

        /*-----!      Computação de w        !-----*/
        //std::cout << "j\n";
        wt->transpose(); //Destranspõe W transposta

        delete w;
        w = wt;

        /*-----!     Redefinição de w        !-----*/
        //*
        //std::cout << "k\n";
        for (unsigned i = 1; i <= w->getNumberOfLines(); i++){
            for(unsigned j = 1; j <= w->getNumberOfColumns(); j++){
                if(w->at(i, j) < -eps){
                    w->setValue(i, j, 0); 
                }
            }
        }                
        
        //*/

        //Calculating error
        /*
        Matrix* wxh = (*w) * h;
        double newErr = 0;
        
        for(unsigned i = 1; i <= n; i++){
            for(unsigned j = 1; j <= m; j++){
                //std::cout << "[" << i << "][" << j << "] ";
                double aux = (a->at(i,j) - wxh->at(i,j));
                newErr += aux * aux;
                //std::cout << aux * aux << " " << err << "\n";
            }
        }
        delete wxh;
        //std::cout << "Erro calculado: " << newErr << "\n";

        if (it == 0) {
            err = newErr;
            dErr = 1;
        }
        else {
            //std::cout << err << " - " << newErr << " = " << fabs(err - newErr) << "\n";
            dErr = fabs(err - newErr);
            err = newErr;
        }
        //*/

        a2->transpose();
        it++;

    }

    delete a2;

    return w;
}