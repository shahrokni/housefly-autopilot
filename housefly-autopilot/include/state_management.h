#ifndef AUTOPILOT_HF_STATE_MANAGEMENT
#define AUTOPILOT_HF_STATE_MANAGEMENT

typedef enum {
  GND = 0,
  TO = 1,
  LND = 2,
  TRN = 3,
  IDLE = 4,
  TST = 5,
  HLT = 6
} FlightState;

typedef struct {
  unsigned char service_ceiling;
  unsigned char safe_landing_altitude;
  unsigned char reaction_latency;
} Vehicle;

typedef struct {
  unsigned char flags;
  FlightState state;
  Vehicle *vehicle;
} FlightStatus;

void set_sftytstflg(unsigned char *flags);

void reset_sftytstflg(unsigned char *flags);

void reset_flags(unsigned char *flags);

void reset_state(FlightState *current_state);

void set_state(FlightState *current_state, FlightState new_state);

FlightStatus *init();

#endif