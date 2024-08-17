#define TESTING
#include "../../brick_game/tetris/FiniteStateMachines/FiniteStateMachines.h"
#include "../../brick_game/tetris/FiniteStateMachines/Helpers/FSMHelpers.h"
#include "test.h"

START_TEST(test_fsm_start) {
  GameTetris bgt_prmt = {0};
  bgt_prmt.state = START;
  UserAction_t action = Start;
  FSM_Start(action, &bgt_prmt);
  ck_assert_int_eq(bgt_prmt.state, SPAWN);

  action = Terminate;
  FSM_Start(action, &bgt_prmt);
  ck_assert_int_eq(bgt_prmt.state, EXIT);

  bgt_prmt.state = START;
  action = Up;
  FSM_Start(action, &bgt_prmt);
  ck_assert_int_eq(bgt_prmt.state, START);
}
END_TEST

START_TEST(test_fsm_spawn) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = SPAWN;

  FSM_Spawn(&bgt_prmt);

  ck_assert_ptr_nonnull(bgt_prmt.models.models);
  ck_assert_ptr_nonnull(bgt_prmt.current.model_);
  // ck_assert_ptr_nonnull(bgt_prmt.next.model_);
  ck_assert_ptr_nonnull(bgt_prmt.engine.next);
  ck_assert_int_eq(bgt_prmt.state, MOVE);

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_spawn2) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = SPAWN;

  FSM_Spawn(&bgt_prmt);
  ck_assert_ptr_nonnull(bgt_prmt.models.models);
  ck_assert_ptr_nonnull(bgt_prmt.current.model_);
  // ck_assert_ptr_nonnull(bgt_prmt.next.model_);
  ck_assert_ptr_nonnull(bgt_prmt.engine.next);
  ck_assert_int_eq(bgt_prmt.state, MOVE);

  bgt_prmt.state = SPAWN;
  FSM_Spawn(&bgt_prmt);
  ck_assert_ptr_nonnull(bgt_prmt.models.models);
  ck_assert_ptr_nonnull(bgt_prmt.current.model_);
  // ck_assert_ptr_nonnull(bgt_prmt.next.model_);
  ck_assert_ptr_nonnull(bgt_prmt.engine.next);
  ck_assert_int_eq(bgt_prmt.state, MOVE);

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_spawn3) {
  GameTetris *bgt_prmt = NULL;
  FSM_Spawn(bgt_prmt);
  ck_assert_ptr_null(bgt_prmt);
}
END_TEST

void checkCorrectMatrix(const Model *truem, const Model *checkedm) {
  ck_assert_int_eq(truem->cols, checkedm->cols);
  ck_assert_int_eq(truem->rows, checkedm->rows);
  ck_assert_ptr_nonnull(truem->model_);
  ck_assert_ptr_nonnull(checkedm->model_);
  for (size_t i = 0; i < truem->rows; i++)
    for (size_t j = 0; j < truem->cols; j++) {
      ck_assert_int_eq(truem->model_[i][j], checkedm->model_[i][j]);
    }
}

