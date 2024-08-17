#include <iostream>

#include "../../brick_game/snake/AC_Snake.hpp"
#include "GT_main.hpp"
using namespace s21;

TEST(GT_TestActorSnake, TestLength_1) {
  AC_Snake snake;
  EXPECT_EQ(snake.getLength(), 1);
}

TEST(GT_TestActorSnake, TestLength_2) {
  AC_Snake snake;
  snake.IncreaseLength();
  EXPECT_EQ(snake.getLength(), 1);
}

TEST(GT_TestActorSnake, TestLength_3) {
  AC_Snake snake(2, {1, 1});
  for (int i = 0; i < 5; i++) snake.IncreaseLength();
  EXPECT_EQ(snake.getLength(), 7);
  for (int i = 0; i < 5; i++) snake.IncreaseLength();
  EXPECT_EQ(snake.getLength(), 12);
  snake.setIsAlive(false);
  snake.IncreaseLength();
  EXPECT_EQ(snake.getLength(), 12);
}

TEST(GT_TestActorSnake, TestLength_4) {
  AC_Snake snake(100, ST_LOCATION_SNAKE);
  EXPECT_EQ(snake.getLength(), 4);
}

TEST(GT_TestActorSnake, TestMove_1) {
  AC_Snake snake;
  EXPECT_EQ(snake.getRotation(), ST_ROTATION_SNAKE);
  EXPECT_EQ(snake.getLocation(), ST_LOCATION_SNAKE);
  snake.move();
  EXPECT_EQ(snake.getLocation(), ST_LOCATION_SNAKE);
}

TEST(GT_TestActorSnake, TestMove_2) {
  AC_Snake snake;
  EXPECT_EQ(snake.getRotation(), ST_ROTATION_SNAKE);
  EXPECT_EQ(snake.getLocation(), ST_LOCATION_SNAKE);
  snake.setMovementBlocked(false);
  snake.move();
  Coordinate snc = ST_LOCATION_SNAKE;
  snc += ST_ROTATION_SNAKE;
  EXPECT_EQ(snake.getLocation(), snc);
}

TEST(GT_TestActorSnake, TestRotation_1) {
  AC_Snake snake;
  EXPECT_EQ(snake.getRotation(), ST_ROTATION_SNAKE);
  snake.setRotation(1, 1);
  EXPECT_EQ(snake.getRotation(), ST_ROTATION_SNAKE);
  snake.setRotation(1, 0);
  EXPECT_EQ(snake.getRotation(), ST_ROTATION_SNAKE);
  snake.setRotation(0, 1);
  EXPECT_EQ(snake.getRotation(), ST_ROTATION_SNAKE);
  snake.setRotation(0, 0);
  EXPECT_EQ(snake.getRotation(), ST_ROTATION_SNAKE);
}

TEST(GT_TestActorSnake, TestRotation_2) {
  AC_Snake snake;
  EXPECT_EQ(snake.getRotation(), ST_ROTATION_SNAKE);
  snake.setRotation(Coordinate({1, 1}));
  EXPECT_EQ(snake.getRotation(), ST_ROTATION_SNAKE);
  snake.setRotation(Coordinate({1, 0}));
  EXPECT_EQ(snake.getRotation(), ST_ROTATION_SNAKE);
  snake.setRotation(Coordinate({0, 1}));
  EXPECT_EQ(snake.getRotation(), ST_ROTATION_SNAKE);
  snake.setRotation(Coordinate({0, 0}));
  EXPECT_EQ(snake.getRotation(), ST_ROTATION_SNAKE);
}

TEST(GT_TestActorSnake, TestRotation_3) {
  AC_Snake snake(ST_INIT_LENGTH_SNAKE, ST_LOCATION_SNAKE);
  snake.setMovementBlocked(false);
  snake.move();
  EXPECT_EQ(snake.getRotation(), ST_ROTATION_SNAKE);
  snake.setRotation(Coordinate({0, 1}));
  EXPECT_EQ(snake.getRotation(), Coordinate({0, 1}));
  snake.move();
  snake.setRotation(Coordinate({1, 0}));
  EXPECT_EQ(snake.getRotation(), ST_ROTATION_SNAKE);
}

TEST(GT_TestActorSnake, TestBodySnake_1) {
  AC_Snake snake;
  auto sb = snake.getSnake();
  EXPECT_EQ(snake.getLength(), sb.size());
}

TEST(GT_TestActorSnake, TestReferenceActor_1) {
  ReferenceActor ref;
  EXPECT_EQ(ref.getLocation(), Coordinate({0, 0}));
}

TEST(GT_TestActorSnake, TestReferenceActorMove_1) {
  ReferenceActor ref;
  EXPECT_EQ(ref.getLocation(), Coordinate({0, 0}));
  ref.move();
  ref.setRotation(1, 0);
  EXPECT_EQ(ref.getRotation(), Coordinate({0, 0}));
  ref.setMovementBlocked(false);
  ref.setRotation(1, 0);
  EXPECT_EQ(ref.getRotation(), Coordinate({1, 0}));
  ref.move();
  EXPECT_EQ(ref.getLocation(), Coordinate({1, 0}));
}

TEST(GT_TestActorSnake, TestReferenceActorLocation_1) {
  ReferenceActor ref;
  EXPECT_EQ(ref.getLocation(), Coordinate({0, 0}));
  ref.setLocation(1, 1);
  EXPECT_EQ(ref.getLocation(), Coordinate({0, 0}));
  ref.setMovementBlocked(false);
  ref.setLocation(1, 1);
  EXPECT_EQ(ref.getLocation(), Coordinate({1, 1}));
  EXPECT_FALSE(ref.getMovementBlocked());
}