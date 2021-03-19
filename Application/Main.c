/****************************************************************************************************/
/**
  \mainpage
  \n 
  \brief        Main application (main module)
  \author       Diego Mejia 
  \version      1.0
  \date         2020
*/
/****************************************************************************************************/

/*~~~~~~  Headers ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include    "device.h" /*Required for IRQ enum*/
/** Task scheduler definitions */
#include    "SchM.h"
/** LED control definitions */ 
#include    "Led_Ctrl.h"

/*~~~~~~  Local definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~  Private Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~  Local variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~  Global variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~  Local functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 *  \brief getting-started Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */



extern int main( void )
{
  /*Disable Watchdog.*/
  *((unsigned int *)(0x400E1854))|= 1<<15;
  /* Configure LEDs */
	LedCtrl_Configure();
  Init_Interrupt();
  /*Scheduler Init*/
  SchM_Init();
  /* An embedded system shall not exit main function, otherwise bad things can happen. */
  while(1)
  {
    /*Infinite Loop*/
  }                    

}
