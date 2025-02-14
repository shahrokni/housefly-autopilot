#ifndef AUTOPILOT_HF_STATE_MANAGEMENT
#define AUTOPILOT_HF_STATE_MANAGEMENT

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

void reset_state(unsigned char *current_state);

void set_requested_state(unsigned char *current_state, unsigned char new_state,
                         const unsigned char *flag);

char validate_requested_state(unsigned char *current_state,
                              unsigned char new_state,
                              const unsigned char *flag);

FlightStatus *init();

#endif