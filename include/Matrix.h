#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>


class Matrix
{
public:
    Matrix(unsigned n, unsigned m); // initializes a MxN matrix filled with zeroes.
    Matrix(unsigned n, unsigned m, double initial); // initializes a MxN matrix filled with an initial value.
    Matrix(std::vector<std::vector<double>*>* values); // initializas a matrix with pre established values stored in a vector container.
    Matrix(std::string filePath, unsigned n);
    ~Matrix();

    void print(); // maximum matrix size is 9x9. It is pretty slow.

    void setValue(unsigned n, unsigned m, double newValue);
    void setRow(unsigned n, std::vector<double>* newRow);
    void setColumn(unsigned m, std::vector<double>* newColumn);
    void setValues(std::vector<std::vector<double>*>* newValues);
    
    double at(unsigned n, unsigned m);
    std::vector<double>* getRow(unsigned n);
    std::vector<double>* getColumn(unsigned m);
    std::vector<std::vector<double>*>* getValues();

    unsigned getNumberOfLines();
    unsigned getNumberOfColumns();

    // Operations
    void transpose(); //naive algorithm, O(n²)
   

    Matrix* operator+(Matrix* m);
    Matrix* operator-(Matrix* m);
    Matrix* operator*(Matrix* m); // naive algorithm, O(n³)

    Matrix* operator*(double d);


private:
    unsigned n; // number of lines
    unsigned m; // number of columns

    std::vector<std::vector<double>*>* values;
};

#endif

/**template for the print function:
 * 
 *       1       2       3       4       5       6       7       8       9
 *    ---------------------------------------------------------------                                              _
 *  1| 11.00  22.00  33.00  44.00  55.00  66.00  77.00  88.00  99.00 |
 *  2| 1.00  2.00  3.00  4.00  5.00  6.00  7.00  8.00  9.00 |
 *  3| 1.00  2.00  3.00  4.00  5.00  6.00  7.00  8.00  9.00 |
 *  4| 1.00  2.00  3.00  4.00  5.00  6.00  7.00  8.00  9.00 |
 *  5| 1.00  2.00  3.00  4.00  5.00  6.00  7.00  8.00  9.00 |
 *  6| 1.00  2.00  3.00  4.00  5.00  6.00  7.00  8.00  9.00 |
 *  7| 1.00  2.00  3.00  4.00  5.00  6.00  7.00  8.00  9.00 |
 *  8| 1.00  2.00  3.00  4.00  5.00  6.00  7.00  8.00  9.00 |
 *  9| 11.00  22.00  33.00  44.00  55.00  66.00  77.00  88.00  99.00 |
 *    ---------------------------------------------------------------
**/