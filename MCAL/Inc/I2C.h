/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  I2C.h
 *       Module:  I2C
 *
 *  Description:  header file for I2C Module    
 *********************************************************************************************************************/


#ifndef I2C_H_
#define I2C_H_
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include <math.h>
#include "../../Libs/Types.h"
#include "../../libs/Registers.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*** I2C CONTROL ***/

#define I2C_MODE                SLAVE

#if I2C_MODE == SLAVE
	#define I2C_SLAVE_ADDRESS    2
#endif

#define I2C_PRESCALER            PRESC4

#define SCL_FREQUENCY            100000UL
#define I2C_TWBR_VALUE           ceil(((F_CPU/SCL_FREQUENCY)-16)/(2*pow(4,I2C_PRESCALER)))
                                 


//Status  for I2C.
#define START_ACK                          0x08
#define REP_START_ACK                      0x10
#define SLAVE_ADD_AND_WR_ACK               0x18
#define SLAVE_ADD_AND_WR_NACK              0x20
#define SLAVE_ADD_AND_RD_ACK               0x40
#define SLAVE_ADD_AND_RD_NACK              0x48
#define WR_BYTE_ACK                        0x28
#define WR_BYTE_NACK                       0x30
#define RD_BYTE_WITH_NACK                  0x58
#define RD_BYTE_WITH_ACK                   0x50
#define SLAVE_ADD_RCVD_RD_REQ              0xA8
#define SLAVE_ADD_RCVD_WR_REQ              0x60
#define SLAVE_DATA_RECEIVED_WITH_ACK       0x80
#define SLAVE_DATA_RECEIVED_WITH_NACK      0x88
#define SLAVE_BYTE_TRANSMITTED_WITH_NACK   0xC0
#define SLAVE_BYTE_TRANSMITTED_WITH_ACK    0xB8



/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#define I2C_ENABLE()                        I2C->CONTROL = (1<<TWEN)
#define I2C_ENABLE_ACKNOWLDGEMENT(ack)	    {\
												if(ack == ACK){\
												   BIT_SET(I2C->CONTROL,TWEA);\
												}else{\
												   BIT_CLR(I2C->CONTROL,TWEA);\
												}\
											}

