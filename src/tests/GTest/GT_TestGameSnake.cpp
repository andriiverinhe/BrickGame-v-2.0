#define TESTING
#include <string>

#include "../../brick_game/common/ReferenceGame/ReferenceClassGame.hpp"
#include "../../brick_game/snake/GameSnake.hpp"
#include "GT_main.hpp"

using namespace s21;

TEST(GT_TestGameSnake, TestGameSnake_1) {
  GameSnake game;
  EXPECT_EQ(game.getState(), START);
  game.userInput(Start, false);
  EXPECT_EQ(game.getState(), SPAWN);
  game.reset(START);
  EXPECT_EQ(game.getState(), START);
  game.reset(SPAWN);
  EXPECT_EQ(game.getState(), SPAWN);
}

TEST(GT_TestGameSnake, TestGameSnake_2) {
  GameSnake game;
  game.userInput((UserAction_t)-1, false);
  EXPECT_EQ(game.getState(), START);
  game.userInput(Terminate, false);
  EXPECT_EQ(game.getState(), EXIT);
  game.reset(START);
  EXPECT_EQ(game.getState(), START);
  game.userInput(Start, false);
  EXPECT_EQ(game.getState(), SPAWN);
  game.userInput((UserAction_t)-1, false);
  EXPECT_EQ(game.getState(), MOVE);
  game.userInput(Right, false);
  EXPECT_EQ(game.getState(), MOVE);
  game.userInput(Up, false);
  EXPECT_EQ(game.getState(), MOVE);
  game.userInput(Left, false);
  EXPECT_EQ(game.getState(), MOVE);
  game.userInput(Down, false);
  EXPECT_EQ(game.getState(), MOVE);
  game.userInput(Action, false);
  EXPECT_EQ(game.getState(), SHIFT);
  game.userInput((UserAction_t)-1, false);
  EXPECT_EQ(game.getState(), COLLISION);
  game.userInput((UserAction_t)-1, false);
  EXPECT_EQ(game.getState(), GAMEOVER);
  game.userInput(Terminate, false);
  EXPECT_EQ(game.getState(), EXIT);
}

TEST(GT_TestGameSnake, TestGameSnake_3) {
  GameSnake game;
  game.userInput(Terminate, false);
  EXPECT_EQ(game.getState(), EXIT);
  game.reset(START);
  EXPECT_EQ(game.getState(), START);
  game.userInput(Start, false);
  EXPECT_EQ(game.getState(), SPAWN);
  game.userInput((UserAction_t)-1, false);
  EXPECT_EQ(game.getState(), MOVE);
  game.userInput(Pause, false);
  EXPECT_EQ(game.getState(), PAUSE);
  game.userInput(Action, false);
  EXPECT_EQ(game.getState(), PAUSE);
  game.userInput(Pause, false);
  EXPECT_EQ(game.getState(), MOVE);
  game.userInput(Action, false);
  EXPECT_EQ(game.getState(), SHIFT);
}

TEST(GT_TestGameSnake, TestGameSnake_4) {
  GameSnake game;
  EXPECT_TRUE(game.timer.getDuration() > (std::chrono::milliseconds)0);
  game.userInput(Terminate, false);
  EXPECT_EQ(game.getState(), EXIT);
  game.reset(START);
  EXPECT_EQ(game.getState(), START);
  game.userInput(Start, false);
  EXPECT_EQ(game.getState(), SPAWN);
  game.userInput((UserAction_t)-1, false);
  EXPECT_EQ(game.getState(), MOVE);
  game.userInput(Right, false);
  EXPECT_EQ(game.getState(), MOVE);
  game.userInput(Up, false);
  EXPECT_EQ(game.getState(), MOVE);
  game.userInput(Left, false);
  EXPECT_EQ(game.getState(), MOVE);
  game.userInput(Down, false);
  EXPECT_EQ(game.getState(), MOVE);
  game.userInput(Action, false);
  EXPECT_EQ(game.getState(), SHIFT);
  game.userInput((UserAction_t)-1, false);
  EXPECT_EQ(game.getState(), COLLISION);
  game.userInput((UserAction_t)-1, false);
  EXPECT_EQ(game.getState(), GAMEOVER);
  game.userInput((UserAction_t)-1, false);
  EXPECT_EQ(game.getState(), GAMEOVER);
  game.userInput(Start, false);
  EXPECT_EQ(game.getState(), SPAWN);
}