START_TEST(test_fsm_move_action) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = SPAWN;
  UserAction_t action = Action;

  for (size_t i = 0; i < 20; i++) {
    FSM_Spawn(&bgt_prmt);
    bgt_prmt.current.position[X] = 5;
    bgt_prmt.current.position[Y] = 6;
    Model truem = {0};
    copyModel(&bgt_prmt.current, &truem);

    FSM_Move(action, &bgt_prmt);
    ck_assert_int_eq(bgt_prmt.state, MOVE);

    ck_assert_int_eq(rotateModel(&truem), true);
    checkCorrectMatrix(&truem, &bgt_prmt.current);

    freeModel(&truem);
    zeroingInfo(&bgt_prmt);
  }
  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_move_action2) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = SPAWN;
  UserAction_t action = Action;

  FSM_Spawn(&bgt_prmt);

  Model truem = {0};
  copyModel(&bgt_prmt.current, &truem);

  bgt_prmt.current.position[X] = 5;
  bgt_prmt.current.position[Y] = 6;
  bgt_prmt.engine.field[5][6] = true;

  FSM_Move(action, &bgt_prmt);
  ck_assert_int_eq(bgt_prmt.state, MOVE);
  checkCorrectMatrix(&truem, &bgt_prmt.current);

  freeModel(&truem);
  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_move_action3) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = SPAWN;
  UserAction_t action = Action;

  FSM_Spawn(&bgt_prmt);

  Model truem = {0};
  copyModel(&bgt_prmt.current, &truem);

  bgt_prmt.current.position[X] = -1;
  bgt_prmt.current.position[Y] = -2;

  FSM_Move(action, &bgt_prmt);
  ck_assert_int_eq(bgt_prmt.state, MOVE);

  checkCorrectMatrix(&truem, &bgt_prmt.current);
  freeModel(&truem);
  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_move_action4) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = MOVE;
  UserAction_t action = Action;

  // FSM_Spawn(&bgt_prmt);
  copyModel(&bgt_prmt.models.models[3], &bgt_prmt.current);
  int x_pos = 5;

  bgt_prmt.current.position[X] = x_pos;
  bgt_prmt.current.position[Y] = 5;

  FSM_Move(action, &bgt_prmt);
  ck_assert_int_eq(bgt_prmt.state, MOVE);
  ck_assert_int_eq(bgt_prmt.current.position[X], x_pos);

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_move_left) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = SPAWN;

  FSM_Spawn(&bgt_prmt);

  int x_pos = 5;

  bgt_prmt.current.position[X] = x_pos;
  bgt_prmt.current.position[Y] = 5;

  UserAction_t action = Up;
  FSM_Move(action, &bgt_prmt);
  ck_assert_int_eq(bgt_prmt.state, MOVE);

  action = Left;
  FSM_Move(action, &bgt_prmt);
  ck_assert_int_eq(bgt_prmt.state, MOVE);
  ck_assert_int_eq(bgt_prmt.current.position[X], (x_pos - 1));

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_move_left2) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = SPAWN;
  UserAction_t action = Left;

  FSM_Spawn(&bgt_prmt);

  int x_pos = 0;

  bgt_prmt.current.position[X] = x_pos;
  bgt_prmt.current.position[Y] = 5;

  FSM_Move(action, &bgt_prmt);
  ck_assert_int_eq(bgt_prmt.state, MOVE);
  ck_assert_int_eq(bgt_prmt.current.position[X], x_pos);

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_move_left3) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = MOVE;
  UserAction_t action = Left;

  // FSM_Spawn(&bgt_prmt);
  copyModel(&bgt_prmt.models.models[0], &bgt_prmt.current);
  int x_pos = 5;

  bgt_prmt.current.position[X] = x_pos;
  bgt_prmt.current.position[Y] = 5;
  bgt_prmt.engine.field[5][x_pos - 2] = true;

  FSM_Move(action, &bgt_prmt);
  ck_assert_int_eq(bgt_prmt.state, MOVE);
  ck_assert_int_eq(bgt_prmt.current.position[X], x_pos);

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_move_right) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = SPAWN;
  UserAction_t action = Right;

  FSM_Spawn(&bgt_prmt);

  int x_pos = 5;

  bgt_prmt.current.position[X] = x_pos;
  bgt_prmt.current.position[Y] = 5;

  FSM_Move(action, &bgt_prmt);
  ck_assert_int_eq(bgt_prmt.state, MOVE);
  ck_assert_int_eq(bgt_prmt.current.position[X], (x_pos + 1));

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_move_right2) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = SPAWN;
  UserAction_t action = Right;

  FSM_Spawn(&bgt_prmt);

  int x_pos = 10;

  bgt_prmt.current.position[X] = x_pos;
  bgt_prmt.current.position[Y] = 5;

  FSM_Move(action, &bgt_prmt);
  ck_assert_int_eq(bgt_prmt.state, MOVE);
  ck_assert_int_eq(bgt_prmt.current.position[X], x_pos);

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_move_right3) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = MOVE;
  UserAction_t action = Right;

  // FSM_Spawn(&bgt_prmt);
  copyModel(&bgt_prmt.models.models[0], &bgt_prmt.current);
  int x_pos = 5;

  bgt_prmt.current.position[X] = x_pos;
  bgt_prmt.current.position[Y] = 5;
  bgt_prmt.engine.field[5][x_pos + 3] = true;

  FSM_Move(action, &bgt_prmt);
  ck_assert_int_eq(bgt_prmt.state, MOVE);
  ck_assert_int_eq(bgt_prmt.current.position[X], x_pos);

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_move_dowm) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = MOVE;
  UserAction_t action = Down;

  // FSM_Spawn(&bgt_prmt);
  copyModel(&bgt_prmt.models.models[0], &bgt_prmt.current);
  int x_pos = 5;

  bgt_prmt.current.position[X] = x_pos;
  bgt_prmt.current.position[Y] = 5;
  bgt_prmt.engine.field[5][x_pos + 3] = true;

  FSM_Move(action, &bgt_prmt);
  ck_assert_int_eq(bgt_prmt.state, COLLISION);
  ck_assert_int_eq(bgt_prmt.current.position[Y], 19);

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_shift) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = SHIFT;

  copyModel(&bgt_prmt.models.models[0], &bgt_prmt.current);
  int x_pos = 5;

  bgt_prmt.current.position[X] = x_pos;
  bgt_prmt.current.position[Y] = 4;
  bgt_prmt.engine.field[5][5] = true;

  FSM_Shift(&bgt_prmt);

  ck_assert_int_eq(bgt_prmt.state, COLLISION);
  ck_assert_int_eq(bgt_prmt.current.position[Y], 4);

  cleanGameTetris(&bgt_prmt);
}
END_TEST

