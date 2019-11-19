#include "queue.h"
#include "unity.h"
#include "unity_fixture.h"

QueueFifo dummy_fifo;
uint8_t dummy_max = 50;

TEST_GROUP(queue_tests);

TEST_SETUP(queue_tests) {
  dummy_fifo = queue_fifo_new(dummy_max);
}

TEST_TEAR_DOWN(queue_tests) {}

TEST(queue_tests, test_queue_fifo_is_empty) {
  TEST_ASSERT_EQUAL(true, queue_fifo_is_empty(&dummy_fifo));
  TEST_ASSERT_EQUAL(true, queue_fifo_is_empty(&dummy_fifo));
  queue_fifo_push(&dummy_fifo);
  TEST_ASSERT_EQUAL(false, queue_fifo_is_empty(&dummy_fifo));
}

TEST(queue_tests, test_queue_fifo_push) {
  TEST_ASSERT_EQUAL(0, dummy_fifo.count);
  queue_fifo_push(&dummy_fifo);
  TEST_ASSERT_EQUAL(1, dummy_fifo.count);
}

TEST(queue_tests, test_queue_fifo_pop) {
  TEST_ASSERT_EQUAL(0, dummy_fifo.count);
  queue_fifo_push(&dummy_fifo);
  TEST_ASSERT_EQUAL(1, dummy_fifo.count);
  queue_fifo_push(&dummy_fifo);
  TEST_ASSERT_EQUAL(2, dummy_fifo.count);
  TEST_ASSERT_EQUAL(0, queue_fifo_pop(&dummy_fifo));
  TEST_ASSERT_EQUAL(1, dummy_fifo.count);
  TEST_ASSERT_EQUAL(1, queue_fifo_pop(&dummy_fifo));
  TEST_ASSERT_EQUAL(0, dummy_fifo.count);
}

TEST(queue_tests, test_queue_fifo_peek) {
  queue_fifo_push(&dummy_fifo);
  queue_fifo_push(&dummy_fifo);

  TEST_ASSERT_EQUAL(0, queue_fifo_peek(&dummy_fifo));
  TEST_ASSERT_EQUAL(0, queue_fifo_peek(&dummy_fifo));
  TEST_ASSERT_EQUAL(0, queue_fifo_pop(&dummy_fifo));
  TEST_ASSERT_EQUAL(1, queue_fifo_peek(&dummy_fifo));
}

TEST(queue_tests, test_queue_fifo_push_rollover) {
  for(uint8_t i = 0; i < dummy_max; i++) {
    TEST_ASSERT_EQUAL(i, dummy_fifo.count);
    queue_fifo_push(&dummy_fifo);
    TEST_ASSERT_EQUAL(0, queue_fifo_peek(&dummy_fifo));
  }

  TEST_ASSERT_EQUAL(dummy_max, dummy_fifo.count);

  for(uint8_t i = 0; i < (dummy_max / 2); i++) {
    TEST_ASSERT_EQUAL(i, queue_fifo_peek(&dummy_fifo));
    queue_fifo_push(&dummy_fifo);
    TEST_ASSERT_EQUAL(dummy_max, dummy_fifo.count);
  }

  for(uint8_t i = (dummy_max / 2); i < dummy_max; i++) {
    TEST_ASSERT_EQUAL(i, queue_fifo_pop(&dummy_fifo));
    TEST_ASSERT_EQUAL(dummy_max - (i - (dummy_max / 2) + 1), dummy_fifo.count);
  }
}

TEST_GROUP_RUNNER(queue_tests) {
  RUN_TEST_CASE(queue_tests, test_queue_fifo_is_empty);
  RUN_TEST_CASE(queue_tests, test_queue_fifo_push);
  RUN_TEST_CASE(queue_tests, test_queue_fifo_pop);
  RUN_TEST_CASE(queue_tests, test_queue_fifo_peek);
  RUN_TEST_CASE(queue_tests, test_queue_fifo_push_rollover);
}
