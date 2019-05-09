#include "MatrixPersistence.h"

void save(std::string filePath, Matrix* w) {
    
    std::ofstream output;
    output.open(filePath, std::ios::trunc);

    if (output.fail()) {
        throw new std::runtime_error("File writing failed.");
    }
    
    for (unsigned i = 1; i <= w->getNumberOfLines(); i++) {
        for (unsigned j = 1; j <= w->getNumberOfColumns(); i++) {
            output << w->at(i, j);
            if (j < w->getNumberOfColumns()) {
                output << " ";
            }
        }
        output << "\n";
    }
}

Matrix* load(std::string filePath, unsigned n, unsigned m) {
    std::ifstream input;
    input.open(filePath);
    
    //allocates necessary space
    Matrix* w = new Matrix(n, m);

    double data = 0;
    unsigned i = 0;
    while (i < n && input.good()) {
        if (input.fail())
            break;
        
        for (unsigned j = 1; j <= m; j++) {
            input >> data;
            w->setValue(i, j, data);
        }

        i++;
    }

    input.close();

    return w;
}

Matrix* load(std::string filePath, unsigned n) {
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

    input.close();

    return load(filePath, n, columnCount);
}
    
Matrix* load(std::string filePath) {
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

    while (input.good()) {
        std::getline(input, firstLine);
        lineCount++;
    }

    return load(filePath, lineCount, columnCount);
}
