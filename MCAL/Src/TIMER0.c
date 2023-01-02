/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  I2C.c
 *        \brief  This file include the functions that deliver I2C functionality
 *
 *      \details  - Initiation of ADC Based on preset options
 *                - Makes the ADC do conversion and return the result 
 *                - Sets the ISR call back function
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../../libs/Types.h"
#include "../../libs/BitMath.h"
#include "../../Libs/Registers.h"

#include "../Inc/TIMER0.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
callBack_t (* TIMER0_callBack)(void) = (void*) 0;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void TIMER0_init(void){
	TIMER0_SET_OUTPUT_COMPARE_MODE(TIMER0_OUTPUT_COMPARE_MODE);
	TIMER0_SET_MODE(TIMER0_MODE);
}

void TIMER0_delayUS(uint16 period){
	TIMER0_SET_MODE(TIMER0_NORMAL);//Sets the timer mode as normal mode
	TIMER0_SET_CLK_SRC(TIMER0_PRESC1);//sets the prescaler
    if (period < 256){
        TIMER0 -> COMPARE  = period;//setting the value of OCR0 to compare to
	    while(!(TIFR &(1<<TOV0)));//checking for compare match
		TIFR = 1;//clearing the over flow flag
		TIMER0 -> COMPARE = 0;//Shut down the timer
	}else{
	    TIMER0 -> COMPARE  = TIMER0_COMP_VALUE;//setting the value of OCR0 to compare to
		for (int counter = 0;counter < period;counter++)
		{
			while(!(TIFR &(1<<TOV0)));//checking for compare match
			TIFR = 1;//clearing the over flow flag
		}
		TIMER0 -> COMPARE = 0;//clearing the over flow flag
	}
}

void TIMER0_delayMS(uint16 period){
	TIMER0_SET_MODE(TIMER0_NORMAL);//Sets the timer mode as normal mode
	TIMER0_SET_CLK_SRC(TIMER0_PRESC64);//sets the prescaler
	TIMER0 -> COMPARE  = 124;//setting the value of TCNT0 to compare to
	for (int counter = 0;counter < period - (2*(period/100)) ;counter++)
	{
		while((TIFR &(1<<TOV0)) == 0);//checking for compare match
		TIFR = 1;//clearing the over flow flag
	}
	TIMER0 -> COMPARE = 0;//Shut down the timer
}

void TIMER0_pwm(uint8 dutyCycle,TIMER0clkSrc_t prescaler){
	TIMER0_SET_CLK_SRC(prescaler);//Sets the timer prescaler
	if(TIMER0_MODE == TIMER0_PWM_PHASE_CORRECT){//Check for PWM PHASE Correct mode 
		if(TIMER0_OUTPUT_COMPARE_MODE == TIMER0_SET_ON_CM){//check for inverting and non inverting
			uint8 val = (510 - ((dutyCycle*510UL)/100))/2;//calculate the value for duty cycle
			TIMER0_SET_COMPARE_VALUE(vaL);//set the value of duty cycle
		}else{
			uint8 val = (dutyCycle*510UL)/200;//calculate the value for duty cycle
			TIMER0_SET_COMPARE_VALUE(vaL);//set the value of duty cycle
		}
		
	}else if(TIMER0_MODE == TIMER0_PWM_FAST){//Check for PWM fast mode
		if(TIMER0_OUTPUT_COMPARE_MODE == TIMER0_SET_ON_CM){//check for inverting and non inverting
			uint8 val = (256 - ((dutyCycle*256UL)/100)) - 1;//calculate the value for duty cycle
			TIMER0_SET_COMPARE_VALUE(vaL);//set the value of duty cycle
		}else{
			uint8 val = ((dutyCycle*256UL)/100) - 1;//calculate the value for duty cycle
			TIMER0_SET_COMPARE_VALUE(vaL);//set the value of duty cycle
		}
	} else{
		TIMER0_SET_OUTPUT_COMPARE_MODE(TIMER0_TOGGEL_ON_CM);//sets the mode of OCR0
		uint8 val = ((dutyCycle*256UL)/100);//calculate the value for duty cycle
		TIMER0_SET_COMPARE_VALUE(vaL);//calculate the value for duty cycle
	}
}

void TIMER0_setCallBack(callBack_t (*TIMER0_isr)(void)){
	TIMER0_callBack = TIMER0_isr;
}

/**********************************************************************************************************************
 *  END OF FILE: ADC.c
 *********************************************************************************************************************/
