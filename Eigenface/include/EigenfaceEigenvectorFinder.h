#include "EigenfaceMathBase.h"

namespace Eigenface {
    class EigenvectorFinder {
    public: 
        /**
         * Function to orthogonalize a set of vectors using Gram-Schmidt process
         */
        template<long unsigned int n, long unsigned int m>
        static void gramSchmidtOrthogonalization(Matrix<n, m>& vectors) {
            for (uint16_t i = 0; i < m; ++i) {
                for (uint16_t j = 0; j < i; ++j) {
                    float dotProduct = 0.0f;
                    for (uint16_t k = 0; k < n; ++k) {
                        dotProduct += vectors[k][i] * vectors[k][j];
                    }
                    for (uint16_t k = 0; k < n; ++k) {
                        vectors[k][i] -= dotProduct * vectors[k][j];
                    }
                }
                Math::normalize(vectors[i]);
            }
        }
        
        /**
         * Function to find the M most significant eigenvalues and eigenvectors using Orthogonal Iteration
         */
        template<long unsigned int n, long unsigned int m>
        static std::pair<std::array<float, m>, Matrix<n, m>> orthogonalIteration(const Matrix<n, n>& matrix, uint16_t maxIterations = 1000, float tolerance = 1e-6) {
        VectorList<n, m> vectors = {0};
            for (uint16_t i = 0; i < m; ++i) {
                vectors[i][i] = 1.0f; // Initial guess for the eigenvectors
            }
        
            for (uint16_t iteration = 0; iteration < maxIterations; ++iteration) {
                // Multiply the matrix by the current set of vectors
                Matrix<n, m> newVectors = {0};
                for (uint16_t i = 0; i < m; ++i) {
                    auto columnVector = Math::multiplyMatrixVector(matrix, vectors[i]);
                    for (uint16_t j = 0; j < n; ++j) {
                        newVectors[j][i] = columnVector[j];
                    }
                }
        
                // Orthogonalize and normalize the resulting vectors
                gramSchmidtOrthogonalization(newVectors);
        
                // Check for convergence
                float diff = 0.0f;
                for (uint16_t i = 0; i < n; ++i) {
                    for (uint16_t j = 0; j < m; ++j) {
                        diff += std::fabs(newVectors[i][j] - vectors[i][j]);
                    }
                }
                if (diff < tolerance) {
                    break;
                }
        
                vectors = newVectors;
            }
        
            // Compute the Rayleigh quotient for the eigenvalues
            std::array<float, m> eigenvalues = {0};
            for (uint16_t i = 0; i < m; ++i) {
                auto Av = Math::multiplyMatrixVector(matrix, vectors[i]);
                for (uint16_t j = 0; j < n; ++j) {
                    eigenvalues[i] += vectors[j][i] * Av[j];
                }
            }
        
            return {eigenvalues, vectors};
        }
        /*
         * Function to find eigenvalues and eigenvectors
         */
        template<uint64_t x, uint64_t y, uint64_t m>
        static std::pair<std::array<float, m>, Matrix<x, m>> find(const Matrix<x, y>& matrix, const uint64_t M=m) {
            // Ensure the matrix is square
            static_assert(x == y, "Matrix must be square to calculate eigenvalues and eigenvectors");
            static_assert(m <= x, "Number of requested eigenvectors must be less than or equal to matrix size");
        
            // Find the M most significant eigenvalues and eigenvectors using Orthogonal Iteration
            return orthogonalIteration<m, m>(matrix);
        }
    };
}
