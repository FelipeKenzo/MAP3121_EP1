#include "MatrixOp.h"
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
    //unsigned m = a->getNumberOfColumns();

    Matrix* w  = new Matrix(n, p);
    Matrix* h;  //= new Matrix(p, m);
    Matrix* wt; //= new Matrix(p, n);
    Matrix* a2;  // Temporary Object

    //std::cout << "n: " << n << "\n";
    //std::cout << "m: " << m << "\n";
    //std::cout << "p: " << p << "\n";

    //Initializing a random positive w
    //std::cout << "setValue chamado.\n";
    for (unsigned i = 1; i <= w->getNumberOfLines(); i++) {
        for (unsigned j = 1; j <= w->getNumberOfColumns(); j++) {
            double random = double(rand() % 9 +1);
            w->setValue(i, j, random);
        }        
    }


    unsigned it = 0;
    double err = 1;
    double dErr = 1;

    while (it < 100 && dErr > eps) {
        std::cout << "It: " << it << "\n";
        //std::cout << "=== iteracao: " << it << " ===\n";
        //std::cout << "======= erro: " << err << " ===\n";

        /*------! Criando uma cópia de A !-----*/
        //std::cout << "setValue chamado (copia de A).\n";
        //std::cout << "n: " << n << "\n";
        //std::cout << "n(A): " << a2->getNumberOfLines() << "\n";
        
        auto c_start = std::chrono::high_resolution_clock::now();
        a2 = new Matrix(n, m);
        
        for(unsigned i = 1; i <= n; i++){
            for(unsigned j = 1; j <= m; j++){
                a2->setValue(i,j, a->at(i,j));
            }
        }
        //auto c_finish = std::chrono::high_resolution_clock::now();
        //std::chrono::duration<double> c_elapsed = c_finish - c_start;

        //std::cout << "Copy time: " << c_elapsed.count() << "\n";

        /*-------!  Normalização W  !---------*/
        //std::cout << "setValue chamado.\n";
        for (unsigned j = 1; j <= w->getNumberOfColumns(); j++) {
            double aux = 0;
            
            for (unsigned i = 1; i <= w->getNumberOfLines(); i++) {
                aux += w->at(i, j) * w->at(i, j);
            }
            for (unsigned i = 1; i <= w->getNumberOfLines(); i++) {
                w->setValue(i, j, w->at(i, j)/sqrt(aux));
            }          
        }

        /*-----!    MMQ para determinar h     !-----*/
        h = solveLinearSystems(w, a2);
        //std::cout << "n(A): " << a2->getNumberOfLines() << "\n";

        //std::cout << "Matriz H:";
        //h->print();

        /*-----!      Redefinição de h       !------*/
        //std::cout << "setValue chamado.\n";
        for (unsigned i = 1; i <= h->getNumberOfLines(); i++){
            for(unsigned j = 1; j <= h->getNumberOfColumns(); j++){                
                if(h->at(i,j) < -eps){                
                    h->setValue(i, j, 0); 
                }
            }                
        }

        //std::cout << "Matriz H Redefinida:";
        //h->print();

        /*-----! Computação de A transposta  !-----*/
        //reseta os valores de a2 aos da matriz original.
        //std::cout << "setValue chamado.\n";
        for(unsigned i = 1; i <= n; i++){
            for(unsigned j = 1; j <= m; j++){
                a2->setValue(i,j, a->at(i,j));
            }
        }

        a2->transpose();

        //std::cout << "Matriz A Transposta:";
        //a2->print();

        //std::cout << "Matriz H Transposta:";
        
        Matrix* ht = new Matrix (p, m);
        
        //std::cout << "setValue chamado.\n";
        for(unsigned i = 1; i <= p; i++){
            for(unsigned j = 1; j <= m; j++){
                ht->setValue(i,j, h->at(i,j));
            }
        }
        
        ht->transpose();
        //ht->print();

        /*-----!      MMQ das Transpostas    !-----*/
        wt = solveLinearSystems(ht, a2);

        delete ht;


        //std::cout << "Matriz W Transposta: (Encontrada pelo MMQ)";
        //wt->print();

        /*-----!      Computação de w        !-----*/
        wt->transpose();
        
        //std::cout << "Wt transposta:";
        //wt->print();


        delete w;
        delete a2;
        w = wt;

        //w->print();

        /*-----!     Redefinição de w        !-----*/
        //std::cout << "setValue chamado.\n";
        for (unsigned i = 1; i <= w->getNumberOfLines(); i++){
            for(unsigned j = 1; j <= w->getNumberOfColumns(); j++){
                //std::cout << "[" << i << "][" << j << "]\n";
                if(w->at(i, j) < -eps){
                    //std::cout << w->at(i, j) << "\n";
                    w->setValue(i, j, 0); 
                }
            }                
        
        //Calculating error
        //*
        err = 0;

        Matrix* wxh = (*w) * h;

        //a->print();
        //wxh->print();

        
        for(unsigned i = 1; i <= n; i++){
            for(unsigned j = 1; j <= m; j++){
                //std::cout << "[" << i << "][" << j << "] ";
                double aux = (a->at(i,j) - wxh->at(i,j));
                err += aux * aux;
                //std::cout << aux * aux << " " << err << "\n";
            }
        }
        delete wxh;
        }

        dErr = fabs(dErr - err);
        std::cout << "dErr: " << dErr << "\n";

        //std::cout << "Matriz W redefinida";
        //w->print();   

        //*/

        delete h;

        it++;

        //if (it < 100 || err < eps)
            //delete h;
    }

    //std::cout << "Resultado\n\n";

    //std::cout << "Iteracoes: " << it << "\n";
    //std::cout << "Erro: " << err << "\n\n";

    //std::cout << "Matriz H:\n";
    //h->print();

    //std::cout << "Matriz W:\n";
    //w->print();

    //std::cout << "Matriz W * H:\n";
    //((*w) * h)->print();


    return w;
}