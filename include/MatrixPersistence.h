#ifndef MATRIXPERSISTENCE_H
#define MATRIXPERSISTANCE_H

#include <string>
#include <fstream>
#include <stdexcept>

#include "../include/Matrix.h"

class MatrixPersistence {
public:
    MatrixPersistence();
    ~MatrixPersistence();

    void save(std::string filePath, Matrix* w);

    Matrix* load(std::string filePath, unsigned n, unsigned m);
    Matrix* load(std::string filePath, unsigned n);
    Matrix* load(std::string filePath);

private:

};

#endif