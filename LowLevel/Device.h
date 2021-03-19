/*
 * Device.h
 *
 *      Author: Diego Mejia
 */

#ifndef SAMV71X_B_TOOLSET_GCC_DEVICE_H_
#define SAMV71X_B_TOOLSET_GCC_DEVICE_H_


/**< Interrupt Number Definition */
typedef enum IRQn
{
/******  Cortex-M7 Processor Exceptions Numbers ******************************/
  NonMaskableInt_IRQn   = -14, /**<  2 Non Maskable Interrupt                */
  HardFault_IRQn        = -13, /**<  3 HardFault Interrupt                   */
  MemoryManagement_IRQn = -12, /**<  4 Cortex-M7 Memory Management Interrupt */
  BusFault_IRQn         = -11, /**<  5 Cortex-M7 Bus Fault Interrupt         */
  UsageFault_IRQn       = -10, /**<  6 Cortex-M7 Usage Fault Interrupt       */
  SVCall_IRQn           = -5,  /**< 11 Cortex-M7 SV Call Interrupt           */
  DebugMonitor_IRQn     = -4,  /**< 12 Cortex-M7 Debug Monitor Interrupt     */
  PendSV_IRQn           = -2,  /**< 14 Cortex-M7 Pend SV Interrupt           */
  SysTick_IRQn          = -1,  /**< 15 Cortex-M7 System Tick Interrupt       */
/******  SAMV71Q21 specific Interrupt Numbers *********************************/

  SUPC_IRQn            =  0, /**<  0 SAMV71Q21 Supply Controller (SUPC) */
  RSTC_IRQn            =  1, /**<  1 SAMV71Q21 Reset Controller (RSTC) */
  RTC_IRQn             =  2, /**<  2 SAMV71Q21 Real Time Clock (RTC) */
  RTT_IRQn             =  3, /**<  3 SAMV71Q21 Real Time Timer (RTT) */
  WDT_IRQn             =  4, /**<  4 SAMV71Q21 Watchdog Timer (WDT) */
  PMC_IRQn             =  5, /**<  5 SAMV71Q21 Power Management Controller (PMC) */
  EFC_IRQn             =  6, /**<  6 SAMV71Q21 Enhanced Embedded Flash Controller (EFC) */
  UART0_IRQn           =  7, /**<  7 SAMV71Q21 UART 0 (UART0) */
  UART1_IRQn           =  8, /**<  8 SAMV71Q21 UART 1 (UART1) */
  PIOA_IRQn            = 10, /**< 10 SAMV71Q21 Parallel I/O Controller A (PIOA) */
  PIOB_IRQn            = 11, /**< 11 SAMV71Q21 Parallel I/O Controller B (PIOB) */
  PIOC_IRQn            = 12, /**< 12 SAMV71Q21 Parallel I/O Controller C (PIOC) */
  USART0_IRQn          = 13, /**< 13 SAMV71Q21 USART 0 (USART0) */
  USART1_IRQn          = 14, /**< 14 SAMV71Q21 USART 1 (USART1) */
  USART2_IRQn          = 15, /**< 15 SAMV71Q21 USART 2 (USART2) */
  PIOD_IRQn            = 16, /**< 16 SAMV71Q21 Parallel I/O Controller D (PIOD) */
  PIOE_IRQn            = 17, /**< 17 SAMV71Q21 Parallel I/O Controller E (PIOE) */
  HSMCI_IRQn           = 18, /**< 18 SAMV71Q21 Multimedia Card Interface (HSMCI) */
  TWIHS0_IRQn          = 19, /**< 19 SAMV71Q21 Two Wire Interface 0 HS (TWIHS0) */
  TWIHS1_IRQn          = 20, /**< 20 SAMV71Q21 Two Wire Interface 1 HS (TWIHS1) */
  SPI0_IRQn            = 21, /**< 21 SAMV71Q21 Serial Peripheral Interface 0 (SPI0) */
  SSC_IRQn             = 22, /**< 22 SAMV71Q21 Synchronous Serial Controller (SSC) */
  TC0_IRQn             = 23, /**< 23 SAMV71Q21 Timer/Counter 0 (TC0) */
  TC1_IRQn             = 24, /**< 24 SAMV71Q21 Timer/Counter 1 (TC1) */
  TC2_IRQn             = 25, /**< 25 SAMV71Q21 Timer/Counter 2 (TC2) */
  TC3_IRQn             = 26, /**< 26 SAMV71Q21 Timer/Counter 3 (TC3) */
  TC4_IRQn             = 27, /**< 27 SAMV71Q21 Timer/Counter 4 (TC4) */
  TC5_IRQn             = 28, /**< 28 SAMV71Q21 Timer/Counter 5 (TC5) */
  AFEC0_IRQn           = 29, /**< 29 SAMV71Q21 Analog Front End 0 (AFEC0) */
  DACC_IRQn            = 30, /**< 30 SAMV71Q21 Digital To Analog Converter (DACC) */
  PWM0_IRQn            = 31, /**< 31 SAMV71Q21 Pulse Width Modulation 0 (PWM0) */
  ICM_IRQn             = 32, /**< 32 SAMV71Q21 Integrity Check Monitor (ICM) */
  ACC_IRQn             = 33, /**< 33 SAMV71Q21 Analog Comparator (ACC) */
  USBHS_IRQn           = 34, /**< 34 SAMV71Q21 USB Host / Device Controller (USBHS) */
  MCAN0_IRQn           = 35, /**< 35 SAMV71Q21 MCAN Controller 0 (MCAN0) */
  MCAN0_LINE1_IRQn     = 36, /**< 36 SAMV71Q21 MCAN Controller 0 LINE1 (MCAN0) */
  MCAN1_IRQn           = 37, /**< 37 SAMV71Q21 MCAN Controller 1 (MCAN1) */
  MCAN1_LINE1_IRQn     = 38, /**< 38 SAMV71Q21 MCAN Controller 1 LINE1 (MCAN1) */
  GMAC_IRQn            = 39, /**< 39 SAMV71Q21 Ethernet MAC (GMAC) */
  AFEC1_IRQn           = 40, /**< 40 SAMV71Q21 Analog Front End 1 (AFEC1) */
  TWIHS2_IRQn          = 41, /**< 41 SAMV71Q21 Two Wire Interface 2 HS (TWIHS2) */
  SPI1_IRQn            = 42, /**< 42 SAMV71Q21 Serial Peripheral Interface 1 (SPI1) */
  QSPI_IRQn            = 43, /**< 43 SAMV71Q21 Quad I/O Serial Peripheral Interface (QSPI) */
  UART2_IRQn           = 44, /**< 44 SAMV71Q21 UART 2 (UART2) */
  UART3_IRQn           = 45, /**< 45 SAMV71Q21 UART 3 (UART3) */
  UART4_IRQn           = 46, /**< 46 SAMV71Q21 UART 4 (UART4) */
  TC6_IRQn             = 47, /**< 47 SAMV71Q21 Timer/Counter 6 (TC6) */
  TC7_IRQn             = 48, /**< 48 SAMV71Q21 Timer/Counter 7 (TC7) */
  TC8_IRQn             = 49, /**< 49 SAMV71Q21 Timer/Counter 8 (TC8) */
  TC9_IRQn             = 50, /**< 50 SAMV71Q21 Timer/Counter 9 (TC9) */
  TC10_IRQn            = 51, /**< 51 SAMV71Q21 Timer/Counter 10 (TC10) */
  TC11_IRQn            = 52, /**< 52 SAMV71Q21 Timer/Counter 11 (TC11) */
  MLB_IRQn             = 53, /**< 53 SAMV71Q21 MediaLB (MLB) */
  AES_IRQn             = 56, /**< 56 SAMV71Q21 AES (AES) */
  TRNG_IRQn            = 57, /**< 57 SAMV71Q21 True Random Generator (TRNG) */
  XDMAC_IRQn           = 58, /**< 58 SAMV71Q21 DMA (XDMAC) */
  ISI_IRQn             = 59, /**< 59 SAMV71Q21 Camera Interface (ISI) */
  PWM1_IRQn            = 60, /**< 60 SAMV71Q21 Pulse Width Modulation 1 (PWM1) */
  SDRAMC_IRQn          = 62, /**< 62 SAMV71Q21 SDRAM Controller (SDRAMC) */
  RSWDT_IRQn           = 63, /**< 63 SAMV71Q21 Reinforced Secure Watchdog Timer (RSWDT) */

  PERIPH_COUNT_IRQn    = 64  /**< Number of peripheral IDs */
} IRQn_Type;


