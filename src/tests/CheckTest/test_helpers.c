#include "../../brick_game/tetris/FiniteStateMachines/Helpers/FSMHelpers.h"
#include "../../brick_game/tetris/Helpers/GameTetrisHelpers.h"
#include "../../brick_game/tetris/Model/Helpers/ModelHelpers.h"
#include "test.h"

START_TEST(test_incorrect_index) {
  const GameTetris *p = NULL;
  ck_assert_int_eq(isNormalNextIndex(p), false);
}
END_TEST

START_TEST(test_correct_size) {
  Model model = {0};
  model.cols = 3;
  model.rows = 3;
  ck_assert_int_eq(checkSizeModel(&model), true);
}
END_TEST

START_TEST(test_incorrect_size) {
  Model model = {0};
  model.cols = 0;
  model.rows = 0;
  ck_assert_int_eq(checkSizeModel(&model), false);
}
END_TEST

START_TEST(test_incorrect1_size) {
  Model model = {0};
  model.cols = 1;
  model.rows = 0;
  ck_assert_int_eq(checkSizeModel(&model), false);
}
END_TEST

START_TEST(test_incorrect2_size) {
  Model model = {0};
  model.cols = 0;
  model.rows = 1;
  ck_assert_int_eq(checkSizeModel(&model), false);
}
END_TEST

START_TEST(test_initializeModels) {
  Models models = {0};
  ck_assert_int_eq(initializeModels(&models, NAME_FILE_TEMPLATE), true);
  ck_assert_int_eq(models.count, ST_MODELS_COUNT);
  freeModels(&models);
}
END_TEST

START_TEST(test_initializeModels2) {
  Models *models = {0};
  ck_assert_int_eq(initializeModels(models, NAME_FILE_TEMPLATE), false);
  freeModels(models);
}
END_TEST

START_TEST(test_initializeModels3) {
  Models models = {0};
  ck_assert_int_eq(initializeModels(&models, "NOFILE"), false);
  freeModels(&models);
}
END_TEST

START_TEST(test_initializeModels4) {
  Models models = {0};
  ck_assert_int_eq(
      initializeModels(&models, "../src/tests/CheckTest/testfile/two_model.txt"),
      false);
  ck_assert_int_eq(models.count, 2);
  freeModels(&models);
}
END_TEST

START_TEST(test_initializeModels5) {
  Models models = {0};
  ck_assert_int_eq(
      initializeModels(&models, "../src/tests/CheckTest/testfile/bad_model.txt"),
      false);
  ck_assert_int_eq(models.count, 2);
  freeModels(&models);
}
END_TEST

START_TEST(test_initializeModels6) {
  Models models = {0};
  models.count = __INT_MAX__;
  allocateModels(&models);
  ck_assert_ptr_null(models.models);
  ck_assert_int_eq(initializeModels(&models, NAME_FILE_TEMPLATE), false);
  ck_assert_int_ne(models.count, ST_MODELS_COUNT);
  freeModels(&models);
}
END_TEST

START_TEST(test_obtaingModels) {
  Models models = {0};
  int code = false;
  obtainingModels(&models, &code, NAME_FILE_TEMPLATE);
  ck_assert_int_eq(code, true);
  ck_assert_int_eq(models.count, ST_MODELS_COUNT);
  freeModels(&models);
}
END_TEST

START_TEST(test_obtaingModels2) {
  Models *models = NULL;
  int code = false;
  obtainingModels(models, &code, NAME_FILE_TEMPLATE);
  ck_assert_int_eq(code, false);
  freeModels(models);
}
END_TEST

START_TEST(test_obtaingModels3) {
  Models models = {0};
  int code = false;
  obtainingModels(&models, &code, "../src/tests/CheckTest/testfile/empty.txt");
  ck_assert_int_eq(code, true);
  freeModels(&models);
}
END_TEST

START_TEST(test_obtaingModels4) {
  Models models = {0};
  int code = false;
  obtainingModels(&models, &code, "../tests/testfile/nofile.txt");
  ck_assert_int_eq(code, false);
  freeModels(&models);
}
END_TEST

