#pragma once
#include "EigenfaceMathBase.h"
#include "EigenfaceEigenvectorFinder.h"
#include <cstdint>

namespace Eigenface {
    /**
    * @brief Class whose members shall provide all functionality needed to implement and use the Eigenface algorithm
    *
    * The implementation shall be based on:
    * Matthew Turk, Alex Pentland; Eigenfaces for Recognition. J Cogn Neurosci 1991; 3 (1): 71–86. 
    * doi: https://doi.org/10.1162/jocn.1991.3.1.71
    */
    class Eigenface {
    private:
    public:
        //! X dimension of the face images
        static constexpr uint32_t dimX = 256; 
        //! Y dimension of the face images
        static constexpr uint32_t dimY = 256; 
        //! batch size for processing the face images
        static constexpr uint32_t batchSize = 8; 
        
        Eigenface();
        ~Eigenface() {};
        
        /**
         * @brief Get the average face in a batch of faces.
         * 
         * This Function takes in C-Style arrays to make it more straitforward to write a cython wrapper for use from 
         * python code.
         *
         * @param faces batch of faces of which the average shall be calculated
         * @param avgFace buffer for returning the average Face
         */
        void getAverageFace(float faces[dimX*dimY*batchSize], float avgFace[dimX*dimY]);
    };
}