void fillField(const int y, GameTetris *bgt_prmt) {
  for (int i = 0; i < WFIELD; i++) bgt_prmt->engine.field[y][i] = true;
}

START_TEST(test_fsm_collide_one_level) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = COLLISION;

  fillField(19, &bgt_prmt);

  FSM_Collision(&bgt_prmt);

  ck_assert_int_eq(bgt_prmt.state, SPAWN);
  ck_assert_int_eq(bgt_prmt.engine.score, POINT_ONE_LINE);

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_collide_two_level) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = COLLISION;

  fillField(19, &bgt_prmt);
  fillField(18, &bgt_prmt);

  FSM_Collision(&bgt_prmt);

  ck_assert_int_eq(bgt_prmt.state, SPAWN);
  ck_assert_int_eq(bgt_prmt.engine.score, POINT_TWO_LINE);

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_collide_three_level) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = COLLISION;

  fillField(19, &bgt_prmt);
  fillField(18, &bgt_prmt);
  fillField(17, &bgt_prmt);

  FSM_Collision(&bgt_prmt);

  ck_assert_int_eq(bgt_prmt.state, SPAWN);
  ck_assert_int_eq(bgt_prmt.engine.score, POINT_THREE_LINE);

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_collide_four_level) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = COLLISION;

  fillField(19, &bgt_prmt);
  fillField(18, &bgt_prmt);
  fillField(17, &bgt_prmt);
  fillField(16, &bgt_prmt);

  FSM_Collision(&bgt_prmt);

  ck_assert_int_eq(bgt_prmt.state, SPAWN);
  ck_assert_int_eq(bgt_prmt.engine.score, POINT_FOUR_LINE);

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_collide_one_level_and_big_score) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  int score = 66666;
  bgt_prmt.engine.score = score;
  bgt_prmt.state = COLLISION;

  fillField(19, &bgt_prmt);

  FSM_Collision(&bgt_prmt);

  ck_assert_int_eq(bgt_prmt.state, SPAWN);
  ck_assert_int_eq(bgt_prmt.engine.score, score + POINT_ONE_LINE);

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_collide_zero_level) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = COLLISION;

  FSM_Collision(&bgt_prmt);

  ck_assert_int_eq(bgt_prmt.state, SPAWN);
  ck_assert_int_eq(bgt_prmt.engine.score, 0);

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_collide_bad_level) {
  GameTetris bgt_prmt = {0};
  initializeGameTetris(&bgt_prmt);
  bgt_prmt.state = COLLISION;

  fillField(0, &bgt_prmt);

  FSM_Collision(&bgt_prmt);

  ck_assert_int_eq(bgt_prmt.state, GAMEOVER);

  cleanGameTetris(&bgt_prmt);
}
END_TEST

START_TEST(test_fsm_collision_level) {
  GameTetris bgt_prmt = {0};

  setLevel(&bgt_prmt.engine, LFIRST);
  ck_assert_int_eq(getTime(&bgt_prmt.engine), COEF_SPEED_LEVEL_1);
  setLevel(&bgt_prmt.engine, LSECOND);
  ck_assert_int_eq(getTime(&bgt_prmt.engine), COEF_SPEED_LEVEL_2);
  setLevel(&bgt_prmt.engine, LTHIRD);
  ck_assert_int_eq(getTime(&bgt_prmt.engine), COEF_SPEED_LEVEL_3);
  setLevel(&bgt_prmt.engine, LFOURTH);
  ck_assert_int_eq(getTime(&bgt_prmt.engine), COEF_SPEED_LEVEL_4);
  setLevel(&bgt_prmt.engine, LFIFTH);
  ck_assert_int_eq(getTime(&bgt_prmt.engine), COEF_SPEED_LEVEL_5);
  setLevel(&bgt_prmt.engine, LSIXTH);
  ck_assert_int_eq(getTime(&bgt_prmt.engine), COEF_SPEED_LEVEL_6);
  setLevel(&bgt_prmt.engine, LSEVENTH);
  ck_assert_int_eq(getTime(&bgt_prmt.engine), COEF_SPEED_LEVEL_7);
  setLevel(&bgt_prmt.engine, LEIGHTH);
  ck_assert_int_eq(getTime(&bgt_prmt.engine), COEF_SPEED_LEVEL_8);
  setLevel(&bgt_prmt.engine, LNINETH);
  ck_assert_int_eq(getTime(&bgt_prmt.engine), COEF_SPEED_LEVEL_9);
  setLevel(&bgt_prmt.engine, LTENTH);
  ck_assert_int_eq(getTime(&bgt_prmt.engine), COEF_SPEED_LEVEL_10);

  bgt_prmt.engine.level = 12;
  ck_assert_int_eq(getTime(&bgt_prmt.engine), COEF_SPEED_LEVEL_1);
}
END_TEST