TEST(GT_TestGameSnake, TestGameSnake_5) {
  GameSnake game;
  game.setState((GameState_t)-1);
  EXPECT_EQ(game.getState(), -1);
}

TEST(GT_TestGameSnake, TestGameSnake_6) {
  GameSnake game;
  EXPECT_EQ(game.getState(), START);
  game.userInput(Start, false);
  EXPECT_EQ(game.getState(), SPAWN);
  game.reset(MOVE);
  EXPECT_EQ(game.getState(), SPAWN);
}

TEST(GT_TestGameSnake, TestGameSnake_7) {
  GameSnake game;
  game.userInput(Terminate, false);
  EXPECT_EQ(game.getState(), EXIT);
  game.reset(START);
  EXPECT_EQ(game.getState(), START);
  game.userInput(Start, false);
  EXPECT_EQ(game.getState(), SPAWN);
  game.userInput((UserAction_t)-1, false);
  EXPECT_EQ(game.getState(), MOVE);
  game.userInput(Terminate, false);
  EXPECT_EQ(game.getState(), GAMEOVER);
}

TEST(GT_TestGameSnake, TestUpdateCurrentState_1) {
  GameSnake game;
  auto engine = game.updateCurrentState();

  EXPECT_EQ(engine.level, 0);
  EXPECT_EQ(engine.speed, ST_INIT_SPEED);

  game.fruit.setIsAlive(true);
  engine = game.updateCurrentState();
  EXPECT_EQ(engine.level, 0);
  EXPECT_EQ(engine.speed, ST_INIT_SPEED);
}

TEST(GT_TestGameSnake, TestUpdateCurrentState_2) {
  GameSnake game;
  auto engine = game.updateCurrentState();

  EXPECT_EQ(engine.level, 0);
  EXPECT_EQ(engine.speed, ST_INIT_SPEED);

  game.userInput(Start, false);
  EXPECT_EQ(game.getState(), SPAWN);
  game.userInput((UserAction_t)-1, false);
  EXPECT_EQ(game.getState(), MOVE);

  engine = game.updateCurrentState();
  EXPECT_EQ(engine.level, 0);
  EXPECT_EQ(engine.speed, ST_INIT_SPEED);
}

TEST(GT_TestGameSnake, TestUpdateCurrentState_3) {
  GameSnake game;
  game.setDiraction((UserAction_t)-1);
  EXPECT_TRUE(game.snake.getIsAlive());
}

TEST(GT_TestGameSnake, TestCheckCollide_1) {
  GameSnake game;
  game.snake.setMovementBlocked(false);
  game.snake.setLocation(ST_SIZE_WIDTH, 10);
  std::string object = "\0";
  game.checkCollide(object);
  EXPECT_TRUE(object.compare("Wall") == 0);
}

TEST(GT_TestGameSnake, TestCheckCollide_2) {
  GameSnake game;
  game.userInput(Terminate, false);
  EXPECT_EQ(game.getState(), EXIT);
  game.reset(START);
  EXPECT_EQ(game.getState(), START);
  game.userInput(Start, false);
  EXPECT_EQ(game.getState(), SPAWN);
  game.userInput((UserAction_t)-1, false);
  EXPECT_EQ(game.getState(), MOVE);

  std::string object = "\0";
  game.checkCollide(object);
  EXPECT_TRUE(object.compare("No Collide") == 0);

  game.snake.setMovementBlocked(false);
  game.snake.setLocation(game.fruit.getLocation());
  game.checkCollide(object);
  EXPECT_TRUE(object.compare("Fruit") == 0);
}

