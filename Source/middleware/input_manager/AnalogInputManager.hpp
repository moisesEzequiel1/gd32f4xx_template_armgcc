#pragma once

#include <cstdint>
#include <array>
#include "gd32f4xx.h"
#include "gd32f4xx_adc.h"
#include "gd32f4xx_gpio.h"
#include "gd32f4xx_rcu.h"

class AnalogInputManager {
public:
    static constexpr uint8_t MAX_ANALOG_INPUTS = 8;
    
    struct Config {
        uint8_t channel;       // ADC_CHANNEL_0 to ADC_CHANNEL_18
        uint32_t sample_time;  // ADC_SAMPLETIME_3 to ADC_SAMPLETIME_480
    };

    struct State {
        uint16_t value{0};
        bool is_updated{false};
    };

    AnalogInputManager();
    
    bool add_channel(uint8_t input_id, Config config);
    uint16_t read(uint8_t input_id) const;
    void update();
    bool is_updated(uint8_t input_id);

private:
    void init_adc();
    void configure_gpio(uint8_t channel);

    std::array<Config, MAX_ANALOG_INPUTS> configs_;
    std::array<State, MAX_ANALOG_INPUTS> states_;
    uint8_t num_inputs_{0};
    bool adc_initialized_{false};
};