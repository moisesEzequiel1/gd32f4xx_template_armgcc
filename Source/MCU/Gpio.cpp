#include "Gpio.hpp"


template<typename E>
constexpr auto etoi(E const value){
    return static_cast<std::underlying_type_t<E>>(value);
}

void Gpio::SetPinMode(const Pin pin, const Mode mode) {
    CTL = (CTL & ~(0b11 << etoi(pin) * 2)) | (etoi(mode) << etoi(pin) * 2);

}

void Gpio::SetOutputType(const Pin pin, const OutputType type) {
    OMODE = (OMODE & ~(0b1 << etoi(pin))) | (etoi(type) << etoi(pin));
}

void Gpio::SetOutputTypeSpeed(const Pin pin, const OutputSpeed speed) {
    OSPEED = (OSPEED & ~(0b11 << etoi(pin) * 2)) | (etoi(speed) << etoi(pin) * 2);
}
void Gpio::SetPinPull(const Pin pin, const Pull pull) {
    PUD = (PUD & ~(0b11 << etoi(pin) * 2)) | (etoi(pull) << etoi(pin) * 2);
}
// Note: The above code assumes that the Pin enum values are sequential and start from 0
//       If they are not, you may need to adjust the bit shifting logic accordingly.
//       The `etoi` function converts the enum value to its underlying integer type for bit manipulation.

bool Gpio::ReadPin(const Pin pin) {
    return (ISTAT & (1 << etoi(pin))) != 0 ? false: true;
}

void Gpio::SetPin(const Pin pin) {
    BOP |= (1 << etoi(pin));
}

void Gpio::ResetPin(const Pin pin) {
    BOP |= (1 << etoi(pin)) << 16;
}

void Gpio::TogglePin(const Pin pin) {
    TG ^= (1 << etoi(pin));
}

void Gpio::SetAlternateFunction(const Pin pin, const AlternateFunction function) {
    if(pin < Pin::Pin8)
    {
        AFSEL0 = ((AFSEL0 & ~(0xF << (etoi(pin) * 4))) | (etoi(function) << (etoi(pin) * 4)));
    }
    else
    {
        AFSEL1 = ((AFSEL1 & ~(0xF << ((etoi(pin)-etoi(Pin::Pin8)) * 4))) | (etoi(function) << ((etoi(pin)-etoi(Pin::Pin8)) * 4)));
    }
}

GpioPin::GpioPin(Gpio& gpio, const Gpio::Pin pin)
    :gpio(gpio), pin(pin)
{

}

void GpioPin::Set(void) const
{
    gpio.SetPin(pin);
}

void GpioPin::Reset(void) const
{
    gpio.ResetPin(pin);
}

void GpioPin::Toggle(void) const
{
    gpio.TogglePin(pin);
}

bool GpioPin::GetState(void) const
{
    return gpio.ReadPin(pin);
}

void GpioPin::SetMode(const Gpio::Mode mode) const
{
    gpio.SetPinMode(pin, mode);
}

void GpioPin::SetOutputType(const Gpio::OutputType type) const
{
    gpio.SetOutputType(pin, type);
}

void GpioPin::SetOutputSpeed(const Gpio::OutputSpeed speed) const
{
    gpio.SetOutputTypeSpeed(pin, speed);
}

void GpioPin::SetPull(const Gpio::Pull pull) const
{
    gpio.SetPinPull(pin, pull);
}

void GpioPin::SetAlternateFunction(const Gpio::AlternateFunction function) const
{
    gpio.SetAlternateFunction(pin, function);
}