typedef struct _DeviceVectors
{
  /* Stack pointer */
  void* pvStack;

  /* Cortex-M handlers */
  void* pfnReset_Handler;
  void* pfnNMI_Handler;
  void* pfnHardFault_Handler;
  void* pfnMemManage_Handler;
  void* pfnBusFault_Handler;
  void* pfnUsageFault_Handler;
  void* pfnReserved1_Handler;
  void* pfnReserved2_Handler;
  void* pfnReserved3_Handler;
  void* pfnReserved4_Handler;
  void* pfnSVC_Handler;
  void* pfnDebugMon_Handler;
  void* pfnReserved5_Handler;
  void* pfnPendSV_Handler;
  void* pfnSysTick_Handler;

  /* Peripheral handlers */
  void* pfnSUPC_Handler;   /*  0 Supply Controller */
  void* pfnRSTC_Handler;   /*  1 Reset Controller */
  void* pfnRTC_Handler;    /*  2 Real Time Clock */
  void* pfnRTT_Handler;    /*  3 Real Time Timer */
  void* pfnWDT_Handler;    /*  4 Watchdog Timer */
  void* pfnPMC_Handler;    /*  5 Power Management Controller */
  void* pfnEFC_Handler;    /*  6 Enhanced Embedded Flash Controller */
  void* pfnUART0_Handler;  /*  7 UART 0 */
  void* pfnUART1_Handler;  /*  8 UART 1 */
  void* pvReserved9;
  void* pfnPIOA_Handler;   /* 10 Parallel I/O Controller A */
  void* pfnPIOB_Handler;   /* 11 Parallel I/O Controller B */
  void* pfnPIOC_Handler;   /* 12 Parallel I/O Controller C */
  void* pfnUSART0_Handler; /* 13 USART 0 */
  void* pfnUSART1_Handler; /* 14 USART 1 */
  void* pfnUSART2_Handler; /* 15 USART 2 */
  void* pfnPIOD_Handler;   /* 16 Parallel I/O Controller D */
  void* pfnPIOE_Handler;   /* 17 Parallel I/O Controller E */
  void* pfnHSMCI_Handler;  /* 18 Multimedia Card Interface */
  void* pfnTWIHS0_Handler; /* 19 Two Wire Interface 0 HS */
  void* pfnTWIHS1_Handler; /* 20 Two Wire Interface 1 HS */
  void* pfnSPI0_Handler;   /* 21 Serial Peripheral Interface 0 */
  void* pfnSSC_Handler;    /* 22 Synchronous Serial Controller */
  void* pfnTC0_Handler;    /* 23 Timer/Counter 0 */
  void* pfnTC1_Handler;    /* 24 Timer/Counter 1 */
  void* pfnTC2_Handler;    /* 25 Timer/Counter 2 */
  void* pfnTC3_Handler;    /* 26 Timer/Counter 3 */
  void* pfnTC4_Handler;    /* 27 Timer/Counter 4 */
  void* pfnTC5_Handler;    /* 28 Timer/Counter 5 */
  void* pfnAFEC0_Handler;  /* 29 Analog Front End 0 */
  void* pfnDACC_Handler;   /* 30 Digital To Analog Converter */
  void* pfnPWM0_Handler;   /* 31 Pulse Width Modulation 0 */
  void* pfnICM_Handler;    /* 32 Integrity Check Monitor */
  void* pfnACC_Handler;    /* 33 Analog Comparator */
  void* pfnUSBHS_Handler;  /* 34 USB Host / Device Controller */
  void* pfnMCAN0_Handler;  /* 35 MCAN Controller 0 */
  void* pfnMCAN0_Line1_Handler;  /* 36 MCAN Controller 0 */
  void* pfnMCAN1_Handler;  /* 37 MCAN Controller 1 */
  void* pfnMCAN1_Line1_Handler;  /* 38 MCAN Controller 1 */
  void* pfnGMAC_Handler;   /* 39 Ethernet MAC */
  void* pfnAFEC1_Handler;  /* 40 Analog Front End 1 */
  void* pfnTWIHS2_Handler; /* 41 Two Wire Interface 2 HS */
  void* pfnSPI1_Handler;   /* 42 Serial Peripheral Interface 1 */
  void* pfnQSPI_Handler;   /* 43 Quad I/O Serial Peripheral Interface */
  void* pfnUART2_Handler;  /* 44 UART 2 */
  void* pfnUART3_Handler;  /* 45 UART 3 */
  void* pfnUART4_Handler;  /* 46 UART 4 */
  void* pfnTC6_Handler;    /* 47 Timer/Counter 6 */
  void* pfnTC7_Handler;    /* 48 Timer/Counter 7 */
  void* pfnTC8_Handler;    /* 49 Timer/Counter 8 */
  void* pfnTC9_Handler;    /* 50 Timer/Counter 9 */
  void* pfnTC10_Handler;   /* 51 Timer/Counter 10 */
  void* pfnTC11_Handler;   /* 52 Timer/Counter 11 */
  void* pfnMLB_Handler;    /* 53 MediaLB */
  void* pvReserved54;
  void* pvReserved55;
  void* pfnAES_Handler;    /* 56 AES */
  void* pfnTRNG_Handler;   /* 57 True Random Generator */
  void* pfnXDMAC_Handler;  /* 58 DMA */
  void* pfnISI_Handler;    /* 59 Camera Interface */
  void* pfnPWM1_Handler;   /* 60 Pulse Width Modulation 1 */
  void* pvReserved61;
  void* pfnSDRAMC_Handler; /* 62 SDRAM Controller */
  void* pfnRSWDT_Handler;  /* 63 Reinforced Secure Watchdog Timer */
} DeviceVectors;




