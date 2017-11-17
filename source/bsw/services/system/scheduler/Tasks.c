/*
 * Tasks.c
 *
 * Created: 6/21/2016 7:25:43 PM
 *  Author: Francisco Martinez
 */ 

#include "Tasks.h"
#include "led.h"       

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

  AFEC_SetClock(AFEC0, 500 ,BOARD_MCK);
  AFEC_SetTiming(AFEC0, AFEC_MR_STARTUP_SUT640 , AFEC_MR_TRACKTIM(0),		0);
  AFEC_SetTrigger( AFEC0,/* AFEC_MR_TRGSEL_AFEC_TRIG0 |*/ AFEC_MR_TRGSEL_AFEC_TRIG4); //Comentada si jala
  AFEC_SetNumberOfBits( AFEC0, AFEC_EMR_RES_OSR256);
  AFEC_EnableChannel(AFEC0,AFEC_CHER_CH0);
  AFEC_StartConversion(AFEC0);

//Revisar cual de estos puede jalar por aparte y crearle funciones
//  pAfe_ADC0.AFEC_CR = AFEC_CR_SWRST;       /**< \brief (Afec Offset: 0x00) AFEC Control Register */
//  pAfe_ADC0.AFEC_MR = AFEC_MR_TRGEN_EN | AFEC_MR_TRGSEL_AFEC_TRIG4;       /**< \brief (Afec Offset: 0x04) AFEC Mode Register */
//  pAfe_ADC0.AFEC_EMR = AFEC_MR_SLEEP_NORMAL;      /**< \brief (Afec Offset: 0x08) AFEC Extended Mode Register */
//  pAfe_ADC0.AFEC_CHER = AFEC_CHER_CH0;     /**< \brief (Afec Offset: 0x14) AFEC Channel Enable Register */
//  pAfe_ADC0.AFEC_IER = AFEC_IER_EOC0 | AFEC_IER_DRDY;      /**< \brief (Afec Offset: 0x24) AFEC Interrupt Enable Register */
//  pAfe_ADC0.AFEC_CGR = AFEC_CVR_GAINCORR(1);      /**< \brief (Afec Offset: 0x54) AFEC Channel Gain Register */
//  pAfe_ADC0.AFEC_ACR = AFEC_ACR_PGA0EN;      /**< \brief (Afec Offset: 0x94) AFEC Analog Control Register */
//  pAfe_ADC0.AFEC_SHMR = AFEC_SHMR_DUAL0;     /**< \brief (Afec Offset: 0xA0) AFEC Sample & Hold Mode Register */
 
  
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

