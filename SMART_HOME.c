/*****************************************************************************************************************************/
/*************   			  Name :   NAYERA RAMADAN & ISRAA SALAH **********************************************************/
/*************   			  Date :   21/09/2022	  	            **********************************************************/
/*************   		 	   SWC :   APP"Smart_Home		 	    **********************************************************/
/*************   		   Version :   1.0  			            **********************************************************/
/*****************************************************************************************************************************/

/******************************************************* LIB layer ***********************************************************/
#include "../../../LIB/STD_TYPES.h"
#include "../../../LIB/BIT_MATH.h"

#define F_CPU  8000000UL
#include <util/delay.h>

/******************************************************* MCAL ****************************************************************/
/****************************** ADC *********************************/
#include "../../../MCAL/ADC/Header/ADC_interface.h"
/****************************** TIMER *******************************/
#include "../../../MCAL/TIMER/Header/Timer_interface.h"

/******************************************************* HAL *****************************************************************/
/****************************** LCD *********************************/
#include "../../../HAL/LCD/Header/LCD_interface.h"
/****************************** KEY_PAD *****************************/
#include "../../../HAL/Keypad/Header/Keypad_interface.h"
/****************************** SERVO_MOTOR**************************/
#include "../../../HAL/SERVO_MOTOR/SERVO_interface.h"
/****************************** LED *********************************/
#include "../../../HAL/LED/Header/LED_interface.h"

/******************************************************* APP *****************************************************************/
#include "../Header/SMART_HOME.h"
/******************************************************* GLOBAL_VARIABLES ****************************************************/
	 u8   Global_u8value ;
	 u8   Global_u8_number;

