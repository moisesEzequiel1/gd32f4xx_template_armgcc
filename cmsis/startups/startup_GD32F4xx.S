/**************************************************************************//**
 * @file     startup_GD32F4xx.S
 * @version  V2.00
 * $Revision: 3 $
 * $Date: 20/05/22 7:57p $
 * @brief    CMSIS Cortex-M4 Core Device Startup File for gd32f4xx.s
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0   
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

	.syntax	unified
	.arch	armv7-m

	.section .stack
	.align	3
#ifdef __STACK_SIZE
	.equ	Stack_Size, __STACK_SIZE
#else
	.equ	Stack_Size, 0x00000400
#endif
	.globl	__StackTop
	.globl	__StackLimit
__StackLimit:
	.space	Stack_Size
	.size	__StackLimit, . - __StackLimit
__StackTop:
	.size	__StackTop, . - __StackTop

	.section .heap
	.align	3
#ifdef __HEAP_SIZE
	.equ	Heap_Size, __HEAP_SIZE
#else
	.equ	Heap_Size, 0x00000400
#endif
	.globl	__HeapBase
	.globl	__HeapLimit
__HeapBase:
	.if	Heap_Size
	.space	Heap_Size
	.endif
	.size	__HeapBase, . - __HeapBase
__HeapLimit:
	.size	__HeapLimit, . - __HeapLimit

	.section .vectors
	.align	2
	.globl	__Vectors
__Vectors:
	.long	__StackTop            /* Top of Stack */
	.long	Reset_Handler         /* Reset Handler */
	.long	NMI_Handler           /* NMI Handler */
	.long	HardFault_Handler     /* Hard Fault Handler */
	.long	MemManage_Handler     /* MemManage_Handler */
	.long	BusFault_Handler      /* BusFault_Handler */
	.long	UsageFault_Handler    /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	SVC_Handler           /* SVCall Handler */
	.long	DebugMon_Handler      /* Reserved */
	.long	0                     /* Reserved */
	.long	PendSV_Handler        /* PendSV Handler */
	.long	SysTick_Handler       /* SysTick Handler */

	/* External interrupts */
    .long   WWDGT_IRQHandler                  /* ; 16:Window Watchdog Timer */
    .long   LVD_IRQHandler                    /* ; 17:LVD through EXTI Line detect */
    .long   TAMPER_STAMP_IRQHandler           /* ; 18:Tamper and TimeStamp through EXTI Line detect */
    .long   RTC_WKUP_IRQHandler               /* ; 19:RTC Wakeup through EXTI Line */
    .long   FMC_IRQHandler                    /* ; 20:FMC */
    .long   RCU_CTC_IRQHandler                /* ; 21:RCU and CTC */
    .long   EXTI0_IRQHandler                  /* ; 22:EXTI Line 0 */
    .long   EXTI1_IRQHandler                  /* ; 23:EXTI Line 1 */
    .long   EXTI2_IRQHandler                  /* ; 24:EXTI Line 2 */
    .long   EXTI3_IRQHandler                  /* ; 25:EXTI Line 3 */
    .long   EXTI4_IRQHandler                  /* ; 26:EXTI Line 4 */
    .long   DMA0_Channel0_IRQHandler          /* ; 27:DMA0 Channel0 */
    .long   DMA0_Channel1_IRQHandler          /* ; 28:DMA0 Channel1 */
    .long   DMA0_Channel2_IRQHandler          /* ; 29:DMA0 Channel2 */
    .long   DMA0_Channel3_IRQHandler          /* ; 30:DMA0 Channel3 */
    .long   DMA0_Channel4_IRQHandler          /* ; 31:DMA0 Channel4 */
    .long   DMA0_Channel5_IRQHandler          /* ; 32:DMA0 Channel5 */
    .long   DMA0_Channel6_IRQHandler          /* ; 33:DMA0 Channel6 */
    .long   ADC_IRQHandler                    /* ; 34:ADC */
    .long   CAN0_TX_IRQHandler                /* ; 35:CAN0 TX */
    .long   CAN0_RX0_IRQHandler               /* ; 36:CAN0 RX0 */
    .long   CAN0_RX1_IRQHandler               /* ; 37:CAN0 RX1 */
    .long   CAN0_EWMC_IRQHandler              /* ; 38:CAN0 EWMC */
    .long   EXTI5_9_IRQHandler                /* ; 39:EXTI5 to EXTI9 */
    .long   TIMER0_BRK_TIMER8_IRQHandler      /* ; 40:TIMER0 Break and TIMER8 */
    .long   TIMER0_UP_TIMER9_IRQHandler       /* ; 41:TIMER0 Update and TIMER9 */
    .long   TIMER0_TRG_CMT_TIMER10_IRQHandler /* ; 42:TIMER0 Trigger and Commutation and TIMER10 */
    .long   TIMER0_Channel_IRQHandler         /* ; 43:TIMER0 Channel Capture Compare */
    .long   TIMER1_IRQHandler                 /* ; 44:TIMER1 */
    .long   TIMER2_IRQHandler                 /* ; 45:TIMER2 */
    .long   TIMER3_IRQHandler                 /* ; 46:TIMER3 */
    .long   I2C0_EV_IRQHandler                /* ; 47:I2C0 Event */
    .long   I2C0_ER_IRQHandler                /* ; 48:I2C0 Error */
    .long   I2C1_EV_IRQHandler                /* ; 49:I2C1 Event */
    .long   I2C1_ER_IRQHandler                /* ; 50:I2C1 Error */
    .long   SPI0_IRQHandler                   /* ; 51:SPI0 */
    .long   SPI1_IRQHandler                   /* ; 52:SPI1 */
    .long   USART0_IRQHandler                 /* ; 53:USART0 */
    .long   USART1_IRQHandler                 /* ; 54:USART1 */
    .long   USART2_IRQHandler                 /* ; 55:USART2 */
    .long   EXTI10_15_IRQHandler              /* ; 56:EXTI10 to EXTI15 */
    .long   RTC_Alarm_IRQHandler              /* ; 57:RTC Alarm */
    .long   USBFS_WKUP_IRQHandler             /* ; 58:USBFS Wakeup */
    .long   TIMER7_BRK_TIMER11_IRQHandler     /* ; 59:TIMER7 Break and TIMER11 */
    .long   TIMER7_UP_TIMER12_IRQHandler      /* ; 60:TIMER7 Update and TIMER12 */
    .long   TIMER7_TRG_CMT_TIMER13_IRQHandler /* ; 61:TIMER7 Trigger and Commutation and TIMER13 */
    .long   TIMER7_Channel_IRQHandler         /* ; 62:TIMER7 Capture Compare */
    .long   DMA0_Channel7_IRQHandler          /* ; 63:DMA0 Channel7 */
    .long   EXMC_IRQHandler                   /* ; 64:EXMC */
    .long   SDIO_IRQHandler                   /* ; 65:SDIO */
    .long   TIMER4_IRQHandler                 /* ; 66:TIMER4 */
    .long   SPI2_IRQHandler                   /* ; 67:SPI2 */
    .long   UART3_IRQHandler                  /* ; 68:UART3 */
    .long   UART4_IRQHandler                  /* ; 69:UART4 */
    .long   TIMER5_DAC_IRQHandler             /* ; 70:TIMER5 and DAC0 DAC1 Underrun error */
    .long   TIMER6_IRQHandler                 /* ; 71:TIMER6 */
    .long   DMA1_Channel0_IRQHandler          /* ; 72:DMA1 Channel0 */
    .long   DMA1_Channel1_IRQHandler          /* ; 73:DMA1 Channel1 */
    .long   DMA1_Channel2_IRQHandler          /* ; 74:DMA1 Channel2 */
    .long   DMA1_Channel3_IRQHandler          /* ; 75:DMA1 Channel3 */
    .long   DMA1_Channel4_IRQHandler          /* ; 76:DMA1 Channel4 */
    .long   ENET_IRQHandler                   /* ; 77:Ethernet */
    .long   ENET_WKUP_IRQHandler              /* ; 78:Ethernet Wakeup through EXTI Line */
    .long   CAN1_TX_IRQHandler                /* ; 79:CAN1 TX */
    .long   CAN1_RX0_IRQHandler               /* ; 80:CAN1 RX0 */
    .long   CAN1_RX1_IRQHandler               /* ; 81:CAN1 RX1 */
    .long   CAN1_EWMC_IRQHandler              /* ; 82:CAN1 EWMC */
    .long   USBFS_IRQHandler                  /* ; 83:USBFS */
    .long   DMA1_Channel5_IRQHandler          /* ; 84:DMA1 Channel5 */
    .long   DMA1_Channel6_IRQHandler          /* ; 85:DMA1 Channel6 */
    .long   DMA1_Channel7_IRQHandler          /* ; 86:DMA1 Channel7 */
    .long   USART5_IRQHandler                 /* ; 87:USART5 */
    .long   I2C2_EV_IRQHandler                /* ; 88:I2C2 Event */
    .long   I2C2_ER_IRQHandler                /* ; 89:I2C2 Error */
    .long   USBHS_EP1_Out_IRQHandler          /* ; 90:USBHS Endpoint 1 Out */
    .long   USBHS_EP1_In_IRQHandler           /* ; 91:USBHS Endpoint 1 in */
    .long   USBHS_WKUP_IRQHandler             /* ; 92:USBHS Wakeup through EXTI Line */
    .long   USBHS_IRQHandler                  /* ; 93:USBHS */
    .long   DCI_IRQHandler                    /* ; 94:DCI */
    .long   0                                 /* ; 95:Reserved */
    .long   TRNG_IRQHandler                   /* ; 96:TRNG */
    .long   FPU_IRQHandler                    /* ; 97:FPU */

	.size	__Vectors, . - __Vectors

	.text
	.thumb
	.thumb_func
	.align	2
	.globl	Reset_Handler
	.type	Reset_Handler, %function
