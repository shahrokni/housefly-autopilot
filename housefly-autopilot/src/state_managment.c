#include "../include/state_managment.h"

static FlightStatus flight_state;

void set_sftytstflg(unsigned char *sftytstflg) {}

FlightStatus *init() {
  flight_state.flags = 0b00000000;
  flight_state.state = 0;

  return &flight_state;
}