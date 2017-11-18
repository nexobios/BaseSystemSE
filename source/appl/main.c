/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "app_scheduler.h"
#include "Tasks.h"    
#include "fpu.h"   
#include <stdbool.h>
#include <stdio.h>
/**  Fast fourier transform */
#include    "fft.h"
#include    "ecg_data.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/
/*@Yisus Adc struct*/
#define BOARD_MCK    150000000 
#define RxBufferDMASize   8

/*~~~~~~  Local definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define TEST_LENGTH_SAMPLES 2048
/*~~~~~~  Global variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** Auxiliary input buffer to accomodate data as FFT function expects it */
float       fft_inputData[TEST_LENGTH_SAMPLES];
/** Output magnitude data */
float       fft_signalPower[TEST_LENGTH_SAMPLES/2];
/** Auxiliary output variable that holds the frequency bin with the highest level of signal power */
uint32_t    u32fft_maxPowerIndex;
/** Auxiliary output variable that holds the maximum level of signal power */
float       fft_maxPower;

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
	/** Auxiliary array index */
    uint16_t    u16index;
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
  PWM0_Init();
  AFEC0_Init();  
  /* Init ADC  @Yisus */
	
  /*-- Loop through all the periodic tasks from Task Scheduler --*/
	for(;;)
    {	
		/*Prepare data for FFT operation */
        for (u16index = 0; u16index < (TEST_LENGTH_SAMPLES/2); u16index++)
        {
            fft_inputData[(2*u16index)] = ecg_resampled[u16index];
            fft_inputData[(2*u16index) + 1] = 0;
        }
        /** Perform FFT on the input signal */
        fft(fft_inputData, fft_signalPower, TEST_LENGTH_SAMPLES/2, &u32fft_maxPowerIndex, &fft_maxPower);
        
        /* Publish through emulated Serial the byte that was previously sent through the regular Serial channel */
		printf("%5d  %5.4f \r\n", u32fft_maxPowerIndex, fft_maxPower);
		
        /** Perform periodically activated tasks */
		vfnTask_Scheduler();
       

	}

}

   