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

    //Matrix<Eigenface::dimX,Eigenface::dimY> Eigenface::getAverageFace(MatrixList<Eigenface::dimX,Eigenface::dimY,8> //faces) {
    //    auto facesFlat = *reinterpret_cast<VectorList<Eigenface::dimX*Eigenface::dimY, 8>*>(&faces);
    //    auto averageVec = Math::averageVector(facesFlat);
    //    return *reinterpret_cast<Matrix<Eigenface::dimX, Eigenface::dimY>*>(&averageVec);
    //}
    //void Eigenface::getAverageFace(float faces[dimX*dimY*batchSize], float avgFace[dimX*dimY]) {
    //    auto facesFlat = *reinterpret_cast<VectorList<dimX*dimY,batchSize>*>(faces);
    //    auto tmp = Math::averageVector(facesFlat);
    //    for (auto i = 0U; i< tmp.size(); i++) {
    //        avgFace[i] = tmp[i];
    //    }
    //}
    //Vector<dimX*dimY> Eigenface::getAverageFace(float faces[dimX*dimY*batchSize]) {
    //    auto facesFlat = *reinterpret_cast<VectorList<dimX*dimY,batchSize>*>(faces);
    //    return Math::averageVector(facesFlat);
    //}    
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
