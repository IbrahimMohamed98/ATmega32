/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  UART.h
 *       Module:  UART
 *
 *  Description:  header file for UART Module    
 *
 *  
 *********************************************************************************************************************/
#ifndef UART_H_
#define UART_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../../Libs/Types.h"
#include "../../Libs/BitMath.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum{
	MPCM,
	U2X,
	PE,
	DOR,
	FE,
	UDRE,
	TXC,
	RXC
}UARTControlA_t;

typedef enum{
	TXB8,
	RXB8,
	UCSZ2,
	TXEN,
	RXEN,
	UDRIE,
	TXCIE,
	RXCIE
}UARTControlB_t;

typedef enum{
	UCPOL,
	UCSZ0,
	UCSZ1,
	USBS,
	UPM0,
	UPM1,
	UMSEL,
	URSEL
}UARTControlC_t;

typedef enum{
	SIZE5 = 0,
	SIZE6 = 1,
	SIZE7 = 2,
	SIZE8 = 3,
	SIZE9 = 7
	
}UARTCharSize_t;

typedef enum{
	DATA_EMPTY = 5,
	TRANMIT_COMPELETE,
	RECIEVE_COMPELETE,
	BOTH_TX_RX_COMPELETE,
	NON_UART_INTERRUPT
}UARTInterrupt_t;

typedef enum{
	Receiver,
	Transmitter,
	HalfDuplex
}UARTMode_t;

typedef struct{
	volatile char BAUDL;
	volatile char CONTROL_B;
	volatile char CONTROL_A;
	volatile char DATA;
	volatile char RESERVED[19];
	volatile char CONTROL_C;
}UART_t;

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

                            /***Control Options***/
//Speed options
#define BAUD_RATE  115200UL   // The UART BAUD rate.
#define UART_2x_SPEED   0//Disable Double speed mode ->0
                         //Enable Double speed mode  ->1
//mode options
#define UART_MODE       HalfDuplex   //-Transmitter -> to transmit only
                                   //-Receiver    -> to receive only
								   //-HalfDuplex  -> to receive and transmit
//Interrupt options
#define UART_INTERRUPT_SRC NON_UART_INTERRUPT//-DATA_EMPTY           ->   fire the interrupt when the data register is empty
                                             //-TRANMIT_COMPELETE    ->   fire the interrupt when Tranmition complete
                                             //-RECEIVE_COMPELETE    ->   fire the interrupt when reception complete
					    		 			 //-BOTH_TX_RX_COMPELETE ->   fire the interrupt when Tranmition complete and 
						    	 			 //                             reception complete
							    			 //NON_UART_INTERRUPT    ->   No interrupt is fired
#define CHAR_SIZE          SIZE8  //choose the char size either SIZE5,6,7,8,or9 bits
//setting the char size
#define UART            ((UART_t *)0x29)	

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
//Check for UART Chosen char size and set it
#define UART_SET_CHARSIZE(){\
	if(CHAR_SIZE <  SIZE9){\
		BIT_SET(UART->CONTROL_C,URSEL);\
		VAL_SET(UART->CONTROL_C,CHAR_SIZE,UCSZ0);\
	}else{\
		BIT_SET(UART->CONTROL_B,UCSZ2);\
		BIT_SET(UART->CONTROL_C,URSEL);\
		VAL_SET(UART->CONTROL_C,SIZE8,UCSZ0);\
	}\
}

//Check for UART Chosen mode and set it
#define UART_SET_MODE(){\
	if (UART_MODE == Transmitter){\
		BIT_SET(UART->CONTROL_B,TXEN);\
	}else if(UART_MODE == Receiver){\
		BIT_SET(UART->CONTROL_B,RXEN);\
	}else{\
		BIT_SET(UART->CONTROL_B,TXEN);\
		BIT_SET(UART->CONTROL_B,RXEN);\
	}\
}
//Set the UART BAUD rate
#define UART_START(){\
	int baud_rate = 0;\
	if(UART_2x_SPEED != 1){\
		baud_rate = ceil((F_CPU /(double)(16 * BAUD_RATE))) -1;\
	}else{\
		baud_rate = ceil((F_CPU /(double)(8*BAUD_RATE))) - 1;\
	}\
	if(baud_rate <= 255){\
		UART->BAUDL = baud_rate;\
	}else{\
		BIT_SET(UART->CONTROL_C,URSEL);\
		VAL_SET(UART->CONTROL_C,(8 >> baud_rate),0);\
		UART->BAUDL = baud_rate;\
	}\
}
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 /******************************************************************************
* \Syntax          : void UART_init(void)                                  
* \Description     : This function initiate the UART                                   
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Non-reentrant      
* \Parameters (in) : void 
                      
					  
* \Parameters (out):  non
* \Return value:   :  void
*******************************************************************************/
void UART_init(void);

/******************************************************************************
* \Syntax          : void UART_send(uint8 msg)                                  
* \Description     : This function sends data over UART                                  
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Non-reentrant      
* \Parameters (in) : uint8 msg -> the message the UART would send
                      
					  
* \Parameters (out):  non
* \Return value:   :  void
*******************************************************************************/
void UART_send(uint8 msg);

/******************************************************************************
* \Syntax          : uint8 UART_receive(void)                                  
* \Description     : This function receive data over UART                                  
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Non-reentrant      
* \Parameters (in) : void
                      
					  
* \Parameters (out):  non
* \Return value:   :  uint8
*******************************************************************************/
uint8 UART_receive(void);

/******************************************************************************
* \Syntax          : void UART_setReceiveCallBack(callBack_t (*UART_RecieveISR)(void));                                  
* \Description     : This function sets the  UART callback at receive interrupt                                   
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Non-reentrant      
* \Parameters (in) : allBack_t (*UART_RecieveISR)(void) -> a pointer to function that deliver the ISR
                      
					  
* \Parameters (out): non
* \Return value:   : void
*******************************************************************************/
void UART_setReceiveCallBack(callBack_t (*UART_RecieveISR)(void));
/******************************************************************************
* \Syntax          : void UART_setSendCallBack(callBack_t (*UART_SendISR)(void));                                 
* \Description     : This function sets the  UART callback at send interrupt                                   
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Non-reentrant      
* \Parameters (in) : callBack_t (*UART_ISR)(void) -> a pointer to function that deliver the ISR
                      
					  
* \Parameters (out): non
* \Return value:   : void
*******************************************************************************/
void UART_setSendCallBack(callBack_t (*UART_SendISR)(void));

#endif /* UART_H_ */
/**********************************************************************************************************************
 *  END OF FILE: UART.h
 *********************************************************************************************************************/
