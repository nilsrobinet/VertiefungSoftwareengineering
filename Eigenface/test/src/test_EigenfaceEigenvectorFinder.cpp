#include <gtest/gtest.h>
#include <array>
#include "EigenfaceEigenvectorFinder.h"

using namespace Eigenface;


TEST(test_EigenfaceEigenvectorFinder, test_gramSchmidtOrthogonalization) {
    Matrix<2,2> mat = {{{3,1},
                    {2,2}}};
    auto result = EigenvectorFinder::gramSchmidtOrthogonalization( mat );
    
    auto dotProduct = 0.0f;
    for (int i = 0; i < 2; ++i) {
        dotProduct += result[0][i] * result[1][i];
    }
    EXPECT_NEAR(0.0f, dotProduct, 1e-5);

}

TEST(test_EigenfaceEigenvectorFinder, test_orthogonaleIteration) {
    Matrix<3,3> matrix = {{{1.0f, 2.0f, 3.0f},
                           {4.0f, 5.0f, 6.0f},
                           {7.0f, 8.0f, 9.0f}}};
    auto [eigenvalue, eigenvectors] = EigenvectorFinder::find<3,3,3>(matrix);
    // TODO: remove me: I'm here because the build is built with -Wall and -Werr
    eigenvalue[0] += 0.1;
    eigenvectors[0][0] += 0.1;
    // TODO: verdict
}
