#include "output_manager.hpp"

namespace middleware {

void OutputManager::init() {
    output_count_ = 0;
}

uint8_t OutputManager::register_output(const OutputConfig& config) {
    if(output_count_ >= MAX_OUTPUTS) return 0xFF;

    // Configuración usando HAL original
    switch(config.type) {
        case OutputType::DIGITAL:
            gpio_mode_set(config.port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, config.pin);
            gpio_output_options_set(config.port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, config.pin);
            gpio_bit_write(config.port, config.pin, (config.initial_value > 0.5f) ? SET : RESET);
            break;
        case OutputType::PWM:
            // Configuración específica para PWM usando timer
            break;
    }

    outputs_[output_count_] = {
        config,
        config.initial_value
    };

    return output_count_++;
}

void OutputManager::set_value(uint8_t output_id, float value) {
    if(output_id >= output_count_) return;

    auto& output = outputs_[output_id];
    output.current_value = value;

    switch(output.config.type) {
        case OutputType::DIGITAL:
            gpio_bit_write(output.config.port, output.config.pin, (value > 0.5f) ? SET : RESET);
            break;
        case OutputType::PWM:
            // Actualizar duty cycle del PWM
            break;
    }
}

// Implementaciones restantes...
} // namespace middleware