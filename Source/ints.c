/*Archivo con la funciones de interrupcion del micrcontroladores, revisar archivo startup_stm32g0b1.S */
#include "bsp.h"


/* cppcheck-suppress misra-c2012-8.4 ; its external linkage is declared at HAL library */
void NMI_Handler( void )
{
}

/* cppcheck-suppress misra-c2012-8.4 ; its external linkage is declared at HAL library */
void HardFault_Handler( void )
{
    while (1) {
        // Bucle infinito en caso de fallo grave
    }
}

/* cppcheck-suppress misra-c2012-8.4 ; its external linkage is declared at HAL library */
void SVC_Handler( void )
{
}

/* cppcheck-suppress misra-c2012-8.4 ; its external linkage is declared at HAL library */
void PendSV_Handler( void )
{
}

/* cppcheck-suppress misra-c2012-8.4 ; its external linkage is declared at HAL library */
void SysTick_Handler( void )
{
    gpio_bit_toggle(GPIOC, GPIO_PIN_7);

}