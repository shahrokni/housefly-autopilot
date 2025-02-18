#ifndef AUTOPILOT_HF_STATE_MANAGEMENT
#define AUTOPILOT_HF_STATE_MANAGEMENT

typedef enum {
  NON_STAT = -1,
  GND_STAT = 0,
  TO_STAT = 1,
  LND_STAT = 2,
  TRN_STAT = 3,
  IDLE_STAT = 4,
  TST_STAT = 5,
  HLT_STAT = 6
} FlightState;

typedef struct {
  unsigned char service_ceiling;
  unsigned char reaction_latency;
} Vehicle;

typedef struct {
  unsigned char flags;
  unsigned char state;
  Vehicle *vehicle;
} FlightStatus;

void set_sftytstflg(unsigned char *flags);

void reset_sftytstflg(unsigned char *flags);

void reset_flags(unsigned char *flags);

void reset_state(FlightState *current_state);

void set_requested_state(FlightState *current_state, FlightState new_state,
                         const unsigned char flags);

char validate_requested_state(FlightState current_state, FlightState new_state,
                              const unsigned char flags);

FlightStatus *init();

#endif