#include "base/vg_path.h"
#include "gtest/gtest.h"

TEST(VGPath, move_to) {
  vg_path_t* first = vg_path_add_move_to(NULL, 10, 20);
  ASSERT_EQ(first->type, VG_PATH_MOVE_TO);
  ASSERT_EQ(first->u.move_to.x, 10);
  ASSERT_EQ(first->u.move_to.y, 20);
  ASSERT_EQ(first->next, (vg_path_t*)NULL);
  vg_path_destroy(first);
}

TEST(VGPath, line_to) {
  vg_path_t* first = vg_path_add_line_to(NULL, 10, 20);
  ASSERT_EQ(first->type, VG_PATH_LINE_TO);
  ASSERT_EQ(first->u.line_to.x, 10);
  ASSERT_EQ(first->u.line_to.y, 20);
  ASSERT_EQ(first->next, (vg_path_t*)NULL);
  vg_path_destroy(first);
}

TEST(VGPath, cubic_to) {
  vg_path_t* first = vg_path_add_cubic_to(NULL, 10, 20, 30, 40, 50, 60);
  ASSERT_EQ(first->type, VG_PATH_CUBIC_TO);
  ASSERT_EQ(first->u.cubic_to.ox, 10);
  ASSERT_EQ(first->u.cubic_to.oy, 20);
  ASSERT_EQ(first->u.cubic_to.ix, 30);
  ASSERT_EQ(first->u.cubic_to.iy, 40);
  ASSERT_EQ(first->u.cubic_to.x, 50);
  ASSERT_EQ(first->u.cubic_to.y, 60);
  ASSERT_EQ(first->next, (vg_path_t*)NULL);
  vg_path_destroy(first);
}

TEST(VGPath, close) {
  vg_path_t* first = vg_path_add_close(NULL);
  ASSERT_EQ(first->type, VG_PATH_CLOSE);
  ASSERT_EQ(first->next, (vg_path_t*)NULL);
  vg_path_destroy(first);
}

TEST(VGPath, multi) {
  vg_path_t* first = vg_path_add_move_to(NULL, 10, 20);
  first = vg_path_add_line_to(first, 30, 40);
  first = vg_path_add_cubic_to(first, 1, 2, 3, 4, 5, 6);
  first = vg_path_add_close(first);

  ASSERT_EQ(first->type, VG_PATH_MOVE_TO);
  ASSERT_EQ(first->next->type, VG_PATH_LINE_TO);
  ASSERT_EQ(first->next->next->type, VG_PATH_CUBIC_TO);
  ASSERT_EQ(first->next->next->next->type, VG_PATH_CLOSE);

  vg_path_destroy(first);
}
