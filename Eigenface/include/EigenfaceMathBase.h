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
    /**
    * @brief this module shall provide some simple helper functions for working with matricies and vectors
    */
    class Math {
    private:
        // helper functions
        static constexpr int max( int a, int b) { if (a > b) return a; else return b;};

    public:
        /**
         * @brief Calculate the average vector of a list of vectors
         *
         * @tparam dim dimesion of the vectors
         * @tparam numVectors number of vectors in the input
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

        /*
         * @brief Function to normalize a vector
         *
         * @tparam dim dimesion of the vectors
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
         * @brief Transpose a matrix
         *
         * @tparam x dimension of the matrix
         * @tparam y dimension of the matrix
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
         * @brief Multiply two matricies
         *
         * @tparam x X-Dimension of the first input matrix
         * @tparam y Y-Dimension of the firs input matrix and X-Dimension of the second input matrix
         * @tparam z Y-Dimension of the second input matrix
         * @param mat1 first input matrix
         * @param mat2 second input matrix
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

        /**
         * @brief multiply a matrix by a vector
         *
         * @tparam x X-Dimension of the matrix
         * @tparam y Y-Dimension of the matrix and dimension of the vector
         * @param matrix matrix input
         * @param vec vector input
         *
         * @returns the vector that is the result of the multiplication
         */
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
