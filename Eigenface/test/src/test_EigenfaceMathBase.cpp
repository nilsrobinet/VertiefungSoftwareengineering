#include <gtest/gtest.h>
#include <array>
#include <cstdint>
#include "EigenfaceMathBase.h"

using namespace Eigenface;

TEST(test_EigenfaceMathBase, test_avgVector) {
    constexpr int dim = 4;
    constexpr int numVec = 4;
    VectorList<dim, numVec> testVectorList_1 = {{
        { 1.0 , 1.0, 1.0, 1.0  },
        { 1.0 , 1.0, 1.0, 1.0  },
        { 1.0 , 1.0, 1.0, 1.0  },
        { 1.0 , 1.0, 1.0, 1.0  },
    }};
    VectorList<dim, numVec> testVectorList_2 = {{
        { 1.0 , 1.0, 1.0, 1.0  },
        { 1.0 , 1.0, 1.0, 0.0  },
        { 1.0 , 1.0, 0.0, 0.0  },
        { 1.0 , 0.0, 0.0, 0.0  },
    }};

    Vector<dim> result1 = Math::averageVector(testVectorList_1);
    Vector<dim> result2 = Math::averageVector(testVectorList_2);

    Vector<dim> expected1 = {1.0,1.0,1.0,1.0};
    Vector<dim> expected2 = {1.0,0.75,0.5,0.25};
    EXPECT_EQ(result1, expected1);
    EXPECT_EQ(result2, expected2);
}

// TODO: move to eigenface specific test
//TEST(test_EigenfaceMathBase, test_normalize) {
//    constexpr int dim = 4;
//    constexpr int numVec = 4;
//    VectorList<dim, numVec> testVectorList_1 = {{
//        { 1.0 , 1.0, 1.0, 1.0  },
//        { 1.0 , 1.0, 1.0, 1.0  },
//        { 1.0 , 1.0, 1.0, 1.0  },
//        { 1.0 , 1.0, 1.0, 1.0  },
//    }};
//    Vector<dim> normVec = {2.0, 5.0, 1.0, 0.0};
//
//    Math::normalize<dim,numVec>(testVectorList_1, normVec);
//    
//    VectorList<dim, numVec> expected1 = {{
//        { -1.0 , -4.0, 0.0, 1.0  },
//        { -1.0 , -4.0, 0.0, 1.0  },
//        { -1.0 , -4.0, 0.0, 1.0  },
//        { -1.0 , -4.0, 0.0, 1.0  },
//    }};
//    EXPECT_EQ(testVectorList_1, expected1); 
//}

TEST(test_EigenfaceMathBase, test_normalize) {
    Vector<4U> testVec = {4.0f, 3.0f, 0.0f, 0.0f};
    Vector<4U> expectedVec = {0.8f, 0.6f, 0.0f, 0.0f};
    Math::normalize(testVec);
    for (int i = 0; i < 4; ++i) {
        EXPECT_NEAR(expectedVec[i], testVec[i], 1e-5);
    }
}

TEST(test_EigenfaceMathBase, test_transpose) {
    
    Matrix<1,3> testMat_1 = {{
                                  {2,4,6}
                              }};
    Matrix<3,2> testMat_2 = {{
                                  {1,2},
                                  {3,4},
                                  {5,6}
                              }};
   
    Matrix<3,1> expectedMat_1 = {{
                                {2},
                                {4},
                                {6}
                              }};

    Matrix<2,3> expectedMat_2 = {{
                                  {1,3,5},
                                  {2,4,6}
                              }};
    auto result_1 = Math::transpose(testMat_1);
    EXPECT_EQ(expectedMat_1, result_1);
    auto result_2 = Math::transpose(testMat_2);
    EXPECT_EQ(expectedMat_2, result_2);
}

TEST(test_EigenfaceMathBase, test_matMul) {
    Matrix<3,2> testMat_1 = {{
                                  {1,1},
                                  {2,2},
                                  {3,3}
                              }};
    Matrix<2,3> testMat_2 = {{
                                  {1,1,1},
                                  {2,2,2}
                              }};
    auto result = Math::matMul(testMat_1, testMat_2 );
    Matrix<3,3> expectedMatrix = {{
                                    {3,3,3},
                                    {6,6,6},
                                    {9,9,9},
                                   }};
    EXPECT_EQ(result, expectedMatrix);
}
