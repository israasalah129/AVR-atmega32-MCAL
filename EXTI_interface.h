
 /***********************************************************************************/
/*************   			  Name :    ISRAA SALAH 	    ************************/
/*************   			  Date : 	30/08/2022	  	    ************************/
/*************   		 	   SWC :	 EXternal_INT		 	    ************************/
/*************   		   Version :     1.0  			    ************************/
/***********************************************************************************/

#ifndef MCAL_EXTI_HEADER_EXTI_INTERFACE_H_
#define MCAL_EXTI_HEADER_EXTI_INTERFACE_H_

/* macros for External modes for INT0,INT1 */
#define  EXTI_LOW_LEVEL                0b00000000
#define  EXTI_ANY_LOGICAL_CHANGE       0b00000001
#define  EXTI_FALLING_EDGE             0b00000010
#define  EXTI_RISING_EDGE              0b00000011

/*macros for interrupt pins */
typedef enum
{
	INT0,
	INT1,
	INT2

}interrupt_pins;

typedef enum
{
  exti_low_level,
  exti_any_logical_change,
  exti_falling_edge,
  exti_rising_edge
}Modes;

/* macros for External modes for INT2 */
#define  EXTI_INT2_FALLING_EDGE        0
#define  EXTI_INT2_RISING_EDGE         1

/* macros for enable/disable state */
#define  EXTI_ENABLE_STATE              1
#define  EXTI_DISABLE_STATE             0

#define NULL    0

/*function to initialize EXI*/
void External_interrupt_init(void);

/*functions to enable / disable GIE */
void External_interrupt_Enable_G_EXI(void);
void External_interrupt_Disable_G_EXI(void);

/*functions to enable / disable INT0 */
void External_interrupt_Enable_INT0(void);
void External_interrupt_disable_INT0(void);

/*functions to enable / disable INT1 */
void External_interrupt_Enable_INT1(void);
void External_interrupt_disable_INT1(void);

/*functions to enable / disable INT2 */
void External_interrupt_Enable_INT2(void);
void External_interrupt_disable_INT2(void);

/*enable INT0,1,2 with CS selection*/
void External_interrupt_Enable_EXI(interrupt_pins EXTI_index , Modes Edge );

/*functions for ISR  */

/*function to take pointer of interrupting Function */
void Inttrupting_Function(void (*copyCall_Fun_Ptr)(void));


#endif /* MCAL_EXTI_HEADER_EXTI_INTERFACE_H_ */
