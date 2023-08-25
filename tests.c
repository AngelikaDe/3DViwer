#include <check.h>

#include "s21_parser.h"

#define EPS 1e-06

START_TEST(parser_1) {
  model_data d = {0};
  const char *filename_1 = "obj_files/cube.obj";
  int res = parser(&d, filename_1);
  ck_assert_int_eq(res, 0);
}

START_TEST(parser_2) {
  model_data d = {0};
  const char *filename_2 = NULL;
  int res = parser(&d, filename_2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(affine_rotate_X_1) {
  model_data d = {0};
  const char *filename = "obj_files/cube.obj";
  double vertices_arr[] = {
      0.000000, 0.000000, 0.000000,  0.000000, 0.444614, -0.369880,
      0.000000, 0.069413, -0.068582, 0.000000, 0.514027, -0.438462,
      0.450000, 0.000000, 0.000000,  0.450000, 0.444614, -0.369880,
      0.450000, 0.069413, -0.068582, 0.450000, 0.514027, -0.438462,
  };
  parser(&d, filename);
  rotate(&d, 30, 1);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices[i], vertices_arr[i], EPS);
    i++;
  }
}
END_TEST

START_TEST(affine_rotate_Y_1) {
  model_data d = {0};
  const char *filename = "obj_files/cube.obj";
  double vertices_arr[] = {
      0.000000, 0.000000, 0.000000, -0.444614, 0.000000, -0.369880,
      0.000000, 0.450000, 0.000000, -0.444614, 0.450000, -0.369880,
      0.069413, 0.000000, 0.068582, -0.375201, 0.000000, -0.301297,
      0.069413, 0.450000, 0.068582, -0.375201, 0.450000, -0.301297};
  parser(&d, filename);
  rotate(&d, 30, 2);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices[i], vertices_arr[i], EPS);
    i++;
  }
}
END_TEST

START_TEST(affine_rotate_Z_1) {
  model_data d = {0};
  const char *filename = "obj_files/cube.obj";
  double vertices_arr[] = {
      0.000000, 0.000000,  0.000000, 0.000000, 0.000000,  0.450000,
      0.444614, -0.369880, 0.000000, 0.444614, -0.369880, 0.450000,
      0.069413, -0.068582, 0.000000, 0.069413, -0.068582, 0.450000,
      0.514027, -0.438462, 0.000000, 0.514027, -0.438462, 0.450000,
  };
  parser(&d, filename);
  rotate(&d, 30, 3);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices[i], vertices_arr[i], EPS);
    i++;
  }
}
END_TEST

START_TEST(affine_scale_1) {
  model_data d = {0};
  const char *filename = "obj_files/cube.obj";
  double vertices_arr[] = {
      0.0000000, 0.0000000, 0.0000000, 0.0000000, 0.0000000, 1.3500000,
      0.0000000, 1.3500000, 0.0000000, 0.0000000, 1.3500000, 1.3500000,
      1.3500000, 0.0000000, 0.0000000, 1.3500000, 0.0000000, 1.3500000,
      1.3500000, 1.3500000, 0.0000000, 1.3500000, 1.3500000, 1.3500000};
  parser(&d, filename);
  scaling(&d, 3);
  ck_assert_int_eq(d.vertices_count, 8);
  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices[i], vertices_arr[i], EPS);
    i++;
  }
}
END_TEST

START_TEST(affine_move_X_1) {
  model_data d = {0};
  const char *filename = "obj_files/cube.obj";
  double vertices_arr[] = {
      3.0000000, 0.0000000, 0.0000000, 3.0000000, 0.0000000, 0.4500000,
      3.0000000, 0.4500000, 0.0000000, 3.0000000, 0.4500000, 0.4500000,
      3.4500000, 0.0000000, 0.0000000, 3.4500000, 0.0000000, 0.4500000,
      3.4500000, 0.4500000, 0.0000000, 3.4500000, 0.4500000, 0.4500000};
  parser(&d, filename);
  move_obj(&d, 3.0, 0.0, 0.0);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices[i], vertices_arr[i], EPS);
    i++;
  }
}
END_TEST