/******************************************************* SMART_INSIDE ********************************************************/
void Smart_voidInside(void)
{
	   SmartHome_voidDirections();
	   SmartHome_voidINIT();

	   while(1)
	   {
	   SmartHome_voidLIGHT_LED();
	   SmartHome_voidTemperature_Fan();
	   }
}
/******************************************************* SMART_OUTSIDE *******************************************************/
void Smart_voidOutside(void)
{
	while(1)
	{
	SmartHome_voidOpenDoor();
	}
}
/******************************************************FUNCTIONS_IMPLEMENTATIONS *********************************************/
/* SET_DIERECTTIONS_TO_PINS */
void SmartHome_voidDirections(void)
{
	/* ADC_CHANNEL0_PIN " LDR_SENSOR " AS_INPUT */
	DIO_u8SetPinDirection	(ADC_CHANNEL0_PORT , ADC_CHANNEL0_PIN , DIO_u8_INPUT);
	DIO_u8SetPinDirection	(ADC_CHANNEL1_PORT , ADC_CHANNEL1_PIN , DIO_u8_INPUT);

	/* LED1_PIN  AS_OUTPUT */
	INITLED_void	(LED1_PORT , LED1_PIN);
	/* LED2_PIN  AS_OUTPUT */
	INITLED_void	(LED2_PORT , LED2_PIN);
	/* LED2_PIN  AS_OUTPUT */
	INITLED_void	(LED3_PORT , LED3_PIN);

	/* SET_LOW_AS_INITAL_VALUE */
    LED_OFF_void(LED1_PORT , LED1_PIN);
    LED_OFF_void(LED2_PORT , LED2_PIN);
    LED_OFF_void(LED3_PORT , LED3_PIN);

	/* OC_PIN_AS_OUTPUT "DC_MOTOR */
	DIO_u8SetPinDirection	(DC_MOTOR_PORT , DC_MOTOR_PIN , DIO_u8_OUTPUT);
}
/***********************************************SmartHome_INIT_FUNC**********************************************************/
void SmartHome_voidINIT(void)
{
	 /* STEP_ONE : MEASURE_LIGHT_AT_HOME_USING_LDR_SENSOR */

	 /*  ADC_INITALIZATION */
	 ADC_INIT();

     /*  LCD_INITALIZATION */
	 LCD_voidInit();

	 /*  CURSOR_OFF */
	 LCD_voidSendCmd(0b00001100);
	 _delay_ms(1);


	 /* START "TIMER 0 " IN_FAST_PWM_MODE_FOR_DC_MOTOR */
	 TMR_voidTimer0Init_PWM(TIM_FAST_PWM_MODE,NON_INVERTING_MODE);

	 /* KEYPAD_INITALIZATION */
	 KPD_INIT();

}
/*****************************************************************************************************************************/
/***********************************************SmartHome_OPEN_DOOR_FUNC******************************************************/
/* USE_LOGIN_SYSTEM_TO_OPEN_DOOR */
void SmartHome_voidOpenDoor(void)
{
	 /* SERVO_PIN "OC1A" AS_ OUTPUT */
	 DIO_u8SetPinDirection	(SERVO_PORT , SERVO_PIN , DIO_u8_OUTPUT);

	 /* LCD & KEYPAD INITALIZATION */
	 LCD_voidInit();
	 KPD_INIT();


	 /*  START "TIMER 1 " IN_FAST_PWM_MODE_ICR_TOP_FOR_SERVO */
	 TMR1_INIT_FAST_PWMMODE_ICRTOP();

	 /* STEP_ONE : TAKE_PASSWORD_FOR_ENTER */
	 /* LOCAL_VARIABLIES */
	 //u8   Local_u8value ;
	 u16  Local_u16Number = 0;
	 u8   Local_u8count = 0;
	 u16  Local_u16Pass = 0;

	 /* LCD_INTERFACE */
	 LCD_void_writestring ("ENTER PASS:",0,1);
	 LCD_voidGoToXY(1,0);

	 /*********GET_PASS_FOM_KEYPAD***************************/
     while(1)
     {
        /* GET_ONE_CHAR */
 		KPD_u8GetKey(&Global_u8value);
 		if(Global_u8value != KPD_NOT_PRESSED)
 		{

 	        /* SWITCH_FOR_ENTERED_DIGIT */
			switch(Global_u8value)
			{
			/**********PASS_IS_ENTERD_COMPLETELY*************/
	        /**********PRESSING_KEY_AFYER_ENTERING***********/
			case 'O':
				Local_u16Pass = Local_u16Number ;
				/***********THREE_TIMES_FOR_TRY**************/
				while(Local_u8count<=2)
				{
					if(Local_u16Pass != 123 && Local_u8count != 2)
					{

				      /* CLEAR_LCD */
				      LCD_voidClear();
				      /* TYR_AGAIN */
				      LCD_void_writestring ("TRY AGAIN :",0,1);
				      /* PASS_IN_SECOND_LINE */
				      LCD_voidGoToXY(1,0);
				      /* COUNT_FOR_ANOTHER_TRY */
				      Local_u8count++;
				      /* TAKA_A_NEW_PASS */
				      Local_u16Number=0;
				      /* BREAK_WHILE */
				      break;

					}
					  /* THREE_TRIES_IS_USED */
					  else if (Local_u16Pass != 123 && Local_u8count == 2)
					  {
					  	LCD_voidClear();
					  	/* DOOR_WILL_NOT_BE_OPENED */
					  	LCD_void_writestring ("NO MORE TRIES ",0,1);
					  	break;
					  }
					  else
					{

						LCD_voidClear();
						/* DISPLAY_WELCOME_MESSAGE */
						LCD_void_writestring ("WELCOME :",1,0);
						/* ROTATE_SERVO_MOTOR_90_ */
						SERVO_ROTATE(90);
						/* BREAK_WHILE"TRIES" */
						break;
						/* BREAK_WHILE"PASS"  */
						break;

					}
		    }
			/* BREAK_CASE_'O' */
		    break;

		    /* DEFAULT_CASE"PASS_IS_NOT_COMPLETED */
		    /* TAKE_ANOTHER_DIGIT */
		    default :

		    /* DISPLAY_*_FOR_DIGIT */
		    LCD_voidSendChar('*');

		    Keypad_u8Convert_number();
		    Local_u16Number = Local_u16Number*10 + Global_u8_number;
		    /* BREAK_DEFAULT_CASE */
		    break;
			}
	   }
   }

}
/***********************************************SmartHome_OPEN_DOOR_FUNC******************************************************/
void Keypad_u8Convert_number(void)
{
	switch ( Global_u8value)

	{
	case '1' :
		Global_u8_number = 1 ;
		break;

	case '2' :
		Global_u8_number = 2 ;
		break;

	case '3' :
		Global_u8_number = 3 ;
		break;

	case '4' :
		Global_u8_number = 4 ;
		break;

	case '5' :
		Global_u8_number = 5 ;
		break;

	case '6' :
		Global_u8_number = 6 ;
		break;

	case '7' :
		Global_u8_number = 7 ;
		break;

	case '8' :
		Global_u8_number = 8 ;
		break;

	case '9' :
		Global_u8_number = 9 ;
		break;
	}
}
/******************************************************************************************************************************/
/******************************************************************************************************************************/
/***********************************************SmartHome_voidLIGHT_LED_FUNC***************************************************/
/* USE_LDR_SENSOR_TO_CONTROL_LIGHT */
void SmartHome_voidLIGHT_LED(void)

