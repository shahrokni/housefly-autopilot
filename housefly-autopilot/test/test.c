#include "config_repository.h"
#include "state_management.h"
#include "unity.h"

/* STATE MANAGEMENT TESTS */

void should_set_init_flag() {
  char flags = 0x01;
  set_initflg(&flags);
  TEST_ASSERT_MESSAGE(flags == 0x03,
                      "Should set the init flag to 1 (final binary reads 3)");
}

void should_reset_safety_test_flag() {
  char flags = 0x01;
  TEST_ASSERT_MESSAGE(flags == 0x01,
                      "Should have set the flight safety flag to 1");
  reset_sftytstflg(&flags);
  TEST_ASSERT_MESSAGE(flags == 0x00,
                      "Should have reset the flight safety flag");
}

void should_set_safety_test_flag() {
  char flags = 0x00;
  TEST_ASSERT_MESSAGE(flags == 0x00,
                      "Should have reset the flight safety flag");
  set_sftytstflg(&flags);
  TEST_ASSERT_MESSAGE(flags == 0x01,
                      "Should have set the flight safety flag to 1");
}

void should_reset_all_flags() {
  unsigned char flags = 0xff;
  TEST_ASSERT_EQUAL(flags, 0xff);
  reset_flags(&flags);
  TEST_ASSERT_MESSAGE(flags == 0x00, "Should have reset all flight flags");
}

void should_reset_flight_state() {
  FlightState states[] = {GND_STAT, TO_STAT,   TRN_STAT, LND_STAT,
                          NON_STAT, IDLE_STAT, TST_STAT, HLT_STAT};

  for (int i = 0; i < 7; i += 1) {
    FlightState state = states[i];
    reset_state(&state);
    TEST_ASSERT_MESSAGE(state == 0x00, "Should have reset the flight state");
  }
}

/**
 * @brief Regardless of the flags, the new state can not be set to GND if
 * the current state exists in the invalid array
 */
void should_validation_return_false_for_new_state_GND() {
  FlightState new_state = GND_STAT;
  FlightState possible_invalid_current_states[] = {TO_STAT, IDLE_STAT, GND_STAT,
                                                   TRN_STAT, HLT_STAT};
  int len = sizeof(possible_invalid_current_states) / sizeof(int);

  for (int i = 0; i < len; i += 1) {
    for (int j = 0; j < 256; j += 1) {
      int result = validate_requested_state(possible_invalid_current_states[i],
                                            new_state, j);
      TEST_ASSERT_MESSAGE(result == 0, "Validation should return 0 (invalid)");
    }
  }
}

void should_validation_return_true_for_new_state_GND() {
  FlightState new_state = GND_STAT;
  FlightState possible_valid_current_states[] = {NON_STAT, TST_STAT, LND_STAT};
  int len = sizeof(possible_valid_current_states) / sizeof(int);

  for (int i = 0; i < len; i += 1) {
    for (int j = 0; j < 256; j += 1) {
      int result = validate_requested_state(possible_valid_current_states[i],
                                            new_state, j);
      TEST_ASSERT_MESSAGE(result == 1, "Validation should return 1 (valid)");
    }
  }
}

void should_validation_return_false_for_new_state_TO() {
  FlightState new_state = TO_STAT;
  FlightState possible_invalid_current_states[] = {
      TO_STAT, TRN_STAT, LND_STAT, NON_STAT, IDLE_STAT, TST_STAT, HLT_STAT};
  int len = sizeof(possible_invalid_current_states) / sizeof(int);

  for (int i = 0; i < len; i += 1) {
    for (int j = 0; j < 256; j += 1) {
      int result = validate_requested_state(possible_invalid_current_states[i],
                                            new_state, j);
      TEST_ASSERT_MESSAGE(result == 0, "Validation should return 0 (invalid)");
    }
  }
}

/**
 * @brief Although the transition from GND to TO is valid, since the safety test
 * flag is not set, the validation should return 0
 */
void should_validation_return_false_fo_new_state_TO_wrong_flags() {
  FlightState new_state = TO_STAT;
  FlightState possible_valid_current_states[] = {GND_STAT};
  int flags = 0x00;
  int len = sizeof(possible_valid_current_states) / sizeof(int);

  for (int i = 0; i < len; i += 1) {
    int result = validate_requested_state(possible_valid_current_states[i],
                                          new_state, flags);
    TEST_ASSERT_MESSAGE(result == 0, "Validation should return 0 (invalid)");
  }
}

