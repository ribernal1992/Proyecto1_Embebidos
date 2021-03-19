/****************************************************************************************************/
/**
\file       Led_Ctrl.c
\brief      MCU abstraction level - LED control
\author     Abraham Tezmol
\version    1.0
\project    Tau 
\date       24/June/2016
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/** Own headers */
#include "Led_Ctrl.h"
#include "device.h" /*Required for IRQ enum*/
#include "core_cm7.h" /*CMSIS functions*/
#include "pmc.h"
#include "pio.h"
#include "tc.h"
#include "pio_definitions.h"
/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

/****************************************************************************************************
* Declaration of module wide FUNCTIONs 
****************************************************************************************************/
static void LED_TurnOn(uint8_t index);
static void LED_TurnOff(uint8_t index);
/****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

static void LED_TurnOn(uint8_t index)
{

    if(index == 0)
    {
        /*Clear Output for LEDs, set initial value*/
        PIOA->PIO_CODR |= PIO_CODR_P23;
        
    }
    else
    {
        /*Clear Output for LEDs, set initial value*/
        PIOC->PIO_CODR |= PIO_CODR_P9;
    }
}
static void LED_TurnOff(uint8_t index)
{
    if(index == 0)
    {
        PIOA->PIO_SODR |= PIO_CODR_P23;
    }
    else
    {
        PIOC->PIO_SODR |= PIO_CODR_P9;
    }
}
/*****************************************************************************************************/
/**
* \brief    Configures LED 0 and 1 of SAMV71 board
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void LedCtrl_Configure( void )
{
   //Enable PIO peripherals for led and buzzer
  PMC_EnablePeripheral(ID_PIOA);
  PMC_EnablePeripheral(ID_PIOC);

  /* Led outputs to be handled by PIO (Hence PIO Enabled)*/
  PIOA->PIO_PER = PIO_PER_P23;  /*pin 23 (LED0) enable*/
  PIOC->PIO_PER = PIO_PER_P9;  /*pin 9 (LED1) enable*/
  /* Output Enable for LEDS*/
  PIOA->PIO_OER = PIO_OER_P23;
  PIOC->PIO_OER = PIO_OER_P9;
  /*Clear Output for LEDs, set initial value*/
  PIOA->PIO_CODR |= PIO_CODR_P23;
  PIOC->PIO_CODR |= PIO_CODR_P9;
  
}

/*****************************************************************************************************/
/**
* \brief    Turn a combination of 2 LEDs with a unique blinking pattern.
			Call this function periodically @ 10ms to operate
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void LedCtrl_BlinkingPattern(void)
{
/* Global state machine status for LED flashing control  */
	static uint8_t LocPatternIndex;

    LocPatternIndex++;
    
    switch ((LocPatternIndex))
    {
        case  1:
            LED_TurnOn(0);
            LED_TurnOn(1);
            break;
        case  11:
            LED_TurnOn(0);
            LED_TurnOn(1);
            break;
        case  3:
            LED_TurnOff(0);
            LED_TurnOff(1);
            break;
        case  13:
            LED_TurnOff(0);
            LED_TurnOff(1);
            break;
        case 101:
            LocPatternIndex = 0;
            break;
        default:
            break;
    }
}

/**************/
void Init_Interrupt(void){ /* Interrupt initialitation*/
PIOA->PIO_PER = PIO_PA9;
PIOA->PIO_IER = PIO_IER_P9; /*Interrupt enable register*/
//PIOA->PIO_IMR = PIO_IMR_P9; /*Interrupt Mask register*/

//PIOA->PIO_AIMER = PIO_AIMER_P9;/*Enable additional interrupt Modes*/

//PIOA->PIO_AIMMR = PIO_AIMMR_P9; /*read through the additional interupt modes mask register*/
PIOA->PIO_ESR = PIO_ESR_P9; /*Edge select register*/
PIOA->PIO_REHLSR = PIO_FELLSR_P9; /*Falling Edge/high-Level select register*/
PIOA->PIO_FELLSR = PIO_FELLSR_P9; /*The debouncing filter is able to filter pulses with a duration <tdivslck/2*/
PIOA->PIO_IFER = PIO_IFER_P9; /*Enables the input glitch filter on the I/O line*/
NVIC_ClearPendingIRQ(PIOA_IRQn);
__enable_irq();
NVIC_EnableIRQ(PIOA_IRQn);  
Init_Timer();


}

void Init_Timer(void)
{
  PMC->PMC_MCKR = PMC_MCKR_CSS_MAIN_CLK;
  PMC->PMC_MCKR = PMC_MCKR_PRES_CLK_4;
  PMC->PMC_MCKR = PMC_MCKR_MDIV_PCK_DIV3;
  PMC->PMC_PCER1 = PMC_PCER1_PID52;
  
  TC3->TC_CHANNEL[2].TC_CCR = TC_CCR_CLKEN;
  TC3->TC_CHANNEL[2].TC_CCR = TC_CCR_SWTRG;
  
  TC3->TC_CHANNEL[2].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK2;
  
  //TC_Start(TC3,2);
  
}


/*******************************************************************************/