START_TEST(affine_move_Y_1) {
  model_data d = {0};
  const char *filename = "obj_files/cube.obj";
  double vertices_arr[] = {
      0.0000000, 3.0000000, 0.0000000, 0.0000000, 3.0000000, 0.4500000,
      0.0000000, 3.4500000, 0.0000000, 0.0000000, 3.4500000, 0.4500000,
      0.4500000, 3.0000000, 0.0000000, 0.4500000, 3.0000000, 0.4500000,
      0.4500000, 3.4500000, 0.0000000, 0.4500000, 3.4500000, 0.4500000};
  parser(&d, filename);
  move_obj(&d, 0, 3, 0);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices[i], vertices_arr[i], EPS);
    i++;
  }
}
END_TEST

START_TEST(affine_move_Z_1) {
  model_data d = {0};
  const char *filename = "obj_files/cube.obj";
  double vertices_arr[] = {
      0.0000000, 0.0000000, 3.0000000, 0.0000000, 0.0000000, 3.4500000,
      0.0000000, 0.4500000, 3.0000000, 0.0000000, 0.4500000, 3.4500000,
      0.4500000, 0.0000000, 3.0000000, 0.4500000, 0.0000000, 3.4500000,
      0.4500000, 0.4500000, 3.0000000, 0.4500000, 0.4500000, 3.4500000};
  parser(&d, filename);
  move_obj(&d, 0, 0, 3);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices[i], vertices_arr[i], EPS);
    i++;
  }
}
END_TEST

Suite *lib_suite(void) {
  Suite *s;
  s = suite_create("Check");
  TCase *tc_parser_1;
  tc_parser_1 = tcase_create("parser_1");
  suite_add_tcase(s, tc_parser_1);
  tcase_add_test(tc_parser_1, parser_1);

  TCase *tc_parser_2;
  tc_parser_2 = tcase_create("parser_2");
  suite_add_tcase(s, tc_parser_2);
  tcase_add_test(tc_parser_2, parser_2);

  TCase *tc_affine_rotate_X_1;
  tc_affine_rotate_X_1 = tcase_create("affine_rotate_X_1");
  suite_add_tcase(s, tc_affine_rotate_X_1);
  tcase_add_test(tc_affine_rotate_X_1, affine_rotate_X_1);

  TCase *tc_affine_rotate_Y_1;
  tc_affine_rotate_Y_1 = tcase_create("affine_rotate_Y_1");
  suite_add_tcase(s, tc_affine_rotate_Y_1);
  tcase_add_test(tc_affine_rotate_Y_1, affine_rotate_Y_1);

  TCase *tc_affine_rotate_Z_1;
  tc_affine_rotate_Z_1 = tcase_create("affine_rotate_Z_1");
  suite_add_tcase(s, tc_affine_rotate_Z_1);
  tcase_add_test(tc_affine_rotate_Z_1, affine_rotate_Z_1);

  TCase *tc_affine_scale_1;
  tc_affine_scale_1 = tcase_create("affine_scale_1");
  suite_add_tcase(s, tc_affine_scale_1);
  tcase_add_test(tc_affine_scale_1, affine_scale_1);

  TCase *tc_affine_move_X_1;
  tc_affine_move_X_1 = tcase_create("affine_move_X_1");
  suite_add_tcase(s, tc_affine_move_X_1);
  tcase_add_test(tc_affine_move_X_1, affine_move_X_1);

  TCase *tc_affine_move_Y_1;
  tc_affine_move_Y_1 = tcase_create("affine_move_Y_1");
  suite_add_tcase(s, tc_affine_move_Y_1);
  tcase_add_test(tc_affine_move_Y_1, affine_move_Y_1);

  TCase *tc_affine_move_Z_1;
  tc_affine_move_Z_1 = tcase_create("affine_move_Z_1");
  suite_add_tcase(s, tc_affine_move_Z_1);
  tcase_add_test(tc_affine_move_Z_1, affine_move_Z_1);

  return s;
}

int main(void) {
  Suite *s;
  SRunner *sr;
  s = lib_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
  return 0;
}
