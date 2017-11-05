/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "app_scheduler.h"
#include "Tasks.h" 
#include "fpu.h"   
#include <stdbool.h>
#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/
 
 /*----------------------------------------------------------------------------
 *        Global variables
 *----------------------------------------------------------------------------*/
 
float       spf_result;
float       spf_result1;
float       spf_result2;
float       spf_int1 = 256;
float       spf_int2 = 10;
uint32_t    u32_result;
uint32_t    u32_int1;
uint32_t    u32_int2;
int32_t     s32_result;
int32_t     s32_int1;
int32_t     s32_int2;


TaskType Tasks[]={
/*  TaskPriority    TaskId   TaskFunctionPointer   */
  {      5,        TASK_1MS,       vfnTsk_1ms    },
  {      4,        TASK_2MSA,      vfnTsk_2msA   },
  {      4,        TASK_2MSB,      vfnTsk_2msB   },
  {      3,        TASK_10MS,      vfnTsk_10ms   },
  {      2,        TASK_50MS,      vfnTsk_50ms   },
  {      1,        TASK_100MS,     vfnTsk_100ms  }
};

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
    /* Enable Floating Point Unit */
    vfnFpu_enable();
	
	printf( "Configure LED PIOs.\n\r" ) ;
	_ConfigureLeds() ;
  
  	/* Initialize Task Scheduler */
	vfnScheduler_Init(&Tasks[0]);
	/* Start execution of task scheduler */
	vfnScheduler_Start();

	/*-- Loop through all the periodic tasks from Task Scheduler --*/
	for(;;)
	{
        __asm ( "nop" );
        /* Float operations */
        spf_result = spf_int1 - spf_int2;
        spf_result1 = spf_int1 + spf_int2;
        spf_result2  =   spf_result  * spf_result1;
        spf_result = spf_int1 * spf_int2;
        spf_result = spf_int1 / spf_int2;
        /* Float to int conversion operations */
        u32_int1 = spf_int1;
		u32_int2 = spf_int2;
		
		s32_int1 = spf_int1;
		s32_int2 = spf_int2;
        /* Int to Float conversion operations */
        spf_result = u32_result;
        spf_result = s32_result;
		/* Integer operations */
		u32_result = u32_int1 - u32_int2;
		u32_result = u32_int1 + u32_int2;
		u32_result = u32_int1 * u32_int2;
		u32_result = u32_int1 / u32_int2;
		s32_result = s32_int1 - s32_int2;
		s32_result = s32_int1 + s32_int2;
		s32_result = s32_int1 * s32_int2;
		s32_result = s32_int1 / s32_int2;
		/* Perform all scheduled tasks */
		vfnTask_Scheduler();
	}

}
