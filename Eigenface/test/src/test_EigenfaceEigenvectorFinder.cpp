#include <gtest/gtest.h>
#include <array>
#include "EigenfaceEigenvectorFinder.h"

using namespace Eigenface;

TEST(test_EigenfaceEigenvectorFinder, test_orthogonaleIteration) {
    Matrix<3,3> matrix = {{{1.0f, 2.0f, 3.0f},
                           {4.0f, 5.0f, 6.0f},
                           {7.0f, 8.0f, 9.0f}}};
    auto [eigenvalue, eigenvectors] = EigenvectorFinder::find<3,3,3>(matrix,3ULL);

}
