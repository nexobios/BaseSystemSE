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
//#include    "led_ctrl.h"
#include    "led.h"
/** UART communication */
//#include    "serial_ctrl.h"
/** Watchdog control function prototypes definitions */
//#include    "wdt_ctrl.h"
/** Dynamic Memory allocation services */
//#include    "memory_allocation.h"
/** Input Image */
#include    "lena_image.h"
/** Image Processing services */
//#include    "image_processing.h"

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
float AvgMask2x2[2][2] =
{
    0.25, 0.25,   
    0.25, 0.25
};

 uint32_t *ptrScaled;
 float *ptrOriginal;
  //#define DebugCom
  #define SameValue
  #define ASM_Code
/* Intermediate scaled up image - temporary pixel calculation */     
uint32_t Filtered2x2scaled __attribute__((section(".four_byte_aligment")));
uint32_t var_a __attribute__((section(".four_byte_aligment")));
uint32_t var_b __attribute__((section(".four_byte_aligment")));
uint32_t var_c __attribute__((section(".four_byte_aligment")));
uint32_t var_d __attribute__((section(".four_byte_aligment")));
uint32_t f00 __attribute__((section(".four_byte_aligment")));
uint32_t *pImage __attribute__((section(".four_byte_aligment")));
uint32_t *pImageColAdd __attribute__((section(".four_byte_aligment")));
              
