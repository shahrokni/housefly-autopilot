#include "state_management.h"

static FlightStatus flight_state;

void set_sftytstflg(unsigned char *flags) { *flags |= (1 << 0); }

void reset_sftytstflg(unsigned char *flags) { *flags &= ~(1 << 0); }

void reset_flags(unsigned char *flags) { *flags = 0; }

void reset_state(FlightState *current_state) { *current_state = 0; }

void set_state(FlightState *current_state, FlightState new_state) {}

FlightStatus *init() {
  reset_flags(&flight_state.flags);
  reset_state(&flight_state.state);
  return &flight_state;
}