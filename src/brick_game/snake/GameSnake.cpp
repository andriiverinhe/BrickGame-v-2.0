/**
 * @file GameSnake.cpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Snake game source file.
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "GameSnake.hpp"

namespace s21 {

static inline bool isNormalCoordField(const Coordinate coord);

/**
 * @brief Construct a new Game Snake:: Game Snake object
 *
 */
GameSnake::GameSnake(void)
    : Game(),
      snake(AC_Snake(ST_INIT_LENGTH_SNAKE, ST_LOCATION_SNAKE)),
      fruit(ReferenceActor("Apple", false, false, ST_BAD_POSITION,
                           ST_BAD_POSITION)),
      state(START) {
  allocateField(&engine);
  allocateNext(&engine);

  this->readSave();
  engine.score = ST_INIT_LENGTH_SNAKE;
  engine.speed = ST_INIT_SPEED;
  timer.setDuration((std::chrono::milliseconds)engine.speed);
}

/**
 * @brief Destroy the Game Snake:: Game Snake object
 *
 */
GameSnake::~GameSnake() {
  freeField(&engine);
  freeNext(&engine);
}

/**
 * @brief Gets the current state of the game.
 *
 * @return GameState_t
 */
GameState_t GameSnake::getState() const { return state; }

/**
 * @brief Sets the current state of the game to a new value.
 *
 * @param sstate
 */
void GameSnake::setState(const GameState_t sstate) { state = sstate; };

/**
 * @brief Generates a new fruit
 *
 * @param x The x-coordinate of the new fruit.
 * @param y The y-coordinate of the new fruit
 */
void GameSnake::generateFruit(const int x, const int y) {
  fruit.setLocation(x, y);
  fruit.setIsAlive(true);
}

/**
 * @brief Checks whether a given coordinate is within the normal game field
 * boundaries.
 *
 * @param coord The Coordinate to check.
 * @return true
 * @return false
 */
static inline bool isNormalCoordField(const Coordinate coord) {
  return (coord.y >= 0 && coord.y < ST_SIZE_HEIGHT) &&
         (coord.x >= 0 && coord.x < ST_SIZE_WIDTH);
}

/**
 * @brief Generates a new fruit at a random position within the game field.
 */
void GameSnake::generateFruitInRandomPosition() {
  std::vector<Coordinate> vector_position;

  vector_position.reserve(ST_MAX_LENGTH_SNAKE - ST_INIT_LENGTH_SNAKE);

  for (int i = 0; i < ST_SIZE_HEIGHT; i++)
    for (int j = 0; j < ST_SIZE_WIDTH; j++)
      if (engine.field[i][j] == 0) vector_position.push_back({j, i});

  if (!vector_position.empty()) {
    Coordinate random_vector =
        vector_position[std::rand() % vector_position.size()];
    generateFruit(random_vector.x, random_vector.y);
  }
}

/**
 * @brief Updates the game state and spawns a new fruit after the previous one
 * has been eaten.
 *
 */
void GameSnake::helperFsmSpawn() {
  generateFruitInRandomPosition();

  if (fruit.getIsAlive() == true)
    state = MOVE;
  else
    state = GAMEOVER;
}

/**
 * @brief Auxiliary function for determining the direction
 *
 * @param action The direction of movement
 */
void GameSnake::setDiraction(UserAction_t action) {
  int x = 0;
  int y = 0;

  switch (action) {
    case Left:
      x = ST_DIRACTION_LEFT;
      break;
    case Right:
      x = ST_DIRACTION_RIGHT;
      break;
    case Up:
      y = ST_DIRACTION_UP;
      break;
    case Down:
      y = ST_DIRACTION_DOWN;
      break;
    default:
      break;
  }

  snake.setRotation(x, y);
}

/**
 * @brief Checks if the snake has collided with itself.
 *
 * @return true
 * @return false
 */
bool GameSnake::checkCollideSnake() {
  Coordinate head = snake.getLocation();
  bool collide = false;
  for (auto it = (snake.getSnake().begin() + 1);
       (it != (snake.getSnake().end())) && !collide; it++)
    if (head == (*it)) collide = true;
  return collide;
}

/**
 * @brief Checks if the snake has collided with an object.
 *
 * @param object The object to check for collisions.
 * @return true
 * @return false
 */
bool GameSnake::checkCollide(std::string &object) {
  bool collide = true;
  Coordinate head = snake.getLocation();

  if (!isNormalCoordField(head))
    object = CS_Wall;
  else if (head == fruit.getLocation())
    object = CS_Fruit;
  else if (checkCollideSnake())
    object = CS_Snake;
  else {
    collide = false;
    object = CS_NoCollide;
  }

  return collide;
}

/**
 * @brief Auxiliary function for the finite state machine (FSM) for the shift
 * state.
 */
