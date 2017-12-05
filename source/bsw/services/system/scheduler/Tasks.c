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
uint32_t u32AfecBuff[RxBufferDMASize];

void AFEC0_Init()
{ 
  PIO_Configure(&pinsAFECs[0], 1);
  AFEC_Initialize( AFEC0, ID_AFEC0);           

  AFEC_SetClock(AFEC0, 256 ,BOARD_MCK);
  AFEC_SetTiming(AFEC0, AFEC_MR_STARTUP(AFEC_MR_STARTUP_SUT8), AFEC_MR_TRACKTIM(0),		0);
  AFEC_SetTrigger( AFEC0,(0x1u << 7)); 
  AFEC_SetNumberOfBits( AFEC0, AFEC_EMR_RES(AFEC_EMR_RES_OSR256));
  AFEC0->AFEC_MR=0x0f840c81;
  AFEC_EnableChannel(AFEC0,0);
  AFEC_StartConversion(AFEC0);
  
 
}
 
void PWM0_Init(uint32_t Period)
{
  PMC_EnablePeripheral(ID_PWM0);
  PWMC_Initialice(PWM0);
                            
  
  PWMC_ConfigureClocks(PWM0, Period , 0,  BOARD_MCK);
  PWMC_DisableChannel(PWM0, PWM_DIS_CHID0);//PWM_ENA_CHID0
  
  PWMC_DisableIt(PWM0,PWM_IER1_CHID0 ,PWM_IER2_CMPM0 | PWM_IER2_WRDY | PWM_IER2_UNRE |PWM_IER2_CMPU0);  
  
  PWMC_ConfigureChannel( PWM0, 0, PWM_CMR_CPRE_CLKA,0,PWM_CMR_CPOL);
  PWMC_SetPeriod( PWM0, 0, 200);// );      
  PWMC_SetDutyCycle( PWM0, 0, 100);
 // PWMC_SetDeadTime( PWM0, 0, 200, 0);
  PWMC_ConfigureSyncChannel( PWM0,0,PWM_SCM_SYNC0,PWM_SCM_UPDM(PWM_SCM_UPDM_MODE2),PWM_SCM_PTRCS(0));
  PWMC_ConfigureComparisonUnit( PWM0, 0,200 ,1);
  //PWMC_SetSyncChannelUpdatePeriod() 
  PWMC_SetSyncChannelUpdateUnlock(PWM0);
  PWMC_EnableChannel( PWM0, 0);
  PWMC_EnableIt(PWM0,          
                PWM_IER1_CHID0 | PWM_IER1_FCHID0 ,
                PWM_IER2_CMPM0 | PWM_IER2_CMPU0 | PWM_IER2_WRDY | PWM_IER2_UNRE );  
  PWMC_EnableChannelIt( PWM0, 0);
  
  NVIC_DisableIRQ(PWM0_IRQn);
	NVIC_ClearPendingIRQ(PWM0_IRQn);
	NVIC_SetPriority(PWM0_IRQn, 0);
	NVIC_EnableIRQ(PWM0_IRQn);
}

void SET_AFEC_SAMPLING(uint32_t SAMP_PER, uint32_t *RxDMABuffer, uint16_t SIZE)
{ 
  AFEC0_Init();
  Afe_Dma_Init(RxDMABuffer,SIZE);
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
//	ADCGetValue = AFEC_GetConvertedData(AFEC0,0);
}

void vfnTsk_10ms(void)
{
	/*static uint8_t u8500ms_Ctr=0;
  //AFEC_StartConversion(AFEC0);
  
  uint16_t value= AFEC_GetConvertedData( AFEC0,AFEC_CHER_CH0);
  
  //printf("\nValue &d",&pAfe_ADC0.AFEC_LCDR);
	u8500ms_Ctr++;
	
	if (25 <= u8500ms_Ctr)
	{
		u8500ms_Ctr = 0;
		LED_Toggle( 1 );
	} */  
}

void vfnTsk_50ms(void)
{
}

void vfnTsk_100ms(void)
{
  /*			
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
	} */
}

