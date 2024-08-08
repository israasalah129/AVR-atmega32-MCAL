/***********************************************************************************/
/*************   			  Name :    ISRAA SALAH 	    ************************/
/*************   			  Date : 	12/09/2022	  	    ************************/
/*************   		 	   SWC :	 TIMER		 	    ************************/
/*************   		   Version :     1.0  			    ************************/
/***********************************************************************************/

/* include LIB */
#include "../../../LIB/BIT_MATH.h"
#include "../../../LIB/STD_TYPES.h"

#define F_CPU  8000000UL
#include <util/delay.h>

/* MCAL  */
#include "../Header/Timer_private.h"
#include "../Header/Timer_interface.h"
#include "../Header/Timer_config.h"
/*****************************************Global Pointers*******************************************************/
/*ISR pointer TMR0 OVF*/
void(*TMR_pfTimer0OVF)(void) = NULL;

/*ISR pointer TMR0 CTC*/
void(*TMR_pfTimer0CTC)(void) = NULL;

/*****************************************NORMAL_MODE_INIT_FUNC ************************************************/
void TMR_voidTimer0Init_NORMAL_MODE ()
{

	/*SELECT NORMAL_MODE*/
	CLR_BIT(TMR_u8_TCCR0_REG,WGM01);
	CLR_BIT(TMR_u8_TCCR0_REG,WGM00);

	/*SET PRELOAD VALUE*/
	TMR_u8_TCNT0_REG = 192;

	/*ENABLE NORMAL_MODE INTERRUPT*/
    SET_BIT (TMR_u8_TIMSK_REG,TOIE0);

	/*SELECT TIMER FREQ "PRESCALAR"*/
	/*CLEAR THREE BITS RELATED TO PRESCALAR*/
	TMR_u8_TCCR0_REG &= TMR_PRESCALAR_CLEAR_TCCR0 ;
	TMR_u8_TCCR0_REG |= TMR_PRESCALAR_8 ;

}
/*****************************************COMPARE_MATCH_INIT_FUNC **********************************************/
void TMR_voidTimer0Init_CTC ()
{
	/*SELECT NORMAL_MODE*/
	SET_BIT(TMR_u8_TCCR0_REG,WGM01);
	CLR_BIT(TMR_u8_TCCR0_REG,WGM00);

    /*SET OCR0 VALUE*/
	TMR_u8_OCR0_REG = 99;

	/*ENABLE NORMAL_MODE INTERRUPT*/
    SET_BIT (TMR_u8_TIMSK_REG,OCIE0);

	/*SELECT TIMER FREQ "PRESCALAR"*/
	/*CLEAR THREE BITS RELATED TO PRESCALAR*/
	TMR_u8_TCCR0_REG &= TMR_PRESCALAR_CLEAR_TCCR0 ;
	TMR_u8_TCCR0_REG |= TMR_PRESCALAR_8 ;

}
/*****************************************FAST_PWM_MODE_FUNC **********************************************/

void TMR_voidTimer0Init_PWM (u8 copy_u8PWMmode , u8 copy_u8OC0Action)
{
    switch(copy_u8PWMmode)
   {

    /***************************FAST_PWM_MODE************************/
    case TIM_FAST_PWM_MODE :
       {

    	/*SELECT FAST_PWM_MODE */
    	SET_BIT(TMR_u8_TCCR0_REG,WGM01);
    	SET_BIT(TMR_u8_TCCR0_REG,WGM00);

    	switch(copy_u8OC0Action)
    	  {

    	case NON_INVERTING_MODE :
    	     {

    		 SET_BIT(TMR_u8_TCCR0_REG , COM01 );
    		 CLR_BIT(TMR_u8_TCCR0_REG , COM00 );

    	     }
    	break;

    	case INVERTING_MODE:
	         {

	    	 SET_BIT(TMR_u8_TCCR0_REG , COM01 );
	    	 SET_BIT(TMR_u8_TCCR0_REG , COM00 );

	         }
    	break;
          }
       }
    break;
    /***************************PHASE_CORRECT_MODE************************/
    case TIM_PHASE_CORRECT_MODE :
    {

 	/*SELECT PHASE_CORRECT_MODE */
 	CLR_BIT(TMR_u8_TCCR0_REG,WGM01);
 	SET_BIT(TMR_u8_TCCR0_REG,WGM00);

 	switch(copy_u8OC0Action)
 	  {

 	case NON_INVERTING_MODE :
 	     {

 		 SET_BIT(TMR_u8_TCCR0_REG , COM01 );
 		 CLR_BIT(TMR_u8_TCCR0_REG , COM00 );

 	     }
 	break;

 	case INVERTING_MODE:
	         {

	    	 SET_BIT(TMR_u8_TCCR0_REG , COM01 );
	    	 SET_BIT(TMR_u8_TCCR0_REG , COM00 );

	         }
 	break;
    }
    }
    break;

  }
	/*SELECT TIMER FREQ "PRESCALAR"*/
	/*CLEAR THREE BITS RELATED TO PRESCALAR*/
	TMR_u8_TCCR0_REG  &= TMR_PRESCALAR_CLEAR_TCCR0 ;
	TMR_u8_TCCR0_REG  |= TMR_PRESCALAR_8 ;


}
/*************************************TMR0_Call_Back_Function_OVF******************************************/
void   TMR_u8Timer0OVFSetCallBack(void(*copy_u8pftmr0ovr)(void))
{
	TMR_pfTimer0OVF = copy_u8pftmr0ovr ;
}

