/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "app_scheduler.h"
#include "Tasks.h"    
#include <stdbool.h>
#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/
/*@Yisus Adc struct*/
#define BOARD_MCK    150000000 
#define RxBufferDMASize   8
uint32_t *RxDMABuffer;
extern Afec pAfe_ADC0;
extern Pwm pPwm_0;                
extern AfeDma pAfed;     
extern sXdmad pXdmad;
extern AfeCmd pAfeCmd;
//#define AfeId   35
//static const Pin pinsAFECs[] = {AFEC_PIN_CFG};
/*@Yisus Adc struct*/


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

	printf( "Configure LED PIOs.\n\r" ) ;
	_ConfigureLeds() ;
  
  	/* Initialize Task Scheduler */
	vfnScheduler_Init(&Tasks[0]);
	/* Start execution of task scheduler */
	vfnScheduler_Start();
  
  
  /* Init ADC  @Yisus */

  
 /* To configure a XDMA channel, the user has to follow these few steps :
 * <li> Initialize a XDMA driver instance by XDMAD_Initialize().</li>
 * <li> choose an available (disabled) channel using XDMAD_AllocateChannel().</li>
 * <li> After the XDMAC selected channel has been programmed, 
 * XDMAD_PrepareChannel() is to enable clock and dma peripheral of the DMA, and 
 * set Configuration register to set up the transfer type (memory or non-memory 
 * peripheral for source and destination) and flow control device.</li>
 * <li> Invoke XDMAD_StartTransfer() to start DMA transfer  or 
 * XDMAD_StopTransfer() to force stop DMA transfer.</li>
 * <li> Once the buffer of data is transferred, XDMAD_IsTransferDone() 
 * checks if DMA transfer is finished.</li>
 * <li> XDMAD_Handler() handles XDMA interrupt, and invoking XDMAD_SetCallback()
 * if provided.</li>
  */
  
/**
 * \brief Initialize xDMA driver instance.
 * \param pXdmad Pointer to xDMA driver instance.
 * \param bPollingMode Polling DMA transfer:
 *                     1. Via XDMAD_IsTransferDone(); or
 *                     2. Via XDMAD_Handler().
 */
  //XDMAD_Initialize(&pXdmad, 0 );

/**
 * \brief Allocate a XDMA channel for upper layer.
 * \param pXdmad  Pointer to xDMA driver instance.
 * \param bSrcID Source peripheral ID, 0xFF for memory.
 * \param bDstID Destination peripheral ID, 0xFF for memory.
 * \return Channel number if allocation successful, return
 * XDMAD_ALLOC_FAILED if allocation failed.
 */
  //XDMAD_AllocateChannel( &pXdmad,	ID_AFEC0, XDMAD_TRANSFER_MEMORY);

/**
 * \brief Enable clock of the xDMA peripheral, Enable the dma peripheral,
 * configure configuration register for xDMA transfer.
 * \param pXdmad     Pointer to xDMA driver instance.
 * \param dwChannel ControllerNumber << 8 | ChannelNumber.
 * \param dwCfg     Configuration value.
 */
  //XDMAD_PrepareChannel( &pXdmad, 1);
/*
XDMAD_StartTransfer();
XDMAD_IsTransferDone();
 XDMAD_Handler();
 */
  
  
/**
 * \brief Initializes the AfeDma structure and the corresponding AFE & DMA .
 * hardware select value.
 * The driver will uses DMA channel 0 for RX .
 * The DMA channels are freed automatically when no DMA command processing.
 *
 * \param pAfed  Pointer to a AfeDma instance.
 * \param pAfeHw Associated Afe peripheral.
 * \param AfeId  Afe peripheral identifier.
 * \param pDmad  Pointer to a Dmad instance. 
 */
  //Afe_ConfigureDma( &pAfed ,AFEC0, ID_AFEC0, &pXdmad );            //AFEC0         //pAfe_ADC0
  //pAfeCmd.pRxBuff =RxDMABuffer;
	//pAfeCmd.RxSize =RxBufferDMASize;
	//pAfeCmd.callback = (*AfeCallback)NULL;
	//void *pArgument;

  //Afe_SendData( &pAfed , &pAfeCmd);
 

  PMC_EnablePeripheral(ID_PWM0);
  PWMC_ConfigureClocks(PWM0, 14200, 0,  BOARD_MCK);
  //PWMC_ConfigureChannel(PWM0, CHANNEL_PWM_LCD, PWM_CMR_CPRE_CLKA,0, PWM_CMR_CPOL);
  PWMC_ConfigureChannel( PWM0,	PWM_ENA_CHID0, PWM_CMR_CPRE_CLKA, 0, PWM_CMR_CPOL);
  PWMC_SetPeriod( PWM0, PWM_ENA_CHID0, 100);  
  PWMC_SetDutyCycle( PWM0, PWM_ENA_CHID0, 50);
  PWMC_EnableChannel( PWM0, PWM_ENA_CHID0);
  PWMC_EnableChannelIt( PWM0, PWM_ENA_CHID0);
  PWMC_EnableIt(PWM0,PWM_IER2_CMPU0,0);  //PWM_IER2_CMPM0
  
  

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
 
  /* Init ADC  @Yisus */
	
  /*-- Loop through all the periodic tasks from Task Scheduler --*/
	for(;;)
	{
		/* Perform all scheduled tasks */
		vfnTask_Scheduler();
       

	}

}

   