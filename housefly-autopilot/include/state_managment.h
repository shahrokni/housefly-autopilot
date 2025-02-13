#ifndef AUTOPILOT_HF_STATE_MANAGEMENT
#define AUTOPILOT_HF_STATE_MANAGEMENT

typedef struct {
  unsigned char weight;
  unsigned char service_ceiling;
  unsigned char safe_landing_altitude;
} Vehicle;

typedef struct {
  unsigned char flags;
  unsigned char state;
  Vehicle *vehicle;
} FlightStatus;

FlightStatus *init();

void change_state(FlightStatus *fs);

#endif