START_TEST(test_allocate_int_bad_size) {
  int code = false;
  int **test = allocateInt(__LONG_LONG_MAX__, __LONG_LONG_MAX__, &code);
  ck_assert_ptr_null(test);
  ck_assert_int_eq(code, BAD_ALLOCATE);
  freeIntDoubleArray(&test, HFIELD);
  ck_assert_ptr_null(test);
}
END_TEST

START_TEST(test_allocate_int_bad_size2) {
  int code = false;
  int **test = allocateInt(HFIELD, __LONG_LONG_MAX__, &code);
  ck_assert_ptr_nonnull(test);
  ck_assert_int_eq(code, BAD_ALLOCATE);
  freeIntDoubleArray(&test, HFIELD);
  ck_assert_ptr_null(test);
}
END_TEST

START_TEST(test_allocate_int_normal_size) {
  int code = false;
  int **test = allocateInt(HFIELD, WFIELD, &code);
  ck_assert_ptr_nonnull(test);
  ck_assert_int_eq(code, GOOD_ALLOCATE);
  freeIntDoubleArray(&test, HFIELD);
  ck_assert_ptr_null(test);
}
END_TEST

START_TEST(test_allocate_int_normal_size2) {
  int code = false;
  int **test = allocateInt(HNEXT, WNEXT, &code);
  ck_assert_ptr_nonnull(test);
  ck_assert_int_eq(code, GOOD_ALLOCATE);
  freeIntDoubleArray(&test, HNEXT);
  ck_assert_ptr_null(test);
}
END_TEST

START_TEST(test_allocate_int_incorrect_size) {
  int code = false;
  int **test = allocateInt(0, WNEXT, &code);
  ck_assert_ptr_null(test);

  freeIntDoubleArray(&test, 0);
  ck_assert_ptr_null(test);
}
END_TEST

START_TEST(test_allocate_int_incorrect_size2) {
  int code = false;
  int **test = allocateInt(HNEXT, 0, &code);
  ck_assert_ptr_null(test);

  freeIntDoubleArray(&test, 0);
  ck_assert_ptr_null(test);
}
END_TEST

START_TEST(test_allocate_int_incorrect_size3) {
  int code = false;
  int **test = allocateInt(0, 0, &code);
  ck_assert_ptr_null(test);

  freeIntDoubleArray(&test, 0);
  ck_assert_ptr_null(test);
}
END_TEST

START_TEST(test_random_index1) {
  int count_models = ST_MODELS_COUNT;
  ck_assert_int_eq(getRandomIndex(count_models) < count_models, true);

  count_models = 20;
  ck_assert_int_eq(getRandomIndex(count_models) < count_models, true);

  count_models = 1;
  ck_assert_int_eq(getRandomIndex(count_models) < count_models, true);
}
END_TEST

START_TEST(test_isNormalModel) {
  const Model *model = NULL;
  ck_assert_int_eq(isNormalModel(model), false);
}
END_TEST

START_TEST(test_isNormalModel2) {
  Model model = {0};
  model.cols = 0;
  model.rows = 0;
  ck_assert_int_eq(isNormalModel(&model), false);
  model.cols = 3;
  model.rows = 3;
  ck_assert_int_eq(isNormalModel(&model), false);
}
END_TEST

START_TEST(test_copyModel) {
  Model *src = NULL;
  Model *dest = NULL;
  copyModel(src, dest);
  ck_assert_ptr_null(src);
  ck_assert_ptr_null(dest);
}
END_TEST

START_TEST(test_copyModel2) {
  Model src = {0};
  Model *dest = NULL;
  copyModel(&src, dest);
  ck_assert_ptr_null(dest);
}
END_TEST

START_TEST(test_copyModel3) {
  Model *src = NULL;
  Model dest = {0};
  copyModel(src, &dest);
  ck_assert_ptr_null(src);
}
END_TEST