{

	/*  DEFINE_VARIABLES */
	u16 Local_u16DigitalValue , Local_u16AnalogValue;

	/* ADC_START_SINGLE_CONVERSION */
    ADC_START_CONVERSION(ADC_CHANNEL_ADC0_);

    /* READ_ANALOG_VALUE */
    GET_ADC_RESULT(&Local_u16DigitalValue);
    Local_u16AnalogValue = (u16)((Local_u16DigitalValue * 5000UL) /1024) ;

    /* STEP_TWO  : TAKE_AN_ACTION */

    /*********************STATE_ONE "EVENING "**************************/
    if(Local_u16AnalogValue >= 3000)
    {

   	    /* DISPLAY_AT_LCD */
    	LCD_void_writestring("GOOD  EVENING",0,0);

    	/* TURN_ON_ALL_LEDS */
    	LED_ON_void(LED1_PORT , LED1_PIN);
    	LED_ON_void(LED2_PORT , LED2_PIN);
    	LED_ON_void(LED3_PORT , LED3_PIN);

    }
    /**********************STATE_TWO "AFTERNOON "***********************/
    else if (Local_u16AnalogValue < 3000  && Local_u16AnalogValue > 1500)

    {
    	LCD_void_writestring("GOOD AFTERNOON",0,0);
    	/* TURN_ON_ONLY_TWO_LEDS_ */
    	LED_ON_void(LED1_PORT , LED1_PIN);
    	LED_ON_void(LED2_PORT , LED2_PIN);
        LED_OFF_void(LED3_PORT , LED3_PIN);

    }
    /**********************STATE_THREE " MORNING "**********************/
    else

    {
    	LCD_void_writestring("GOOD  MORNINNG",0,0);
    	/* TURN_ON_ONLY_ONE_LEDS_ */

     	LED_ON_void(LED1_PORT , LED1_PIN);
        LED_OFF_void(LED2_PORT , LED2_PIN);
        LED_OFF_void(LED3_PORT , LED3_PIN);

    }
    /*******************************************************************/
}
/***********************************************SmartHome_voidTemperature_Fan_FUNC******************************************************/
/* USE_TEMP_SENSOR_TO_CONTROL_FAN */
void SmartHome_voidTemperature_Fan(void)
{

	/*  DEFINE_VARIABLES */
	u16 Local_u16DigitalValue , Local_u16AnalogValue;
	u8  Local_u8Temperature ;
    u8  Local_u8OCRValue = 0;

	/* ADC_START_SINGLE_CONVERSION */
    ADC_START_CONVERSION(ADC_CHANNEL_ADC1_);

    /* READ_ANALOG_VALUE */
    GET_ADC_RESULT(&Local_u16DigitalValue);
    Local_u16AnalogValue = (u16)((Local_u16DigitalValue * 5000UL) /1024) ;

    /* MEASURE_TEMPERATURE */
    /* TEMPERATURE = VOUT / 10mv */
    Local_u8Temperature  = Local_u16AnalogValue/10 ;

  /* STEP_TWO  : TAKE_AN_ACTION */
	/*  DISPLAY_TEMPERATURE_AT_LCD */
    LCD_void_writestring("TEMP:",1,0);
    LCD_voidGoToXY(1,9);
    LCD_voidlongNumber(Local_u8Temperature,3);
    LCD_void_writestring("C",1,11);

    /* DC_MOTOR_ACTION "FAN" */
    /* TAKE_AN_ACTION_FOR_TEMP_RANGE " 2 : 150 C " */

    /* OCR_VALUE_DUE_TO_TEMP_VALUE */
    Local_u8OCRValue = ( 255UL *(Local_u8Temperature) - 5865 ) / 17;

    /* CHANGE_DC_MOTOR_SPEED */
    TMR_voidTimer0SetCompareMatchValue(Local_u8OCRValue);
}
/***************************************************************************************************************************************/





