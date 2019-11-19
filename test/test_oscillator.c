#include "oscillator.h"
#include "unity.h"
#include "unity_fixture.h"

Oscillator dummy_osc;

TEST_GROUP(oscillator_tests);

TEST_SETUP(oscillator_tests) {
  dummy_osc = oscillator_new(1);
}

TEST_TEAR_DOWN(oscillator_tests) {}

TEST(oscillator_tests, test_oscillator_step) {
  for(int16_t i = 255; 0 <= i; i--) {
    TEST_ASSERT_EQUAL(i, dummy_osc.value);
    oscillator_step(&dummy_osc);
  }

  for(int16_t i = 1; i < 255; i++) {
    TEST_ASSERT_EQUAL(i, dummy_osc.value);
    oscillator_step(&dummy_osc);
  }

  for(int16_t i = 255; 0 <= i; i--) {
    TEST_ASSERT_EQUAL(i, dummy_osc.value);
    oscillator_step(&dummy_osc);
  }

  for(int16_t i = 1; i < 255; i++) {
    TEST_ASSERT_EQUAL(i, dummy_osc.value);
    oscillator_step(&dummy_osc);
  }
}

TEST(oscillator_tests, test_oscillator_step_increment) {
  uint8_t cases[64] = {
    225,
    195,
    165,
    135,
    105,
    75,
    45,
    15,
    0,
    30,
    60,
    90,
    120,
    150,
    180,
    210,
    240,
    255,
    225,
    195
  };

  dummy_osc.increment = 30;

  char msg[50];
  for(uint8_t i = 0; i < 20; i++) {
    sprintf(msg, "Iteration %i", i);
    oscillator_step(&dummy_osc);
    TEST_ASSERT_EQUAL_MESSAGE(cases[i], dummy_osc.value, msg);
  }
}

TEST_GROUP_RUNNER(oscillator_tests) {
  RUN_TEST_CASE(oscillator_tests, test_oscillator_step);
  RUN_TEST_CASE(oscillator_tests, test_oscillator_step_increment);
}
