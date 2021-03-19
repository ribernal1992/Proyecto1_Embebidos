/*******************************************************************************/
/**
   \file       startup_sam.c
   \brief      Low Level Initialization routine SAMV71 specific, based on ATMEL startup
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        Diego Mejia
   \description    Initial version
   \date          2020
*/


#include <stdint.h>
#include "device.h"
#include "core_cm7.h"

/* Initialize segments */
extern uint32_t _sfixed;
extern uint32_t _efixed;
extern uint32_t _etext;
extern uint32_t _srelocate;
extern uint32_t _erelocate;
extern uint32_t _szero;
extern uint32_t _ezero;
extern uint32_t _estack;

/* An extern declaration in a .c file is a bad programming practice*/
/* However, an exception will be made for CSTARTUP */
extern int main(void);

/*Static Functions*/
static void Reset_Handler(void);

/**
 * \brief Default interrupt handler for unused IRQs.
 */
void Dummy_Handler(void)
{
	while (1)
	{
	}
}

extern void SysTick_Handler();
extern void PIOA_Handler();

/* Exception Table */
__attribute__ ((section(".vectors")))
const DeviceVectors exception_table = {

	/* Configure Initial Stack Pointer, using linker-generated symbols */
	.pvStack = (void*) (&_estack),

	.pfnReset_Handler      = (void*) Reset_Handler,

	.pfnNMI_Handler        = (void*) Dummy_Handler,
	.pfnHardFault_Handler  = (void*) Dummy_Handler,
	.pfnMemManage_Handler  = (void*) Dummy_Handler,
	.pfnBusFault_Handler   = (void*) Dummy_Handler,
	.pfnUsageFault_Handler = (void*) Dummy_Handler,
	.pfnReserved1_Handler  = (void*) (0UL),          /* Reserved */
	.pfnReserved2_Handler  = (void*) (0UL),          /* Reserved */
	.pfnReserved3_Handler  = (void*) (0UL),          /* Reserved */
	.pfnReserved4_Handler  = (void*) (0UL),          /* Reserved */
	.pfnSVC_Handler        = (void*) Dummy_Handler,
	.pfnDebugMon_Handler   = (void*) Dummy_Handler,
	.pfnReserved5_Handler  = (void*) (0UL),          /* Reserved */
	.pfnPendSV_Handler     = (void*) Dummy_Handler,
	.pfnSysTick_Handler    = (void*) SysTick_Handler,

	/* Configurable interrupts */
	.pfnSUPC_Handler   = (void*) Dummy_Handler,   /* 0  Supply Controller */
	.pfnRSTC_Handler   = (void*) Dummy_Handler,   /* 1  Reset Controller */
	.pfnRTC_Handler    = (void*) Dummy_Handler,    /* 2  Real Time Clock */
	.pfnRTT_Handler    = (void*) Dummy_Handler,    /* 3  Real Time Timer */
	.pfnWDT_Handler    = (void*) Dummy_Handler,    /* 4  Watchdog Timer 0 */
	.pfnPMC_Handler    = (void*) Dummy_Handler,    /* 5  Power Management Controller */
	.pfnEFC_Handler    = (void*) Dummy_Handler,    /* 6  Enhanced Embedded Flash Controller */
	.pfnUART0_Handler  = (void*) Dummy_Handler,  /* 7  UART 0 */
	.pfnUART1_Handler  = (void*) Dummy_Handler,  /* 8  UART 1 */
	.pvReserved9       = (void*) (0UL),          /* 9  Reserved */
	.pfnPIOA_Handler   = (void*) PIOA_Handler,   /* 10 Parallel I/O Controller A */
	.pfnPIOB_Handler   = (void*) Dummy_Handler,   /* 11 Parallel I/O Controller B */
	.pfnPIOC_Handler   = (void*) Dummy_Handler,   /* 12 Parallel I/O Controller C */
	.pfnUSART0_Handler = (void*) Dummy_Handler, /* 13 USART 0 */
	.pfnUSART1_Handler = (void*) Dummy_Handler, /* 14 USART 1 */
	.pfnUSART2_Handler = (void*) Dummy_Handler, /* 15 USART 2 */
	.pfnPIOD_Handler   = (void*) Dummy_Handler,   /* 16 Parallel I/O Controller D */
	.pfnPIOE_Handler   = (void*) Dummy_Handler,   /* 17 Parallel I/O Controller E */
	.pfnHSMCI_Handler  = (void*) Dummy_Handler,  /* 18 Multimedia Card Interface */
	.pfnTWIHS0_Handler = (void*) Dummy_Handler, /* 19 Two Wire Interface 0 HS */
	.pfnTWIHS1_Handler = (void*) Dummy_Handler, /* 20 Two Wire Interface 1 HS */
	.pfnSPI0_Handler   = (void*) Dummy_Handler,   /* 21 Serial Peripheral Interface 0 */
	.pfnSSC_Handler    = (void*) Dummy_Handler,    /* 22 Synchronous Serial Controller */
	.pfnTC0_Handler    = (void*) Dummy_Handler,    /* 23 Timer/Counter 0 */
	.pfnTC1_Handler    = (void*) Dummy_Handler,    /* 24 Timer/Counter 1 */
	.pfnTC2_Handler    = (void*) Dummy_Handler,    /* 25 Timer/Counter 2 */
	.pfnTC3_Handler    = (void*) Dummy_Handler,    /* 26 Timer/Counter 3 */
	.pfnTC4_Handler    = (void*) Dummy_Handler,    /* 27 Timer/Counter 4 */
	.pfnTC5_Handler    = (void*) Dummy_Handler,    /* 28 Timer/Counter 5 */
	.pfnAFEC0_Handler  = (void*) Dummy_Handler,  /* 29 Analog Front End 0 */
	.pfnDACC_Handler   = (void*) Dummy_Handler,   /* 30 Digital To Analog Converter */
	.pfnPWM0_Handler   = (void*) Dummy_Handler,   /* 31 Pulse Width Modulation 0 */
	.pfnICM_Handler    = (void*) Dummy_Handler,    /* 32 Integrity Check Monitor */
	.pfnACC_Handler    = (void*) Dummy_Handler,    /* 33 Analog Comparator */
	.pfnUSBHS_Handler  = (void*) Dummy_Handler,  /* 34 USB Host / Device Controller */
	.pfnMCAN0_Handler  = (void*) Dummy_Handler,  /* 35 CAN Controller 0 */
	.pfnMCAN0_Line1_Handler = (void*) Dummy_Handler, /* 36 CAN Controller 0 - Line 1  */
	.pfnMCAN1_Handler  = (void*) Dummy_Handler,  /* 37 CAN Controller 1 */
	.pfnMCAN1_Line1_Handler = (void*) Dummy_Handler, /* 38 CAN Controller 1 - Line 1  */
	.pfnGMAC_Handler   = (void*) Dummy_Handler,   /* 39 Ethernet MAC */
	.pfnAFEC1_Handler  = (void*) Dummy_Handler,  /* 40 Analog Front End 1 */
	.pfnTWIHS2_Handler = (void*) Dummy_Handler, /* 41 Two Wire Interface 2 HS */
	.pfnSPI1_Handler   = (void*) Dummy_Handler,   /* 42 Serial Peripheral Interface 1 */
	.pfnQSPI_Handler   = (void*) Dummy_Handler,   /* 43 Quad I/O Serial Peripheral Interface */
	.pfnUART2_Handler  = (void*) Dummy_Handler,  /* 44 UART 2 */
	.pfnUART3_Handler  = (void*) Dummy_Handler,  /* 45 UART 3 */
	.pfnUART4_Handler  = (void*) Dummy_Handler,  /* 46 UART 4 */
	.pfnTC6_Handler    = (void*) Dummy_Handler,    /* 47 Timer/Counter 6 */
	.pfnTC7_Handler    = (void*) Dummy_Handler,    /* 48 Timer/Counter 7 */
	.pfnTC8_Handler    = (void*) Dummy_Handler,    /* 49 Timer/Counter 8 */
	.pfnTC9_Handler    = (void*) Dummy_Handler,    /* 50 Timer/Counter 9 */
	.pfnTC10_Handler   = (void*) Dummy_Handler,   /* 51 Timer/Counter 10 */
	.pfnTC11_Handler   = (void*) Dummy_Handler,   /* 52 Timer/Counter 11 */
	.pfnMLB_Handler    = (void*) Dummy_Handler,    /* 53 MediaLB */
	.pvReserved54      = (void*) (0UL),          /* 54 Reserved */
	.pvReserved55      = (void*) (0UL),          /* 55 Reserved */
	.pfnAES_Handler    = (void*) Dummy_Handler,    /* 56 AES */
	.pfnTRNG_Handler   = (void*) Dummy_Handler,   /* 57 True Random Generator */
	.pfnXDMAC_Handler  = (void*) Dummy_Handler,  /* 58 DMA */
	.pfnISI_Handler    = (void*) Dummy_Handler,    /* 59 Camera Interface */
	.pfnPWM1_Handler   = (void*) Dummy_Handler,   /* 60 Pulse Width Modulation 1 */
	.pvReserved61      = (void*) (0UL),          /* 61 Reserved */
	.pfnSDRAMC_Handler = (void*) Dummy_Handler, /* 62 SDRAM Controller */
	.pfnRSWDT_Handler   = (void*) Dummy_Handler    /* 63 Watchdog Timer 1 */
};


/**
 * \brief This is the code that gets called on processor reset.
 * To initialize the device, and call the main() routine.
 */
void Reset_Handler(void)

{
	    uint32_t *pSrc, *pDest;

		/* Initialize the relocate segment */
		pSrc = &_etext;
		pDest = &_srelocate;


        if (pSrc != pDest) {
				for (; pDest < &_erelocate;) {
						*pDest++ = *pSrc++;
				}
		}

		/* Clear the zero segment */
		for (pDest = &_szero; pDest < &_ezero;) {
				*pDest++ = 0;
		}

		/* Set the vector table base address*/
		/* Not necessary for default configuration*/
		//pSrc = (uint32_t *) & _sfixed;
		//SCB->VTOR = ((uint32_t) pSrc & SCB_VTOR_TBLOFF_Msk);


        /* Perform clock Initialization */
		//LowLevelInit();

		/* Branch to main function */
		main();

		/* Infinite loop */
		while (1);
}