TEST(GT_TestGameSnake, TestCheckCollide_4) {
  GameSnake game;
  game.snake.setMovementBlocked(false);
  game.snake.setLocation(-5, 5);
  std::string object = "\0";
  game.checkCollide(object);
  EXPECT_TRUE(object.compare("Wall") == 0);
}

TEST(GT_TestGameSnake, TestCheckCollide_5) {
  GameSnake game;
  game.snake.setMovementBlocked(false);
  game.snake.setLocation(-5, -5);
  std::string object = "\0";
  game.checkCollide(object);
  EXPECT_TRUE(object.compare("Wall") == 0);
}

TEST(GT_TestGameSnake, TestCheckCollide_6) {
  GameSnake game;
  game.snake.setMovementBlocked(false);
  game.snake.setLocation(5, -5);
  std::string object = "\0";
  game.checkCollide(object);
  EXPECT_TRUE(object.compare("Wall") == 0);
}

TEST(GT_TestGameSnake, TestCheckCollide_7) {
  GameSnake game;
  game.snake.setMovementBlocked(false);
  game.snake.setLocation(25, 5);
  std::string object = "\0";
  game.checkCollide(object);
  EXPECT_TRUE(object.compare("Wall") == 0);
}

TEST(GT_TestGameSnake, TestCheckCollide_8) {
  GameSnake game;
  game.snake.setMovementBlocked(false);
  game.snake.setLocation(25, 25);
  std::string object = "\0";
  game.checkCollide(object);
  EXPECT_TRUE(object.compare("Wall") == 0);
}

TEST(GT_TestGameSnake, TestCheckCollide_9) {
  GameSnake game;
  game.snake.setMovementBlocked(false);
  game.snake.setLocation(5, 25);
  std::string object = "\0";
  game.checkCollide(object);
  EXPECT_TRUE(object.compare("Wall") == 0);
}

TEST(GT_TestGameSnake, TestMaxLengthSnake_1) {
  GameSnake game;
  for (; !game.snake.body.empty();) game.snake.body.pop_back();

  EXPECT_EQ(game.snake.getLength(), 0);
  for (int i = 0; i < HFIELD; i++)
    for (int j = 0; j < WFIELD; j++)
      game.snake.body.push_back(Coordinate{j, i});

  EXPECT_EQ(game.snake.getLength(), ST_MAX_LENGTH_SNAKE);
}

TEST(GT_TestGameSnake, TestMaxLengthSnake_2) {
  GameSnake game;
  for (; !game.snake.body.empty();) game.snake.body.pop_back();

  EXPECT_EQ(game.snake.getLength(), 0);
  for (int i = 0; i < HFIELD; i++)
    for (int j = 0; j < WFIELD; j++)
      game.snake.body.push_back(Coordinate{j, i});

  EXPECT_EQ(game.snake.getLength(), ST_MAX_LENGTH_SNAKE);
  game.snake.setIsAlive(false);
  game.addSnakeToField();
  game.snake.setIsAlive(true);
  game.addSnakeToField();
  game.helperFsmSpawn();
  EXPECT_EQ(game.getState(), GAMEOVER);
}

TEST(GT_TestGameSnake, TestShiftSnake_1) {
  GameSnake game;
  game.userInput(Start, false);
  game.userInput((UserAction_t)-1, false);
  EXPECT_EQ(game.getState(), MOVE);
  game.snake.setIsAlive(false);
  game.helperFsmShift();
  EXPECT_EQ(game.getState(), GAMEOVER);
}

TEST(GT_TestGameSnake, TestShiftSnake_2) {
  GameSnake game;
  game.userInput(Start, false);
  game.userInput((UserAction_t)-1, false);
  EXPECT_EQ(game.getState(), MOVE);
  game.helperFsmShift();
  EXPECT_EQ(game.getState(), MOVE);
}

