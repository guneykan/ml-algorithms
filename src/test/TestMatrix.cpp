#include "gtest/gtest.h"

#include "../util/math/matrix.h"

TEST(Matrix, sum_1by1) {
  Matrix m1(std::vector<double>{0.5}, 1, 1);
  Matrix m2(std::vector<double>{91.2}, 1, 1);

  Matrix calculated = m1.plus(m2);
  Matrix actual(std::vector<double>{91.7}, 1, 1);

  ASSERT_EQ(actual.get(0, 0), calculated.get(0, 0));
}

TEST(Matrix, sum_3by3) {
  Matrix m1({6, 4, 5, 4, 5, 1, 2, 8, 3}, 3, 3);
  Matrix m2({3, 4, 0, 9, 1, 6, 1, 8, 2}, 3, 3);

  Matrix calculated = m1.plus(m2);
  Matrix actual({9, 8, 5, 13, 6, 7, 3, 16, 5}, 3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_EQ(actual.get(i, j), calculated.get(i, j));
    }
  }
}

TEST(Matrix, sum_4by5) {
  Matrix m1({632.929,  490.984,  5121.213, 495.065,  5121.910,
             1998.129, 2968.190, 854.135,  32.621,   1254.411,
             467.149,  1200.486, 6043.216, 5032.697, 5124.764,
             917.703,  534.215,  7100.643, 451.096,  91.431},
            4, 5);

  Matrix m2({398.013, 43.514,   995.812, 911.531, 1000.548, 69.541,  110.461,
             800.694, 2485.441, 322.973, 434.869, 661.964,  857.333, 3.885,
             83.132,  995.143,  456.877, 331.583, 901.671,  67.123},
            4, 5);

  Matrix calculated = m1.plus(m2);

  Matrix actual({1030.942, 534.498, 6117.025, 1406.596, 6122.458, 2067.670,
                 3078.651, 1654.829, 2518.062, 1577.384, 902.018, 1862.450,
                 6900.549, 5036.582, 5207.896, 1912.846, 991.092, 7432.226,
                 1352.767, 158.554},
                4, 5);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      ASSERT_NEAR(actual.get(i, j), calculated.get(i, j), 1E-9);
    }
  }
}

TEST(Matrix, sum_dimension_error) {
  Matrix m1({4, 5, 4, 5, 1, 2, 8, 3}, 2, 4);
  Matrix m2({9, 3, 9, 1, 6, 1, 8, 2}, 4, 2);
  try {
 	 Matrix calculated = m1.plus(m2);
     FAIL() << "Expected Dimension Error";
   }
   catch(DimensionException& e){
        EXPECT_EQ(e.what(),std::string("Dimension Error"));
   }catch(...){
   	    FAIL() << "Expected Dimension Error";
   }
}
