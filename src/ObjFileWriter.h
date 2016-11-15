/*
 * ObjFileWriter.h
 * Henry Chang
 */

#ifndef OBJFILEWRITER_H
#define OBJFILEWRITER_H

#include "ColoredVertexMatrix.h"
#include "stdlib.h"
#include <ofstream>
#include <vector>

using namespace std;

class ObjFileWriter{
private:
	ColoredVertexMatrix * CoordinateMatrix;
    ColoredVertex * Coordinate;
    ofstream objFile;
    int vertexLabel;
    
    // Helper Methods
    ColoredVertexMatrix & normalizeVertices(ColoredVertexMatrix & CoordinateMap);
    void printVerticesToFile(ColoredVertexMatrix & CoordinateMap);

public:
    ObjFileWriter();
    ~ObjFileWriter();

    ColoredVertexMatrix & initiliaze(string fileName, ColoredVertexMatrix & CoordinateList);
    void execute(string fileName, ColoredVertexMatrix & CoordinateList);
    
}

#endif //OBJFILEWRITER_H