START_TEST(test_fsm_gameover) {
  GameTetris bgt_prmt = {0};
  bgt_prmt.state = GAMEOVER;
  UserAction_t action = Start;
  FSM_GameOver(action, &bgt_prmt);
  ck_assert_int_eq(bgt_prmt.state, SPAWN);

  bgt_prmt.state = GAMEOVER;
  action = Terminate;
  FSM_GameOver(action, &bgt_prmt);
  ck_assert_int_eq(bgt_prmt.state, EXIT);

  bgt_prmt.state = GAMEOVER;
  action = Up;
  FSM_GameOver(action, &bgt_prmt);
  ck_assert_int_eq(bgt_prmt.state, GAMEOVER);
}
END_TEST

START_TEST(test_addModelToField) {
  GameTetris *bgt_prmt = NULL;
  addedModelToField(bgt_prmt);
  ck_assert_ptr_null(bgt_prmt);
}

START_TEST(test_timer) {
  GameTetris bgt_prmt = {0};
  bool code = initializeGameTetris(&bgt_prmt);
  ck_assert_int_eq(code, true);
  updateParams(&bgt_prmt);
  bgt_prmt.state = MOVE;

  runTime(&bgt_prmt.timer);
  stopTime(&bgt_prmt.timer);
  GameState_t true_state = SHIFT;
  ck_assert_int_eq(bgt_prmt.state, true_state);

  cleanGameTetris(&bgt_prmt);
}

START_TEST(test_timer2) {
  GameTimer_t *timer = NULL;
  initializeTimer(timer);
  ck_assert_ptr_null(timer);
  freeTimer(timer);
  ck_assert_ptr_null(timer);
  stopTime(timer);
  ck_assert_ptr_null(timer);
}

START_TEST(test_timer3) {
  GameTimer_t timer = {0};

  freeTimer(&timer);
  ck_assert_ptr_null(timer.thread);
  stopTime(&timer);
  ck_assert_ptr_null(timer.thread);
}

Suite *test_fsm(void) {
  Suite *s = suite_create("FSM test");
  TCase *tc = tcase_create("Case FSM");

  tcase_add_test(tc, test_fsm_start);

  tcase_add_test(tc, test_fsm_spawn);
  tcase_add_test(tc, test_fsm_spawn2);
  tcase_add_test(tc, test_fsm_spawn3);

  tcase_add_test(tc, test_fsm_move_action);
  tcase_add_test(tc, test_fsm_move_action2);
  tcase_add_test(tc, test_fsm_move_action3);
  tcase_add_test(tc, test_fsm_move_action4);

  tcase_add_test(tc, test_fsm_move_left);
  tcase_add_test(tc, test_fsm_move_left2);
  tcase_add_test(tc, test_fsm_move_left3);

  tcase_add_test(tc, test_fsm_move_right);
  tcase_add_test(tc, test_fsm_move_right2);
  tcase_add_test(tc, test_fsm_move_right3);

  tcase_add_test(tc, test_fsm_move_dowm);
  tcase_add_test(tc, test_fsm_shift);

  tcase_add_test(tc, test_fsm_collide_one_level);
  tcase_add_test(tc, test_fsm_collide_two_level);
  tcase_add_test(tc, test_fsm_collide_three_level);
  tcase_add_test(tc, test_fsm_collide_four_level);
  tcase_add_test(tc, test_fsm_collide_one_level_and_big_score);
  tcase_add_test(tc, test_fsm_collide_zero_level);
  tcase_add_test(tc, test_fsm_collide_bad_level);
  tcase_add_test(tc, test_fsm_collision_level);

  tcase_add_test(tc, test_fsm_gameover);

  tcase_add_test(tc, test_addModelToField);

  tcase_add_test(tc, test_timer);
  tcase_add_test(tc, test_timer2);
  tcase_add_test(tc, test_timer3);

  suite_add_tcase(s, tc);
  return s;
}