#include <gtest/gtest.h>
#include <array>
#include "Eigenface.h"

TEST(test_Eigenface, test_avgVector) {
    constexpr int dim = 4;
    constexpr int numVec = 4;
    VectorList_t<dim, numVec> testVectorList_1 = {{
        { 1.0 , 1.0, 1.0, 1.0  },
        { 1.0 , 1.0, 1.0, 1.0  },
        { 1.0 , 1.0, 1.0, 1.0  },
        { 1.0 , 1.0, 1.0, 1.0  },
    }};
    VectorList_t<dim, numVec> testVectorList_2 = {{
        { 1.0 , 1.0, 1.0, 1.0  },
        { 1.0 , 1.0, 1.0, 0.0  },
        { 1.0 , 1.0, 0.0, 0.0  },
        { 1.0 , 0.0, 0.0, 0.0  },
    }};

    std::array<float, dim> result1 = Eigenface::averageVector<dim, numVec>(testVectorList_1);
    std::array<float, dim> result2 = Eigenface::averageVector<dim, numVec>(testVectorList_2);

    std::array<float, dim> expected1 = {1.0,1.0,1.0,1.0};
    std::array<float, dim> expected2 = {1.0,0.75,0.5,0.25};
    EXPECT_EQ(result1, expected1);
    EXPECT_EQ(result2, expected2);
}

TEST(test_Eigenface, test_normalize) {
    constexpr int dim = 4;
    constexpr int numVec = 4;
    VectorList_t<dim, numVec> testVectorList_1 = {{
        { 1.0 , 1.0, 1.0, 1.0  },
        { 1.0 , 1.0, 1.0, 1.0  },
        { 1.0 , 1.0, 1.0, 1.0  },
        { 1.0 , 1.0, 1.0, 1.0  },
    }};
    Vector_t<dim> normVec = {2.0, 5.0, 1.0, 0.0};

    Eigenface::normalize<dim,numVec>(testVectorList_1, normVec);
    
    VectorList_t<dim, numVec> expected1 = {{
        { -1.0 , -4.0, 0.0, 1.0  },
        { -1.0 , -4.0, 0.0, 1.0  },
        { -1.0 , -4.0, 0.0, 1.0  },
        { -1.0 , -4.0, 0.0, 1.0  },
    }};
    EXPECT_EQ(testVectorList_1, expected1); 
}

TEST(test_Eigenface, test_transpose) {
    
    Matrix_t<1,3> testMat_1 = {{
                                  {2,4,6}
                              }};
    Matrix_t<3,2> testMat_2 = {{
                                  {1,2},
                                  {3,4},
                                  {5,6}
                              }};
   
    Matrix_t<3,1> expectedMat_1 = {{
                                {2},
                                {4},
                                {6}
                              }};

    Matrix_t<2,3> expectedMat_2 = {{
                                  {1,3,5},
                                  {2,4,6}
                              }};
    auto result_1 = Eigenface::transpose<1,3>(testMat_1);
    EXPECT_EQ(expectedMat_1, result_1);
    auto result_2 = Eigenface::transpose<3,2>(testMat_2);
    EXPECT_EQ(expectedMat_2, result_2);
}

TEST(test_Eigenface, test_matMul) {
    Matrix_t<3,2> testMat_1 = {{
                                  {1,1},
                                  {2,2},
                                  {3,3}
                              }};
    Matrix_t<2,3> testMat_2 = {{
                                  {1,1,1},
                                  {2,2,2}
                              }};
    auto result = Eigenface::matMul<3,2,2,3>(testMat_1, testMat_2 );

}
