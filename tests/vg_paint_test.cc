#include "base/vg_paint.h"
#include "gtest/gtest.h"

TEST(VGPaint, basic) {
  vg_paint_t* p = vg_paint_create();
  
  ASSERT_EQ(vg_paint_set_type(p, VG_PAINT_STROKE), RET_OK);
  ASSERT_EQ(p->type, VG_PAINT_STROKE);
  
  ASSERT_EQ(vg_paint_set_type(p, VG_PAINT_FILL), RET_OK);
  ASSERT_EQ(p->type, VG_PAINT_FILL);

  ASSERT_EQ(vg_paint_set_join_type(p, VG_JOIN_MITTER), RET_OK);
  ASSERT_EQ(p->join, VG_JOIN_MITTER);
  
  ASSERT_EQ(vg_paint_set_cap_type(p, VG_CAP_ROUND), RET_OK);
  ASSERT_EQ(p->cap, VG_CAP_ROUND);

  ASSERT_EQ(vg_paint_set_line_width(p, 5), RET_OK);
  ASSERT_EQ(p->line_width, 5);

  ASSERT_EQ(vg_paint_set_linear_gradient(p, 1, 2, 3, 4), RET_OK);
  ASSERT_EQ(vg_paint_add_gradient_stop(p, color_init(1, 1, 1, 1), 1), RET_OK);
  ASSERT_EQ(p->gradient->type, VG_GRADIENT_LINEAR);
  ASSERT_EQ(vg_gradient_get_stop(p->gradient, 0)->offset, 1);
  
  ASSERT_EQ(vg_paint_set_radial_gradient(p, 1, 2, 3, 4), RET_OK);
  ASSERT_EQ(vg_paint_add_gradient_stop(p, color_init(1, 1, 1, 1), 1), RET_OK);
  ASSERT_EQ(p->gradient->type, VG_GRADIENT_RADIAL);
  ASSERT_EQ(vg_gradient_get_stop(p->gradient, 0)->offset, 1);

  vg_paint_destroy(p);
}

