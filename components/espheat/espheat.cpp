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