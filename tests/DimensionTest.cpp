//
// Created by a19stude on 4/17/19.
//

#include <gtest/gtest.h>
#include "../src/Dimension.hpp"

class DimensionTest : public ::testing::Test {
protected:
	unsigned int maxX;
	unsigned int maxY;
	Dimension uut1;

	DimensionTest() : maxX(420), maxY(2137), uut1{maxX, maxY} {}
};

TEST_F(DimensionTest, pointCreationOK) {
	EXPECT_EQ(maxX, uut1.width);
	EXPECT_EQ(maxY, uut1.height);
}

TEST_F(DimensionTest, negativeValueIsOutOfBoard) {
	EXPECT_FALSE(uut1.isInside({-1, 69}));
	EXPECT_FALSE(uut1.isInside({69, -1}));
	EXPECT_FALSE(uut1.isInside({-1, -1}));

	EXPECT_FALSE(uut1.isInside({-9000, 69}));
	EXPECT_FALSE(uut1.isInside({69, -9000}));
	EXPECT_FALSE(uut1.isInside({-9000, -9000}));
}

TEST_F(DimensionTest, zeroIsInside) {
	EXPECT_TRUE(uut1.isInside({0, 69}));
	EXPECT_TRUE(uut1.isInside({69, 0}));
	EXPECT_TRUE(uut1.isInside({0, 0}));
}

TEST_F(DimensionTest, OneBeforeThresholdIsInside) {
	EXPECT_TRUE(uut1.isInside({static_cast<int>(maxX - 1), 69}));
	EXPECT_TRUE(uut1.isInside({69, static_cast<int>(maxY - 1)}));
	EXPECT_TRUE(uut1.isInside({static_cast<int>(maxX - 1), static_cast<int>(maxY - 1)}));
}

TEST_F(DimensionTest, thresholdIsOutOfBoard) {
	EXPECT_FALSE(uut1.isInside({static_cast<int>(maxX), 69}));
	EXPECT_FALSE(uut1.isInside({69, static_cast<int>(maxY)}));
	EXPECT_FALSE(uut1.isInside({static_cast<int>(maxX), static_cast<int>(maxY)}));
}

TEST_F(DimensionTest, tooBigValueIsOutOfBoard) {
	EXPECT_FALSE(uut1.isInside({9000, 69}));
	EXPECT_FALSE(uut1.isInside({69, 9000}));
	EXPECT_FALSE(uut1.isInside({9000, 9000}));
}
