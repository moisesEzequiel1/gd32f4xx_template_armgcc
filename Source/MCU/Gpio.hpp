#pragma once 
#include <stdint.h>
#include <type_traits>
class Gpio {
public:

    enum class Pin: uint8_t {
        Pin0, Pin1, Pin2, Pin3, Pin4, Pin5, Pin6, Pin7,
        Pin8, Pin9, Pin10, Pin11, Pin12, Pin13,
        Pin14, Pin15
    };
    enum class Mode : uint8_t {
        Input     = 0b00,   // GPIO Input mode (reset value)
        Output    = 0b01,   // GPIO Output mode
        Alternate = 0b10,   // Alternate function mode
        Analog    = 0b11    // Analog mode
    };

    enum class OutputType : uint8_t {
        PushPull = 0b0,     // Push-pull output
        OpenDrain = 0b1     // Open-drain output
    };
    enum class OutputSpeed : uint8_t {
        SpeedLevel0 = 0b00, // Low speed
        SpeedLevel1 = 0b01, // Medium speed
        SpeedLevel2 = 0b10, // High speed
        SpeedLevel3 = 0b11  // Very high speed
    };
    enum class Pull : uint8_t {
        NoPull    = 0b00,   // No pull-up or pull-down
        PullUp    = 0b01,   // Pull-up
        PullDown  = 0b10    // Pull-down
    };
    enum class AlternateFunction: uint8_t {
        AF0 = 0b0000, // Alternate function 0
        AF1 = 0b0001, // Alternate function 1
        AF2 = 0b0010, // Alternate function 2
        AF3 = 0b0011, // Alternate function 3
        AF4 = 0b0100, // Alternate function 4
        AF5 = 0b0101, // Alternate function 5
        AF6 = 0b0110, // Alternate function 6
        AF7 = 0b0111, // Alternate function 7
        AF8 = 0b1000, // Alternate function 8
        AF9 = 0b1001, // Alternate function 9
        AF10 = 0b1010,// Alternate function 10
        AF11 = 0b1011,// Alternate function 11
        AF12 = 0b1100,// Alternate function 12
        AF13 = 0b1101,// Alternate function 13
        AF14 = 0b1110,// Alternate function 14
        AF15 = 0b1111 // Alternate function 15
    };

    void SetPinMode(const Pin pin, const Mode mode);
    void SetOutputType(const Pin pin, const OutputType type);
    void SetOutputTypeSpeed(const Pin pin, const OutputSpeed speed);
    void SetPinPull(const Pin pin, const Pull pull);
    bool ReadPin(const Pin pin);
    void SetPin(const Pin pin);
    void ResetPin(const Pin pin);
    void TogglePin(const Pin pin);
    void SetAlternateFunction(const Pin pin, const AlternateFunction function);

private:

    volatile uint32_t CTL;  // Control register
    volatile uint32_t OMODE; // Output mode register
    volatile uint32_t OSPEED; // Output speed register
    volatile uint32_t PUD; // Pull-up/pull-down register
    volatile uint32_t ISTAT; // Input status register
    volatile uint32_t OCTL; // Output control register
    volatile uint32_t BOP; // Bit operation register
    volatile uint32_t LOCK; // Lock register
    volatile uint32_t AFSEL0; // Alternate function selection register 0                 
    volatile uint32_t AFSEL1; // Alternate function selection register 1
    volatile uint32_t BC; // Bit clear register
    volatile uint32_t TG; // Toggle register

};


class GpioPin
{
public:
    GpioPin(Gpio& gpio, const Gpio::Pin pin);

    void Set(void) const;
    void Reset(void) const;
    void Toggle(void) const;

    bool GetState(void) const;

    void SetMode(const Gpio::Mode mode) const;
    void SetOutputType(const Gpio::OutputType type) const;
    void SetOutputSpeed(const Gpio::OutputSpeed speed) const;
    void SetPull(const Gpio::Pull pull) const;
    void SetAlternateFunction(const Gpio::AlternateFunction function) const;

private:
    Gpio& gpio;
    const Gpio::Pin pin;
};

static_assert(std::is_standard_layout<Gpio>::value, "Gpio class is NOT standard layout");
