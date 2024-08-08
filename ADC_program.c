/***********************************************************************************/
/*************   			  Name :    ISRAA SALAH 	    ************************/
/*************   			  Date : 	29/08/2022	  	    ************************/
/*************   		 	   SWC :	 LCD		 	    ************************/
/*************   		   Version :     1.0  			    ************************/
/***********************************************************************************/

/* include LIB */
#include "../../../LIB/STD_TYPES.h"
#include "../../../LIB/BIT_MATH.h"

#define F_CPU  8000000UL
#include <util/delay.h>

/* MCAL  */
#include "../Header/ADC_private.h"
#include "../Header/ADC_interface.h"
#include "../Header/ADC_config.h"

/*****************************************ADC_INITALIZATION*****************************************************/
void ADC_INIT(void)
{

	/* 1--SELECTING_VOLTAGE_REFERENCE */
    /* 1- clear ADMUX_VOLTAGE_SELECT_ bits
     * 2- SELECT VOLTAGE_REFERENCE     */

	ADMUX_REG  &=   ADC_VOLTAGE_CLEAR_ADMUX_REG ;
	ADMUX_REG  |=   ADC_VOLTAGE ;

	/*SELECTING ADC_MODE */

    #if ADC_MODE == ADC_MODE_AUTO_TRIGGER
	SET_BIT(ADCSRA_REG,5);

    #elif ADC_MODE == ADC_MODE_SINGLE_CONVERSION
	CLR_BIT(ADCSRA_REG,5);

    #endif

	/* 2--SELECTING_AUTO_TRIGGER_MODE*/
	/* 1- clear ADMUX_VOLTAGE_SELECT_ bits
     SELECT_AUTO_TRIGGER_MODE

	SFIOR_REG &= ADC_AUTO_TRIGGER_CLEAR_SFIOR ;
	SFIOR_REG |= ADC_AUTO_TRIGGER_MODE;

    */

	/* 3- SELECT_ADJUSTMENT */

    #if   ADC_RESULT_MODE == ADC_RIGHT_ADJUSTED
	CLR_BIT(ADMUX_REG,5);

    #elif ADC_RESULT_MODE == ADC_LEFT_ADJUSTED
	SET_BIT(ADMUX_REG,5);

    #endif

	/* 4-- CLOCK /64   */

    #if ADC_PRESCALAR == ADC_PRESCALAR_64
	{
	ADCSRA_REG        &= ADC_PRESCALAR_CLEAR_ADSRA ;
	ADCSRA_REG		  |= ADC_PRESCALAR_64 ;
	}
    #endif

	/*clear interrupt flag*/
	SET_BIT(ADCSRA_REG,4);

	/*ENABLE_ADC*/
	SET_BIT(ADCSRA_REG,7);

}

/*****************************************ADC_GET_RESULT*****************************************************/

u8 GET_ADC_RESULT(u16 * Copy_pu16DigitalValue)
{

	u8 Local_u8ErrorState = STD_TYPES_OK;
	if((Copy_pu16DigitalValue != NULL))
    {

	/*take result after conversion is completed flag is 1 */
	while(!GET_BIT(ADCSRA_REG,4));
	*Copy_pu16DigitalValue =  ADCLH_REG ;
	/* ---------------- clear Flag  >>>>> */SET_BIT(ADCSRA_REG,4);  /* <<<<<--------------------*/

    }

	else
	{
	   Local_u8ErrorState = STD_TYPES_NOK;
	}

	   return Local_u8ErrorState;
}


/*****************************************ADC_START_CONVERSION*****************************************************/

u8 ADC_START_CONVERSION (u8 copy_u8Adc_Channel)//0b00000000
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(copy_u8Adc_Channel <32)
	{

	/*SELECT ADC_CHANNEL */
	/*Clear  ANDMUX_REG_FIVE_BITS_FOR_CHANNEL
	 *SELECT ACD_CHANNEL */

	ADMUX_REG &= ADC_CHANNEL_CLEAR_ADMUX ;
	/* ------------------ >>> */	ADMUX_REG |= copy_u8Adc_Channel;   /* <<<------------------ */
                                    //0b010
	/*START_CONVERSION*/
	SET_BIT(ADCSRA_REG,6);

	}

	else
	{
	    Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}
