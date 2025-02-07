#include "../include/state_managment.h"

static FlightState flight_state;

FlightState *init() {
  flight_state.flight_flags = 0;
  flight_state.state = 0;

  return &flight_state;
}