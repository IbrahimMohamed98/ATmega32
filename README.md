
# Atmega32

-This repo includes the drivers needes for the Atmega32 prephirals according to the manual
-The repo include 3 parts  -> 
                                - Libs (BitMath.h , Registers.h , Types.h)
                                - Src  (Which includes the drivers source files)
                                - Inc  (Which includes the drivers header files)

## Repo content 
   The repo contain the following drivers

    *DIO
    *UART
    *SPI
    *I2C
    *ADC
    *TIMERS
    





## API Reference

#### DIO module

```http
header -> MCAL/Inc/DIO.h
source -> MCAL/Src/DIO.c
```

| Function    |  Description                                         |
| :--------   |  :---------------------------------------------------|
| `DIO_init`  |  *Initiate certain pin to be either output or input* |
| `DIO_write` |  *make a certain pin to be either HIGH or LOW output*|
| `DIO_read`  |  *Reads a certain pin logic level either HIGH or LOW*|
| `DIO_toggel`|  *Toggels a certain pin logic*                       |

#### SPI module

```http
header -> MCAL/Inc/SPI.h
source -> MCAL/Src/SPI.c
```

| Function          |  Description                                         |
| :--------         |  :---------------------------------------------------|
| `SPI_init`        |  *Initiate  SPI to be either MASTER or SLAVE*     |
| `SPI_send`        |  *Sends a Byte over SPI*                             |
| `SPI_receive`     |  *Recieve a Byte over SPI*                           |
| `SPI_setCallBack` |  *Sets the SPI ISR functionality*                    |

#### UART module

```http
header -> MCAL/Inc/UART.h
source -> MCAL/Src/UART.c
```

| Function                   |  Description                                         |
| :--------                  |  :---------------------------------------------------|
| `UART_init`                |  *Initiate  UART and configure it's attributes*   |
| `UART_send`                |  *Sends a Byte over UART*                            |
| `UART_receive`             |  *Recieve a Byte over UART*                          |
| `UART_setReceiveCallBack`  |  *Sets the UART receive ISR functionality*           |
| `UART_setSendCallBack`     |  *Sets the SPI send ISR functionality*               |

#### I2C module

```http
header -> MCAL/Inc/I2C.h
source -> MCAL/Src/I2C.c
```

| Function                   |  Description                                                                |
| :--------                  |  :--------------------------------------------------------------------------|
| `I2C_init`                 |  *Initiate  I2C and configure it's attributes*                           |
| `I2C_sendStart`            |  *Sends a start condition and return if it succeeded or not*                |
| `I2C_masterSend`           |  *Makes the master sends data over I2C and return if the process succeeded* |
| `I2C_masterReceive`        |  *Makes the master reads the slave data and return if the process succeeded*|
| `I2C_slaveRecieve`         |  *Makes the slave receive master data and return if the process succeeded*  |
| `I2C_slaveSend`            |  *Makes the slave sends data to master and return if the process succeeded* |


#### ADC module

```http
header -> MCAL/Inc/ADC.h
source -> MCAL/Src/ADC.c
```

| Function             |  Description                                                 |
| :--------------------|  :-----------------------------------------------------------|
| `ADC_initChanel`     |  *Initiate a certain ADC channel to a certain cofigurations* |
| `ADC_doConversion`   |  *Makes ADC do conversion and return the result*             |
| `ADC_setCallBack`    |  *Sets the adc call back function for ISR*                   |


#### TIMER0 module

```http
header -> MCAL/Inc/TIMER0.h
source -> MCAL/Src/TIMER0.c
```

| Function             |  Description                                         |
| :--------            |  :---------------------------------------------------|
| `TIMER0_init`        |  *Initiate TIMER0 and configure it's attributes*     |
| `TIMER0_delayUS`     |  *Makes a system delay of micro seconds*             |
| `TIMER0_delayMS`     |  *Makes a system delay of milli seconds*             |
| `TIMER0_pwm`         |  *Allow you to make pwm signals*                     |
| `TIMER0_setCallBack` |  *Sets the timer callBack function for ISR *         |


## Author

- [@IbrahimMohamed98](https://www.github.com/IbrahimMohamed98)
