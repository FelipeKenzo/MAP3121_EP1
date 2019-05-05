#include "Matrix.h"
#define eps 1e-6

Matrix::Matrix(unsigned n, unsigned m) :
    n(n), m(m)
{
    values = new std::vector<std::vector<double>*>();
    values->resize(n);
    for (unsigned i = 0; i < values->size(); i++)
    {
        (*values)[i] = new std::vector<double>();
        (*values)[i]->resize(m, 0);
    }
}

Matrix::Matrix(unsigned n, unsigned m, double initial) :
    n(n), m(m)
{
    values = new std::vector<std::vector<double>*>();
    values->resize(n);
    for (unsigned i = 0; i < values->size(); i++)
    {
        (*values)[i] = new std::vector<double>();
        (*values)[i]->resize(m, initial);
    }
}

Matrix::Matrix(std::vector<std::vector<double>*>* values)
{
    if (values->size() < 1)
    {
        throw new std::length_error("Dimensional error");
    }

    unsigned max_size = 0;

    for (unsigned i = 0; i < values->size(); i++)
    {
        if ((*values)[i]->size() > max_size)
        {
            max_size = (*values)[i]->size();
        }

        if (max_size == 0)
        {
            throw new std::length_error("Dimensional_error");
        }
    }

    for (unsigned i = 0; i < values->size(); i++) {
        if ((*values)[i]->size() < max_size)
        {
            (*values)[i]->resize(max_size, 0);
        }
    }

    this->values = values;
    n = values->size();
    m = max_size;
}

Matrix::~Matrix()
{
    for (unsigned i = 0; i < values->size(); i++)
    {
        delete (*values)[i];
    }

    delete values;
}

void Matrix::print()
{
    if (m < 1 || n < 1)
        throw new std::length_error("Dimensional error");

    unsigned msd = 0;
    for (unsigned i = 0; i < n; i++)
    {
        for (unsigned j = 0; j < m; j++)
        {
            unsigned base10 = 0;
            int aux = fabs((*(*values)[i])[j]);
            while (aux > 0)
            {
                aux = aux/10;
                if (aux != 0)
                {
                    base10++;
                }
            }

            if (base10 > msd)
            {
                msd = base10;
            }
        }
    }

    // column indexes
    /*
    std::cout << "\n       0";

    for (unsigned i = 1; i < m; i++)
    {
        for (unsigned j = 0; j < msd; j++)
        {
            std::cout << " ";
        }
        std::cout << "     " << i;
    }

    //upper border
    std::cout << "\n    ";

    for (unsigned i = 0; i < m; i++)
    {
        for (unsigned j = 0; j < msd; j++)
        {
            std::cout << "-";
        }

        std::cout << "------";
    }

    */
    std::cout << "\n";

    // row indexes and actual values
    for (unsigned i = 0; i < n; i++)
    {
        //std::cout << "  " << i << "|";
        std::cout << "|";

        for (unsigned j = 0; j < m; j++)
        {
            
                if ((*(*values)[i])[j] > 0 || fabs((*(*values)[i])[j]) < eps) {
                    std::cout << " ";
                }

            //std::cout << (*(*values)[i][j])/pow(10, msd) << "\n";
            if (fabs((*(*values)[i])[j])/pow(10, msd) < 1){
                unsigned base10 = 0;
                int aux = fabs((*(*values)[i])[j]);
                while (aux > 0)
                {
                    aux = aux/10;
                    if (aux != 0)
                    {
                        base10++;
                    }
                }
                
                for (base10 = msd - base10; base10 > 0; base10--)
                {
                    std::cout << " ";
                }
            }


            if (fabs((*(*values)[i])[j]) < eps) {
                //std::cout << fabs((*(*values)[i][j])) << " eh zero->\n";
                std::cout << "0.000000 ";    
            }
            else {
                std::cout << std::fixed
                        << std::setprecision(6) 
                        << (*(*values)[i])[j] << " ";
            }
        }

        std::cout << "|";

        if (i != n-1)
        {
            std::cout << "\n";
        }
    }

    /*
    //lower border
    std::cout << "\n    ";

    for (unsigned i = 0; i < m; i++)
    {
        for (unsigned j = 0; j < msd; j++)
        {
            std::cout << "-";
        }
        std::cout << "------";
    }
    */
    
    std::cout << "\n\n";
}

