#ifndef AUTOPILOT_HF_CONFIG_REPOSITORY
#define AUTOPILOT_HF_CONFIG_REPOSITORY

/* -- DEFAULT CONFIGURATIONS -- */
#define FLYING_VEHICLE_REACTION_LATENCY 150
#define FLYING_VEHICLE_SERVICE_CEILING 10
#define FLYING_VEHICLE_WEIGHT 1.0

typedef struct {
  unsigned char service_ceiling;
  unsigned char reaction_latency;
  float weight;
} FlyingVehicle;

typedef struct {
  FlyingVehicle flying_vehicle;
} ConfigRepository;

/**
 * @brief Returns the config repository
 * @return Returns the pointer to the config repository
 */
ConfigRepository *get_config();

#endif
