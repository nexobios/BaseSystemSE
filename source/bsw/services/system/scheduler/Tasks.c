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
uint16_t ADCGetValue=0;
uint32_t u32AfecBuff[RxBufferDMASize];

void AFEC0_Init()
{ 
  PIO_Configure(&pinsAFECs[0], 1);
  AFEC_Initialize( AFEC0, ID_AFEC0);           

  AFEC_SetClock(AFEC0, 256 ,BOARD_MCK);
  AFEC_SetTiming(AFEC0, AFEC_MR_STARTUP_SUT640 , AFEC_MR_TRACKTIM(0),		0);
  AFEC_SetTrigger( AFEC0,AFEC_MR_FREERUN_ON ); 
  AFEC_SetNumberOfBits( AFEC0, AFEC_EMR_RES_OSR256);
  AFEC_EnableChannel(AFEC0,AFEC_CHER_CH0);
  AFEC_StartConversion(AFEC0);
  NVIC_DisableIRQ(AFEC0_IRQn);
	NVIC_ClearPendingIRQ(AFEC0_IRQn);
	NVIC_SetPriority(AFEC0_IRQn, 0);
	NVIC_EnableIRQ(AFEC0_IRQn);
  
}
 
void PWM0_Init(uint16_t Period)
{
  PMC_EnablePeripheral(ID_PWM0);
  PWMC_Initialice(PWM0);
                                                                  
  PWMC_ConfigureClocks(PWM0, 14200 , 14200,  BOARD_MCK);
  PWMC_DisableChannel(PWM0, PWM_DIS_CHID0);//PWM_ENA_CHID0
  
  PWMC_DisableIt(PWM0,PWM_IER1_CHID0 | PWM_IER1_FCHID1,PWM_IER2_CMPM0 | PWM_IER2_WRDY | PWM_IER2_UNRE |PWM_IER2_CMPU0);  
  
  PWMC_ConfigureChannel( PWM0, 1, PWM_CMR_CPRE(PWM_CMR_CPRE_MCK_DIV_64),PWM_CMR_CALG ,PWM_CMR_CPOL);
  PWMC_SetPeriod( PWM0, 1, PWM_CPRD_CPRD(200));// );      
  PWMC_SetDutyCycle( PWM0, 1, 200);
  //PWMC_SetDeadTime( PWM0, 1, 200, 0);
  //PWMC_ConfigureSyncChannel( PWM0,0,PWM_SCM_SYNC0|PWM_SCM_SYNC1,PWM_SCM_UPDM(PWM_SCM_UPDM_MODE0),PWM_SCM_PTRCS(1));
  //PWMC_ConfigureComparisonUnit( PWM0, 1,200 ,1);
  //PWMC_SetSyncChannelUpdatePeriod() 
  PWMC_SetSyncChannelUpdateUnlock(PWM0);
  PWMC_EnableChannel( PWM0, PWM_ENA_CHID0 | PWM_ENA_CHID1);
  PWMC_EnableIt(PWM0,          
                PWM_IER1_CHID0 |PWM_IER1_CHID1 /*| PWM_IER1_FCHID0 */ ,
                PWM_IER2_CMPM0 |PWM_IER2_CMPM1 | PWM_IER2_WRDY | PWM_IER2_UNRE | PWM_IER2_CMPU0 | PWM_IER2_CMPU1);  
  PWMC_EnableChannelIt( PWM0, PWM_ENA_CHID0 | PWM_ENA_CHID1);
  
  NVIC_DisableIRQ(PWM0_IRQn);
	NVIC_ClearPendingIRQ(PWM0_IRQn);
	NVIC_SetPriority(PWM0_IRQn, 0);
	NVIC_EnableIRQ(PWM0_IRQn);
}

void SET_AFEC_SAMPLING(uint16_t SAMP_PER, uint16_t *RxDMABuffer, uint16_t SIZE)
{ 
  AFEC0_Init();
  Afe_Dma_Init(&u32AfecBuff[0],RxBufferDMASize);
  TASK_AFEC_DMA();               
  PWM0_Init(SAMP_PER);
}
void vfnTsk_1ms(void)
{
  
}

void vfnTsk_2msA(void)
{
	
}

void vfnTsk_2msB(void)
{
	ADCGetValue = AFEC_GetConvertedData(AFEC0,0);
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

