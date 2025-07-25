/**
 * @file    main.c
 * @brief   **Template Application entry point**
 *
 * The main file is the entry point of the application or any user code, please provide the
 * proper description of this file according to your own implementation
 * This Demo app only blinks an LED connected to PortA Pin 5
 *
 * @note    Only the files inside folder app will be take them into account when the
 *          doxygen runs by typing "make docs", index page is generated in
 *          Build/doxigen/html/index.html
 */
#include "MCU/Gpio.hpp"
#include "bsp.h"
#include "AnalogInputManager.hpp"


#include "Gpio.hpp"
#include "gd32f4xx.h"
#include "gd32f4xx_rcu.h"

int main() {

    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOA);

    Gpio& gpioC = *reinterpret_cast<Gpio*>(GPIO_BASE + 0x00000800U);
    Gpio& gpioA= *reinterpret_cast<Gpio*>(GPIO_BASE + 0x00000000U);


  // 3. Crear pines como objetos GpioPin
    GpioPin led(gpioC, Gpio::Pin::Pin6);      // LED en PC6
    GpioPin button(gpioA, Gpio::Pin::Pin0);   // Botón en PA0

    // 4. Configurar LED como salida push-pull
    led.SetMode(Gpio::Mode::Output);
    led.SetOutputType(Gpio::OutputType::PushPull);
    led.SetOutputSpeed(Gpio::OutputSpeed::SpeedLevel0);

    // 5. Configurar botón como entrada pull-up
    button.SetMode(Gpio::Mode::Input);
    button.SetPull(Gpio::Pull::PullUp);

    // 6. Loop principal
    while (1) {
        if (!button.GetState()) {
            // Botón presionado (estado bajo)
            led.Reset(); // Enciende el LED
        } else {
            // Botón no presionado (estado alto)
            led.Set(); // Apaga el LED
        }
    }
}
