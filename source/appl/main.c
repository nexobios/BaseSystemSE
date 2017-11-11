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

#define C_Code 1

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
	//SCB_EnableICache();
    //SCB_EnableDCache();
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
    
    
  #ifdef  C_Code
        spf_result = spf_int1 - spf_int2;
        spf_result1 = spf_int1 + spf_int2;
        spf_result2  =   spf_result  * spf_result1;
        spf_result = spf_int1 * spf_int2;
        spf_result = spf_int1 / spf_int2;
        u32_int1 = spf_int1;
		    u32_int2 = spf_int2;
		    spf_result = u32_result;
        spf_result = s32_result;
        u32_result = u32_int1 - u32_int2;
		    u32_result = u32_int1 + u32_int2;
        u32_result = u32_int1 * u32_int2;
        u32_result = u32_int1 / u32_int2;
        s32_result = s32_int1 - s32_int2;
        s32_result = s32_int1 + s32_int2;
        s32_result = s32_int1 * s32_int2;
        s32_result = s32_int1 / s32_int2;
  #else
        //spf_result = spf_int1 - spf_int2;
        __asm__( "ldr       r3, =spf_int1" ); 
        __asm__( "vldr.32   s14,[r3]      ");    
        __asm__( "ldr       r3, =spf_int2" ); 
        __asm__( "vldr.32   s15,[r3]      ");    
        __asm__( "ldr       r3, =spf_result" ); 
        __asm__( "vsub.F32  s15,s14,s15   " );    
        __asm__( "vstr.32   s15,[r3]      " );    
        
        //spf_result1 = spf_int1 + spf_int2;
        __asm__( "ldr       r3, =spf_int1" ); 
        __asm__( "vldr.32   s14,[r3]      ");    
        __asm__( "ldr       r3, =spf_int2" ); 
        __asm__( "vldr.32   s15,[r3]      ");    
        __asm__( "ldr       r3, =spf_result1 " ); 
        __asm__( "vadd.F32  s15,s14,s15   " );    
        __asm__( "vstr.32   s15,[r3]      " );    
        
        //spf_result2  =   spf_result  * spf_result1;
        __asm__( "ldr       r3, =spf_result  " ); 
        __asm__( "vldr.32   s14,[r3]      ");    
        __asm__( "ldr       r3, =spf_result1" ); 
        __asm__( "vldr.32   s15,[r3]      ");    
        __asm__( "ldr       r3, =spf_result2" ); 
        __asm__( "vmul.F32  s15,s14,s15   " );    
        __asm__( "vstr.32   s15,[r3]      " );    
        
        //spf_result = spf_int1 * spf_int2;
        __asm__( "ldr       r3, =spf_int1" ); 
        __asm__( "vldr.32   s14,[r3]      ");    
        __asm__( "ldr       r3, =spf_int2" ); 
        __asm__( "vldr.32   s15,[r3]      ");    
        __asm__( "ldr       r3, =spf_result" ); 
        __asm__( "vmul.F32  s15,s14,s15   " );    
        __asm__( "vstr.32   s15,[r3]      " );    
        
        //spf_result = spf_int1 / spf_int2;
        __asm__( "ldr       r3, =spf_int1" ); 
        __asm__( "vldr.32   s14,[r3]      ");    
        __asm__( "ldr       r3, =spf_int2" ); 
        __asm__( "vldr.32   s15,[r3]      ");    
        __asm__( "ldr       r3, =spf_result" ); 
        __asm__( "vdiv.F32  s15,s14,s15   " );    
        __asm__( "vstr.32   s15,[r3]      " );    
                      
        /* Float to int conversion operations */
        //u32_int1 = spf_int1;
		    __asm__( "ldr             r3, =spf_int1" ); 
        __asm__( "vldr.32         s15,[r3]      ");    
        __asm__( "vcvt.U32.F32  s15, s15" );
        __asm__( "vmov            r2,s15      ");    
        __asm__( "ldr             r3, =u32_int1 " ); 
        __asm__( "str             r2, [r3]" );    
        
        
        //u32_int2 = spf_int2;
		    __asm__( "ldr             r3, =spf_int2" ); 
        __asm__( "vldr.32         s15,[r3]      ");    
        __asm__( "vcvt.U32.F32  s15, s15" );
        __asm__( "vmov            r2,s15      ");    
        __asm__( "ldr             r3, =u32_int2 " ); 
        __asm__( "str             r2, [r3]" ); 
        
        /* Int to Float conversion operations */
        //spf_result = u32_result;
        __asm__( "ldr             r3, =u32_result" ); 
        __asm__( "vldr.32         s15,[r3]      ");    
        __asm__( "vcvt.F32.U32    s15, s15" );
        __asm__( "vmov            r2,s15      ");    
        __asm__( "ldr             r3, =spf_result " ); 
        __asm__( "str             r2, [r3]" );    
        
        //spf_result = s32_result;
        __asm__( "ldr             r3, =s32_result" ); 
        __asm__( "vldr.32         s15,[r3]      ");    
        __asm__( "vcvt.F32.S32    s15, s15" );
        __asm__( "vmov            r2,s15      ");    
        __asm__( "ldr             r3, =spf_result " ); 
        __asm__( "str             r2, [r3]" );    
        
		/* Integer operations */
		//u32_result = u32_int1 - u32_int2;
		    __asm__( "ldr             r3, =u32_int1" ); 
        __asm__( "ldr             r2, [r3]" ); 
        __asm__( "ldr             r3, =u32_int2" ); 
        __asm__( "ldr             r3, [r3]" ); 
        __asm__( "sub             r3, r2,r3" ); 
        __asm__( "ldr             r2, =u32_result" ); 
        __asm__( "str             r3, [r2]" );    
        
    //u32_result = u32_int1 + u32_int2;
        __asm__( "ldr             r3, =u32_int1" ); 
        __asm__( "ldr             r2, [r3]" ); 
        __asm__( "ldr             r3, =u32_int2" ); 
        __asm__( "ldr             r3, [r3]" ); 
        __asm__( "add             r3, r2,r3" ); 
        __asm__( "ldr             r2, =u32_result" ); 
        __asm__( "str             r3, [r2]" );    
		//u32_result = u32_int1 * u32_int2;
        __asm__( "ldr             r3, =u32_int1" ); 
        __asm__( "ldr             r2, [r3]" ); 
        __asm__( "ldr             r3, =u32_int2" ); 
        __asm__( "ldr             r3, [r3]" ); 
        __asm__( "mul             r3, r2,r3" ); 
        __asm__( "ldr             r2, =u32_result" ); 
        __asm__( "str             r3, [r2]" );    
		//u32_result = u32_int1 / u32_int2;
        __asm__( "ldr             r3, =u32_int1" ); 
        __asm__( "ldr             r2, [r3]" ); 
        __asm__( "ldr             r3, =u32_int2" ); 
        __asm__( "ldr             r3, [r3]" ); 
        __asm__( "udiv             r3, r2,r3" ); 
        __asm__( "ldr             r2, =u32_result" ); 
        __asm__( "str             r3, [r2]" );    
		//s32_result = s32_int1 - s32_int2;
        __asm__( "ldr             r3, =u32_int1" ); 
        __asm__( "ldr             r2, [r3]" ); 
        __asm__( "ldr             r3, =u32_int2" ); 
        __asm__( "ldr             r3, [r3]" ); 
        __asm__( "sub             r3, r2,r3" ); 
        __asm__( "ldr             r2, =u32_result" ); 
        __asm__( "str             r3, [r2]" );    
		//s32_result = s32_int1 + s32_int2;
        __asm__( "ldr             r3, =u32_int1" ); 
        __asm__( "ldr             r2, [r3]" ); 
        __asm__( "ldr             r3, =u32_int2" ); 
        __asm__( "ldr             r3, [r3]" ); 
        __asm__( "add             r3, r2,r3" ); 
        __asm__( "ldr             r2, =u32_result" ); 
        __asm__( "str             r3, [r2]" );    
		//s32_result = s32_int1 * s32_int2;
        __asm__( "ldr             r3, =u32_int1" ); 
        __asm__( "ldr             r2, [r3]" ); 
        __asm__( "ldr             r3, =u32_int2" ); 
        __asm__( "ldr             r3, [r3]" ); 
        __asm__( "mul             r3, r2,r3" ); 
        __asm__( "ldr             r2, =u32_result" ); 
        __asm__( "str             r3, [r2]" );    
		//s32_result = s32_int1 / s32_int2;
        __asm__( "ldr             r3, =u32_int1" ); 
        __asm__( "ldr             r2, [r3]" ); 
        __asm__( "ldr             r3, =u32_int2" ); 
        __asm__( "ldr             r3, [r3]" ); 
        __asm__( "sdiv             r3, r2,r3" ); 
        __asm__( "ldr             r2, =u32_result" ); 
        __asm__( "str             r3, [r2]" );    
        
    #endif
		/* Perform all scheduled tasks */
		vfnTask_Scheduler();
	}

}
