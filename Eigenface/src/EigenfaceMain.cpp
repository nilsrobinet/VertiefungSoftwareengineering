#include "EigenfaceMain.h"
#include <cstring>
#include <iostream>

namespace Eigenface {
    constexpr auto dimX = Eigenface::dimX;
    constexpr auto dimY = Eigenface::dimY;
    constexpr auto batchSize= Eigenface::batchSize;
    
    Eigenface::Eigenface() {
        // TODO
    }

    void Eigenface::getAverageFace(float faces[dimX*dimY*batchSize], float avgFace[dimX*dimY]) {
        if (!faces || !avgFace) {
            std::cerr << "Null pointer provided to getAverageFace." << std::endl;
            return;
        }
        auto facesFlat = *reinterpret_cast<VectorList<dimX*dimY, batchSize>*>(faces);
        auto tmp = Math::averageVector(facesFlat);
        std::memcpy(avgFace, tmp.data(), dimX * dimY * sizeof(float));
    }
    
    void Eigenface::getDeviationFromAverageFace(float faces[dimX*dimY*batchSize]){
        float avgFace[dimX*dimY];
        this->getAverageFace(faces,avgFace);
        //float facesIterable[dimX][dimY][batchSize] = faces;
        for (auto i = 0U; i < batchSize; i++) {
            for (auto x = 0U; x < dimX; x++){
                for (auto y = 0U; y < dimY; y++){
                    // Dangerous pointer arithmetic
                    faces[x*dimX+y+i*batchSize] = faces[x*dimX+y+i*batchSize] - avgFace[x*dimX+y];
                    //facesIterable[x][y][i] = facesIterable[x][y][i] - avgFace[x][y];
                }
            }
        }
    }
}
