/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  TIMER0.h
 *       Module:  TIMER0
 *
 *  Description:  header file for TIMER0 Module    
 *********************************************************************************************************************/
#ifndef TIMER0_H_
#define TIMER0_H_


/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include <math.h>
#include "../../Libs/Types.h"
#include "../../Libs/Registers.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define TIMER0_CLK_SRC                TIMER0_PRESC1
#define TIMER0_PRESCALER_VALUE        TIMER0_PRESC_OF_1
#define TIMER0_FREQUENCY              1000000UL
#define TIMER0_COMP_VALUE             ceil((F_CPU/(2*TIMER0_PRESCALER_VALUE))/TIMER0_FREQUENCY) - 1
#define TIMER0_MODE                   TIMER0_NORMAL
#define TIMER0_OUTPUT_COMPARE_MODE    TIMER0_NON_ON_CM

                      
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#define TIMER0_SET_MODE(mode)                 TIMER0 -> CONTROL = (TIMER0 -> CONTROL & 0xB7)| (mode&0x48)
#define TIMER0_SET_CLK_SRC(clkSrc)            VAL_SET(TIMER0 -> CONTROL,clkSrc,CS00)
#define TIMER0_SET_OUTPUT_COMPARE_MODE(out)   TIMER0 -> CONTROL =(TIMER0 -> CONTROL & 0xCF)|(out<<COM00)
#define TIMER0_SET_COMPARE_VALUE(vaL)         TIMER0->COMPARE = val              
/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
//output modes
typedef enum{
	TIMER0_NON_ON_CM  = 0,
	TIMER0_TOGGEL_ON_CM = 1,
	TIMER0_CLEAR_ON_CM = 2,
	TIMER0_SET_ON_CM = 3
}TIMER0OCmode_t;

typedef enum{
	TIMER0_PRESC_OF_1 = 1,
	TIMER0_PRESC_OF_8 = 8,
	TIMER0_PRESC_OF_64 = 64,
	TIMER0_PRESC_OF_265 = 256,
	TIMER0_PRESC_OF_1024 = 1024,
}PRESCALERvalue_t;
//Clock sources
typedef enum{
	TIMER0_STOPPED,
	TIMER0_PRESC1,
	TIMER0_PRESC8,
	TIMER0_PRESC64,
    TIMER0_PRESC256,
	TIMER0_PRESC1024,
	TIMER0_T0_FALLING,
	TIMER0_T0_RISING
}TIMER0clkSrc_t;
//Timer modes
typedef enum{
	TIMER0_NORMAL,
	TIMER0_CLEAR_ON_COMPARE = 0x08,
	TIMER0_PWM_PHASE_CORRECT = 0x40,
	TIMER0_PWM_FAST = 0x48
}TIMER0Mode_t;


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/******************************************************************************
* \Syntax          : void TIMER0_init(void)                                
* \Description     : This function initiate the Timer                                    
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Nonreentrant      
* \Parameters (in) : void 
					  
* \Parameters (out):  non
* \Return value:   :  void
*******************************************************************************/
void TIMER0_init(void);
/******************************************************************************
* \Syntax          : void TIMER0_delayUS(uint16 period)                                
* \Description     : This function allow the timer to make a delay of microseconds                                   
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Nonreentrant      
* \Parameters (in) : uint16 period -> the delay period          
					  
* \Parameters (out):  non
* \Return value:   :  void
*******************************************************************************/
void TIMER0_delayUS(uint16 period);
/******************************************************************************
* \Syntax          : void TIMER0_delayMS(uint16 period)                                
* \Description     : This function allow the timer to make a delay of milliseconds                                   
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Nonreentrant      
* \Parameters (in) : uint16 period -> the delay period 
					  
* \Parameters (out):  non
* \Return value:   :  void
*******************************************************************************/
void TIMER0_delayMS(uint16 period);
/******************************************************************************
* \Syntax          : void TIMER0_pwm(uint8 dutyCycle,TIMER0clkSrc_t prescaler)                                
* \Description     : This function Allow timer zero to deliver PWM signals                                   
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Nonreentrant      
* \Parameters (in) : uint8 dutyCycle -> the pwm duty cylcle
                     TIMER0clkSrc_t prescaler -> timer clock source prescaler 
					  
* \Parameters (out):  non
* \Return value:   :  void
*******************************************************************************/
void TIMER0_pwm(uint8 dutyCycle,TIMER0clkSrc_t prescaler);
/******************************************************************************
* \Syntax          : void TIMER0_setCallBack(callBack_t (*TIMER0_isr)(void));                                
* \Description     : This function initiate the ADC specific channel                                   
*                                                                             
* \Sync\Async      : Sync                                             
* \Reentrancy      : Nonreentrant      
* \Parameters (in) : callBack_t (*TIMER0_isr)(void)-> The isr callback function 
					  
* \Parameters (out):  non
* \Return value:   :  void
*******************************************************************************/
void TIMER0_setCallBack(callBack_t (*TIMER0_isr)(void));
#endif /* TIMER0_H_ */
/**********************************************************************************************************************
 *  END OF FILE: ADC.h
 *********************************************************************************************************************/
