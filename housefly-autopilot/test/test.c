#include "state_management.h"
#include "unity.h"

/* STATE MANAGEMENT TESTS */
void should_reset_safety_test_flag() {
  char flags = 0x01;
  TEST_ASSERT_EQUAL(flags, 0x01);
  reset_flags(&flags);
  TEST_ASSERT_EQUAL(flags, 0x00);
}

void should_set_safety_test_flag() {
  char flags = 0x00;
  TEST_ASSERT_EQUAL(flags, 0x00);
  set_sftytstflg(&flags);
  TEST_ASSERT_EQUAL(flags, 0x01);
}

/*  SUITES */
void suite_state_management() {
  should_reset_safety_test_flag();
  should_set_safety_test_flag();
}

void setUp(void) {}
void tearDown(void) {}

int main() {
  UNITY_BEGIN();
  RUN_TEST(suite_state_management);
  return UNITY_END();
}