TEST(GT_TestGameSnake, TestCheckCollideHelper_1) {
  GameSnake game;
  game.snake.setMovementBlocked(false);
  game.snake.setLocation(ST_SIZE_WIDTH, 10);
  game.helperFsmCollision();
  EXPECT_EQ(game.getState(), GAMEOVER);
}

TEST(GT_TestGameSnake, TestCheckCollideHelper_2) {
  GameSnake game;
  game.userInput(Terminate, false);
  EXPECT_EQ(game.getState(), EXIT);
  game.reset(START);
  EXPECT_EQ(game.getState(), START);
  game.userInput(Start, false);
  EXPECT_EQ(game.getState(), SPAWN);
  game.userInput((UserAction_t)-1, false);
  EXPECT_EQ(game.getState(), MOVE);

  game.helperFsmCollision();
  EXPECT_EQ(game.getState(), GAMEOVER);

  game.snake.setMovementBlocked(false);
  game.snake.setLocation(game.fruit.getLocation());
  game.helperFsmCollision();
  EXPECT_EQ(game.getState(), SPAWN);
}

TEST(GT_TestGameSnake, TestCheckCollideHelper_3) {
  GameSnake game;

  for (; !game.snake.body.empty();) game.snake.body.pop_back();

  EXPECT_EQ(game.snake.getLength(), 0);
  for (int i = 0; i < HFIELD; i++)
    for (int j = 0; j < WFIELD; j++)
      game.snake.body.push_back(Coordinate{j, i});

  EXPECT_EQ(game.snake.getLength(), ST_MAX_LENGTH_SNAKE);

  game.snake.body.pop_back();
  game.fruit.setMovementBlocked(false);
  game.fruit.setLocation(game.snake.getLocation());
  game.helperFsmCollision();
  EXPECT_EQ(game.getState(), GAMEOVER);
}
TEST(GT_TestGameSnake, TestCheckCollideHelper_4) {
  GameSnake game;
  game.userInput(Terminate, false);
  EXPECT_EQ(game.getState(), EXIT);
  game.reset(START);
  EXPECT_EQ(game.getState(), START);
  game.userInput(Start, false);
  EXPECT_EQ(game.getState(), SPAWN);
  game.addSnakeToField();
  game.userInput((UserAction_t)-1, false);
  EXPECT_EQ(game.getState(), MOVE);

  game.helperFsmCollision();
  EXPECT_EQ(game.getState(), GAMEOVER);

  game.snake.setMovementBlocked(false);
  game.snake.setLocation(game.fruit.getLocation());
  game.helperFsmCollision();
  EXPECT_EQ(game.getState(), SPAWN);
}

TEST(GT_TestGameSnake, TestReferenceGame_1) {
  Game rgame;
  rgame.userInput(Start, false);
  auto engine = rgame.updateCurrentState();
  EXPECT_EQ(engine.level, 0);
}

TEST(GT_TestGameSnake, TestReferenceGame_2) {
  Game rgame("../tests/GTest/testfile/empty.txt");
  rgame.cleanField();
  rgame.readSave();
  auto engine = rgame.updateCurrentState();
  EXPECT_EQ(engine.level, 0);
}

TEST(GT_TestGameSnake, TestReferenceGame_3) {
  Game rgame("not_file.txt");
  rgame.save();
  auto engine = rgame.updateCurrentState();
  EXPECT_EQ(engine.level, 0);
}

TEST(GT_TestGameSnake, TestUpdateInf_1) {
  GameSnake sn;
  sn.engine.score = 15000;
  sn.updateInfo();
  EXPECT_EQ(sn.engine.level, 10);
}

TEST(GT_TestGameSnake, TestConvertToStr_1) {
  EXPECT_STREQ(convertStateToStrInf(START), DS_Start);
  EXPECT_STREQ(convertStateToStrInf(GAMEOVER), DS_End);
  EXPECT_STREQ(convertStateToStrInf(MOVE), DS_Not);
}
