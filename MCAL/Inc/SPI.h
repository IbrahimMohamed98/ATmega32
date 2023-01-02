/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  SPI.h
 *       Module:  SPI
 *
 *  Description:  header file for SPI Module    
 *********************************************************************************************************************/


#ifndef SPI_H_
#define SPI_H_
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../../Libs/Types.h"
#include "../Inc/DIO.h"
#include "../../libs/Registers.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
                      /****SPI CONTROL****/
#define SPI_X2SPEED                 0//to Double the speed      SPI_X2SPEED = 1.
                                     //to keep the normal speed SPI_X2SPEED = 0.
								      
#define SPI_INTERRUPT_ENABLE        0//to Enable Interrupt  SPI_INTERRUPT_ENABLE = 1.
                                     //to Disable Interrupt SPI_INTERRUPT_ENABLE = 0.
								       
#define SPI_ENABLE_PIN              6//to Enable PIN of the SPI.
								    
#define SPI_MASTER                  1//to Enable SPI MASTER SPI_MASTER = 1.
                                     //to Enable SPI SLAVE  SPI_MASTER = 0.
#define SPI_MASTER_PIN              4//SPI master pin
								  
#define SPI_INTERRUPT_EN_FLAG_PIN   7//the Interrupt PIN of the SPI.

#define SPI_DATA_ORDER              0//To transfer the most significant bit first SPI_DATA_ORDER = 1
                                     //To transfer the least significant bit first SPI_DATA_ORDER = 0

//SPI pins
#define MOSI                        5
#define MISO                        6
#define SS                          4
#define SCK                         7

#define SPI_PORT                    PORT_B


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
//SPI frequency type
typedef enum{
	Freq_Div4,
	Freq_Div16,
	Freq_Div64,
	Freq_Div128
}SPIFreq_t;



/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
/******************************************************************************
* \Syntax          : void SPI_init(SPIFreq_t freq)                                  
* \Description     : This function initiate the SPI                                   
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Nonreentrant      
* \Parameters (in) : SPIFreq_t freq -> the frequency the SPI operates on 
                      
					  
* \Parameters (out):  non
* \Return value:   :  void
*******************************************************************************/
void SPI_init(SPIFreq_t freq);

/******************************************************************************
* \Syntax          : void SPI_send(uint8 msg);                                  
* \Description     : This function makes the SPI send data                                  
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Non-reentrant      
* \Parameters (in) : SPIFreq_t freq -> the frequency the SPI operates on 
                      
					  
* \Parameters (out):  non
* \Return value:   :  void
*******************************************************************************/
void SPI_send(uint8 msg);

/******************************************************************************
* \Syntax          : uint8 SPI_send(void);                                
* \Description     : This function makes the SPI receive data                                  
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Non-reentrant      
* \Parameters (in) : void 
                      
					  
* \Parameters (out):  non
* \Return value:   :  uint8
*******************************************************************************/
uint8 SPI_receive(void);
/******************************************************************************
* \Syntax          : void SPI_setCallBack(callBack_t(*ISR_Handler)(void))                               
* \Description     : This function Sets the SPI callback function for ISR                                  
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Non-reentrant      
* \Parameters (in) : callBack_t(*ISR_Handler)(void) -> a pointer to ISR Functionality
                     to deliver.
                      
					  
* \Parameters (out):  non
* \Return value:   :  void
*******************************************************************************/
void SPI_setCallBack(callBack_t(*ISR_Handler)(void));



#endif /* SPI_H_ */
/**********************************************************************************************************************
 *  END OF FILE: SPI.h
 *********************************************************************************************************************/