START_TEST(test_copyModel4) {
  Model src = {0};
  Model dest = {0};
  src.cols = 3;
  src.rows = 3;
  dest.cols = 3;
  dest.rows = 3;
  ck_assert_int_eq(allocateModel(&src), GOOD_ALLOCATE);
  ck_assert_int_eq(allocateModel(&dest), GOOD_ALLOCATE);

  copyModel(&src, &dest);

  ck_assert_ptr_nonnull(src.model_);
  ck_assert_ptr_nonnull(dest.model_);

  freeModel(&src);
  freeModel(&dest);
}
END_TEST

START_TEST(test_bad_zeroing) {
  GameInfo_t *gameInfo = NULL;
  zeroingNext(gameInfo);
  ck_assert_ptr_null(gameInfo);
  zeroingField(gameInfo);
  ck_assert_ptr_null(gameInfo);
}
END_TEST

START_TEST(test_bad_zeroing2) {
  GameInfo_t gameInfo = {0};
  zeroingNext(&gameInfo);
  ck_assert_ptr_null(gameInfo.next);
}
END_TEST

START_TEST(test_bad_zeroing3) {
  GameTetris *prmt = NULL;
  zeroingInfo(prmt);
  ck_assert_ptr_null(prmt);
}
END_TEST

START_TEST(test_model_operation) {
  GameTetris *bgt_prmt = NULL;
  addedModelToField(bgt_prmt);
  ck_assert_ptr_null(bgt_prmt);
}
END_TEST

START_TEST(test_model_operation2) {
  GameTetris bgt_prmt = {0};
  ck_assert_int_eq(allocateField(&bgt_prmt.engine), GOOD_ALLOCATE);

  addedModelToField(&bgt_prmt);
  ck_assert_ptr_null(bgt_prmt.current.model_);
  freeField(&bgt_prmt.engine);
}
END_TEST

START_TEST(test_save_1) {
  GameInfo_t *engine = NULL;
  saveHighScore(engine);
  initializeHighScore(engine);
  ck_assert_ptr_null(engine);
}
END_TEST

Suite *test_model(void) {
  Suite *s = suite_create("Model test");
  TCase *tc = tcase_create("Case parsing model");

  // Parser test
  tcase_add_test(tc, test_correct_size);
  tcase_add_test(tc, test_incorrect_size);
  tcase_add_test(tc, test_incorrect1_size);
  tcase_add_test(tc, test_incorrect2_size);

  tcase_add_test(tc, test_initializeModels);
  tcase_add_test(tc, test_initializeModels2);
  tcase_add_test(tc, test_initializeModels3);
  tcase_add_test(tc, test_initializeModels4);
  tcase_add_test(tc, test_initializeModels5);
  tcase_add_test(tc, test_initializeModels6);
  tcase_add_test(tc, test_obtaingModels);
  tcase_add_test(tc, test_obtaingModels2);
  tcase_add_test(tc, test_obtaingModels3);
  tcase_add_test(tc, test_obtaingModels4);

  // Type test

  tcase_add_test(tc, test_allocate_int_bad_size);
  tcase_add_test(tc, test_allocate_int_bad_size2);
  tcase_add_test(tc, test_allocate_int_normal_size);
  tcase_add_test(tc, test_allocate_int_normal_size2);
  tcase_add_test(tc, test_allocate_int_incorrect_size);
  tcase_add_test(tc, test_allocate_int_incorrect_size2);
  tcase_add_test(tc, test_allocate_int_incorrect_size3);

  // FSM test
  tcase_add_test(tc, test_incorrect_index);
  tcase_add_test(tc, test_random_index1);
  tcase_add_test(tc, test_isNormalModel);
  tcase_add_test(tc, test_isNormalModel2);
  tcase_add_test(tc, test_copyModel);
  tcase_add_test(tc, test_copyModel2);
  tcase_add_test(tc, test_copyModel3);
  tcase_add_test(tc, test_copyModel4);
  tcase_add_test(tc, test_bad_zeroing);
  tcase_add_test(tc, test_bad_zeroing2);
  tcase_add_test(tc, test_bad_zeroing3);

  tcase_add_test(tc, test_model_operation);
  tcase_add_test(tc, test_model_operation2);

  tcase_add_test(tc, test_save_1);

  suite_add_tcase(s, tc);
  return s;
}