#define I2C_CLR_INTERRUPT()                 BIT_SET(I2C->CONTROL,TWINT)
#define I2C_SET_BITRATE()                   I2C -> BITRATE = I2C_TWBR_VALUE
#define I2C_SET_PRESCALER()                 VAL_SET(I2C -> STATUS,I2C_PRESCALER,0)
#define I2C_SET_SLAVEADDRESS()              I2C -> ADDRESS = (I2C_SLAVE_ADDRESS << 1)
#define I2C_GET_STATUS(status)              ((I2C -> STATUS & 0xF8) == status)
#define I2C_SEND_SLAVE_WRITE_ADDRESS(addr)  I2C -> DATA = (addr << 1)
#define I2C_SEND_SLAVE_READ_ADDRESS(addr)   I2C -> DATA = ((addr << 1)|(1<<0))
#define I2C_START()                         BIT_SET(I2C -> CONTROL,TWSTA)
#define I2C_STOP()                          BIT_SET(I2C -> CONTROL,TWSTO)
#define I2C_WAIT_STOP()                     while(!BIT_VAL(I2C -> CONTROL,TWSTO))				  
#define I2C_WAIT_INTERRUPT()                while(!BIT_VAL(I2C->CONTROL,TWINT))
#define I2C_SEND_DATA(data)                 I2C -> DATA = (data)    


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
//I2C Acknowledgment type
typedef enum{
	ACK,
	NACK
}I2CACK_t;
//I2C error Type
typedef enum{
	I2C_START_error,
	Master_Send_Address_error,
	I2C_Master_Write_DATA_error,
	I2C_MASTER_READ_DATA_error,
	I2C_SLAVE_Write_DATA_error,
	I2C_SLAVE_READ_DATA_error,
	I2C_Master_Write_ADDRESS_error,
	I2C_MASTER_READ_ADDRESS_error,
	I2C_SLAVE_ADDRESS_NOT_RECEIVED,
	I2C_ok
}I2CStatus_t;
//I2C prescaler type
typedef enum{
	PRESC1 = 0UL,
	PRESC4 = 1UL,
	PRESC16= 2UL,
	PRESC64= 3UL
}I2CPrescaler_t;
//I2C Operating mode
typedef enum{
	MASTER,
	SLAVE
}I2CMode_t;


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
/******************************************************************************
* \Syntax          : void I2C_init(void)                                  
* \Description     : This function initiate the I2C                                   
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Nonreentrant      
* \Parameters (in) : void
                      
					  
* \Parameters (out):  non
* \Return value:   :  void
*******************************************************************************/
void I2C_init(void);
/******************************************************************************
* \Syntax          : I2CStatus_t I2C_sendStart(I2CACK_t Acknowledgment);                                  
* \Description     : This function send start condition and return if the device get the arbitration                                   
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Nonreentrant      
* \Parameters (in) : void 
                      
					  
* \Parameters (out):  non
* \Return value:   :  I2CStatus_t
*******************************************************************************/
I2CStatus_t I2C_sendStart(void);
/******************************************************************************
* \Syntax          : I2CStatus_t I2C_masterSend(uint8 Slave_Address,uint8 *data,I2CACK_t Acknowledgment,const int size);                                  
* \Description     : This function returns if the data sent over I2C is a success or not                                   
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Nonreentrant      
* \Parameters (in) : uint8 Slave_Address -> the slave to send the data to
                     uint8 *data -> the data we want to send
					 I2CACK_t Acknowledgment -> if we want to Receive ACK or not
					 const int size -> the size of the data to be sent
                      
					  
* \Parameters (out):  non
* \Return value:   :  I2CStatus_t
*******************************************************************************/
I2CStatus_t I2C_masterSend(uint8 Slave_Address,uint8 *data,I2CACK_t Acknowledgment,const int size);
/******************************************************************************
* \Syntax          : I2CStatus_t I2C_masterRecieve(uint8 Slave_Address,uint8 *data,I2CACK_t Acknowledgment,const char size);                                  
* \Description     : This function returns if the master received the data over I2C successfully                                   
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Nonreentrant      
* \Parameters (in) : uint8 Slave_Address -> the slave to send the data to
                     uint8 *data -> the data buffer for sent data
                     I2CACK_t Acknowledgment -> if we want to Receive ACK or not
                     const int size -> the size of the data to be sent
                      
					  
* \Parameters (out):  non
* \Return value:   :  I2CStatus_t
*******************************************************************************/
I2CStatus_t I2C_masterRecieve(uint8 Slave_Address,uint8 *data,I2CACK_t Acknowledgment,const char size);
/******************************************************************************
* \Syntax          : I2CStatus_t I2C_slaveRecieve(uint8 *data,I2CACK_t Acknowledgment,const int size);                                 
* \Description     : This function makes the slave receive data over I2C                                  
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Nonreentrant      
* \Parameters (in) : uint8 *data -> the data buffer for received data data
                     I2CACK_t Acknowledgment -> if we want to Receive ACK or not
                     const int size -> the size of the data to be sent
					  
* \Parameters (out):  non
* \Return value:   :  I2CStatus_t
*******************************************************************************/
I2CStatus_t I2C_slaveRecieve(uint8 *data,I2CACK_t Acknowledgment,const int size);
/******************************************************************************
* \Syntax          : I2CStatus_t I2C_slaveSend(uint8 *data,I2CACK_t Acknowledgment,const int size);                                  
* \Description     : This function makes the slave device allow the master to read data                                   
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Nonreentrant      
* \Parameters (in) : uint8 *data -> the data buffer for Read data
					 I2CACK_t Acknowledgment -> if we want to Receive ACK or not
					 const int size -> the size of the data to be sent
                      
					  
* \Parameters (out):  non
* \Return value:   :  I2CStatus_t
*******************************************************************************/
I2CStatus_t I2C_slaveSend(uint8 *data,I2CACK_t Acknowledgment,const int size);

#endif /* I2C_H_ */
/**********************************************************************************************************************
 *  END OF FILE: I2C.c
 *********************************************************************************************************************/

