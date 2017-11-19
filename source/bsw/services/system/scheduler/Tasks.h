/*******************************************************************************/
/**
\file       Tasks.h
\author     Francisco Matinez
\version    0.2
\date       06/21/2016
*/

#ifndef __APP_TASKS
#define __APP_TASKS

/*-- Includes ----------------------------------------------------------------*/
#include "afe_dma.h"
#include "afec.h"

/*@Yisus Adc struct*/               
AfeDma pAfed;     
sXdmad pXdmad;
AfeCmd pAfeCmd;

/*-- Variables -------------------------------------------------------*/

/*-- Defines -----------------------------------------------------------------*/

/*-- Macros ------------------------------------------------------------------*/


extern void vfnTsk_1ms(void);
extern void vfnTsk_2msA(void);
extern void vfnTsk_2msB(void);
extern void vfnTsk_10ms(void);
extern void vfnTsk_50ms(void);
extern void vfnTsk_100ms(void);
void AFEC0_Init(void);  
void PWM0_Init(void);

/*============================================================================*/
#endif /*__APP_TASKS */
