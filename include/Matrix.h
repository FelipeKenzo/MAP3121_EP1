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
#include <fstream>


class Matrix
{
public:
    Matrix(unsigned n, unsigned m); // Inicializa a matriz com zeros
    Matrix(unsigned n, unsigned m, double initial); // Inicializa a matriz tamanho N x M com um valor inicial.
    Matrix(std::vector<std::vector<double>*>* values); // Inicializa a matriz com valores preestabelecidos em um vector.
    Matrix(std::string filePath, unsigned n); // Inicializa uma matriz com 748 x n a partir de um arquivo
    ~Matrix();

    void print(unsigned precision); // Tamanho máximo 9x9. Bem lento
    void saveAsVectors(const std::string& filePath);

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

    // Operações
    void transpose(); //naive algorithm, O(n²)
   

    Matrix* operator+(Matrix* m);
    Matrix* operator-(Matrix* m);
    Matrix* operator*(Matrix* m); // naive algorithm, O(n³)

    Matrix* operator*(double d);


private:
    unsigned n; // Número de linhas
    unsigned m; // Número de Colunas

    std::vector<std::vector<double>*>* values;
};

#endif
