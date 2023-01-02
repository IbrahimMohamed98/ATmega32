
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  UART.C
 *        \brief  This file include the functions that deliver SPI functionality
 *
 *      \details  - Initiation of UART Based on preset options
 *                - Sending data over UART
 *                - Receiving data over UART 
 *                - Setting interrupts CallBacks
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include <math.h>
#include "../../libs/Types.h"
#include "../../libs/BitMath.h"
#include "../../Libs/Registers.h"

#include "../Inc/UART.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
callBack_t (*UART_ReceiveCallBack)(void) = (void*)0;
callBack_t (*UART_SendCallBack)(void)    = (void*)0;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void UART_init(void){
	//set the char size
	UART_SET_CHARSIZE();
	//set the UART mode
	UART_SET_MODE();
	//Set the UART baud rate
	UART_START();
}


void UART_send(uint8 msg){
	//Load data into the UDR register
	UART -> DATA = msg;
	//Wait until the data is fully sent
	while (!BIT_VAL(UART -> CONTROL_A,UDRE));
}


uint8 UART_receive(void){
	//A local variable to store the received data
	uint8 Lmsg;
	//Wait until the data is fully received in UDR 
	while (!BIT_VAL(UART -> CONTROL_A,RXC));
	//Load the UDR content in the lmsg Local variable
	Lmsg = UART->DATA;
	return Lmsg;
}


void UART_setReceiveCallBack(callBack_t (*UART_RecieveISR)(void)){
	UART_ReceiveCallBack = UART_RecieveISR;//set the Receive ISR.
}

void UART_setSendCallBack(callBack_t (*UART_SendISR)(void)){
	UART_SendCallBack = UART_SendISR;//Set the send ISR.
}

/**********************************************************************************************************************
 *  END OF FILE: UART.c
 *********************************************************************************************************************/

