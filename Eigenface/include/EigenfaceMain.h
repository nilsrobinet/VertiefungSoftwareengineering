#pragma once
#include "EigenfaceMathBase.h"
#include "EigenfaceEigenvectorFinder.h"
#include <cstdint>

namespace Eigenface {
    class Eigenface {
    private:
    public:
        static constexpr uint32_t dimX = 256;
        static constexpr uint32_t dimY = 256;
        static constexpr uint32_t batchSize = 8;
        
        Eigenface();
        ~Eigenface() {};

        //Matrix<dimX,dimY> getAverageFace(MatrixList<dimX,dimY,8> faces);
        //Vector<dimX*dimY> getAverageFace(float faces[dimX*dimY*batchSize]); // for calling from cython
        void getAverageFace(float faces[dimX*dimY*batchSize], float avgFace[dimX*dimY]);
    };
}
