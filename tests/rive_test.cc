#include "rive/rive.h"
#include "gtest/gtest.h"

TEST(rive, basic) {
  value_t v;
  widget_t* w = rive_create(NULL, 10, 20, 30, 40);

  widget_destroy(w);
}
