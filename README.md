
# Atmega32

This repo includes the drivers needes for the Atmega32 prephirals according to the manual


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
| `SPI_init`        |  *Initiate the SPI to be either MASTER or SLAVE*     |
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
| `UART_init`                |  *Initiate the UART and configure it's attributes*   |
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
| `I2C_init`                 |  *Initiate the I2C and configure it's attributes*                           |
| `I2C_sendStart`            |  *Sends a start condition and return if it succeeded or not*                |
| `I2C_masterSend`           |  *Makes the master sends data over I2C and return if the process succeeded* |
| `I2C_masterReceive`        |  *Makes the master reads the slave data and return if the process succeeded*|
| `I2C_slaveRecieve`         |  *Makes the slave receive master data and return if the process succeeded*  |
| `I2C_slaveSend`            |  *Makes the slave sends data to master and return if the process succeeded* |

## Author

- [@IbrahimMohamed98](https://www.github.com/IbrahimMohamed98)