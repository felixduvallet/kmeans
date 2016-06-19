//
// Created by felixd on 6/19/16.
//

#include <gtest/gtest.h>
#include <cmath>
#include "../point.h"

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

    TEST_F(TestPoint, TestConstructor) {
        Point p(4, 5, 6);
        EXPECT_EQ(3, p.dimensions_);
        EXPECT_EQ(-1, p.cluster_);
    }

    TEST_F(TestPoint, TestUpdateCluster) {
        p1.update(2);
        EXPECT_EQ(2, p1.cluster_);
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


