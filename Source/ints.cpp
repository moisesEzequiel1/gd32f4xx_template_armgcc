#include "bsp.h"

#ifdef __cplusplus
extern "C" {
#endif


void NMI_Handler( void )
{
}

void HardFault_Handler( void )
{
    while (1);
}

void SVC_Handler( void )
{
}

void PendSV_Handler( void )
{
}

#ifdef __cplusplus
}
#endif   