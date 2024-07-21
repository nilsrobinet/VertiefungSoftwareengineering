#pragma once
#include <cstdint>
#include <cmath>
#include <array>

template<unsigned long int dim>
using Vector = std::array<float,dim>;

template<unsigned long int dim, uint16_t numVectors>
using VectorList = std::array<Vector<dim>, numVectors>;

template<uint16_t x, uint16_t y>
using Matrix = std::array<std::array<float, y>, x>;

template<uint16_t x, uint16_t y, uint16_t num>
using MatrixList = std::array<Matrix<x,y>, num>;

namespace Eigenface {
    class Math {
    private:
        // helper functions
        static constexpr int max( int a, int b) { if (a > b) return a; else return b;};
    
    public:
        /**
         * Calculate the average vector of a list of vectors
         * @param vectorList list of vectors of which the average shall be provided
         * 
         * @returns average vector
         */
        template <long unsigned int dim, long unsigned int numVectors>
        static std::array<float,dim> averageVector(const VectorList<dim,numVectors>& vectorList ) {
            std::array<float, dim> averageVector;
            averageVector.fill(0);
            for (auto vecIdx = 0U; vecIdx < numVectors; vecIdx++) {
                for (auto elemIdx = 0U; elemIdx < (dim); elemIdx++) {
                    averageVector[elemIdx] += vectorList[vecIdx][elemIdx];
                }
            }
            for (auto elemIdx = 0U; elemIdx < (dim); elemIdx++) {
                averageVector[elemIdx] /= numVectors;
            }
            return averageVector;
        }
    
        /**
         * TODO: move to eigenface specific class
         * Normalize a list of vectors by subtracting another vector
         */
        //template <int dim, int numVectors>
        //static void normalize(VectorList<dim,numVectors>& vectorList, const Vector<dim>& normVec) {
        //     for (auto vectorIndex = 0; vectorIndex < numVectors; vectorIndex++) {
        //        for (auto elemIndex = 0; elemIndex < dim; elemIndex++) {
        //            vectorList[vectorIndex][elemIndex] = vectorList[vectorIndex][elemIndex] - normVec[elemIndex];
        //        }
        //     }
        //}
        
        /*
         * Function to normalize a vector
         * 
         * @param Reference to vector to be normalized
         */
        template<long unsigned int n>
        static void normalize(Vector<n>& vec) {
            float norm = 0.0f;
            for (auto i = 0U; i < n; ++i) {
                norm += vec[i] * vec[i];
            }
            norm = std::sqrt(norm);
            for (auto i = 0U; i < n; ++i) {
                vec[i] /= norm;
            }
        }
    
        /**
         * Transpose a matrix
         * 
         * @returns a new matirx containing the transposed matrix
         */
        template <long unsigned int x, long unsigned int y>
        static Matrix<y,x> transpose(const Matrix<x,y>& mat) {
            Matrix<y,x> mat_T = {0};
            for (auto rowIndex = 0U; rowIndex < x; rowIndex++) {
                for (auto columnIndex = 0U; columnIndex < y; columnIndex++) {
                    mat_T[columnIndex][rowIndex] = mat[rowIndex][columnIndex];
                }
            }
            return mat_T;
        }
    
        /**
         * Multiply two matricies
         *
         * @returns the product of two matricies
         */
        template <long unsigned int x, long unsigned int y,long unsigned int z>
        static Matrix<x,z> matMul(const Matrix<x,y>& mat1, const Matrix<y,z>& mat2) {
            Matrix<x,z> result = {0};
            for (auto i = 0U; i < x; ++i) {
                for (auto k = 0U; k < y; ++k) {
                    float temp = mat1[i][k];
                    for (auto j = 0U; j < z; ++j) {
                        result[i][j] += temp * mat2[k][j];
                    }
                }
            }
            return result;
        }

        // Function to multiply a matrix by a vector
        template<long unsigned int x, long unsigned int y>
        static Vector<x> matMul(const Matrix<x, y>& matrix, const Vector<y>& vec) {
            Vector<x> result;
            for (uint16_t i = 0; i < x; ++i) {
                result[i] = 0;
                for (uint16_t j = 0; j < y; ++j) {
                    result[i] += matrix[i][j] * vec[j];
                }
            }
            return result;
        }
    
    };
}
