#include "color.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(color_tests);

TEST_SETUP(color_tests) {}

TEST_TEAR_DOWN(color_tests) {}

TEST(color_tests, test_color_hue_to_rgb) {
  typedef struct Case {
    uint16_t hue;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
  } Case;

  Case cases[9] = {
    {0, 255, 0, 0},
    {32, 255, 192, 0},
    {64, 129, 255, 0},
    {96, 0, 255, 60},
    {128, 0, 255, 252},
    {160, 0, 69, 255},
    {192, 120, 0, 255},
    {224, 255, 0, 201},
    {255, 255, 0, 15}
  };

  char msg[50];
  for(uint8_t i = 0; i < 9; i++) {
    Color dummy_color = {
      .hue = cases[i].hue
    };
    color_hue_to_rgb(&dummy_color);

    sprintf(msg, "Failed iteration %i", i);
    TEST_ASSERT_EQUAL_MESSAGE(cases[i].red, dummy_color.red, msg);
    TEST_ASSERT_EQUAL_MESSAGE(cases[i].green, dummy_color.green, msg);
    TEST_ASSERT_EQUAL_MESSAGE(cases[i].blue, dummy_color.blue, msg);
  }
}

TEST_GROUP_RUNNER(color_tests) {
  RUN_TEST_CASE(color_tests, test_color_hue_to_rgb);
}