/*************************************TMR0_Call_Back_Function_CTC******************************************/
void   TMR_u8Timer0CTCSetCallBack(void(*copy_u8pftmr0ctc)(void))
{
	TMR_pfTimer0CTC = copy_u8pftmr0ctc ;
}

/***************************************************ISR_FUNC***********************************************/
/**************************************implementation of ISR Timer0 OVF************************************/
void __vector_11(void)     __attribute__((signal));
void __vector_11(void)
{
	/*count overflows times*/
	static u16 Local_u16counter = 0;
	Local_u16counter++;

	//if (Local_u16counter == *Global_u16_OverFlows )
	if (Local_u16counter == 3907 )
	{
		/* set p_load value */
		//PRELOAD_VALUE = *Global_u8_pPreloadvalue;
		TMR_u8_TCNT0_REG = 192;

		/* Reset Counter */
		Local_u16counter = 0;

		/*call back function*/
		TMR_pfTimer0OVF();
	}
}
/***************************************************ISR_FUNC***********************************************/
/**************************************implementation of ISR Timer0 CTC************************************/
void __vector_10(void)     __attribute__((signal));
void __vector_10(void)
{
	/*count overflows times*/
	static u16 Local_u16counter = 0;
	Local_u16counter++;

	//if (Local_u16counter == *Global_u16_CTC_counts )
	if (Local_u16counter == 10000 )
	{

		/* Reset Counter */
		Local_u16counter = 0;

		/*call back function*/
		TMR_pfTimer0CTC();
	}
}
/************************************OCR VALUE*************************************************************/
void   TMR_voidTimer0SetCompareMatchValue(u8 Copy_u8OCR0Value)
{
		TMR_u8_OCR0_REG = Copy_u8OCR0Value;
}
/************************************PRE_LOAD_VALUE********************************************************/
void   TMR_voidTimer0SetPreLoadValue(u8 Copy_u8TCNT0Value)
{
	    TMR_u8_TCNT0_REG = Copy_u8TCNT0Value;
}
/*******************************************TMR 1 INITALIZATION********************************************/
void TMR1_INIT_OVFMODE(void)
{
	/* select normal mode*/
	CLR_BIT(TMR_u8_TCCR1A,WGM10);
	CLR_BIT(TMR_u8_TCCR1A,WGM10);
	CLR_BIT(TMR_u8_TCCR1B,WGM12);
	CLR_BIT(TMR_u8_TCCR1B,WGM13);

	 /* select 8 PRESCALAR */
	CLR_BIT(TMR_u8_TCCR1B,0);
	SET_BIT(TMR_u8_TCCR1B,1);
	CLR_BIT(TMR_u8_TCCR1B,2);
}
/***************************************************************************************************************/
 void   TMR_voidTimer1SetCompareMatchChannelA(u16 Copy_16OCR1AValue)
{
	TMR_u16_OCR1A = Copy_16OCR1AValue;
}

/***************************************************************************************************************/
 void   TMR_voidTimer1GetCounterValue(u16 * Copy_pu16CounterValue)
 {
 	*Copy_pu16CounterValue = TMR_u16_TCNT1;
 }

 /*******************************************TMR 1 'FAST PWM ''TOP ICR1' INITALIZATION**************************/
 void TMR1_INIT_FAST_PWMMODE_ICRTOP()
 {
 	 /* select Fast PWM mode   "Top ICR1 Top value " */
 	 CLR_BIT(TMR_u8_TCCR1A,WGM10);
 	 SET_BIT(TMR_u8_TCCR1A,WGM11);
 	 SET_BIT(TMR_u8_TCCR1B,WGM12);
 	 SET_BIT(TMR_u8_TCCR1B,WGM13);

 	 /*Select Non inverting mode */
 	 CLR_BIT(TMR_u8_TCCR1A,COM1A0);
 	 SET_BIT(TMR_u8_TCCR1A,COM1A1);

 	 /*Set Max value */
 	 TMR_u16_ICR1 = 19999;

 	 /* select 8 PRESCALAR */
 	 CLR_BIT(TMR_u8_TCCR1B,CS10);
 	 SET_BIT(TMR_u8_TCCR1B,CS11);
     CLR_BIT(TMR_u8_TCCR1B,CS12);

 }
/******************************************************************************************************************/