/**
 * \brief Configuration of the Cortex-M7 Processor and Core Peripherals
 */

#define __CM7_REV              0x0000 /**< SAMV71Q21 core revision number ([15:8] revision number, [7:0] patch number) */
#define __MPU_PRESENT          1      /**< SAMV71Q21 does provide a MPU */
#define __NVIC_PRIO_BITS       3      /**< SAMV71Q21 uses 3 Bits for the Priority Levels */
#define __FPU_PRESENT          1      /**< SAMV71Q21 does provide a FPU                */
#define __FPU_DP               1      /**< SAMV71Q21 Double precision FPU              */
#define __ICACHE_PRESENT       1      /**< SAMV71Q21 does provide an Instruction Cache */
#define __DCACHE_PRESENT       1      /**< SAMV71Q21 does provide a Data Cache         */
#define __DTCM_PRESENT         1      /**< SAMV71Q21 does provide a Data TCM           */
#define __ITCM_PRESENT         1      /**< SAMV71Q21 does provide an Instruction TCM   */
#define __Vendor_SysTickConfig 0      /**< Set to 1 if different SysTick Config is used */



/* ************************************************************************** */
/*   PERIPHERAL ID DEFINITIONS FOR SAMV71Q21 */
/* ************************************************************************** */
/** \addtogroup SAMV71Q21_id Peripheral Ids Definitions */
/*@{*/