/* Intermediate Mask in integer numbers to accelerate execution */
uint32_t AvgMask2x2scaled[2][2] __attribute__((section(".four_byte_aligment")));
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
	//vfnWdtCtrl_Disable();
  
  /* Disable watchdog */
	WDT_Disable( WDT ) ;
  
	/* Enable I and D cache */
	SCB_EnableICache();
	SCB_EnableDCache(); 
  /* Enable Floating Point Unit */
  vfnFpu_enable();
	/* Dynamic Memory Allocation initialization */
	//vfnMemAlloc_Init(&DynamicMemAlloc_config[0]);
	/* Configure LEDs */
	//vfnLedCtrl_Configure();
  LED_Configure(1);
	/* Initialize UART communicaiton */
	//vfnSerialCtrl_Init();
	/* Configure Non-preemtive scheduler */
	vfnScheduler_Init(&Tasks[0]);
	/* Start scheduler */
	vfnScheduler_Start();  
  
  /*@Yisus Implemented Code*/
  uint32_t *ptrScaled;
  float *ptrOriginal;
  ptrOriginal=&AvgMask2x2[0][0];  
  ptrScaled=&AvgMask2x2scaled[0][0];
  const uint32_t vvmul=0x00010000; 
  volatile uint32_t var_b,var_c,var_d;
  uint32_t f11,f01,f10;
  /*@Yisus Implemented Code*/
    /** Indication for measurement */
  
  while(1)       
  {
  LED_Toggle(1);
    
    /* Convert to integer and scale up correlation mask in order to avoid loosing resolution */
     #ifdef DebugCom
      for (i_index = 0; i_index < 2; i_index++)
      {
          for (j_index = 0; j_index < 2; j_index++)
          {     AvgMask2x2scaled[i_index][j_index] = (uint32_t)(AvgMask2x2[i_index][j_index] * 0x00010000);
          }
      } 
      #else
         
        #ifdef  SameValue
          f00=*ptrOriginal * vvmul;
        #else
          f00=*ptrOriginal * vvmul;
          ptrScaled++;
          ptrOriginal++;
          f01=*ptrOriginal * vvmul;
          ptrScaled++;
          ptrOriginal++;
          f10=*ptrOriginal * vvmul;
          ptrScaled++;
          ptrOriginal++;
          f11=*ptrOriginal * vvmul;  
        #endif
      #endif        
       
        
         #ifdef DebugCom
            /* Perform correlation operation */
            for (i_index = 0; i_index < IMAGE_ROWS-1; i_index++)
            {
                for (j_index = 0; j_index < IMAGE_COLS; j_index++)
                {     /* For items on the first column */
                    if(j_index==0)
                       {
                          Filtered2x2scaled = 
                              (uint32_t)(Lena_Image[i_index][j_index] * AvgMask2x2scaled[0][0]) +
                              (uint32_t)(Lena_Image[i_index+1][j_index] * AvgMask2x2scaled[1][1]);       
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
         #else 
            #ifdef  SameValue
              asm volatile(    "ldr R7,=f00"   ); 
            #endif
            for (i_index = 0; i_index < IMAGE_ROWS-1; i_index++)
            {
                #ifdef  SameValue
                      Filtered2x2scaled =   (((uint32_t)Lena_Image[i_index][0])+((uint32_t)Lena_Image[i_index+1][0]))*f00;
                      /* Scale down result */
                      Lena_Image_Filtered[i_index][j_index] = (uint8_t)( Filtered2x2scaled >> 4);
                       
                      for (j_index = 1; j_index < IMAGE_COLS; j_index++)
                      {     /* For items on the first column */
                        
                          #ifdef  ASM_Code
                              pImage =(uint32_t*)&Lena_Image[i_index][j_index-1];
                              
                              //   Lena_Image[i_index][j_index]
                              asm volatile(    "ldr R3,=pImage"   );  //0   (Lena_Image[i_index][j_index])
                              //   Lena_Image[i_index][j_index+1]
                              asm volatile(    "ldr R4,[R3,#4]"   );   // 4   (Lena_Image[i_index][j_index-1] ))
                                  
                              asm volatile(    "add R4,R4,R3"   );    
                              
                              //   Lena_Image[i_index+1][j_index]
                              asm volatile(    "ldr R5,[R3,#00000130]"   );   //304     (Lena_Image[i_index+1][j_index-1] )
                              //   Lena_Image[i_index+1][j_index+1]
                              asm volatile(    "ldr R6,[R5,#4]"   );     //308    (Lena_Image[i_index+1][j_index])
                              
                              asm volatile(    "add R6,R5,R6"   ); 
                              
                              asm volatile(    "add R4,R6,R4"   );
                              
                              asm volatile(    "ldr R3,=Filtered2x2scaled"   );
                                        
                              asm volatile(    "mul r3,r3,r7"   );
                               
                          #else
                              Filtered2x2scaled = (
                                (uint32_t)(Lena_Image[i_index][j_index]) +  //0
                                (uint32_t)(Lena_Image[i_index+1][j_index]) +   //308
                                (uint32_t)(Lena_Image[i_index+1][j_index-1] ) +     //304
                                (uint32_t)(Lena_Image[i_index][j_index-1] ));//*f00;   //4
                          #endif
                           
                       Lena_Image_Filtered[i_index][j_index] = (uint8_t)( Filtered2x2scaled >> 4);
                      }
                #else
                    Filtered2x2scaled = 
                              (uint32_t)(Lena_Image[i_index][0] * f00) +
                              (uint32_t)(Lena_Image[i_index+1][0] * f11);       
                    
                    for (j_index = 0; j_index < IMAGE_COLS; j_index++)
                    {     /* For items on the first column */
                      
                          Filtered2x2scaled = 
                              (uint32_t)(Lena_Image[i_index][j_index] * f00) +
                              (uint32_t)(Lena_Image[i_index+1][j_index] * f10) +
                              (uint32_t)(Lena_Image[i_index+1][j_index-1] * f11) + 
                              (uint32_t)(Lena_Image[i_index][j_index-1] * f01); 
                     
                    }  
                #endif
                 
            }
             
           #endif 
                      
    
    /** End of indication for measurement */
    //LED_Clear(1);
}
    
	/* Once all the basic services have been started, go to infinite loop to serviced activated tasks */
    for(;;)
    {			    
        /** Perform periodically activated tasks */
		vfnTask_Scheduler();
    
    printf( "Matrix: %u ",Lena_Image_Filtered);
	}
}
