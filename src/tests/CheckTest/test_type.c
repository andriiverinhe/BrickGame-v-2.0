#include "../../brick_game/common/Signal/SignalProcessing.h"
#include "../../brick_game/tetris/GameTetris.h"
#include "test.h"

START_TEST(test_pause) {
  GameInfo_t engine = {0};
  setPause(&engine, true);
  ck_assert_int_eq(getPause(&engine), true);
  setPause(&engine, false);
  ck_assert_int_eq(getPause(&engine), false);
}
END_TEST

START_TEST(test_speed) {
  GameInfo_t engine = {0};
  int speed = 10;
  setSpeed(&engine, speed);
  ck_assert_int_eq(getSpeed(&engine), speed);
  speed = -10;
  setSpeed(&engine, speed);
  ck_assert_int_eq(getSpeed(&engine), speed);
}
END_TEST

START_TEST(test_updateCurrentState) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);

  updateParams(&bgt_prmt);
  ck_assert_ptr_nonnull(updateParams(NULL));

  GameInfo_t engine = updateCurrentState();
  ck_assert_ptr_nonnull(engine.field);
  ck_assert_ptr_nonnull(engine.next);
  reset(&bgt_prmt, MOVE);
  ck_assert_int_eq(bgt_prmt.state, SPAWN);
  reset(&bgt_prmt, START);
  ck_assert_int_eq(bgt_prmt.state, START);
  reset(&bgt_prmt, SPAWN);
  ck_assert_int_eq(bgt_prmt.state, SPAWN);
  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_action) {
  ck_assert_int_eq(isInfoState(START), true);
  ck_assert_int_eq(isInfoState(GAMEOVER), true);
  ck_assert_int_eq(isInfoState(MOVE), false);

  ck_assert_int_eq(isGamingState(SPAWN), true);
  ck_assert_int_eq(isGamingState(MOVE), true);
  ck_assert_int_eq(isGamingState(SHIFT), true);
  ck_assert_int_eq(isGamingState(COLLISION), true);
  ck_assert_int_eq(isGamingState(START), false);
  ck_assert_int_eq(isGamingState(GAMEOVER), false);

  ck_assert_int_eq(isGamingStateWithoutKey(SHIFT), true);
  ck_assert_int_eq(isGamingStateWithoutKey(COLLISION), true);
  ck_assert_int_eq(isGamingStateWithoutKey(SPAWN), true);
  ck_assert_int_eq(isGamingStateWithoutKey(GAMEOVER), false);
}
END_TEST

START_TEST(test_action_user_input_signal) {
  ck_assert_int_eq(((int)get_signal(111) == -1), true);
  ck_assert_int_eq((get_signal(KEY_UP_B) == Up), true);
  ck_assert_int_eq((get_signal(KEY_DOWN_B) == Down), true);
  ck_assert_int_eq((get_signal(KEY_LEFT_B) == Left), true);
  ck_assert_int_eq((get_signal(KEY_RIGHT_B) == Right), true);
  ck_assert_int_eq((get_signal(KEY_SPACE) == Action), true);
  ck_assert_int_eq((get_signal(KEY_ENTER1) == Start), true);
  ck_assert_int_eq((get_signal(KEY_ENTER2) == Start), true);
  ck_assert_int_eq((get_signal(KEY_EXIT_BT) == Terminate), true);
  ck_assert_int_eq((get_signal(KEY_PAUSE_LOWER) == Pause), true);
  ck_assert_int_eq((get_signal(KEY_PAUSE_UPPER) == Pause), true);
}
END_TEST

START_TEST(test_action_user_input) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  updateParams(&bgt_prmt);

  userInput(Start, false);
  ck_assert_int_eq((bgt_prmt.state == SPAWN), true);
  userInput(-1, false);
  ck_assert_int_eq((bgt_prmt.state == MOVE), true);
  userInput(Left, false);
  ck_assert_int_eq((bgt_prmt.state == MOVE), true);
  userInput(Right, false);
  ck_assert_int_eq((bgt_prmt.state == MOVE), true);
  userInput(Action, false);
  ck_assert_int_eq((bgt_prmt.state == MOVE), true);

  userInput(Down, false);
  ck_assert_int_eq((bgt_prmt.state == COLLISION), true);

  userInput(Up, false);
  ck_assert_int_eq((bgt_prmt.state == SPAWN), true);

  userInput(Left, false);
  ck_assert_int_eq((bgt_prmt.state == MOVE), true);

  bgt_prmt.state = SHIFT;
  userInput(Left, false);
  ck_assert_int_eq((bgt_prmt.state == MOVE), true);

  bgt_prmt.state = GAMEOVER;
  userInput(Terminate, false);
  ck_assert_int_eq((bgt_prmt.state == EXIT), true);

  userInput(Terminate, false);
  ck_assert_int_eq((bgt_prmt.state == EXIT), true);

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_action_user_input_pause) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  updateParams(&bgt_prmt);

  userInput(Start, false);
  ck_assert_int_eq((bgt_prmt.state == SPAWN), true);
  userInput(-1, false);
  ck_assert_int_eq((bgt_prmt.state == MOVE), true);
  userInput(Left, false);
  ck_assert_int_eq((bgt_prmt.state == MOVE), true);
  userInput(Pause, false);
  ck_assert_int_eq((bgt_prmt.state == MOVE), true);

  userInput(Pause, false);
  ck_assert_int_eq((bgt_prmt.state == MOVE), true);

  userInput(Terminate, false);
  ck_assert_int_eq((bgt_prmt.state == GAMEOVER), true);

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_initialize_1) {
  GameInfo_t *engine = NULL;
  ck_assert_ptr_null(engine);

  initializeGameInfo(engine);
  ck_assert_ptr_null(engine);
}
END_TEST

