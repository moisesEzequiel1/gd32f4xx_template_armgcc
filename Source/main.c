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
// === Inicializa PC7 como salida push-pull ===
static void gpio_output_init(void)
{
    rcu_periph_clock_enable(RCU_GPIOC); // Habilita reloj de GPIOC

    gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_7);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);

    gpio_bit_reset(GPIOC, GPIO_PIN_7); // Estado inicial en bajo
}

// === Configura SysTick a 1ms ===
static void systick_init(void)
{
    SystemCoreClockUpdate(); // Asegura que SystemCoreClock esté correcto

    if (SysTick_Config(SystemCoreClock / 1000)) {
        // Error si no se puede configurar
        while (1);
    }
}

/**
 * @brief   **Application entry point**
 *
 * Ptovide the proper description for function main according to your own
 * implementation
 *
 * @retval  None
 */
int main( void )
{
    gpio_output_init();  // Configura PC7 como salida
    systick_init();      // Configura SysTick a 1 ms

    for( ;; )
    {

    }

}