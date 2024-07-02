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
