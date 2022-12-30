/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  DOI.h
 *       Module:  DOI
 *
 *  Description:  header file for DIO Module    
 *
 *  
 *********************************************************************************************************************/
#ifndef DIO_H_
#define DIO_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../../Libs/Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

//DIO register
#define PORT_A  ((IOPort_t *)0x39)
#define PORT_B  ((IOPort_t *)0x36)
#define PORT_C  ((IOPort_t *)0x33)
#define PORT_D  ((IOPort_t *)0x30)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
//DIO Output Value type
typedef enum{
	LOW_OUT,
	HIGH_OUT
}PinValue_t;

//DIO Direction type
typedef enum{
	IN,
	OUT
}PinDirection_t;

//DIO pins
typedef enum{
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7,
	PIN_8
}PinNum_t;

//DIO register Type
typedef struct{
	volatile uint8 IN;
	volatile uint8 DIR;
	volatile uint8 OUT;
}IOPort_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
/******************************************************************************
* \Syntax          :  void DIO_init(IOPort_t *port,PinNum_t pin,PinDirection_t direction);                                 
* \Description     :  Init a pin in a port to a specific direction either Input or output                                  
*                                                                             
* \Sync\Async      :  Asyn                                            
* \Reentrancy      :  non reentrant                                            
* \Parameters (in) :  IOPort_t *port           -> the pin port(A,B,C,or d)
                      PinNum_t pin             -> (PIN1 : PIN8)
					  PinDirection_t direction -> (IN or OUT)           
* \Parameters (out):  void                                            
* \Return value:   :  void
*******************************************************************************/
void DIO_init(IOPort_t *port,PinNum_t pin,PinDirection_t direction);

/******************************************************************************
* \Syntax          :  void DIO_setPinValue(IOPort_t *port,PinNum_t pin,PinValue_t value);                                 
* \Description     :  Set a pin in a port to a specific value either Low or High                                  
*                                                                             
* \Sync\Async      :  Asyn                                            
* \Reentrancy      :  non reentrant                                            
* \Parameters (in) :  IOPort_t *port   -> the pin port(A,B,C,or d)
                      PinNum_t pin     -> (PIN1 : PIN8)
					  PinValue_t value -> (HIGH or LOW)       
* \Parameters (out):  void                                            
* \Return value:   :  void
*******************************************************************************/
void DIO_setPinValue(IOPort_t *port,PinNum_t pin,PinValue_t value);

/******************************************************************************
* \Syntax          :  void DIO_togglePin(IOPort_t *port,PinNum_t pin);                                 
* \Description     :  Toggle a pin in a port.                                  
*                                                                             
* \Sync\Async      :  Asyn                                            
* \Reentrancy      :  non reentrant                                            
* \Parameters (in) :  IOPort_t *port   -> the pin port(A,B,C,or d)
                      PinNum_t pin     -> (PIN1 : PIN8)        
* \Parameters (out):  void                                            
* \Return value:   :  void
*******************************************************************************/
void DIO_togglePin(IOPort_t *port,PinNum_t pin);

/******************************************************************************
* \Syntax          :  PinValue_t DIO_readPin(IOPort_t *port,PinNum_t pin);                                 
* \Description     :  Returns the input of a specific Bit.                                  
*                                                                             
* \Sync\Async      :  Asyn                                            
* \Reentrancy      :  non reentrant                                            
* \Parameters (in) :  IOPort_t *port   -> the pin port(A,B,C,or d)
                      PinNum_t pin     -> (PIN1 : PIN8)        
* \Parameters (out):  void                                            
* \Return value:   :  PinValue_t
*******************************************************************************/
PinValue_t DIO_readPin(IOPort_t *port,PinNum_t pin);

#endif /* DIO_H_ */
/**********************************************************************************************************************
 *  END OF FILE: DIO.h
 *********************************************************************************************************************/
