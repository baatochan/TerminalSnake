//
// Created by a19stude on 4/17/19.
//

#include <gtest/gtest.h>
#include "../src/Snake.hpp"

class SnakeTest : public ::testing::Test {
protected:
	SnakeTest() : uut({20, 40}, Direction::RIGHT) {}

	Snake uut;

	std::deque<Point> state;
};

TEST_F(SnakeTest, snakeBeingCreatedSuccessfully) {
	state = {{20, 40},
	         {19, 40},
	         {18, 40}};
	EXPECT_EQ(state, uut.getSnakeBody());
	uut.makeAMove();
	state = {{21, 40},
	         {20, 40},
	         {19, 40}};
	EXPECT_EQ(state, uut.getSnakeBody());
}

TEST_F(SnakeTest, snakeMovesCorrectly) {
	state = {{20, 40},
	         {19, 40},
	         {18, 40}};
	EXPECT_EQ(state, uut.getSnakeBody());
	uut.makeAMove();
	state = {{21, 40},
	         {20, 40},
	         {19, 40}};
	EXPECT_EQ(state, uut.getSnakeBody());
	uut.makeAMove();
	state = {{22, 40},
	         {21, 40},
	         {20, 40}};
	EXPECT_EQ(state, uut.getSnakeBody());
	uut.makeAMove();
	state = {{23, 40},
	         {22, 40},
	         {21, 40}};
	EXPECT_EQ(state, uut.getSnakeBody());
	uut.makeAMove();
	state = {{24, 40},
	         {23, 40},
	         {22, 40}};
	EXPECT_EQ(state, uut.getSnakeBody());
	uut.makeAMove();
	state = {{25, 40},
	         {24, 40},
	         {23, 40}};
	EXPECT_EQ(state, uut.getSnakeBody());
}

TEST_F(SnakeTest, snakeTurnsCorrectly) {
	state = {{20, 40},
	         {19, 40},
	         {18, 40}};
	EXPECT_EQ(state, uut.getSnakeBody());

	EXPECT_TRUE(uut.setDirection(Direction::UP));

	uut.makeAMove();
	state = {{20, 39},
	         {20, 40},
	         {19, 40}};
	EXPECT_EQ(state, uut.getSnakeBody());
	uut.makeAMove();
	state = {{20, 38},
	         {20, 39},
	         {20, 40}};
	EXPECT_EQ(state, uut.getSnakeBody());

	EXPECT_TRUE(uut.setDirection(Direction::LEFT));

	uut.makeAMove();
	state = {{19, 38},
	         {20, 38},
	         {20, 39}};
	EXPECT_EQ(state, uut.getSnakeBody());
	uut.makeAMove();
	state = {{18, 38},
	         {19, 38},
	         {20, 38}};
	EXPECT_EQ(state, uut.getSnakeBody());

	EXPECT_TRUE(uut.setDirection(Direction::DOWN));

	uut.makeAMove();
	state = {{18, 39},
	         {18, 38},
	         {19, 38}};
	EXPECT_EQ(state, uut.getSnakeBody());
	uut.makeAMove();
	state = {{18, 40},
	         {18, 39},
	         {18, 38}};
	EXPECT_EQ(state, uut.getSnakeBody());

	EXPECT_TRUE(uut.setDirection(Direction::RIGHT));

	uut.makeAMove();
	state = {{19, 40},
	         {18, 40},
	         {18, 39}};
	EXPECT_EQ(state, uut.getSnakeBody());
	uut.makeAMove();
	state = {{20, 40},
	         {19, 40},
	         {18, 40}};
	EXPECT_EQ(state, uut.getSnakeBody());
}

TEST_F(SnakeTest, snakeGrowsCorrectly) {
	state = {{20, 40},
	         {19, 40},
	         {18, 40}};
	EXPECT_EQ(state, uut.getSnakeBody());

	EXPECT_TRUE(uut.setDirection(Direction::UP));

	uut.makeAMove();
	state = {{20, 39},
	         {20, 40},
	         {19, 40}};
	EXPECT_EQ(state, uut.getSnakeBody());
	uut.grow();
	state = {{20, 38},
	         {20, 39},
	         {20, 40},
	         {19, 40}};
	EXPECT_EQ(state, uut.getSnakeBody());

	EXPECT_TRUE(uut.setDirection(Direction::LEFT));

	uut.makeAMove();
	state = {{19, 38},
	         {20, 38},
	         {20, 39},
	         {20, 40}};
	EXPECT_EQ(state, uut.getSnakeBody());
	uut.grow();
	state = {{18, 38},
	         {19, 38},
	         {20, 38},
	         {20, 39},
	         {20, 40}};
	EXPECT_EQ(state, uut.getSnakeBody());

	EXPECT_TRUE(uut.setDirection(Direction::DOWN));

	uut.makeAMove();
	state = {{18, 39},
	         {18, 38},
	         {19, 38},
	         {20, 38},
	         {20, 39}};
	EXPECT_EQ(state, uut.getSnakeBody());
	uut.grow();
	state = {{18, 40},
	         {18, 39},
	         {18, 38},
	         {19, 38},
	         {20, 38},
	         {20, 39}};
	EXPECT_EQ(state, uut.getSnakeBody());

	EXPECT_TRUE(uut.setDirection(Direction::RIGHT));

	uut.makeAMove();
	state = {{19, 40},
	         {18, 40},
	         {18, 39},
	         {18, 38},
	         {19, 38},
	         {20, 38}};
	EXPECT_EQ(state, uut.getSnakeBody());
	uut.grow();
	state = {{20, 40},
	         {19, 40},
	         {18, 40},
	         {18, 39},
	         {18, 38},
	         {19, 38},
	         {20, 38}};
	EXPECT_EQ(state, uut.getSnakeBody());
}
