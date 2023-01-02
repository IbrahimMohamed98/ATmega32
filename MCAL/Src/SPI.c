/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  SPI.C
 *        \brief  This file include the functions that deliver SPI functionality
 *
 *      \details  - Initiation of SPI Based on preset options
 *                - Sending data over SPI
 *                - Receiving data over SPI 
 *                
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../../libs/Types.h"
#include "../../libs/BitMath.h"
#include "../../libs/Registers.h"

#include "../Inc/DIO.h"
#include "../Inc/SPI.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
callBack_t (*SPI_callBack)(void) = (void*)0;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void SPI_init(SPIFreq_t freq){
	//Choose if the SPI works as master or slave.
	#if SPI_MASTER == 1
		BIT_SET(SPI->CONTROL,SPI_MASTER_PIN);//Set SPI as master
		//Set the SPI frequency.
		#if SPI_X2SPEED == 1
			BIT_SET(SPI->STATUS,0);//Double the frequency
			VAL_SET(SPI ->CONTROL,freq,0);//Set the SPI frequency
		#else
			BIT_CLR(SPI->STATUS,0);//Make the frequency as we set it
			VAL_SET(SPI ->CONTROL,freq,0);//Set the SPI frequency
		#endif
		//Make MOSI,SS and SCK as output.
		DIO_init(SPI_PORT,MOSI,OUT);
		DIO_init(SPI_PORT,SS  ,OUT);
		DIO_init(SPI_PORT,SCK ,OUT);
	#else
	    BIT_CLR(SPI->CONTROL,SPI_MASTER_PIN);//Set SPI as slave.
		DIO_init(SPI_PORT->DIR,MISO,OUT);//Make MISO as output.
		DIO_init(SPI_PORT,SS  ,OUT);
	#endif
	
	//Choose if we will Enable the interrupt or not.
	#if SPI_INTERRUPT_ENABLE == 1
		BIT_SET(SPI->CONTROL,SPI_INTERRUPT_EN_FLAG_PIN);//Enable SPI interrupt.
	#else
		BIT_CLR(SPI->CONTROL,SPI_INTERRUPT_EN_FLAG_PIN);//Disable SPI interrupt.
	#endif
	//choose the Data order
	#if SPI_DATA_ORDER == 1
		BIT_SET(SPI->CONTROL,5);//Enable SPI interrupt.
	#else
		BIT_CLR(SPI->CONTROL,5);//Disable SPI interrupt.
	#endif
	
	
	BIT_SET(SPI->CONTROL,SPI_ENABLE_PIN);
	
}

void SPI_send(uint8 msg){
	DIO_setPinValue(SPI_PORT,SS  ,HIGH_OUT);
	SPI->DATA = msg;//Put the data in the SPI data register.
	while(!BIT_VAL(SPI->STATUS,7));//wait until transmission end.
	DIO_setPinValue(SPI_PORT,SS  ,LOW_OUT);
}

uint8 SPI_receive(void){
	char Lmsg;//Local var to receive the message
	while(!BIT_VAL(SPI->STATUS,SPI_INTERRUPT_EN_FLAG_PIN));//wait until the data received.
	Lmsg = SPI->DATA;//store the data in the Local variable
	return Lmsg;//return the data
}

void SPI_setCallBack(callBack_t(*ISR_Handler)(void)){
	SPI_callBack = ISR_Handler;
}

/**********************************************************************************************************************
 *  END OF FILE: SPI.c
 *********************************************************************************************************************/
