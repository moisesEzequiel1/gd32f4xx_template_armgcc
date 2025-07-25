#include "AnalogInputManager.hpp"
#include "gd32f4xx_gpio.h"
#include "gd32f4xx_rcu.h"

namespace {
    constexpr std::array<uint32_t, 19> channel_to_port = {
        GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA,
        GPIOB, GPIOB, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC,
        GPIOC, GPIOC, GPIOB, GPIOB
    };

    constexpr std::array<uint16_t, 19> channel_to_pin = {
        GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4,
        GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_0, GPIO_PIN_1,
        GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4,
        GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_12
    };

    rcu_periph_enum get_rcu_clock(uint32_t gpio_port) {
        switch(gpio_port) {
            case GPIOA: return RCU_GPIOA;
            case GPIOB: return RCU_GPIOB;
            case GPIOC: return RCU_GPIOC;
            default:    return RCU_GPIOA;
        }
    }
}

AnalogInputManager::AnalogInputManager() {
    states_.fill(State{});
}

bool AnalogInputManager::add_channel(uint8_t input_id, Config config) {
    if (input_id >= MAX_ANALOG_INPUTS || num_inputs_ >= MAX_ANALOG_INPUTS) {
        return false;
    }

    configs_[input_id] = config;
    num_inputs_++;

    if (!adc_initialized_) {
        init_adc();
    }

    configure_gpio(config.channel);
    return true;
}

uint16_t AnalogInputManager::read(uint8_t input_id) const {
    if (input_id >= MAX_ANALOG_INPUTS) {
        return 0;
    }
    return states_[input_id].value;
}

void AnalogInputManager::update() {
    for (uint8_t i = 0; i < num_inputs_; i++) {
        adc_routine_channel_config(ADC0, 0, configs_[i].channel, configs_[i].sample_time);
        adc_software_trigger_enable(ADC0, ADC_ROUTINE_CHANNEL);
        
        while (!adc_flag_get(ADC0, ADC_FLAG_EOC));
        adc_flag_clear(ADC0, ADC_FLAG_EOC);
        
        const uint16_t new_value = adc_routine_data_read(ADC0);
        
        if (new_value != states_[i].value) {
            states_[i].value = new_value;
            states_[i].is_updated = true;
        }
    }
}

bool AnalogInputManager::is_updated(uint8_t input_id) {
    if (input_id >= MAX_ANALOG_INPUTS) {
        return false;
    }
    
    const bool updated = states_[input_id].is_updated;
    states_[input_id].is_updated = false;
    return updated;
}

void AnalogInputManager::init_adc() {
    rcu_periph_clock_enable(RCU_ADC0);
    adc_clock_config(ADC_ADCCK_PCLK2_DIV6);
    adc_resolution_config(ADC0, ADC_RESOLUTION_12B);
    adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);
    adc_special_function_config(ADC0, ADC_SCAN_MODE, ENABLE);
    adc_enable(ADC0);
    adc_initialized_ = true;
}

void AnalogInputManager::configure_gpio(uint8_t channel) {
    if (channel >= channel_to_port.size()) {
        return;
    }

    const uint32_t port = channel_to_port[channel];
    const uint16_t pin = channel_to_pin[channel];

    rcu_periph_clock_enable(get_rcu_clock(port));
    gpio_mode_set(port, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, pin);
    gpio_output_options_set(port, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, pin);
}