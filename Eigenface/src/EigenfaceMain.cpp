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
}