void should_validation_return_true_for_new_state_TO() {
  FlightState new_state = TO_STAT;
  FlightState possible_valid_current_states[] = {GND_STAT};
  /* Flight safety flag is set to 1 */
  int flags = 0x01;
  int len = sizeof(possible_valid_current_states) / sizeof(int);

  for (int i = 0; i < len; i += 1) {
    int result = validate_requested_state(possible_valid_current_states[i],
                                          new_state, flags);
    TEST_ASSERT_MESSAGE(result == 1, "Validation should return 1 (valid)");
  }
}

void should_validation_return_false_for_new_state_LND() {
  FlightState new_state = LND_STAT;
  FlightState possible_invalid_current_states[] = {
      GND_STAT, TO_STAT, TRN_STAT, LND_STAT, NON_STAT, TST_STAT, HLT_STAT};

  int len = sizeof(possible_invalid_current_states) / sizeof(int);

  for (int i = 0; i < len; i += 1) {
    for (int j = 0; j < 256; j += 1) {
      int result = validate_requested_state(possible_invalid_current_states[i],
                                            new_state, j);
      TEST_ASSERT_MESSAGE(result == 0, "Validation should return 0 (invalid)");
    }
  }
}

void should_validation_return_true_for_new_state_LND() {
  FlightState new_state = LND_STAT;
  FlightState possible_valid_current_states[] = {IDLE_STAT};

  int len = sizeof(possible_valid_current_states) / sizeof(int);

  for (int i = 0; i < len; i += 1) {
    for (int j = 0; j < 256; j += 1) {
      int result = validate_requested_state(possible_valid_current_states[i],
                                            new_state, j);
      TEST_ASSERT_MESSAGE(result == 1, "Validation should return 1 (valid)");
    }
  }
}

void should_validation_return_false_for_new_state_TRN() {
  FlightState new_state = TRN_STAT;
  FlightState possible_invalid_current_states[] = {
      GND_STAT, TO_STAT, TRN_STAT, LND_STAT, NON_STAT, TST_STAT, HLT_STAT};

  int len = sizeof(possible_invalid_current_states) / sizeof(int);

  for (int i = 0; i < len; i += 1) {
    for (int j = 0; j < 256; j += 1) {
      int result = validate_requested_state(possible_invalid_current_states[i],
                                            new_state, j);
      TEST_ASSERT_MESSAGE(result == 0, "Validation should return 0 (invalid)");
    }
  }
}

void should_validation_return_true_new_state_TRN() {
  FlightState new_state = TRN_STAT;
  FlightState possible_valid_current_states[] = {IDLE_STAT};

  int len = sizeof(possible_valid_current_states) / sizeof(int);
  for (int i = 0; i < len; i += 1) {
    for (int j = 0; j < 256; j += 1) {
      int result = validate_requested_state(possible_valid_current_states[i],
                                            new_state, j);
      TEST_ASSERT_MESSAGE(result == 1, "Validation should return 1 (valid)");
    }
  }
}

void should_validation_return_false_new_state_IDLE() {
  FlightState new_state = IDLE_STAT;
  FlightState possible_invalid_current_states[] = {
      GND_STAT, LND_STAT, NON_STAT, IDLE_STAT, TST_STAT, HLT_STAT};

  int len = sizeof(possible_invalid_current_states) / sizeof(int);

  for (int i = 0; i < len; i += 1) {
    for (int j = 0; j < 256; j += 1) {
      int result = validate_requested_state(possible_invalid_current_states[i],
                                            new_state, j);
      TEST_ASSERT_MESSAGE(result == 0, "Validation should return 0 (invalid)");
    }
  }
}

void should_validation_return_true_new_state_IDLE() {
  FlightState new_state = IDLE_STAT;
  FlightState possible_invalid_current_states[] = {TRN_STAT, TO_STAT};

  int len = sizeof(possible_invalid_current_states) / sizeof(int);

  for (int i = 0; i < len; i += 1) {
    for (int j = 0; j < 256; j += 1) {
      int result = validate_requested_state(possible_invalid_current_states[i],
                                            new_state, j);
      TEST_ASSERT_MESSAGE(result == 1, "Validation should return 1 (valid)");
    }
  }
}

