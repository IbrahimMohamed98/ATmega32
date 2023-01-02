/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ADC.h
 *       Module:  ADC
 *
 *  Description:  header file for ADC Module    
 *********************************************************************************************************************/
 
#ifndef ADC_H_
#define ADC_H_
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include <math.h>
#include "../../Libs/Types.h"
#include "../../Libs/Registers.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#define ADC_CHOOSE_CHANNEL(channel)  ADC -> MUX = (channel << MUX0)
#define ADC_ENABLE_INTERRUPT()       BIT_SET(ADC -> CONTROL,ADIE)
#define ADC_SET_PRESC(prescaler)     VAL_SET(ADC->CONTROL,prescaler,ADPS0) 
#define ADC_CHOOSE_REFERENCE(ref)    VAL_SET(ADC->CONTROL,ref,REFS0)
#define ADC_START_CONVERSION()       BIT_SET(ADC -> CONTROL,ADSC)
#define ADC_ENABLE()                 BIT_SET(ADC->CONTROL,ADEN)
#define ADC_WAIT_CONVERSION()        while(!BIT_VAL(ADC -> CONTROL,ADIF));
#define ADC_RESULT(buffer)           buffer  = (ADC -> DATALOW);\
                                     buffer |= ((ADC -> DATALOW) <<8);
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
typedef enum{
	ADC_INTERRUPT_DISABLE,
	ADC_INTERRUPT_ENABLE
}ADCInterrupt_t;
typedef enum{
	ADC_AREF,
	ADC_AVCC_WITH_EXTERNAL_CAPACITOR,
	ADC_INTERNAL_WITH_CAPACITOR_AT_AREF
}ADCVref_t;
typedef enum{
	CHANNEL0,
	CHANNEL1,
	CHANNEL2,
	CHANNEL3,
	CHANNEL4,
	CHANNEL5,
	CHANNEL6,
	CHANNEL7
}ADCChannel_t;
typedef enum{
	DIV2= 1,
	DIV4,
	DIV8,
	DIV16,
	DIV32,
	DIV64,
	DIV128
}ADCPresc_t;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
/******************************************************************************
* \Syntax          : void ADC_initChanel(ADCPresc_t prescaler,ADCChannel_t channel,ADCVref_t ref)                                
* \Description     : This function initiate the ADC specific channel                                   
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Nonreentrant      
* \Parameters (in) : ADCPresc_t prescaler-> the prescaler of the ADC
                     ADCChannel_t channel-> the channel we want to Enable
					 ADCVref_t ref -> the reference we want
					 ADCInterrupt_t interrupt -> enable or disables the ADC interrupt
                      
					  
* \Parameters (out):  non
* \Return value:   :  void
*******************************************************************************/
void ADC_initChanel(ADCPresc_t prescaler,ADCChannel_t channel,ADCVref_t ref,ADCInterrupt_t interrupt);
/******************************************************************************
* \Syntax          : void ADC_doConversion();                                 
* \Description     : This function return the ADC conversion result                                   
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Nonreentrant      
* \Parameters (in) : void
                      
					  
* \Parameters (out):  non
* \Return value:   :  uint16
*******************************************************************************/
uint16 ADC_doConversion(void);
/******************************************************************************
* \Syntax          : void ADC_setCallBack(callBack_t (*callBack)(void))                                 
* \Description     : This function sets the ISR callback function                                   
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Nonreentrant      
* \Parameters (in) : callBack_t (*callBack)(void) -> The function to set for callback
                      
					  
* \Parameters (out):  non
* \Return value:   :  void
*******************************************************************************/
void ADC_setCallBack(callBack_t (*callBack)(void));
#endif /* ADC_H_ */
/**********************************************************************************************************************
 *  END OF FILE: ADC.h
 *********************************************************************************************************************/
