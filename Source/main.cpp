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
#include "bsp.h"
#include "Gpio.hpp"
#include "Rcu.hpp"
#include "Pmu.hpp"
#include "gd32f4xx.h"
#include "gd32f4xx_rcu.h"
#include "system_gd32f4xx.h"

int main() {

    // rcu_periph_clock_enable(RCU_GPIOC);
    // rcu_periph_clock_enable(RCU_GPIOA);
    Rcu& rcu = *reinterpret_cast<Rcu*>(RCU_BASE);
    rcu.EnableGpioA();
    rcu.EnableGpioC();
    rcu.EnablePowerInterface(); 


    rcu.EnableExternalClock();
    /* Configure the main PLL, PSC = 25, PLL_N = 400, PLL_P = 2, PLL_Q = 9 */ 
    rcu.ConfigurePll(Rcu::PllClockSource::HXTAL, Rcu::PLLFactors(Rcu::PllFactorP::DIV2, 9, 400, Rcu::PllVcoPrescaler::DIV24));
    rcu.EnablePll();
    rcu.SetAhbPrescaler(Rcu::AhbPrescaler::DIV1);
    rcu.SetApb1Prescaler(Rcu::Apb1Prescaler::DIV2);
    rcu.SetApb2Prescaler(Rcu::Apb2Prescaler::DIV4);
    
    Pmu& pmu = *reinterpret_cast<Pmu*>(PMU_BASE);
    pmu.EnableHighDriverMode();
    pmu.SetHighDriverMode();

    rcu.SetSystemClockSource(Rcu::SystemClockSource::PLLP);

    rcu.UpdateSystemCoreClock();
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
        (void)SystemCoreClock;
        if (!button.GetState()) {
            // Botón presionado (estado bajo)
            led.Reset(); // Enciende el LED
        } else {
            // Botón no presionado (estado alto)
            led.Set(); // Apaga el LED
        }
    }
}