START_TEST(test_initialize_2) {
  GameTetris *game = NULL;
  ck_assert_ptr_null(game);

  initializeGameTetris(game);
  ck_assert_ptr_null(game);

  cleanGameTetris(game);
  ck_assert_ptr_null(game);

  reset(game, START);
  ck_assert_ptr_null(game);
}
END_TEST

START_TEST(test_allocateModel) {
  Model model = {0};
  int code = allocateModel(&model);
  ck_assert_int_eq(code, BAD_SIZE);
}
END_TEST

START_TEST(test_allocateModel2) {
  Model *model = NULL;
  int code = allocateModel(model);
  ck_assert_int_eq(code, BAD_ALLOCATE);
}
END_TEST

START_TEST(test_allocateModels) {
  Models models = {0};
  int code = allocateModels(&models);
  ck_assert_int_eq(code, BAD_SIZE);
}
END_TEST

START_TEST(test_allocateModels2) {
  Models *models = NULL;
  int code = allocateModels(models);
  ck_assert_int_eq(code, BAD_ALLOCATE);
}
END_TEST

START_TEST(test_freeModel) {
  Model *model = NULL;
  freeModel(model);
  Models *models = NULL;
  freeModels(models);

  ck_assert_ptr_null(model);
  ck_assert_ptr_null(models);
}
END_TEST

START_TEST(freeGameInfot) {
  GameInfo_t *engine = NULL;

  cleanGameInfo(engine);
  ck_assert_ptr_null(engine);
}
END_TEST

START_TEST(freeGameInfo2) {
  GameInfo_t *engine = NULL;

  allocateField(engine);
  allocateNext(engine);
  freeNext(engine);
  freeField(engine);
  ck_assert_ptr_null(engine);
}
END_TEST

START_TEST(test_bad_set_and_get_model) {
  Model *model = NULL;
  int size = 5;
  setColsModel(model, size);
  setRowsModel(model, size);

  ck_assert_int_eq(getColsModel(model), 0);
  ck_assert_int_eq(getRowsModel(model), 0);

  Models *models = NULL;
  setCountModels(models, size);
  ck_assert_int_eq(getCountModels(models), 0);

  ck_assert_ptr_null(model);
  ck_assert_ptr_null(models);
}
END_TEST

START_TEST(test_bad_set_and_get_struct) {
  GameInfo_t *engine = NULL;
  setLevel(engine, INIT_LEVEL);
  setSpeed(engine, COEF_SPEED_LEVEL_1);
  setPause(engine, false);
  setScore(engine, INIT_SCORE);
  setHigeScore(engine, INIT_SCORE);

  ck_assert_int_eq(getLevel(engine), 0);
  ck_assert_int_eq(getSpeed(engine), 0);
  ck_assert_int_eq(getPause(engine), false);
  ck_assert_int_eq(getScore(engine), 0);
  ck_assert_int_eq(getHigeScore(engine), 0);
  ck_assert_ptr_null(engine);
}
END_TEST

Suite *type_test(void) {
  Suite *s = suite_create("Type test");
  TCase *tc = tcase_create("Case type");

  tcase_add_test(tc, test_pause);
  tcase_add_test(tc, test_speed);
  // tcase_add_test(tc, test_speed_check);
  tcase_add_test(tc, test_updateCurrentState);

  tcase_add_test(tc, test_action);
  tcase_add_test(tc, test_action_user_input_signal);
  tcase_add_test(tc, test_action_user_input);
  tcase_add_test(tc, test_action_user_input_pause);

  tcase_add_test(tc, test_initialize_1);
  tcase_add_test(tc, test_initialize_2);

  tcase_add_test(tc, test_allocateModel);
  tcase_add_test(tc, test_allocateModel2);
  tcase_add_test(tc, test_allocateModels);
  tcase_add_test(tc, test_allocateModels2);

  tcase_add_test(tc, freeGameInfot);
  tcase_add_test(tc, freeGameInfo2);
  tcase_add_test(tc, test_freeModel);
  tcase_add_test(tc, test_bad_set_and_get_model);
  tcase_add_test(tc, test_bad_set_and_get_struct);

  suite_add_tcase(s, tc);
  return s;
}