void Matrix::setValue(unsigned n, unsigned m, double newValue)
{
    if (n > this->n || m > this->m)
    {
        std::cout << "Erro acessando w[" << n << "][" << m << "]\n";
        throw new std::range_error("Invalid index");
    }

    (*(*values)[n-1])[m-1] = newValue;
}
void Matrix::setRow(unsigned n, std::vector<double>* newRow)
{
    (*values)[n-1] = newRow;

    if (newRow->size() < m)
    {
        (*values)[n-1]->resize(m, 0);
    }
    else if (newRow->size() > m)
    {
        for (unsigned i = 0; i < n-1; i++)
        {
            (*values)[i]->resize(newRow->size(), 0);
        }

        m = newRow->size();
    }
}

void Matrix::setColumn(unsigned m, std::vector<double>* newColumn)
{
    if (newColumn->size() != n)
    {
        throw new std::invalid_argument("Dimensional error");
    }

    for (unsigned i = 0; i < n; i++)
    {
        (*(*values)[i])[m-1] = (*newColumn)[i];
    }
}

double Matrix::at(unsigned n, unsigned m)
{
    return (*(*values)[n-1])[m-1];
}

std::vector<double>* Matrix::getRow(unsigned n)
{
    return (*values)[n-1];
}

std::vector<double>* Matrix::getColumn(unsigned m)
{
    std::vector<double>* column;

    for (unsigned i = 0; i < n; i++)
    {
        column->push_back((*(*values)[i])[m-1]);
    }

    return column;
}

std::vector<std::vector<double>*>* Matrix::getValues()
{
    return values;
}

unsigned Matrix::getNumberOfLines()
{
    return n;
}

unsigned Matrix::getNumberOfColumns()
{
    return m;
}

void Matrix::transpose()
{
    Matrix transposed(m, n);

    for (unsigned i = 0; i < n; i++)
    {
        for (unsigned j = 0; j < m; j++)
        {
            transposed.setValue(j, i, (*(*values)[i])[j]);
        }
    }

    delete values;
    values = transposed.getValues();

    return;
}



Matrix* Matrix::operator+(Matrix* M)
{
    if (M->getNumberOfLines() != n || M->getNumberOfColumns() != m)
        throw new std::invalid_argument("incompatible dimensions");

    Matrix* sum = new Matrix(n, m);// = new Matrix(n, m);

    for (unsigned i = 0; i < n; i++)
    {
        for (unsigned j = 0; j < m; j++)
        {
            sum->setValue(i, j, (*(*values)[i])[j] + M->at(i, j));
        }
    }

    return sum;
}
    
Matrix* Matrix::operator-(Matrix* M)
{
    if (M->getNumberOfLines() != n || M->getNumberOfColumns() != m)
    {
        throw new std::invalid_argument("incompatible dimensions");
    }

    Matrix* sub = new Matrix(n, m);// = new Matrix(n, m);

    for (unsigned i = 0; i < n; i++)
    {
        for (unsigned j = 0; j < m; j++)
        {
            sub->setValue(i, j, (*(*values)[i])[j] - M->at(i, j));
        }
    }

    return sub;
}

Matrix* Matrix::operator*(Matrix* m)
{
    if (this->m != m->getNumberOfLines())
    {
        throw new std::invalid_argument("incompatible dimensions");
    }

    Matrix* mult = new Matrix(n, m->getNumberOfColumns());

    for (unsigned i = 0; i < mult->getNumberOfLines(); i++)
    {
        for (unsigned j = 0; j < mult->getNumberOfColumns(); j++)
        {
            double sum = 0;
            for (unsigned k = 0; k < this->m; k++)
            {
                //std::cout << "left[" << i << "][" << k << "] * "
                //         << "right[" << k << "][" << j << "]\n";
                sum += (*(*values)[i])[k] * m->at(k, j);
            }
            mult->setValue(i, j, sum);
        }
    }
    
    return mult;
}

Matrix* Matrix::operator*(double d)
{
    Matrix* mult = new Matrix(n, m);

    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < m; j++) {
            mult->setValue(i, j, (*(*values)[i])[j] * d);
        }
    }

    return mult;
}