Reset_Handler:
/*  Firstly it copies data from read only memory to RAM. There are two schemes
 *  to copy. One can copy more than one sections. Another can only copy
 *  one section.  The former scheme needs more instructions and read-only
 *  data to implement than the latter.
 *  Macro __STARTUP_COPY_MULTIPLE is used to choose between two schemes.  */

#ifdef __STARTUP_COPY_MULTIPLE
/*  Multiple sections scheme.
 *
 *  Between symbol address __copy_table_start__ and __copy_table_end__,
 *  there are array of triplets, each of which specify:
 *    offset 0: LMA of start of a section to copy from
 *    offset 4: VMA of start of a section to copy to
 *    offset 8: size of the section to copy. Must be multiply of 4
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
	ldr	r4, =__copy_table_start__
	ldr	r5, =__copy_table_end__

.L_loop0:
	cmp	r4, r5
	bge	.L_loop0_done
	ldr	r1, [r4]
	ldr	r2, [r4, #4]
	ldr	r3, [r4, #8]

.L_loop0_0:
	subs	r3, #4
	ldr	r0, [r1,r3]
	str	r0, [r2,r3]
	bge	.L_loop0_0

	adds	r4, #12
	b	.L_loop0

.L_loop0_done:
#else
/*  Single section scheme.
 *
 *  The ranges of copy from/to are specified by following symbols
 *    __etext: LMA of start of the section to copy from. Usually end of text
 *    __data_start__: VMA of start of the section to copy to
 *    __data_end__: VMA of end of the section to copy to
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
	ldr	r1, =__etext
	ldr	r2, =__data_start__
	ldr	r3, =__data_end__

	subs	r3, r2
	ble	.L_loop1_done

.L_loop1:
	subs	r3, #4
	ldr	r0, [r1,r3]
	str	r0, [r2,r3]
	bgt	.L_loop1

.L_loop1_done:

#endif /*__STARTUP_COPY_MULTIPLE */

