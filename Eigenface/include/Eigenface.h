#include <cstdint>

template<uint16_t dim>
using Vector_t = std::array<float,dim>;

template<uint16_t dim, uint16_t numVectors>
using VectorList_t = std::array<Vector_t<dim>, numVectors>;

template<uint16_t x, uint16_t y>
using Image_t = std::array<std::array<float, y>, x>;

template<uint16_t x, uint16_t y, uint16_t numImages>
using ImageList_t = std::array<Image_t<x,y>, numImages>;

class Eigenface {
public:
    /**
     * Calculate the average vector of a list of vectors
     * @param vectorList list of vectors of which the average shall be provided
     * 
     * @returns average vector
     */
    template <int dim, int numVectors>
    static std::array<float,dim> averageVector( VectorList_t<dim,numVectors> vectorList ) {
        std::array<float, dim> averageVector;
        averageVector.fill(0);
        for (int vecIdx = 0; vecIdx < numVectors; vecIdx++) {
            for (int elemIdx = 0; elemIdx < (dim); elemIdx++) {
                averageVector[elemIdx] += vectorList[vecIdx][elemIdx];
            }
        }
        for (int elemIdx = 0; elemIdx < (dim); elemIdx++) {
            averageVector[elemIdx] /= numVectors;
        }
        return averageVector;
    }

    /**
      * Normalize a list of vectors by subtracting another vector
      */
    template <int dim, int numVectors>
    static void normalize(VectorList_t<dim,numVectors>& vectorList, Vector_t<dim>& normVec) {
         for (auto vectorIndex = 0; vectorIndex < numVectors; vectorIndex++) {
            for (auto elemIndex = 0; elemIndex < dim; elemIndex++) {
                vectorList[vectorIndex][elemIndex] - normVec[elemIndex];
            }
         }
    }
    
    //template <uint16_t x, uint16_t y, uint16_t numImages>
    //static void calculateEigenfaces(ImageList_t<x,y,numImages> imageList ){
    //    ;
    //};

};

