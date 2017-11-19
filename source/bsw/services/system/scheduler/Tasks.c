/*
 * Tasks.c
 *
 * Created: 6/21/2016 7:25:43 PM
 *  Author: Francisco Martinez
 */ 

#include "Tasks.h"
#include "led.h"
#include "board.h"

uint8_t u8100ms_Ctr=0;
uint8_t u8100ms_Ctr2=0;

void AFEC0_Init()
{
/*
  Configurate the pins for AFEC.
  Initialize the AFEC with AFEC_Initialize().
  Set AFEC clock and timing with AFEC_SetClock() and AFEC_SetTiming().
  Select the active channel using AFEC_EnableChannel().
  Start the conversion with AFEC_StartConversion().
  Wait the end of the conversion by polling status with AFEC_GetStatus().
  Finally, get the converted data using AFEC_GetConvertedData() or AFEC_GetLastConvertedData().
  */
  /* First config*/
  
  PIO_Configure(&pinsAFECs[0], 1);
  AFEC_Initialize( AFEC0, ID_AFEC0);           

  AFEC_SetClock(AFEC0, T_SAMP ,BOARD_MCK);
  AFEC_SetTiming(AFEC0, AFEC_MR_STARTUP_SUT16 , AFEC_MR_SETTLING_AST3);
  AFEC_SetTrigger( AFEC0, AFEC_MR_TRGEN_DIS); 
  
  AFEC_SetTriggerEnable(AFEC0,0);
  //AFEC_SetTriggerEnable(AFEC0,1);  with PWM
  
  AFEC_SetResolution(AFEC0,AFEC_EMR_RES_OSR4);

  AFEC_SetSignMode(AFEC0,AFEC_EMR_SIGNMODE_ALL_UNSIGNED);

  AFEC_SetAnalogControl(AFEC0,AFEC_ACR_PGA0_ON);
  
  AFEC_EnableChannel(AFEC0,AFEC_CHER_CH0);
}

void PWM0_Init()
{
  PMC_EnablePeripheral(ID_PWM0);
  PWMC_ConfigureClocks(PWM0, 14200, 0,  BOARD_MCK);
  //PWMC_ConfigureChannel(PWM0, CHANNEL_PWM_LCD, PWM_CMR_CPRE_CLKA,0, PWM_CMR_CPOL);
  PWMC_DisableChannel(PWM0, PWM_ENA_CHID0);
  
  PWMC_ConfigureChannel( PWM0,	PWM_ENA_CHID0, PWM_CMR_CPRE_CLKA, 0, PWM_CMR_CPOL);
  
  PWMC_SetPeriod( PWM0, PWM_ENA_CHID0, 16);  
  PWMC_SetDutyCycle( PWM0, PWM_ENA_CHID0, 8);
  PWMC_EnableChannel( PWM0, PWM_ENA_CHID0  );
  PWMC_ConfigureEventLineMode( PWM0, 0, PWM_CMPVUPD_CVUPD(100));

  
  PWMC_EnableChannelIt( PWM0, 1);
  PWMC_EnableIt(PWM0, PWM_IER1_CHID0 ,PWM_IER2_CMPM0);  
}


void vfnTsk_1ms(void)
{
  
}

void vfnTsk_2msA(void)
{
	
}

void vfnTsk_2msB(void)
{
	
}

void vfnTsk_10ms(void)
{
	static uint8_t u8500ms_Ctr=0;
  //AFEC_StartConversion(AFEC0);
  
  uint16_t value= AFEC_GetConvertedData( AFEC0,AFEC_CHER_CH0);
  
  //printf("\nValue &d",&pAfe_ADC0.AFEC_LCDR);
	u8500ms_Ctr++;
	
	if (25 <= u8500ms_Ctr)
	{
		u8500ms_Ctr = 0;
		LED_Toggle( 1 );
	}   
	TASK_AFEC_DMA();
}

void vfnTsk_50ms(void)
{
}

void vfnTsk_100ms(void)
{
  			
	u8100ms_Ctr++;
    u8100ms_Ctr2++;

	if (5 <= u8100ms_Ctr)
	{
		u8100ms_Ctr = 0;
		LED_Toggle( 0 );
	}
    if (10 <= u8100ms_Ctr2)
	{
		u8100ms_Ctr2 = 0;
	}
}

