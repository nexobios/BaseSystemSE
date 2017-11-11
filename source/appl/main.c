/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "app_scheduler.h"
#include "Tasks.h"    
#include "afe_dma.h"
#include "afec.h"
#include <stdbool.h>
#include <stdio.h>

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

/*@Yisus Adc struct*/
Afec pAfe_ADC0;
Pwm pPwm_0;                
AfeDma pAfed;     
sXdmad pXdmad;
//#define AfeId   35
static const Pin pinsAFECs[] = {AFEC_PIN_CFG};
/*@Yisus Adc struct*/
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
XDMAD_Initialize( &pXdmad, 0 );

/**
 * \brief Allocate a XDMA channel for upper layer.
 * \param pXdmad  Pointer to xDMA driver instance.
 * \param bSrcID Source peripheral ID, 0xFF for memory.
 * \param bDstID Destination peripheral ID, 0xFF for memory.
 * \return Channel number if allocation successful, return
 * XDMAD_ALLOC_FAILED if allocation failed.
 */
XDMAD_AllocateChannel( &pXdmad,	ID_AFEC0, XDMAD_TRANSFER_MEMORY);

/**
 * \brief Enable clock of the xDMA peripheral, Enable the dma peripheral,
 * configure configuration register for xDMA transfer.
 * \param pXdmad     Pointer to xDMA driver instance.
 * \param dwChannel ControllerNumber << 8 | ChannelNumber.
 * \param dwCfg     Configuration value.
 */
XDMAD_PrepareChannel( &pXdmad, 1);
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
Afe_ConfigureDma( &pAfed ,AFEC0, ID_AFEC0, &pXdmad );            //AFEC0         //pAfe_ADC0
 // Afe_Rx_Cb(uint32_t channel, AfeDma* pArg);
 
  
  
/*    -# Configures PWM clocks A & B to run at the given frequencies using
 *       \ref PWMC_ConfigureClocks().
 *    -# Configure PWMC channel using \ref PWMC_ConfigureChannel(), 
 * \ref PWMC_ConfigureChannelExt()
 *       \ref PWMC_SetPeriod(), \ref PWMC_SetDutyCycle() and 
 * \ref PWMC_SetDeadTime().
 *    -# Enable & disable channel using \ref PWMC_EnableChannel() and
 *       \ref PWMC_DisableChannel().
 *    -# Enable & disable the period interrupt for the given PWM channel using
 *       \ref PWMC_EnableChannelIt() and \ref PWMC_DisableChannelIt().
 *    -# Enable & disable the selected interrupts sources on a PWMC peripheral
 *       using  \ref PWMC_EnableIt() and \ref PWMC_DisableIt().
 *    -# Control synchronous channel using \ref PWMC_ConfigureSyncChannel(),
 *       \ref PWMC_SetSyncChannelUpdatePeriod() and 
 * \ref PWMC_SetSyncChannelUpdateUnlock().
 *    -# Control PWM override output using \ref PWMC_SetOverrideValue(),
 *       \ref PWMC_EnableOverrideOutput() and \ref PWMC_DisableOverrideOutput().
 *    -# Send data through the transmitter using \ref PWMC_WriteBuffer().
 */
  PWMC_ConfigureClocks(&pPwm_0, 0, 0, BOARD_MCK);
  PWMC_ConfigureChannel( &pPwm_0,	PWM_ENA_CHID0, PWM_CLK_PREA_CLK, 0, 0);
  //PWMC_EnableChannel( &pPwm_0, PWM_ENA_CHID0);
  PWMC_EnableChannelIt(&pPwm_0, PWM_ENA_CHID0);
  PWMC_EnableIt(&pPwm_0,PWM_IER2_CMPU0,0);
  
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
  pAfe_ADC0.AFEC_CR = AFEC_CR_SWRST;       /**< \brief (Afec Offset: 0x00) AFEC Control Register */
  pAfe_ADC0.AFEC_MR = AFEC_MR_TRGEN_EN | AFEC_MR_TRGSEL_AFEC_TRIG4;       /**< \brief (Afec Offset: 0x04) AFEC Mode Register */
  pAfe_ADC0.AFEC_EMR = AFEC_MR_SLEEP_NORMAL;      /**< \brief (Afec Offset: 0x08) AFEC Extended Mode Register */
  pAfe_ADC0.AFEC_CHER = AFEC_CHER_CH0;     /**< \brief (Afec Offset: 0x14) AFEC Channel Enable Register */
  pAfe_ADC0.AFEC_IER = AFEC_IER_EOC0 | AFEC_IER_DRDY;      /**< \brief (Afec Offset: 0x24) AFEC Interrupt Enable Register */
  pAfe_ADC0.AFEC_CGR = AFEC_CVR_GAINCORR(1);      /**< \brief (Afec Offset: 0x54) AFEC Channel Gain Register */
  pAfe_ADC0.AFEC_ACR = AFEC_ACR_PGA0EN;      /**< \brief (Afec Offset: 0x94) AFEC Analog Control Register */
  pAfe_ADC0.AFEC_SHMR = AFEC_SHMR_DUAL0;     /**< \brief (Afec Offset: 0xA0) AFEC Sample & Hold Mode Register */
  
  PIO_Configure(&pinsAFECs[0], 1);
  AFEC_Initialize( &pAfe_ADC0, ID_AFEC0);               
  AFEC_SetClock(&pAfe_ADC0, AFEC_MR_PRESCAL(1),BOARD_MCK);
  AFEC_SetTiming(&pAfe_ADC0, AFEC_MR_STARTUP_SUT0, AFEC_MR_TRACKTIM(1),		0);
  AFEC_EnableChannel(&pAfe_ADC0,AFEC_CHER_CH0);
  AFEC_StartConversion(&pAfe_ADC0);
                 
  
  /* Init ADC  @Yisus */
	
  /*-- Loop through all the periodic tasks from Task Scheduler --*/
	for(;;)
	{
		/* Perform all scheduled tasks */
		vfnTask_Scheduler();
	}

}
