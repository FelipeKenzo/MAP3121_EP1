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

Matrix::Matrix(std::string filePath, unsigned n) {
    
    values = new std::vector<std::vector<double>*>();

    std::ifstream input;
    input.open(filePath);
    
    unsigned lineCount = 0;
    unsigned columnCount = 0;

    //counts number of columns
    std::string firstLine;
    std::getline(input, firstLine);
    
    for (unsigned i = 0; i < firstLine.size(); i++) {
        if (isdigit(firstLine[i]))
            columnCount++;
    }

    std::cout << columnCount << "\n";

    //allocates necessary space
    values->resize(n);
    for (unsigned i = 0; i < values->size(); i++)
    {
        (*values)[i] = new std::vector<double>();
        (*values)[i]->resize(columnCount, 0);
    }

    this->n = n;
    this->m = columnCount;

    //ifstream "reset"
    input.clear();
    input.seekg(0, std::ios::beg);

    double data = 0;
    unsigned i = 0;
    while (i < n && input.good()) {
        if (input.fail())
            break;
        
        for (unsigned j = 0; j < columnCount; j++) {
            input >> data;
            (*(*values)[i])[j] = data;
        }

        i++;
    }


    input.close();
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

    //Para saber o numero com mais algarismos
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

    std::cout << "\n";

    for (unsigned i = 0; i < n; i++)
    {
        std::cout << "|";

        for (unsigned j = 0; j < m; j++)
        {
            //Reserva um espaco para o "-"
            if ((*(*values)[i])[j] > 0 || fabs((*(*values)[i])[j]) < eps) {
                std::cout << " ";
            }

            //Pula casas se com menos casas que o maior numero
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

            //Resolver o zero negativo
            if (fabs((*(*values)[i])[j]) < eps) {
                std::cout << "0.000000 ";    
            }
            //imprime o valor com precisao de 6 casas decimais
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
        for (unsigned i = 0; i < n; i++)
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

void Matrix::setValues(std::vector<std::vector<double>*>* newValues){
    delete values;
    
    values = newValues;
    n = newValues->size();
    m = (*newValues)[0]->size();
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
    std::vector<std::vector<double>*>* tValues= new std::vector<std::vector<double>*>();
    tValues->resize(m);

    for (unsigned i = 0; i < m; i++) {
        (*tValues)[i] = new std::vector<double>();
        (*tValues)[i]->resize(n);
    }

    for (unsigned i = 0; i < n; i++)
    {
        for (unsigned j = 0; j < m; j++)
        {
            (*(*tValues)[j])[i] = (*(*values)[i])[j];
        }
    }

    delete values;
    values = tValues;

    unsigned aux = m;
    m = n;
    n = aux;

    return;
}



Matrix* Matrix::operator+(Matrix* M)
{
    if (M->getNumberOfLines() != n || M->getNumberOfColumns() != m)
        throw new std::invalid_argument("incompatible dimensions");

    Matrix* sum = new Matrix(n, m);// = new Matrix(n, m);

    for (unsigned i = 1; i <= n; i++)
    {
        for (unsigned j = 1; j <= m; j++)
        {
            sum->setValue(i, j, (*(*values)[i-1])[j-1] + M->at(i, j));
        }
    }

    return sum;
}
    
Matrix* Matrix::operator-(Matrix* M)
{
    //std::cout << n << " x " << m << " - " << M->getNumberOfLines() << " x " << M->getNumberOfColumns() << "\n";
    if (M->getNumberOfLines() != n || M->getNumberOfColumns() != m)
    {
        throw new std::invalid_argument("incompatible dimensions");
    }

    Matrix* sub = new Matrix(n, m);// = new Matrix(n, m);

    for (unsigned i = 1; i <= n; i++)
    {
        for (unsigned j = 1; j <= m; j++)
        {
            sub->setValue(i, j, (*(*values)[i-1])[j-1] - M->at(i, j));
        }
    }

    return sub;
}

Matrix* Matrix::operator*(Matrix* m)
{
    //std:: cout << this->m << " e " << m->getNumberOfLines() << "\n";
    if (this->m != m->getNumberOfLines())
    {
        throw new std::invalid_argument("incompatible dimensions");
    }

    Matrix* mult = new Matrix(n, m->getNumberOfColumns());

    //std::cout << "Multiplicação eh " << n << " x " << mult->getNumberOfColumns() << "\n";

    for (unsigned i = 1; i <= mult->getNumberOfLines(); i++)
    {
        for (unsigned j = 1; j <= mult->getNumberOfColumns(); j++)
        {
            double sum = 0;
            for (unsigned k = 1; k <= this->m; k++)
            {
                //std::cout << "left[" << i << "][" << k << "] * "
                //         << "right[" << k << "][" << j << "]\n";
                sum += (*(*values)[i-1])[k-1] * m->at(k, j);
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

