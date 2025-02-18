#include "state_management.h"

static FlightStatus flight_state;

void set_sftytstflg(unsigned char *flags) { *flags |= (1 << 0); }

void reset_sftytstflg(unsigned char *flags) { *flags &= ~(1 << 0); }

void reset_flags(unsigned char *flags) { *flags = 0; }

void reset_state(FlightState *current_state) { *current_state = GND_STAT; }

void set_requested_state(FlightState *current_state, FlightState new_state,
                         const unsigned char flags) {}

char validate_requested_state(FlightState current_state, FlightState new_state,
                              const unsigned char flags) {
  switch (new_state) {
  case GND_STAT:
    return (current_state == NON_STAT || current_state == LND_STAT) ? 1 : 0;
  case TO_STAT:
    return (current_state == GND_STAT && (flags & 0x01)) ? 1 : 0;
  case LND_STAT:
    return current_state == IDLE_STAT ? 1 : 0;
  case TRN_STAT:
    return current_state == IDLE_STAT ? 1 : 0;
  case IDLE_STAT:
    return (current_state == TO_STAT && current_state == TRN_STAT) ? 1 : 0;
  case TST_STAT:
    return current_state == GND_STAT ? 1 : 0;
  case HLT_STAT:
    return 1;
  default:
    return 0;
  }
}

FlightStatus *init() {
  // reset_flags(&flight_state.flags);
  // reset_state(&flight_state.state);
  return &flight_state;
}