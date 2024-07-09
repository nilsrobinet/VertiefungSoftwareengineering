#include <cstdint>

template<uint16_t dim>
using Vector_t = std::array<float,dim>;

template<uint16_t dim, uint16_t numVectors>
using VectorList_t = std::array<Vector_t<dim>, numVectors>;

template<uint16_t x, uint16_t y>
using Matrix_t = std::array<std::array<float, y>, x>;

template<uint16_t x, uint16_t y, uint16_t numImages>
using MatrixList_t = std::array<Matrix_t<x,y>, numImages>;

class Eigenface {
public:
    /**
     * Calculate the average vector of a list of vectors
     * @param vectorList list of vectors of which the average shall be provided
     * 
     * @returns average vector
     */
    template <int dim, int numVectors>
    static std::array<float,dim> averageVector(const VectorList_t<dim,numVectors>& vectorList ) {
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
    static void normalize(VectorList_t<dim,numVectors>& vectorList, const Vector_t<dim>& normVec) {
         for (auto vectorIndex = 0; vectorIndex < numVectors; vectorIndex++) {
            for (auto elemIndex = 0; elemIndex < dim; elemIndex++) {
                vectorList[vectorIndex][elemIndex] = vectorList[vectorIndex][elemIndex] - normVec[elemIndex];
            }
         }
    }

    /**
      * Transpose a matrix
      * 
      * @returns a new matirx containing the transposed matrix
      */
    template <int x, int y>
    static Matrix_t<y,x> transpose(const Matrix_t<x,y>& mat) {
        Matrix_t<y,x> mat_T = {0};
        for (auto rowIndex = 0; rowIndex < x; rowIndex++) {
            for (auto columnIndex = 0; columnIndex < y; columnIndex++) {
                mat_T[columnIndex][rowIndex] = mat[rowIndex][columnIndex];
            }
        }
        return mat_T;
    }

};

