#pragma once
#include "EigenfaceMathBase.h"


namespace Eigenface {
    class EigenvectorFinder {
    public: 
        /**
         * Function to orthogonalize a set of vectors using Gram-Schmidt process
         */
        template<long unsigned int n, long unsigned int k>
        static Matrix<n,k> gramSchmidtOrthogonalization(Matrix<n, k>& V) {
        
            Matrix<n,k> U = {0.0f};
        
            // Compute the first column of U
            double norm_v1 = 0.0;
            for (auto row = 0U; row < n; ++row) {
                norm_v1 += V[row][0] * V[row][0];
            }
            norm_v1 = sqrt(norm_v1);
        
            for (auto row = 0U; row < n; ++row) {
                U[row][0] = V[row][0] / norm_v1;
            }
        
            // Compute the rest of the columns of U
            for (auto i = 1U; i < k; ++i) {
                // Start with vi
                for (auto row = 0U; row < n; ++row) {
                    U[row][i] = V[row][i];
                }
        
                // Subtract projections on previous orthonormal vectors
                for (auto j = 0U; j < i; ++j) {
                    double dot_product = 0.0;
                    for (auto row = 0U; row < n; ++row) {
                        dot_product += U[row][j] * U[row][i];
                    }
                    for (auto row = 0U; row < n; ++row) {
                        U[row][i] -= dot_product * U[row][j];
                    }
                }
        
                // Normalize vi
                double norm_vi = 0.0;
                for (auto row = 0U; row < n; ++row) {
                    norm_vi += U[row][i] * U[row][i];
                }
                norm_vi = sqrt(norm_vi);
        
                for (auto row = 0U; row < n; ++row) {
                    U[row][i] /= norm_vi;
                }
            }
        
            return U;
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
                    auto columnVector = Math::matMul(matrix, vectors[i]);
                    for (uint16_t j = 0; j < n; ++j) {
                        newVectors[j][i] = columnVector[j];
                    }
                }
        
                // Orthogonalize and normalize the resulting vectors
                newVectors = gramSchmidtOrthogonalization(newVectors);
        
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
                auto Av = Math::matMul(matrix, vectors[i]);
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
