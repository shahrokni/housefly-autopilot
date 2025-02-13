#include "../include/state_managment.h"

static FlightStatus flight_state;

FlightStatus *init() {
  flight_state.flags = 0b00000000;
  flight_state.state = 0;

  return &flight_state;
}