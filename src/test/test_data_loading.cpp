// Author: Felix Duvallet

#include <gtest/gtest.h>
#include <cmath>
#include "kmeans.h"

namespace {

class TestDataLoading : public testing::Test {
protected:

  virtual void SetUp() {
  }
};

TEST_F(TestDataLoading, TestLoadA) {
  std::vector<Point> points;
  const std::string filepath = "test_data_3.txt";
  KMeans::loadPoints(filepath, &points);
  ASSERT_EQ(2, points.size());
  ASSERT_EQ(3, points[0].dimensions_);
  ASSERT_EQ(3, points[1].dimensions_);
  EXPECT_EQ(1.23, points[0].data_[0]);
  EXPECT_EQ(4.56, points[0].data_[1]);
  EXPECT_EQ(7.89, points[0].data_[2]);
}

}  // /namespace
