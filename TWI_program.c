/***********************************************************************************/
/*************   			  Name :    IS   	    ************************/
/*************   			  Date : 	12/09/2022	  	    ************************/  
/*************   		 	   SWC :	 TWI		 	    ************************/     
/*************   		   Version :     1.0  			    ************************/    
/***********************************************************************************/  
#include "../../../LIB/STD_TYPES.h"
#include "../../../LIB/BIT_MATH.h"


#include "../Header/TWI_interface.h"
#include "../Header/TWI_config.h"
#include "../Header/TWI_private.h"



void TWI_voidMasterInit(void)
{
	/* set prescaler Value */
	CLR_BIT(TWI_u8_TWSR_REG,1);
	CLR_BIT(TWI_u8_TWSR_REG,0);
	
	/* Set TWBR Value => 200KHZ */
	TWI_u8_TWBR_REG = 12;
	/* Enable ACK */
	SET_BIT(TWI_u8_TWCR_REG,6);
	/* Enable TWI */
	SET_BIT(TWI_u8_TWCR_REG,2);
	
}
u8   TWI_u8SlaveInit(u8 Copy_u8SlaveAddress)
{
	u8 Local_u8ErrorStatus = STD_TYPES_OK;
	/* Set Slave Address in TWAR Register */
	TWI_u8_TWAR_REG = Copy_u8SlaveAddress << 1;
	/* Enable ACK */
	SET_BIT(TWI_u8_TWCR_REG,6);
	/* Enable TWI */
	SET_BIT(TWI_u8_TWCR_REG,2);
	
	return Local_u8ErrorStatus ;
}

TWI_ErrorState   TWI_enuSendStartCondition(void)
{
	TWI_ErrorState Local_enuErrorStatus = TWI_OK;
	/* Send Start Condition */
	SET_BIT(TWI_u8_TWCR_REG,5);
	/* Clear Flag */
    SET_BIT(TWI_u8_TWCR_REG,7);
	/* wait for the Flag to be set */
	while(!GET_BIT(TWI_u8_TWCR_REG,7));
	/* Check ACK => START CONDITION */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x08)
	{
		Local_enuErrorStatus = TWI_SC_ERROR;
	}
	return Local_enuErrorStatus ;
}

TWI_ErrorState   TWI_enuSendReStartCondition(void)
{
	TWI_ErrorState Local_enuErrorStatus = TWI_OK;
	/* Send Start Condition */
	SET_BIT(TWI_u8_TWCR_REG,5);
	/* Clear Flag */
    SET_BIT(TWI_u8_TWCR_REG,7);
	/* wait for the Flag to be set */
	while(!GET_BIT(TWI_u8_TWCR_REG,7));
	/* Check ACK => REPEATED START CONDITION */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x10)
	{
		Local_enuErrorStatus = TWI_RSC_ERROR;
	}
	return Local_enuErrorStatus ;


}

TWI_ErrorState   TWI_enuSendSlaveWithWrite(u8 Copy_u8SlaveAddress)
{
	TWI_ErrorState Local_enuErrorStatus = TWI_OK;
	/* Set TWDR = SLA + W */
	TWI_u8_TWDR_REG = Copy_u8SlaveAddress << 1;
	CLR_BIT(TWI_u8_TWDR_REG,0);
	/* Clear Start Condition */
	CLR_BIT(TWI_u8_TWCR_REG,5);
	/* Clear Flag */
    SET_BIT(TWI_u8_TWCR_REG,7);
	/* wait for the Flag to be set */
	while(!GET_BIT(TWI_u8_TWCR_REG,7));
	/* Check ACK => SLAVE ADDRESS + W */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x18)
	{
		Local_enuErrorStatus = TWI_SLA_W_ERROR;
	}
	return Local_enuErrorStatus ;
	
	
}

TWI_ErrorState   TWI_enuSendSlaveWithRead(u8 Copy_u8SlaveAddress)
{
	TWI_ErrorState Local_enuErrorStatus = TWI_OK;
	/* Set TWDR = SLA + R */
	TWI_u8_TWDR_REG = Copy_u8SlaveAddress << 1;
	SET_BIT(TWI_u8_TWDR_REG,0);
	
	/* Clear Start Condition */
	CLR_BIT(TWI_u8_TWCR_REG,5);
	/* Clear Flag */
    SET_BIT(TWI_u8_TWCR_REG,7);
	/* wait for the Flag to be set */
	while(!GET_BIT(TWI_u8_TWCR_REG,7));
	/* Check ACK => SLAVE ADDRESS + R */
	if((TWI_u8_TWSR_REG & 0xF8) != 0x40)
	{
		Local_enuErrorStatus = TWI_SLA_R_ERROR;
	}
	return Local_enuErrorStatus ;
}

TWI_ErrorState   TWI_enuSendDataByte(u8 Copy_u8SendData)
{
	TWI_ErrorState Local_enuErrorStatus = TWI_OK;
	/* Set TWDR = DATA */
	TWI_u8_TWDR_REG = Copy_u8SendData;
	
	/* Clear Flag */
    SET_BIT(TWI_u8_TWCR_REG,7);
	/* wait for the Flag to be set */
	while(!GET_BIT(TWI_u8_TWCR_REG,7));
	
	/* Check ACK => Write Data*/
	if((TWI_u8_TWSR_REG & 0xF8) != 0x28)
	{
		Local_enuErrorStatus = TWI_DATA_W_ERROR;
	}
	return Local_enuErrorStatus ;
	
}

TWI_ErrorState  TWI_enuReceiveDataByte(u8 *Copy_pu8ReceivedData)
{
	TWI_ErrorState Local_enuErrorStatus = TWI_OK;
	/* Check Pointer */
	if(Copy_pu8ReceivedData != NULL)
	{
		/* Clear Flag */
		SET_BIT(TWI_u8_TWCR_REG,7);
		/* wait for the Flag to be set */
		while(!GET_BIT(TWI_u8_TWCR_REG,7));
		/* Check ACK => Read Data*/
		if((TWI_u8_TWSR_REG & 0xF8) != 0x50)
		{
			Local_enuErrorStatus = TWI_DATA_R_ERROR;
		}
		else
		{
			/* Read Data */
			*Copy_pu8ReceivedData = TWI_u8_TWDR_REG;
		}
	}
	else
	{
		Local_enuErrorStatus = TWI_NULL_POINTER;
	}
	return Local_enuErrorStatus;
	
}

void   TWI_voidSendStopCondition(void)
{
	/* Send Stop Condition */
	SET_BIT(TWI_u8_TWCR_REG,4);
	
	/* Clear Flag */
	SET_BIT(TWI_u8_TWCR_REG,7);
}
