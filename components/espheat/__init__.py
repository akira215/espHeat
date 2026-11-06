'''
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import (
    binary_sensor,
    climate,
    sensor,
)
from esphome.const import (
    CONF_ID, 
    CONF_NAME, 
    UNIT_CELSIUS, 
    UNIT_PERCENT, 
    DEVICE_CLASS_TEMPERATURE, 
    DEVICE_CLASS_HUMIDITY,
    DEVICE_CLASS_PROBLEM,
    STATE_CLASS_MEASUREMENT, 
    ICON_THERMOMETER,
    ICON_WATER_PERCENT,
)



AUTO_LOAD = ["binary_sensor", "climate", "sensor"]


espHeat_ns = cg.esphome_ns.namespace("espheat")
EspHeat = espHeat_ns.class_("EspHeat", cg.PollingComponent)

CONF_TEMPERATURE_SENSOR = "temperature_sensor"
CONF_HUMIDITY_SENSOR = "humidity_sensor"

CONFIG_SCHEMA = climate.climate_schema(EspHeat).extend(
    {
        cv.Optional("outdoor_intake_temperature"): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            icon=ICON_THERMOMETER,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional("coolant_temperature"): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            icon="mdi:coolant-temperature",
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional("indoor_temperature"): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            icon="mdi:home-thermometer",
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
    }
)


SENSOR_TYPES = {
    "outdoor_intake_temperature": "set_outdoor_intake_temperature_sensor",
    "coolant_temperature": "set_coolant_temperature_sensor",
    "indoor_temperature": "set_indoor_temperature_sensor",
}

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await climate.register_climate(var, config)

    for key, funcName in SENSOR_TYPES.items():
        if key in config:
            sens = await sensor.new_sensor(config[key])
            cg.add(getattr(var, funcName)(sens))
'''