/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  I2C.c
 *        \brief  This file include the functions that deliver I2C functionality
 *
 *      \details  - Initiation of I2C Based on preset options
 *                - Sending data over I2C in different modes
 *                - Receiving data over I2C in different modes 
 *                
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../../libs/Types.h"
#include "../../libs/BitMath.h"

#include "../Inc/I2C.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void I2C_init(void){
	if (I2C_MODE == MASTER){
		        /*Initiate in Master mode*/
		//Set BitRate
		I2C_SET_BITRATE();
		//Set Prescaler
		I2C_SET_PRESCALER();
		//Enable I2C
		I2C_ENABLE();
		
	}else{
		        /*Initiate in Slave mode*/
		//Set slave Address
		I2C_SET_SLAVEADDRESS();
		//Enable I2C
		I2C_ENABLE();
	}
}

I2CStatus_t I2C_sendStart(){
	I2C_ENABLE();//Enable the TWEN BIT
	I2C_ENABLE_ACKNOWLDGEMENT(ACK);//Enable the TWEA BIT
	I2C_CLR_INTERRUPT();//Enable the TWINT bit
	I2C_START();//Send start condition
	I2C_WAIT_INTERRUPT();//wait for the Interrupt to happen
	if (I2C_GET_STATUS(START_ACK)||
	    I2C_GET_STATUS(REP_START_ACK))//check for Start or repeated Start condition
	{
		return I2C_ok;
	}else{
		return I2C_START_error;
	}
}


I2CStatus_t I2C_masterSend(uint8 Slave_Address,uint8 *data,I2CACK_t Acknowledgment,const int size){
	
    if (I2C_sendStart() == I2C_ok)//Check for start condition
    {
	    I2C_SEND_SLAVE_WRITE_ADDRESS(Slave_Address);//Send the slave address
	    I2C_ENABLE();//Enable the TWEN BIT
	    I2C_ENABLE_ACKNOWLDGEMENT(Acknowledgment);//Enable the TWEA BIT
	    I2C_CLR_INTERRUPT();//Enable the TWINT bit
	    I2C_WAIT_INTERRUPT();//wait for the Interrupt to happen
	    if (I2C_GET_STATUS(SLAVE_ADD_AND_WR_ACK)||
		    I2C_GET_STATUS(SLAVE_ADD_AND_WR_NACK))//Check for Either slave address Write with ACK or NACK
	    {
		    for (int charcounter = 0;charcounter<size;charcounter++)
		    {
			    I2C_SEND_DATA(data[charcounter]);
			    I2C_ENABLE();//Enable the TWEN BIT
			    I2C_CLR_INTERRUPT();//Enable the TWINT bit
			    I2C_ENABLE_ACKNOWLDGEMENT(Acknowledgment);//Enable the TWEA BIT
			    I2C_WAIT_INTERRUPT();//wait for the Interrupt to happen
			    if (I2C_GET_STATUS(WR_BYTE_ACK)||
			    I2C_GET_STATUS(WR_BYTE_NACK))//Check if data was written sucessfully and ACK or NACK received
			    {
				    
				}else{
				    return I2C_Master_Write_DATA_error;//Data has been not sent successfully
			    }
		    }
		    I2C_STOP();//Send stop condition
		    return I2C_ok;//Data has been sent successfully
		    
		}else{
		    return I2C_Master_Write_ADDRESS_error;//Wrong slave Address
	    }
	}else{
	    return I2C_START_error;//Error in start condition
    }
}

