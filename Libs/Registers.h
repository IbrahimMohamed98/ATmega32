/******************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------*/
/**         \file   Registers.h
 *         \brief   Macros used for Bit Manipulation.
 *         
 *       \details   -
 *****************************************************************************/

#ifndef REGISTERS_H_
#define REGISTERS_H_
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
//DIO
#define PORT_A  ((IOPort_t *)0x39)
#define PORT_B  ((IOPort_t *)0x36)
#define PORT_C  ((IOPort_t *)0x33)
#define PORT_D  ((IOPort_t *)0x30)

//I2C
#define I2C ((volatile I2C_t*)0x20)
//SPI 
#define SPI                         ((SPI_t*)0x2D)
//ADC
#define ADC ((volatile ADC_t*)0x24)
//UART
#define UART            ((UART_t *)0x29)
//TIMER0 
#define TIMER0      ((volatile TIMER0_t*)0x52)
//TIMER interrupt flags
#define TIFR        *((volatile uint8*)0x58)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
//DIO register Type
typedef struct{
	volatile uint8 IN;
	volatile uint8 DIR;
	volatile uint8 OUT;
}IOPort_t;

//I2C
typedef enum{
	TWIE,
	TWEN = 2,
	TWWC,
	TWSTO,
	TWSTA,
	TWEA,
	TWINT
}I2CControl_t;
//I2C Registers
typedef struct{
	volatile uint8 BITRATE;
	volatile uint8 STATUS;
	volatile uint8 ADDRESS;
	volatile uint8 DATA;
	volatile uint8 RESERVED[50];
	volatile uint8 CONTROL;
}I2C_t;
//SPI 
typedef struct{
	volatile uint8 CONTROL;
	volatile uint8 STATUS;
	volatile uint8 DATA;
}SPI_t;
//ADC
typedef enum{
	ADPS0,
	ADPS1,
	ADPS2,
	ADIE,
	ADIF,
	ADATE,
	ADSC,
	ADEN
}ADCControl_t;
typedef enum{
	MUX0,
	MUX1,
	MUX2,
	MUX3,
	MUX4,
	ADLAR,
	REFS0,
	REFS1
}ADCMux_t;

typedef struct{
	volatile uint8 DATAHIGH;
	volatile uint8 DATALOW;
	volatile uint8 CONTROL;
	volatile uint8 MUX;
	
}ADC_t;
//UART
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
typedef struct{
	volatile char BAUDL;
	volatile char CONTROL_B;
	volatile char CONTROL_A;
	volatile char DATA;
	volatile char RESERVED[19];
	volatile char CONTROL_C;
}UART_t;

//Timer0 
typedef enum{
	CS00,
	CS01,
	CS02,
	WGM01,
	COM00,
	COM01,
	WGM00,
	FOC0
}TIMER0Control_t;

typedef struct{
	volatile uint8 COUNTER;
	volatile uint8 CONTROL;
	volatile uint8 reserved[8];
	volatile uint8 COMPARE;
}TIMER0_t;
//TIMERS interrupt flag
typedef enum{
	TOV0,
	OCF0,
	TOV1,
	OCF1B,
	OCF1A,
	ICF1,
	TOV2,
	OCF2
}TIMERInterrupt_t;
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif /* REGISTERS_H_ */
/**********************************************************************************************************************
 *  END OF FILE: Types.h
 *********************************************************************************************************************/