/*  This part of work usually is done in C library startup code. Otherwise,
 *  define this macro to enable it in this startup.
 *
 *  There are two schemes too. One can clear multiple BSS sections. Another
 *  can only clear one section. The former is more size expensive than the
 *  latter.
 *
 *  Define macro __STARTUP_CLEAR_BSS_MULTIPLE to choose the former.
 *  Otherwise efine macro __STARTUP_CLEAR_BSS to choose the later.
 */
#ifdef __STARTUP_CLEAR_BSS_MULTIPLE
/*  Multiple sections scheme.
 *
 *  Between symbol address __copy_table_start__ and __copy_table_end__,
 *  there are array of tuples specifying:
 *    offset 0: Start of a BSS section
 *    offset 4: Size of this BSS section. Must be multiply of 4
 */
	ldr	r3, =__zero_table_start__
	ldr	r4, =__zero_table_end__

.L_loop2:
	cmp	r3, r4
	bge	.L_loop2_done
	ldr	r1, [r3]
	ldr	r2, [r3, #4]
	movs	r0, 0

.L_loop2_0:
	subs	r2, #4
	str 	r0, [r1, r2]
	bgt	.L_loop2_0

	adds	r3, #8
	b	.L_loop2
.L_loop2_done:

#elif defined (__STARTUP_CLEAR_BSS)
/*  Single BSS section scheme.
 *
 *  The BSS section is specified by following symbols
 *    __bss_start__: start of the BSS section.
 *    __bss_end__: end of the BSS section.
 *
 *  Both addresses must be aligned to 4 bytes boundary.
 */
	ldr	r1, =__bss_start__
	ldr	r2, =__bss_end__

    movs    r0, 0

    subs    r2, r1
    ble .L_loop3_done

.L_loop3:
    subs    r2, #4
    str r0, [r1, r2]
    bgt .L_loop3
.L_loop3_done:
#endif /* __STARTUP_CLEAR_BSS_MULTIPLE || __STARTUP_CLEAR_BSS */
#ifndef __NO_SYSTEM_INIT
	bl	SystemInit
#endif
	
//#ifndef __START
//#define __START _start
//#endif
//	bl	__START

    bl  main
    bx  lr

	.pool
	.size	Reset_Handler, . - Reset_Handler

	.align	1
	.thumb_func
	.weak	Default_Handler
	.type	Default_Handler, %function
Default_Handler:
	b	.
	.size	Default_Handler, . - Default_Handler

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
	.macro	def_irq_handler	handler_name
	.weak	\handler_name
	.set	\handler_name, Default_Handler
	.endm

    def_irq_handler	NMI_Handler
    def_irq_handler	HardFault_Handler
    def_irq_handler	MemManage_Handler
    def_irq_handler	BusFault_Handler
    def_irq_handler	UsageFault_Handler
    def_irq_handler	SVC_Handler
    def_irq_handler	DebugMon_Handler
    def_irq_handler	PendSV_Handler
    def_irq_handler	SysTick_Handler
    
    def_irq_handler	WWDGT_IRQHandler
    def_irq_handler	LVD_IRQHandler
    def_irq_handler	TAMPER_STAMP_IRQHandler
    def_irq_handler	RTC_WKUP_IRQHandler
    def_irq_handler	FMC_IRQHandler
    def_irq_handler	RCU_CTC_IRQHandler
    def_irq_handler	EXTI0_IRQHandler
    def_irq_handler	EXTI1_IRQHandler
    def_irq_handler	EXTI2_IRQHandler
    def_irq_handler	EXTI3_IRQHandler
    def_irq_handler	EXTI4_IRQHandler
    def_irq_handler	DMA0_Channel0_IRQHandler
    def_irq_handler	DMA0_Channel1_IRQHandler
    def_irq_handler	DMA0_Channel2_IRQHandler
    def_irq_handler	DMA0_Channel3_IRQHandler
    def_irq_handler	DMA0_Channel4_IRQHandler
    def_irq_handler	DMA0_Channel5_IRQHandler
    def_irq_handler	DMA0_Channel6_IRQHandler
    def_irq_handler	ADC_IRQHandler
    def_irq_handler	CAN0_TX_IRQHandler
    def_irq_handler	CAN0_RX0_IRQHandler
    def_irq_handler	CAN0_RX1_IRQHandler
    def_irq_handler	CAN0_EWMC_IRQHandler
    def_irq_handler	EXTI5_9_IRQHandler
    def_irq_handler	TIMER0_BRK_TIMER8_IRQHandler
    def_irq_handler	TIMER0_UP_TIMER9_IRQHandler
    def_irq_handler	TIMER0_TRG_CMT_TIMER10_IRQHandler
    def_irq_handler	TIMER0_Channel_IRQHandler
    def_irq_handler	TIMER1_IRQHandler
    def_irq_handler	TIMER2_IRQHandler
    def_irq_handler	TIMER3_IRQHandler
    def_irq_handler	I2C0_EV_IRQHandler
    def_irq_handler	I2C0_ER_IRQHandler
    def_irq_handler	I2C1_EV_IRQHandler
    def_irq_handler	I2C1_ER_IRQHandler
    def_irq_handler	SPI0_IRQHandler
    def_irq_handler	SPI1_IRQHandler
    def_irq_handler	USART0_IRQHandler
    def_irq_handler	USART1_IRQHandler
    def_irq_handler	USART2_IRQHandler
    def_irq_handler	EXTI10_15_IRQHandler
    def_irq_handler	RTC_Alarm_IRQHandler
    def_irq_handler	USBFS_WKUP_IRQHandler
    def_irq_handler	TIMER7_BRK_TIMER11_IRQHandler
    def_irq_handler	TIMER7_UP_TIMER12_IRQHandler
    def_irq_handler	TIMER7_TRG_CMT_TIMER13_IRQHandler
    def_irq_handler	TIMER7_Channel_IRQHandler
    def_irq_handler	DMA0_Channel7_IRQHandler
    def_irq_handler	EXMC_IRQHandler
    def_irq_handler	SDIO_IRQHandler
    def_irq_handler	TIMER4_IRQHandler
    def_irq_handler	SPI2_IRQHandler
    def_irq_handler	UART3_IRQHandler
    def_irq_handler	UART4_IRQHandler
    def_irq_handler	TIMER5_DAC_IRQHandler
    def_irq_handler	TIMER6_IRQHandler
    def_irq_handler	DMA1_Channel0_IRQHandler
    def_irq_handler	DMA1_Channel1_IRQHandler
    def_irq_handler	DMA1_Channel2_IRQHandler
    def_irq_handler	DMA1_Channel3_IRQHandler
    def_irq_handler	DMA1_Channel4_IRQHandler
    def_irq_handler	ENET_IRQHandler
    def_irq_handler	ENET_WKUP_IRQHandler
    def_irq_handler	CAN1_TX_IRQHandler
    def_irq_handler	CAN1_RX0_IRQHandler
    def_irq_handler	CAN1_RX1_IRQHandler
    def_irq_handler	CAN1_EWMC_IRQHandler
    def_irq_handler	USBFS_IRQHandler
    def_irq_handler	DMA1_Channel5_IRQHandler
    def_irq_handler	DMA1_Channel6_IRQHandler
    def_irq_handler	DMA1_Channel7_IRQHandler
    def_irq_handler	USART5_IRQHandler
    def_irq_handler	I2C2_EV_IRQHandler
    def_irq_handler	I2C2_ER_IRQHandler
    def_irq_handler	USBHS_EP1_Out_IRQHandler
    def_irq_handler	USBHS_EP1_In_IRQHandler
    def_irq_handler	USBHS_WKUP_IRQHandler
    def_irq_handler	USBHS_IRQHandler
    def_irq_handler	DCI_IRQHandler
    def_irq_handler	TRNG_IRQHandler
    def_irq_handler	FPU_IRQHandler


    .end
