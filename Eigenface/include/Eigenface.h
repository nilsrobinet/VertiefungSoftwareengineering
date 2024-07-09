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

    /**
     * Multiply two matricies
     *
     * @returns the product of two matricies
     */
    template <int x1, int y1, int x2, int y2>
    static Matrix_t<x1,y2> matMul(Matrix_t<x1,y1> mat1, Matrix_t<x2,y2> mat2) {
        static_assert(x1 == y2);
        static_assert(x2 == y1);    
        Matrix_t<x1,y2> res = {0};
        for (auto row = 0; row < x1; row++) {
            for (auto col = 0; col < y2; col++){
            
                for (auto i = 0; i < x2; i++) {
                    res[row][col] += mat1[col][i] * mat2[i][row];
                }
            }
        }
        return res;
     }

    /*
     * Function to normalize a vector
     */
    template<uint16_t n>
    void normalizeVector(std::array<float, n>& vec) {
        float norm = 0.0f;
        for (uint16_t i = 0; i < n; ++i) {
            norm += vec[i] * vec[i];
        }
        norm = std::sqrt(norm);
        for (uint16_t i = 0; i < n; ++i) {
            vec[i] /= norm;
        }
    }
    
    // Function to orthogonalize a set of vectors using Gram-Schmidt process
    template<uint16_t n, uint16_t m>
    void gramSchmidtOrthogonalization(Matrix_t<n, m>& vectors) {
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
            normalizeVector(vectors[i]);
        }
    }
    
    // Function to find the M most significant eigenvalues and eigenvectors using Orthogonal Iteration
    template<uint16_t n, uint16_t m>
    std::pair<std::array<float, m>, Matrix_t<n, m>> orthogonalIteration(const Matrix_t<n, n>& matrix, uint16_t maxIterations = 1000, float tolerance = 1e-6) {
        Matrix_t<n, m> vectors = {0};
        for (uint16_t i = 0; i < m; ++i) {
            vectors[i][i] = 1.0f; // Initial guess for the eigenvectors
        }
    
        for (uint16_t iteration = 0; iteration < maxIterations; ++iteration) {
            // Multiply the matrix by the current set of vectors
            Matrix_t<n, m> newVectors = {0};
            for (uint16_t i = 0; i < m; ++i) {
                auto columnVector = multiplyMatrixVector(matrix, vectors[i]);
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
            auto Av = multiplyMatrixVector(matrix, vectors[i]);
            for (uint16_t j = 0; j < n; ++j) {
                eigenvalues[i] += vectors[j][i] * Av[j];
            }
        }
    
        return {eigenvalues, vectors};
    }


    /**
     * Function to find the M most significant eigenvalues and eigenvectors
     * using the power iteration method
     */
    template<uint16_t x, uint16_t y, uint16_t M>
    std::pair<std::array<float, M>, VectorList_t<x, M>> findEigenvaluesAndEigenvectors(const Matrix_t<x, y>& matrix) {
        // Ensure the matrix is square
        static_assert(x == y, "Matrix must be square to calculate eigenvalues and eigenvectors");
        static_assert(m <= x, "Number of requested eigenvectors must be less than or equal to matrix size");
    
        // Find the M most significant eigenvalues and eigenvectors using Orthogonal Iteration
        return orthogonalIteration<m, m>(matrix);
    }

};

