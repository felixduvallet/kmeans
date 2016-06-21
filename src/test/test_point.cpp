// Author: Felix Duvallet

#include <gtest/gtest.h>
#include "point.h"

namespace {

class TestPoint : public testing::Test {
protected:
  Point p1;
  Point p2;

  virtual void SetUp() {
    p1 = Point(1.0, 2.0, 3.0);
    p2 = Point(2.0, 3.0, 4.0);
  }
};

TEST_F(TestPoint, TestConstructorArguments) {
  Point p(4, 5, 6);
  EXPECT_EQ(3, p.dimensions_);
  EXPECT_EQ(-1, p.cluster_);
}

TEST_F(TestPoint, TestConstructorVector) {
  std::vector<double> vec{0, 1, 2, 3, 4, 5};
  Point point(vec);

  const int ref_size = (int) vec.size();

  EXPECT_EQ(ref_size, point.dimensions_);
  ASSERT_EQ(ref_size, point.data_.size());
  for (int idx = 0; idx < 6; ++idx)
    EXPECT_EQ((double) idx, point.data_[idx]);

}

TEST_F(TestPoint, TestUpdateCluster) {
  bool ret = p1.update(2);
  EXPECT_EQ(2, p1.cluster_);
  EXPECT_EQ(true, ret);
}

TEST_F(TestPoint, TestUpdateClusterNoChange) {
  bool ret = p1.update(2);
  EXPECT_TRUE(ret);
  ret = p1.update(2);
  EXPECT_EQ(2, p1.cluster_);
  EXPECT_FALSE(ret);
}

TEST_F(TestPoint, TestAdd) {
  p1.add(p2);
  EXPECT_EQ(3.0, p1.data_[0]);
  EXPECT_EQ(5.0, p1.data_[1]);
  EXPECT_EQ(7.0, p1.data_[2]);
}

TEST_F(TestPoint, TestDistance) {
  const double dist = Point::distance(p1, p2);
  EXPECT_EQ(sqrt(3), dist);
}

}  // /namespace