void GameSnake::helperFsmShift() {
  if (snake.getIsAlive()) {
    snake.move();
    std::string object;
    if (checkCollide(object)) {
      state = COLLISION;
    } else {
      snake.setMovementBlocked(true);
      state = MOVE;
    }
  } else
    state = GAMEOVER;
}

/**
 * @brief Updates the game information.
 *
 */
void GameSnake::updateInfo() {
  const int16_t level = engine.score / ST_POINT_FOR_LEVEL;
  engine.level = (level > ST_MAX_LEVEL ? ST_MAX_LEVEL : level);

  if (engine.high_score < engine.score) {
    engine.high_score = engine.score;
    this->save();
  }

  engine.speed = ST_INIT_SPEED - (engine.level * ST_COEFICIENT_SPEED);
  timer.setDuration((std::chrono::milliseconds)engine.speed);
}

/**
 * @brief Auxiliary function for the finite state machine (FSM) for the
 * Collision state.
 */
void GameSnake::helperFsmCollision() {
  std::string object;
  if (checkCollide(object)) {
    if (object.compare(CS_Fruit) == 0) {
      engine.score++;
      fruit.setIsAlive(false);
      snake.IncreaseLength();
      if (snake.getLength() >= ST_MAX_LENGTH_SNAKE)
        state = GAMEOVER;
      else
        state = SPAWN;
    } else if (object.compare(CS_Wall) == 0 || object.compare(CS_Snake) == 0) {
      snake.setIsAlive(false);
      state = GAMEOVER;
    }
    updateInfo();
  } else {
    state = GAMEOVER;
  }
}

/**
 * @brief Resets the game state to a specific state.
 *
 * @param reset_state The state to which the game should be moved
 */
void GameSnake::reset(const GameState_t reset_state) {
  if (reset_state == START || reset_state == SPAWN)
    state = reset_state;
  else
    state = SPAWN;
  fruit.setIsAlive(false);

  snake = AC_Snake(ST_INIT_LENGTH_SNAKE, ST_LOCATION_SNAKE);

  engine.level = 0;
  engine.speed = ST_INIT_SPEED;
  engine.score = ST_INIT_LENGTH_SNAKE;
}

/**
 * @brief Auxiliary function for the finite state machine (FSM) for the MOVE
 *
 * @param action The user's input action.
 */
void GameSnake::caseMove(UserAction_t action) {
  if (!timer.getActive()) {
    timer.updateStartTime();
    timer.setActive(true);
  } else
    timer.updateEndTime();

  if (action == Pause) {
    state = PAUSE;
    engine.pause = true;
  } else if (action == Terminate) {
    state = GAMEOVER;
  } else if (action == Action || !timer.getActive()) {
    snake.setMovementBlocked(false);
    state = SHIFT;
  } else if (action == Left || action == Right || action == Up ||
             action == Down) {
    setDiraction(action);
  }
}

/**
 * @brief Processes user input based on the current game state.
 *
 * @param action The user action to process.
 * @param hold Indicates whether the action is being held.
 */
void GameSnake::userInput(UserAction_t action, bool hold) {
  (void)hold;

  switch (state) {
    case START:
      if (action == Start)
        state = SPAWN;
      else if (action == Terminate)
        state = EXIT;
      break;
    case SPAWN:
      helperFsmSpawn();
      break;
    case MOVE:
      this->caseMove(action);
      break;
    case SHIFT:
      helperFsmShift();
      break;
    case COLLISION:
      helperFsmCollision();
      break;
    case GAMEOVER:
      if (action == Start)
        this->reset(SPAWN);
      else if (action == Terminate)
        state = EXIT;
      break;
    case PAUSE:
      if (action == Pause) {
        state = MOVE;
        engine.pause = false;
      }
    default:
      break;
  }
}

/**
 * @brief Adds the snake to the game field.
 */
void GameSnake::addSnakeToField() {
  if (!snake.getIsAlive()) return;
  auto refSnake = snake.getSnake();
  if (!refSnake.empty()) {
    for (auto i : refSnake) {
      if (isNormalCoordField(i)) engine.field[i.y][i.x] = ST_CODE_SNAKE;
    }
  }
}

/**
 * @brief Adds the fruit to the game field.
 */
void GameSnake::addFruitToField() {
  if (!fruit.getIsAlive()) return;
  Coordinate coord = this->fruit.getLocation();
  if (isNormalCoordField(coord)) engine.field[coord.y][coord.x] = ST_CODE_FRUIT;
}

/**
 * @brief Updates and retrieves the current game state information.
 *
 * This function updates and retrieves the current game state information,
 * including the field, next piece, score, level, speed, and pause state.
 *
 * @return GameInfo_t The updated game state information.
 */
GameInfo_t GameSnake::updateCurrentState() {
  this->cleanField();
  this->addSnakeToField();
  this->addFruitToField();
  return engine;
}

}  // namespace s21
