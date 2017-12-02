/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "app_scheduler.h"
#include "Tasks.h"    
#include <stdbool.h>
#include <stdio.h>
#include "Mem_Alloc.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#define MEM_ALLOC_SIZE 100

TaskType Tasks[]={
/*  TaskPriority    TaskId   TaskFunctionPointer   */
  {      5,        TASK_1MS,       vfnTsk_1ms    },
  {      4,        TASK_2MSA,      vfnTsk_2msA   },
  {      4,        TASK_2MSB,      vfnTsk_2msB   },
  {      3,        TASK_10MS,      vfnTsk_10ms   },
  {      2,        TASK_50MS,      vfnTsk_50ms   },
  {      1,        TASK_100MS,     vfnTsk_100ms  }
};


Mem_ReturnType_t ptr_Mem_Return = NULL;
/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Configure LEDs
 *
 *  Configures LEDs \#1 and \#2 (cleared by default).
 */
static void _ConfigureLeds( void )
{
	LED_Configure( 0 ) ;
	LED_Configure( 1 ) ;
}

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

	/* Disable watchdog */
	WDT_Disable( WDT ) ;

	/* Output example information */
	printf( "\n\r-- Getting Started Example Workspace Updated!!! %s --\n\r", SOFTPACK_VERSION ) ;
	printf( "-- %s\n\r", BOARD_NAME ) ;
	printf( "-- Compiled: %s %s With %s--\n\r", __DATE__, __TIME__ , COMPILER_NAME);

	/* Enable I and D cache */
	SCB_EnableICache();
  SCB_EnableDCache();

	printf( "Configure LED PIOs.\n\r" ) ;
	_ConfigureLeds() ;
  
  /* Initialize Task Scheduler */
	vfnScheduler_Init(&Tasks[0]);
  
  /*Mem Alloc Initialization*/
  Mem_init();
  
	/* Start execution of task scheduler */
	vfnScheduler_Start();
  
	/*-- Loop through all the periodic tasks from Task Scheduler --*/
	for(;;)
	{
    
    ptr_Mem_Return = Mem_Alloc((Mem_SizeType_t)MEM_ALLOC_SIZE);
		/* Perform all scheduled tasks */
		vfnTask_Scheduler();
    
    
	}

}