I2CStatus_t I2C_masterRecieve(uint8 Slave_Address,uint8 *data,I2CACK_t Acknowledgment,const char size){
	
	if (I2C_sendStart() == I2C_ok)//Check for start condition
	{
		 I2C_SEND_SLAVE_READ_ADDRESS(Slave_Address);//Send the slave address
		 I2C_ENABLE();//Enable the TWEN BIT
		 I2C_ENABLE_ACKNOWLDGEMENT(Acknowledgment);//Enable the TWEA BIT
		 I2C_CLR_INTERRUPT();//Enable the TWINT bit
		 I2C_WAIT_INTERRUPT();//wait for the Interrupt to happen
		 if (I2C_GET_STATUS(SLAVE_ADD_AND_RD_ACK)||
		     I2C_GET_STATUS(SLAVE_ADD_AND_RD_NACK))//Check for Either slave address Read with ACK or NACK
		 {
			 for (int charcount = 0;charcount < size;charcount++)
			 {
				I2C_ENABLE();//Enable the TWEN BIT
				I2C_ENABLE_ACKNOWLDGEMENT(Acknowledgment);//Enable the TWEA BIT
				I2C_CLR_INTERRUPT();//Enable the TWINT bit
				I2C_WAIT_INTERRUPT();//wait for the Interrupt to happen
				if (I2C_GET_STATUS(RD_BYTE_WITH_ACK)||I2C_GET_STATUS(RD_BYTE_WITH_NACK))
				{
					data[charcount] = I2C->DATA;
				}else{
					return I2C_MASTER_READ_DATA_error;//Data has not been read successfully
				}
				 
			 }
			 I2C_STOP();//Send stop condition
			 return I2C_ok;//Data has been Read successfully
			 
		 }else{
			return I2C_MASTER_READ_ADDRESS_error;//Wrong slave Address
		 }
		
	}else{
		return I2C_START_error;//Error in start condition
	}
}

I2CStatus_t I2C_slaveRecieve(uint8 *data,I2CACK_t Acknowledgment,const int size){
	I2C_ENABLE();//Enable the TWEN BIT
	I2C_ENABLE_ACKNOWLDGEMENT(Acknowledgment);//Enable the TWEA BIT
	I2C_CLR_INTERRUPT();//Enable the TWINT bit
	I2C_WAIT_INTERRUPT();//wait for the Interrupt to happen
	if (I2C_GET_STATUS(SLAVE_ADD_RCVD_WR_REQ)==1)//Check for Slave address and Write request received
	{
		for (int charcounter = 0;charcounter < size;charcounter++)
		{
			I2C_ENABLE();//Enable the TWEN BIT
			I2C_ENABLE_ACKNOWLDGEMENT(Acknowledgment);//Enable the TWEA BIT
			I2C_CLR_INTERRUPT();//Enable the TWINT bit
			I2C_WAIT_INTERRUPT();//wait for the Interrupt to happen
			if (I2C_GET_STATUS(SLAVE_DATA_RECEIVED_WITH_ACK)==1||
			    I2C_GET_STATUS(SLAVE_DATA_RECEIVED_WITH_NACK)==1)//Check for Slave data received with either ACK or NACK
			{
				data[charcounter] = I2C -> DATA;
			}
		}
		return I2C_ok;//All data has been written successfully
	}else{
		return I2C_SLAVE_ADDRESS_NOT_RECEIVED;//Slave address not received
	}
	
}
I2CStatus_t I2C_slaveSend(uint8 *data,I2CACK_t Acknowledgment,const int size){
	I2C->CONTROL = (1<<TWEN)|(1<<TWEA);
	if (I2C_GET_STATUS(SLAVE_ADD_RCVD_RD_REQ) == 1)//Check for Slave address and Read request received
	{
		for (int i = 0;i < size;i++)
		{
			I2C -> DATA = data[i];
			I2C_ENABLE();//Enable the TWEN BIT
			I2C_ENABLE_ACKNOWLDGEMENT(Acknowledgment);//Enable the TWEA BIT
			I2C_CLR_INTERRUPT();//Enable the TWINT bit
			I2C_WAIT_INTERRUPT();//wait for the Interrupt to happen
			if (I2C_GET_STATUS(SLAVE_BYTE_TRANSMITTED_WITH_ACK) != 1 &&
			    I2C_GET_STATUS(SLAVE_BYTE_TRANSMITTED_WITH_NACK) != 1)//Check for Slave data not Transmitted with either ACK or NACK
			{
				i--;
			}
		}
		return I2C_ok;//All data has been read Successfully
	}else{
		return I2C_SLAVE_ADDRESS_NOT_RECEIVED;//Slave address not received
	}
	
}
/**********************************************************************************************************************
 *  END OF FILE: I2C.c
 *********************************************************************************************************************/



