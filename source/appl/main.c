/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include    "board.h"
#include "app_scheduler.h"
#include "Tasks.h"    
#include "fpu.h"    
#include <stdbool.h>
#include <stdio.h>
/** Task scheduler definitions */
#include    "app_scheduler.h"
/** LED control definitions */ 
#include    "led.h"
/** Input Image */
#include    "lena_image.h"

/*----------------------------------------------------------------------------
 *        Defines
 *----------------------------------------------------------------------------*/

  #define OPTIMIZE

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

TaskType Tasks[]={
/*  TaskPriority    TaskId   TaskFunctionPointer   */
  {      5,        TASK_1MS,       vfnTsk_1ms    },
  {      4,        TASK_2MSA,      vfnTsk_2msA   },
  {      4,        TASK_2MSB,      vfnTsk_2msB   },
  {      3,        TASK_10MS,      vfnTsk_10ms   },
  {      2,        TASK_50MS,      vfnTsk_50ms   },
  {      1,        TASK_100MS,     vfnTsk_100ms  }
};

/*~~~~~~  Global variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* Auxiliary variables */
uint16_t i_index;
uint16_t j_index;
uint32_t tmp;

/* Averaging mask */
#ifdef OPTIMIZE
    float AvgMaskVal = 0.25;
#else
    float AvgMask2x2[2][2] =
    {
        0.25, 0.25,   
        0.25, 0.25
    };
#endif /* #ifdef OPTIMIZE */

#ifdef OPTIMIZE
    uint32_t AvgMaskScaled __attribute__((section(".four_byte_aligment")));
    uint32_t *pImage __attribute__((section(".four_byte_aligment")));
#else
    /* Intermediate Mask in integer numbers to accelerate execution */
    uint32_t AvgMask2x2scaled[2][2] __attribute__((section(".four_byte_aligment")));
#endif /* #ifdef OPTIMIZE */

/* Valid for both variants */
/* Intermediate scaled up image - temporary pixel calculation */     
uint32_t Filtered2x2scaled __attribute__((section(".four_byte_aligment")));
/*Output filtered image */     
uint8_t Lena_Image_Filtered[IMAGE_ROWS][IMAGE_COLS] __attribute__((section(".four_byte_aligment")));


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
  
	/* Enable I and D cache */
	SCB_EnableICache();
	SCB_EnableDCache(); 
    /* Enable Floating Point Unit */
    vfnFpu_enable();
	/* Configure LEDs */
    LED_Configure(1);
	/* Configure Non-preemtive scheduler */
	vfnScheduler_Init(&Tasks[0]);
	/* Start scheduler */
	vfnScheduler_Start();  
  
    #ifdef  OPTIMIZE
        /* Variable Inits */
        const uint32_t vvmul=0x00010000; 
    #endif /* #ifdef  OPTIMIZE */

  while(1)       
  {
    /* LED Toggle */
    LED_Toggle(1);
    /* Convert to integer and scale up correlation mask in order to avoid loosing resolution */

    #ifdef  OPTIMIZE
        /* No longer required, shift right used instead */
        /* AvgMaskScaled = AvgMaskVal * vvmul; */
    #else
        for (i_index = 0; i_index < 2; i_index++)
        {
            for (j_index = 0; j_index < 2; j_index++)
            {     /* Mask to be scaled up by a factor of 2^16*/
                AvgMask2x2scaled[i_index][j_index] = (uint32_t)(AvgMask2x2[i_index][j_index] * 0x00010000);
            }
        }
    #endif /* #ifdef OPTIMIZE */

    #ifdef  OPTIMIZE 
        for (i_index = 0; i_index < IMAGE_ROWS-1; i_index++)
        {       
                /* Process elements in the first column j_index = 0 */
                pImage = (uint32_t *) &Lena_Image[i_index][0];
                asm volatile("ldr   R3, =Filtered2x2scaled" );  // Load addr of Filtered2x2scaled
                asm volatile("ldr   R4, =pImage"            );  // Load Lena_Image[i_index][0]
                asm volatile("ldr   R5, [R4, #00000130]"    );  // Load Lena_Image[i_index + 1][0]
                asm volatile("add   R3, R4, R5"             );  // Filtered2x2scaled (R3) = Lena_Image[i_index][0] + Lena_Image[i_index + 1][0]
                /* Scale down result */
                asm volatile("lsr   R3, R3, #2"             );  // Filtered2x2scaled = Filtered2x2scaled >> 2;
                Lena_Image_Filtered[i_index][j_index] = (uint8_t) Filtered2x2scaled;

                for (j_index = 1; j_index < IMAGE_COLS; j_index++)
                {
                    pImage = (uint32_t *) &Lena_Image[i_index][j_index-1];

                    asm volatile("ldr   R3, =Filtered2x2scaled" );  // Load addr of Filtered2x2scaled
                    asm volatile("ldr   R4, =pImage"            );  // Load Lena_Image[i_index][j_index - 1], the -1 offset is required by now.
                    asm volatile("ldr   R5, [R4,#4]"            );  // Load Lena_Image[i_index][j_index]
                    asm volatile("add   R5, R4, R5"             );  // R5 = Lena_Image[i_index][j_index - 1] + Lena_Image[i_index][j_index]
                    asm volatile("ldr   R6, [R4, #00000130]"    );  // Load Lena_Image[i_index + 1][j_index - 1]
                    asm volatile("ldr   R7, [R6, #4]"           );  // Load Lena_Image[i_index + 1][j_index]
                    asm volatile("add   R6, R7, R6"             );  // R6 = Lena_Image[i_index + 1][j_index - 1] + Lena_Image[i_index + 1][j_index]
                    asm volatile("add   R3, R5, R6"             );  // Filtered2x2scaled (R3) = R5 + R6
                    /* Scale down result */
                    asm volatile("lsr   R3, R3, #2"             );  // Filtered2x2scaled = Filtered2x2scaled >> 2;
                    Lena_Image_Filtered[i_index][j_index] = (uint8_t) Filtered2x2scaled;
                }
                /* Set j_index = 0 */
                j_index = 0;
        }
    #else
        for (i_index = 0; i_index < IMAGE_ROWS-1; i_index++)
        {
            for (j_index = 0; j_index < IMAGE_COLS; j_index++)
            {     /* For items on the first column */
                if(j_index == 0)
                {
                    Filtered2x2scaled = 
                        (uint32_t)(Lena_Image[i_index][j_index] * AvgMask2x2scaled[0][0]) +
                        (uint32_t)(Lena_Image[i_index+1][j_index] * AvgMask2x2scaled[1][0]);       
                }
                else
                {
                    Filtered2x2scaled = 
                        (uint32_t)(Lena_Image[i_index][j_index] * AvgMask2x2scaled[0][0]) +
                        (uint32_t)(Lena_Image[i_index+1][j_index] * AvgMask2x2scaled[1][0]) +
                        (uint32_t)(Lena_Image[i_index+1][j_index-1] * AvgMask2x2scaled[1][1]) + 
                        (uint32_t)(Lena_Image[i_index][j_index-1] * AvgMask2x2scaled[0][1]);
                }
                /* Scale down result */
                Lena_Image_Filtered[i_index][j_index] = (uint8_t)( Filtered2x2scaled >> 16);
            }
        }
    #endif

}
    
	/* Once all the basic services have been started, go to infinite loop to serviced activated tasks */
    for(;;)
    {			    
        /** Perform periodically activated tasks */
		vfnTask_Scheduler();
    
    printf( "Matrix: %u ",Lena_Image_Filtered);
	}
}
