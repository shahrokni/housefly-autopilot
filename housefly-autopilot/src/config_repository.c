#include "config_repository.h"

ConfigRepository *get_config() {
  static ConfigRepository config = {
      .flying_vehicle = {.service_ceiling = FLYING_VEHICLE_SERVICE_CEILING,
                         .reaction_latency = FLYING_VEHICLE_REACTION_LATENCY,
                         .weight = FLYING_VEHICLE_WEIGHT}};
  return &config;
}