#ifndef AUTOPILOT_HF_STATE_MANAGEMENT
#define AUTOPILOT_HF_STATE_MANAGEMENT

typedef struct {
  unsigned char flight_flags;
  unsigned char state;
} FlightState;

FlightState *init();

void change_state(FlightState *fs);

#endif