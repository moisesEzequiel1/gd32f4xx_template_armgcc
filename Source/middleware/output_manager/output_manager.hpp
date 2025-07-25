#pragma once
#include "gd32f4xx_gpio.h"

namespace middleware {

class OutputManager {
public:
    enum class OutputType {
        DIGITAL,
        PWM
    };

    struct OutputConfig {
        OutputType type;
        uint32_t port;
        uint32_t pin;
        float initial_value;
    };

    void init();
    uint8_t register_output(const OutputConfig& config);
    
    void set_value(uint8_t output_id, float value);
    void set_bool(uint8_t output_id, bool state);
    void toggle(uint8_t output_id);

private:
    struct OutputState {
        OutputConfig config;
        float current_value;
    };

    static constexpr uint8_t MAX_OUTPUTS = 8;
    OutputState outputs_[MAX_OUTPUTS];
    uint8_t output_count_ = 0;
};

} // namespace middleware