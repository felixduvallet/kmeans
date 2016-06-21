// Author: Felix Duvallet



#include <gtest/gtest.h>
#include <memory>
#include "kmeans.h"

namespace {

class TestEndToEnd : public testing::Test {
protected:

  std::unique_ptr<KMeans> kmeans;

  virtual void SetUp() {

    std::vector<Point> points;
    KMeans::loadPoints("data_200_2.txt", &points);

    kmeans.reset(new KMeans(2, 10));
    kmeans->init(points);
  }
};

TEST_F(TestEndToEnd, TestLoading) {
  ASSERT_EQ(200, kmeans->getPoints().size());
  ASSERT_EQ(2, kmeans->getPoints()[0].dimensions_);

  const std::vector<Point> means = kmeans->getMeans();
  ASSERT_EQ(2, means.size());

  // All means should be initialized to a random (non-zero) point in the data.
  for (const auto &mean : means) {
    ASSERT_EQ(2, mean.dimensions_);
    for (double d : mean.data_)
      EXPECT_NE(0.0, d);
  }
}

TEST_F(TestEndToEnd, TestCompute) {
  // Just check that we converge.
  bool ret = kmeans->run();
  ASSERT_TRUE(ret);
}

}