#include "espheat.h"

namespace esphome {
namespace espheat {

static const char *const TAG = "EspHeat";

EspHeat::EspHeat(): climate::Climate() {

}
 
void EspHeat::setup() {
    ESP_LOGCONFIG(TAG, "Setting up EspHeat...");

}

void EspHeat::loop()
{
    
}

void EspHeat::dump_config()
{
    ESP_LOGCONFIG(TAG, "EspHeat climate:");

}

void EspHeat::control(const climate::ClimateCall &call)
{
    /*
    // Gérer les changements demandés par l'utilisateur (ex: changer la température cible)
    if (call.get_mode().has_value()) {
        this->mode = *call.get_mode();
    }
    if (call.get_target_temperature().has_value()) {
        this->target_temperature = *call.get_target_temperature();
    }
    
    // Indiquer à Home Assistant / ESPHome que l'état a changé
    this->publish_state();
    */
}

climate::ClimateTraits EspHeat::traits()
 {
    auto traits = climate::ClimateTraits();
    traits.add_feature_flags(climate::CLIMATE_SUPPORTS_CURRENT_TEMPERATURE);
    traits.set_supported_modes({
        climate::CLIMATE_MODE_OFF,
        climate::CLIMATE_MODE_HEAT,
    });
    traits.set_supported_fan_modes({
        climate::CLIMATE_FAN_LOW,
        climate::CLIMATE_FAN_MEDIUM,
        climate::CLIMATE_FAN_HIGH,
    });
    traits.add_feature_flags(climate::CLIMATE_SUPPORTS_ACTION);
    traits.set_visual_min_temperature(MIN_TEMPERATURE);
    traits.set_visual_max_temperature(MAX_TEMPERATURE);
    traits.set_visual_target_temperature_step(TEMPERATURE_STEP);
    return traits;
 }

} // namespace espheat
} // namespace esphome