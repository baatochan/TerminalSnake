//
// Created by a19stude on 4/17/19.
//

#include <gtest/gtest.h>
#include "../src/Point.hpp"

class PointTest : public ::testing::Test {
protected:
	Point uut1{};
	Point uut2{};
};

std::ostream& operator <<(std::ostream& out, const Point& p) {
	out << "{ " << p.x << ", " << p.y << " }";
	return out;
}

TEST_F(PointTest, pointCreationOK) {
	uut1 = {420, 2137};
	EXPECT_EQ(420, uut1.x);
	EXPECT_EQ(2137, uut1.y);
}

TEST_F(PointTest, pointsEqual) {
	uut1 = {420, 2137};
	uut2 = {420, 2137};
	EXPECT_EQ(uut1, uut2);
}

TEST_F(PointTest, pointsNotEqual) {
	uut1 = {420, 2137};
	uut2 = {420, 911};
	EXPECT_NE(uut1, uut2);
}
