#include <stdbool.h>

#include "charlieplex.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(charlieplex_tests);

TEST_SETUP(charlieplex_tests) {}

TEST_TEAR_DOWN(charlieplex_tests) {}

TEST(charlieplex_tests, test_charlieplex_new) {
  uint8_t dummy_values[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  CharliePlex dummy_cp = charlieplex_new(12, 34, &dummy_values[0]);

  TEST_ASSERT_EQUAL(false, dummy_cp.led_active);
  TEST_ASSERT_EQUAL(12, dummy_cp.led_count);
  TEST_ASSERT_EQUAL(0, dummy_cp.led_index);
  TEST_ASSERT_EQUAL(34, dummy_cp.value_count);
  TEST_ASSERT_EQUAL(0, dummy_cp.value_index);
}

TEST(charlieplex_tests, test_charlieplex_step) {
  uint8_t dummy_values[6] = {3, 2, 1, 0, 1, 2};
  CharliePlex dummy_cp = charlieplex_new(6, 3, &dummy_values[0]);

  uint8_t expected_led_index[27] = {
    0, 0, 0,
    1, 1, 1,
    2, 2, 2,
    3, 3, 3,
    4, 4, 4,
    5, 5, 5,
    0, 0, 0,
    1, 1, 1,
    2, 2, 2
  };

  uint8_t expected_led_active[27] = {
    true, true, true,
    true, true, false,
    true, false, false,
    false, false, false,
    true, false, false,
    true, true, false,
    true, true, true,
    true, true, false,
    true, false, false
  };

  uint8_t expected_status[27] = {
    3, 0, 0,
    2, 0, 1,
    3, 1, 0,
    2, 0, 0,
    3, 1, 0,
    3, 0, 1,
    3, 0, 0,
    2, 0, 1,
    3, 1, 0
  };

  char msg[50];
  for(uint8_t i = 0; i < 27; i++) {
    sprintf(msg, "Failed iteration %i", i);
    TEST_ASSERT_EQUAL_MESSAGE(expected_led_index[i], dummy_cp.led_index, msg);
    TEST_ASSERT_EQUAL_MESSAGE(expected_led_active[i], dummy_cp.led_active, msg);
    TEST_ASSERT_EQUAL_MESSAGE(expected_status[i], dummy_cp.status, msg);

    charlieplex_step(&dummy_cp);
  }
}

TEST(charlieplex_tests, test_charlieplex_new_initial_active) {
  uint8_t dummy_values[12] = {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  CharliePlex dummy_cp = charlieplex_new(12, 8, &dummy_values[0]);

  TEST_ASSERT_EQUAL(true, dummy_cp.led_active);
  TEST_ASSERT_EQUAL(12, dummy_cp.led_count);
  TEST_ASSERT_EQUAL(0, dummy_cp.led_index);
  TEST_ASSERT_EQUAL(8, dummy_cp.value_count);
  TEST_ASSERT_EQUAL(0, dummy_cp.value_index);
}

TEST_GROUP_RUNNER(charlieplex_tests) {
  RUN_TEST_CASE(charlieplex_tests, test_charlieplex_new);
  RUN_TEST_CASE(charlieplex_tests, test_charlieplex_step);
  RUN_TEST_CASE(charlieplex_tests, test_charlieplex_new_initial_active);
}
