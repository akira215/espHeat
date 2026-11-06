#pragma once

#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/climate/climate.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"

#include "driverHomebus.h"
#include "driverDaikin.h"
#include "driver/uart.h"
#include "driver/gpio.h"



namespace esphome {
namespace espheat {

// Temperature limits
constexpr float MIN_TEMPERATURE = 18.0f;
constexpr float MAX_TEMPERATURE = 28.0f;
constexpr float TEMPERATURE_STEP = 1.0f;


class EspHeat : public climate::Climate, public Component {

public:
    EspHeat();

    void setup() override;
    void loop() override;
    void dump_config() override;

    void control(const climate::ClimateCall &call);
    climate::ClimateTraits traits(void);

    // void set_temperature_sensor(sensor::Sensor *temperature_sensor) { temperature_sensor_ = temperature_sensor; }
    //void set_humidity_sensor(sensor::Sensor *humidity_sensor) { humidity_sensor_ = humidity_sensor; }

    //void update() override {
    //    this->temperature_sensor_->publish_state(this->get_temperature_value());
    //    this->humidity_sensor_->publish_state(this->get_humidity_value());
    //}
    

protected:
    DriverHomebus* hbs_     = nullptr;
    DriverDaikin* _daikin   = nullptr;
    
    SUB_SENSOR(indoor_temperature);
    SUB_SENSOR(outdoor_intake_temperature);
    SUB_SENSOR(coolant_temperature);




  
}; // class EspHeat

} // namespace espheat
} // namespace esphome