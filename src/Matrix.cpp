#include "Matrix.h";

Matrix::Matrix(unsigned n, unsigned m) :
    n(n), m(m)
{
    values.resize(n);
    for (unsigned i = 0; i < values.size(); i++)
    {
        values[i].resize(m, 0);
    }
}

Matrix::Matrix(unsigned n, unsigned m, double initial) :
    n(n), m(m)
{
    values.resize(n);
    for (unsigned i = 0; i < values.size(); i++)
    {
        values[i].resize(m, initial);
    }
}

Matrix::Matrix(std::vector<std::vector<double>> values)
{
    if (values.size() < 1)
    {
        throw new std::length_error("Dimensional error");
    }

    unsigned max_size = 0;

    for (unsigned i = 0; i < values.size(); i++)
    {
        if (values[i].size() > max_size)
        {
            max_size = values[i].size();
        }

        if (max_size == 0)
        {
            throw new std::length_error("Dimensional_error");
        }
    }

    for (unsigned i = 0; i < values.size(); i++) {
        if (values[i].size() < max_size)
        {
            values[i].resize(max_size, 0);
        }
    }

    this->values = values;
    n = values.size();
    m = max_size;
}

Matrix::~Matrix()
{
    //dtor
}

void Matrix::print()
{
    if (m < 1 || n < 1)
        throw new std::length_error("Dimensional error");

    // column indexes
    std::cout << "\n       1";

    for (unsigned i = 2; i <= m; i++)
    {
        std::cout << "     " << i;
    }

    //upper border
    std::cout << "\n    ";
    
    for (unsigned i = 0; i < m; i++)
    {
        std::cout << "------";
    }

    std::cout << "\n";

    // row indexes and actual values
    for (unsigned i = 1; i <= n; i++)
    {
        std::cout << "  " << i << "|";

        for (unsigned j = 0; j < m; j++)
        {
            std::cout << " " << std::fixed << std::setprecision(2) << values[i-1][j] << " ";
        }

        std::cout << "|";

        if (i != n)
        {
            std::cout << "\n";
        }
    }

    //lower border
    std::cout << "\n    ";

    for (unsigned i = 0; i < m; i++)
    {
        std::cout << "------";
    }
    
    std::cout << "\n\n";
}

void Matrix::setValue(unsigned n, unsigned m, double newValue)
{
    if (n > this->n || m > this->m)
    {
        throw new std::range_error("Invalid index");
    }

    values[n][m] = newValue;
}
void Matrix::setRow(unsigned n, std::vector<double> newRow)
{
    values[n] = newRow;

    if (newRow.size() < m)
    {
        values[n].resize(m, 0);
    }
    else if (newRow.size() > m)
    {
        for (unsigned i = 0; i < n; i++)
        {
            values[i].resize(newRow.size(), 0);
        }

        m = newRow.size();
    }
}

void Matrix::setColumn(unsigned n, std::vector<double> newColumn)
{

}

double Matrix::getValue(unsigned n, unsigned m)
{
    return values[n][m];
}

std::vector<double> Matrix::getRow(unsigned n)
{
    return (values[n]);
}

std::vector<double> Matrix::getColumn(unsigned m)
{
    std::vector<double> column;

    for (unsigned i = 0; i < n; i++)
    {
        column.push_back(values[i][m]);
    }

    return column;
}

std::vector<std::vector<double>> Matrix::getValues()
{
    return values;
}

unsigned Matrix::getRowDimension()
{
    return n;
}

unsigned Matrix::getColumnDimension()
{
    return m;
}

Matrix* Matrix::transpose()
{
    Matrix* transposed = new Matrix(m, n);

    for (unsigned i = 0; i < n; i++)
    {
        for (unsigned j = 0; j < m; j++)
        {
            std::cout << i << ", " << j << std::endl;
            transposed->setValue(j, i, values[i][j]);
        }
    }
}

Matrix Matrix::operator+(Matrix M)
{
    if (M.getRowDimension() != n || M.getColumnDimension() != m)
        throw new std::invalid_argument("incompatible dimensions");

    Matrix sum(n, m);// = new Matrix(n, m);

    for (unsigned i = 0; i < n; i++)
    {
        for (unsigned j = 0; j < m; j++)
        {
            sum.setValue(i, j, values[i][j] + M.getValue(i, j));
        }
    }

    return sum;
}
    
Matrix Matrix::operator-(Matrix M)
{
    if (M.getRowDimension() != n || M.getColumnDimension() != m)
    {
        throw new std::invalid_argument("incompatible dimensions");
    }

    Matrix sub(n, m);// = new Matrix(n, m);

    for (unsigned i = 0; i < n; i++)
    {
        for (unsigned j = 0; j < m; j++)
        {
            sub.setValue(i, j, values[i][j] - M.getValue(i, j));
        }
    }

    return sub;
}

Matrix Matrix::operator*(Matrix m)
{
    if (this->m != m.getRowDimension())
    {
        throw new std::invalid_argument("incompatible dimensions");
    }

    Matrix mult(n, m.getColumnDimension());//= new Matrix (n, m->getColumnDimension());
    
    for (unsigned i = 0; i < mult.getRowDimension(); i++)
    {
        for (unsigned j = 0; j < mult.getColumnDimension(); j++)
        {
            double sum = 0;
            for (unsigned k = 0; k < this->m; k++)
            {
                sum += values[i][k] * m.getValue(i, j);
            }
        }
    }
    
    return mult;
}