#define ID_SUPC   ( 0) /**< \brief Supply Controller (SUPC) */
#define ID_RSTC   ( 1) /**< \brief Reset Controller (RSTC) */
#define ID_RTC    ( 2) /**< \brief Real Time Clock (RTC) */
#define ID_RTT    ( 3) /**< \brief Real Time Timer (RTT) */
#define ID_WDT    ( 4) /**< \brief Watchdog Timer (WDT) */
#define ID_PMC    ( 5) /**< \brief Power Management Controller (PMC) */
#define ID_EFC    ( 6) /**< \brief Enhanced Embedded Flash Controller (EFC) */
#define ID_UART0  ( 7) /**< \brief UART 0 (UART0) */
#define ID_UART1  ( 8) /**< \brief UART 1 (UART1) */
#define ID_SMC    ( 9) /**< \brief Static Memory Controller (SMC) */
#define ID_PIOA   (10) /**< \brief Parallel I/O Controller A (PIOA) */
#define ID_PIOB   (11) /**< \brief Parallel I/O Controller B (PIOB) */
#define ID_PIOC   (12) /**< \brief Parallel I/O Controller C (PIOC) */
#define ID_USART0 (13) /**< \brief USART 0 (USART0) */
#define ID_USART1 (14) /**< \brief USART 1 (USART1) */
#define ID_USART2 (15) /**< \brief USART 2 (USART2) */
#define ID_PIOD   (16) /**< \brief Parallel I/O Controller D (PIOD) */
#define ID_PIOE   (17) /**< \brief Parallel I/O Controller E (PIOE) */
#define ID_HSMCI  (18) /**< \brief Multimedia Card Interface (HSMCI) */
#define ID_TWIHS0 (19) /**< \brief Two Wire Interface 0 HS (TWIHS0) */
#define ID_TWIHS1 (20) /**< \brief Two Wire Interface 1 HS (TWIHS1) */
#define ID_SPI0   (21) /**< \brief Serial Peripheral Interface 0 (SPI0) */
#define ID_SSC    (22) /**< \brief Synchronous Serial Controller (SSC) */
#define ID_TC0    (23) /**< \brief Timer/Counter 0 (TC0) */
#define ID_TC1    (24) /**< \brief Timer/Counter 1 (TC1) */
#define ID_TC2    (25) /**< \brief Timer/Counter 2 (TC2) */
#define ID_TC3    (26) /**< \brief Timer/Counter 3 (TC3) */
#define ID_TC4    (27) /**< \brief Timer/Counter 4 (TC4) */
#define ID_TC5    (28) /**< \brief Timer/Counter 5 (TC5) */
#define ID_AFEC0  (29) /**< \brief Analog Front End 0 (AFEC0) */
#define ID_DACC   (30) /**< \brief Digital To Analog Converter (DACC) */
#define ID_PWM0   (31) /**< \brief Pulse Width Modulation 0 (PWM0) */
#define ID_ICM    (32) /**< \brief Integrity Check Monitor (ICM) */
#define ID_ACC    (33) /**< \brief Analog Comparator (ACC) */
#define ID_USBHS  (34) /**< \brief USB Host / Device Controller (USBHS) */
#define ID_MCAN0  (35) /**< \brief MCAN Controller 0 (MCAN0) */
#define ID_MCAN1  (37) /**< \brief MCAN Controller 1 (MCAN1) */
#define ID_GMAC   (39) /**< \brief Ethernet MAC (GMAC) */
#define ID_AFEC1  (40) /**< \brief Analog Front End 1 (AFEC1) */
#define ID_TWIHS2 (41) /**< \brief Two Wire Interface 2 HS (TWIHS2) */
#define ID_SPI1   (42) /**< \brief Serial Peripheral Interface 1 (SPI1) */
#define ID_QSPI   (43) /**< \brief Quad I/O Serial Peripheral Interface (QSPI) */
#define ID_UART2  (44) /**< \brief UART 2 (UART2) */
#define ID_UART3  (45) /**< \brief UART 3 (UART3) */
#define ID_UART4  (46) /**< \brief UART 4 (UART4) */
#define ID_TC6    (47) /**< \brief Timer/Counter 6 (TC6) */
#define ID_TC7    (48) /**< \brief Timer/Counter 7 (TC7) */
#define ID_TC8    (49) /**< \brief Timer/Counter 8 (TC8) */
#define ID_TC9    (50) /**< \brief Timer/Counter 9 (TC9) */
#define ID_TC10   (51) /**< \brief Timer/Counter 10 (TC10) */
#define ID_TC11   (52) /**< \brief Timer/Counter 11 (TC11) */
#define ID_MLB    (53) /**< \brief MediaLB (MLB) */
#define ID_AES    (56) /**< \brief AES (AES) */
#define ID_TRNG   (57) /**< \brief True Random Generator (TRNG) */
#define ID_XDMAC  (58) /**< \brief DMA (XDMAC) */
#define ID_ISI    (59) /**< \brief Camera Interface (ISI) */
#define ID_PWM1   (60) /**< \brief Pulse Width Modulation 1 (PWM1) */
#define ID_SDRAMC (62) /**< \brief SDRAM Controller (SDRAMC) */
#define ID_RSWDT  (63) /**< \brief Reinforced Secure Watchdog Timer (RSWDT) */

#define ID_PERIPH_COUNT (64) /**< \brief Number of peripheral IDs */
/*@}*/




#endif /* _SAMV71Q21_ */
