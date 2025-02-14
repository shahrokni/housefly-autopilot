#include "state_management.h"

static FlightStatus flight_state;

static char state_transition_from[6][6] = {
    {2}, {0}, {4}, {4}, {1, 3}, {0}, {0, 1, 2, 3, 4, 5, 6}};

void set_sftytstflg(unsigned char *flags) { *flags |= (1 << 0); }

void reset_sftytstflg(unsigned char *flags) { *flags &= ~(1 << 0); }

void reset_flags(unsigned char *flags) { *flags = 0; }

void reset_state(unsigned char *current_state) { *current_state = 0; }

void set_requested_state(unsigned char *current_state, unsigned char new_state,
                         const unsigned char *flag) {}

char validate_requested_state(unsigned char *current_state,
                              unsigned char new_state,
                              const unsigned char *flag) {}
FlightStatus *init() {
  reset_flags(&flight_state.flags);
  reset_state(&flight_state.state);
  return &flight_state;
}