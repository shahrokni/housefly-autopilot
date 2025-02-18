#include "state_management.h"
#include "unity.h"

/* STATE MANAGEMENT TESTS */
void should_reset_safety_test_flag() {
  char flags = 0x01;
  TEST_ASSERT_EQUAL(flags, 0x01);
  reset_sftytstflg(&flags);
  TEST_ASSERT_EQUAL(flags, 0x00);
}

void should_set_safety_test_flag() {
  char flags = 0x00;
  TEST_ASSERT_EQUAL(flags, 0x00);
  set_sftytstflg(&flags);
  TEST_ASSERT_EQUAL(flags, 0x01);
}

void should_reset_all_flags() {
  unsigned char flags = 0xff;
  TEST_ASSERT_EQUAL(flags, 0xff);
  reset_flags(&flags);
  TEST_ASSERT_EQUAL(flags, 0x00);
}

void should_reset_flight_state() {
  FlightState states[] = {GND_STAT, TO_STAT,   TRN_STAT, LND_STAT,
                          NON_STAT, IDLE_STAT, TST_STAT, HLT_STAT};

  for (int i = 0; i < 7; i += 1) {
    FlightState state = states[i];
    reset_state(&state);
    TEST_ASSERT_EQUAL(state, 0x00);
  }
}

/**
 * @brief Regardless of the flags, the new state can not be set to GND if the
 * the current state is invalid either
 */
void should_validation_return_false_for_GND() {
  FlightState new_state = GND_STAT;
  FlightState possible_invalid_current_states[] = {TO_STAT, IDLE_STAT, GND_STAT,
                                                   TRN_STAT, HLT_STAT};
  for (int i = 0; i < 5; i += 1) {
    for (int j = 0; j < 256; j += 1) {
      int result = validate_requested_state(possible_invalid_current_states[i],
                                            new_state, j);
      TEST_ASSERT_EQUAL(result, 0);
    }
  }
}

/**
 *@brief with valid flags the validation should return 1
 */
void should_validation_return_true_for_GND() {
  FlightState new_state = GND_STAT;
  FlightState possible_invalid_current_states[] = {NON_STAT, TST_STAT,
                                                   LND_STAT};
  for (int i = 0; i < 3; i += 1) {
    int result = validate_requested_state(possible_invalid_current_states[i],
                                          new_state, 0x01);
    TEST_ASSERT_EQUAL(result, 1);
  }
}

/*  SUITES */
void suite_state_management() {
  should_reset_safety_test_flag();
  should_set_safety_test_flag();
  should_reset_all_flags();
  should_reset_flight_state();
  should_validation_return_false_for_GND();
  should_validation_return_true_for_GND();
}

void setUp(void) {}
void tearDown(void) {}

int main() {
  UNITY_BEGIN();
  RUN_TEST(suite_state_management);
  return UNITY_END();
}