void should_validation_return_false_new_state_TST() {
  FlightState new_state = TST_STAT;
  FlightState possible_invalid_current_states[] = {
      TO_STAT, TRN_STAT, LND_STAT, NON_STAT, IDLE_STAT, TST_STAT, HLT_STAT};

  int len = sizeof(possible_invalid_current_states) / sizeof(int);

  for (int i = 0; i < len; i += 1) {
    for (int j = 0; j < 256; j += 1) {
      int result = validate_requested_state(possible_invalid_current_states[i],
                                            new_state, j);
      TEST_ASSERT_MESSAGE(result == 0, "Validation should return 0 (invalid)");
    }
  }
}

void should_validation_return_true_new_state_TST() {
  FlightState new_state = TST_STAT;
  FlightState possible_invalid_current_states[] = {GND_STAT};

  int len = sizeof(possible_invalid_current_states) / sizeof(int);

  for (int i = 0; i < len; i += 1) {
    for (int j = 0; j < 256; j += 1) {
      int result = validate_requested_state(possible_invalid_current_states[i],
                                            new_state, j);
      TEST_ASSERT_MESSAGE(result == 1, "Validation should return 1 (valid)");
    }
  }
}

void should_validation_always_return_true_new_state_HLT() {
  FlightState new_state = HLT_STAT;
  FlightState possible_valid_current_states[] = {TO_STAT,  TRN_STAT,  LND_STAT,
                                                 NON_STAT, IDLE_STAT, TST_STAT,
                                                 HLT_STAT, GND_STAT};

  int len = sizeof(possible_valid_current_states) / sizeof(int);

  for (int i = 0; i < len; i += 1) {
    for (int j = 0; j < 256; j += 1) {
      int result = validate_requested_state(possible_valid_current_states[i],
                                            new_state, j);
      TEST_ASSERT_MESSAGE(result == 1, "Validation should return 1 (valid)");
    }
  }
}

void should_init_flight_state_and_return_pointer() {
  FlightStatus *flight_status_pointer = NULL;
  TEST_ASSERT_NULL_MESSAGE(flight_status_pointer, "Should be NULL");
  flight_status_pointer = init();
  TEST_ASSERT_NOT_NULL_MESSAGE(flight_status_pointer, "Should NOT be NULL");
}

void should_return_config_repository() {
  ConfigRepository *config_repo_pointer = get_config();
  TEST_ASSERT_NOT_NULL_MESSAGE(config_repo_pointer, "Should NOT be NULL");
  TEST_ASSERT_MESSAGE(config_repo_pointer->flying_vehicle.reaction_latency ==
                          FLYING_VEHICLE_REACTION_LATENCY,
                      "Should have the reaction latency");
  TEST_ASSERT_MESSAGE(config_repo_pointer->flying_vehicle.service_ceiling ==
                          FLYING_VEHICLE_SERVICE_CEILING,
                      "Should have the service ceiling");
  TEST_ASSERT_MESSAGE(config_repo_pointer->flying_vehicle.weight ==
                          FLYING_VEHICLE_WEIGHT,
                      "Should have the weight");
}

void setUp(void) {}
void tearDown(void) {}

int main() {
  UNITY_BEGIN();
  RUN_TEST(should_set_init_flag);
  RUN_TEST(should_reset_safety_test_flag);
  RUN_TEST(should_set_safety_test_flag);
  RUN_TEST(should_reset_all_flags);
  RUN_TEST(should_reset_flight_state);
  RUN_TEST(should_validation_return_false_for_new_state_GND);
  RUN_TEST(should_validation_return_true_for_new_state_GND);
  RUN_TEST(should_validation_return_false_for_new_state_TO);
  RUN_TEST(should_validation_return_false_fo_new_state_TO_wrong_flags);
  RUN_TEST(should_validation_return_true_for_new_state_TO);
  RUN_TEST(should_validation_return_false_for_new_state_LND);
  RUN_TEST(should_validation_return_true_for_new_state_LND);
  RUN_TEST(should_validation_return_false_for_new_state_TRN);
  RUN_TEST(should_validation_return_true_new_state_TRN);
  RUN_TEST(should_validation_return_false_new_state_IDLE);
  RUN_TEST(should_validation_return_true_new_state_IDLE);
  RUN_TEST(should_validation_return_false_new_state_TST);
  RUN_TEST(should_validation_always_return_true_new_state_HLT);
  RUN_TEST(should_init_flight_state_and_return_pointer);
  RUN_TEST(should_return_config_repository);
  return UNITY_END();
}