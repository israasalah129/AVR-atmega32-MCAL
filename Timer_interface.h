/***********************************************************************************/
/*************   			  Name :    ISRAA SALAH 	    ************************/
/*************   			  Date : 	12/09/2022	  	    ************************/
/*************   		 	   SWC :	 TIMER		 	    ************************/
/*************   		   Version :     1.0  			    ************************/
/***********************************************************************************/

#ifndef MCAL_TIMER_HEADER_TIMER_INTERFACE_H_
#define MCAL_TIMER_HEADER_TIMER_INTERFACE_H_

/*************************Macros For Timer/Counter Register "TCCR0 Pins **************************************/
#define FOC0     7
#define WGM01    3
#define WGM00    6
#define COM01    5
#define COM00    4
#define CS00     0
#define CS01     1
#define CS02     2
/**************************************Macros for timer Mode Option********************************************/
#define TIM_NORMAL_MODE                0
#define TIM_CTC_MODE                   1
#define TIM_FAST_PWM_MODE              2
#define TIM_PHASE_CORRECT_MODE         3

/**********************Macros for Compare Output Mode " PWM ***************************************************/
#define COMPARE_OUTPUT_MODE_PWM_CLR_MASK                0b11001111
#define NON_INVERTING_MODE                              0b00101111
#define INVERTING_MODE                                  0b00011111
/*************************Macros For Timer/Counter Register "TIMS" Pins ***************************************/
#define OCIE0    1
#define TOIE0    0
/**************************************Macros for SFIOR pins **************************************************/
#define PSR10    0
/******************************************PRESCALAR***********************************************************/
#define TMR_PRESCALAR_CLEAR_TCCR0            0b11111000
#define TMR_PRESCALAR_2                      0b00000000
#define TMR_PRESCALAR_4                      0b00000000
#define TMR_PRESCALAR_8                      0b00000010
#define TMR_PRESCALAR_16                     0b00000000
#define TMR_PRESCALAR_32                     0b00000000
#define TMR_PRESCALAR_64                     0b00000000
/*****************************PROTOTUPES OF TMR0 FUNCTIONS******************************************************/
void TMR_voidTimer0Init_NORMAL_MODE ();
void TMR_voidTimer0Init_CTC ();
void TMR_voidTimer0Init_PWM (u8 copy_u8PWMmode , u8 copy_u8OC0Action);
void TMR_u8Timer0OVFSetCallBack(void(*copy_u8pftmr0ovr)(void));
void TMR_u8Timer0CTCSetCallBack(void(*copy_u8pftmr0ctc)(void));
void TMR_voidTimer0SetCompareMatchValue(u8 Copy_u8OCR0Value);
void TMR_voidTimer0SetPreLoadValue(u8 Copy_u8TCNT0Value);
void __vector_10(void);
void __vector_11(void);
/***************************************Macros for TMR1 MODES PINS**********************************************/
/*********************TCCR1A************************************************************************************/
#define  WGM10            0
#define  WGM11            1
/*********************TCCR1B************************************************************************************/
#define  WGM12            3
#define  WGM13            4
#define  CS12             2
#define  CS11             1
#define  CS10             0
#define  COM1A1           7
#define  COM1A0           6
/****************************PROTOTUPES OF TMR1 FUNCTIONS*******************************************************/
void TMR1_INIT_OVFMODE(void);
void TMR_voidTimer1SetCompareMatchChannelA(u16 Copy_16OCR1AValue);
void TMR_voidTimer1GetCounterValue(u16 * Copy_pu16CounterValue);
void TMR1_INIT_FAST_PWMMODE_ICRTOP();
/**************************************************************************************************************/
#endif /* MCAL_TIMER_HEADER_TIMER_INTERFACE_H_ */
