/***********************************************************************************/
/*************   			  Name :    ISRAA SALAH 	    ************************/
/*************   			  Date : 	30/08/2022	  	    ************************/
/*************   		 	   SWC :	 EXternal_INT	    ************************/
/*************   		   Version :     1.0  			    ************************/
/***********************************************************************************/

/* include LIB */
#include "../../../LIB/STD_TYPES.h"
#include "../../../LIB/BIT_MATH.h"

/* HAL  */
#include "../../EXTI/Header/EXTI_config.h"
#include "../../EXTI/Header/EXTI_interface.h"
#include "../../EXTI/Header/EXTI_private.h"

/*declaring  pointer to function */
void(*Call_Fun_Ptr)(void) = NULL;

void External_interrupt_init(void)
{
   /*Select sense_control_mode for three PINS
   Clear Four Bits of sense_control REG */
//
//   CLR_BIT(MCUCR_REG , 0);
//   CLR_BIT(MCUCR_REG , 1);
//   CLR_BIT(MCUCR_REG , 2);
//   CLR_BIT(MCUCR_REG , 3);
//   CLR_BIT(MCUSCR_REG  , 6);

   /*SELECT_EXTI0_SENSE_CONTROL*/
   #if    EXTI0_SENSE_CONTROL == EXTI_LOW_LEVEL
       MCUCR_REG |= EXTI_LOW_LEVEL ;
   #elif  EXTI0_SENSE_CONTROL == EXTI_ANY_LOGICAL_CHANGE
       MCUCR_REG |= EXTI_ANY_LOGICAL_CHANGE ;
   #elif  EXTI0_SENSE_CONTROL == EXTI_FALLING_EDGE
	   MCUCR_REG |= EXTI_FALLING_EDGE ;
   #elif  EXTI0_SENSE_CONTROL  == EXTI_RISING_EDGE
	   MCUCR_REG |= EXTI_RISING_EDGE ;
   #endif

//   /*SELECT_EXTI1_SENSE_CONTROL*/
//   #if    EXTI1_SENSE_CONTROL == EXTI_LOW_LEVEL
//	   MCUCR_REG |= ( EXTI_LOW_LEVEL << 2 );
//   #elif  EXTI1_SENSE_CONTROL == EXTI_ANY_LOGICAL_CHANGE
//	   MCUCR_REG |= (EXTI_ANY_LOGICAL_CHANGE << 2);
//   #elif  EXTI1_SENSE_CONTROL == EXTI_FALLING_EDGE
//	   MCUCR_REG |= (EXTI_FALLING_EDGE << 2);
//   #elif  EXTI1_SENSE_CONTROL  == EXTI_RISING_EDGE
//	   MCUCR_REG |= (EXTI_RISING_EDGE << 2);
//   #endif
//
//   /*sense_INT2_control_mode*/
//   #if    EXTI2_SENSE_CONTROL  == EXTI_INT2_FALLING_EDGE
//	   //MCUSCR_REG |= EXTI_INT2_FALLING_EDGE
//	   CLR_BIT(MCUSCR_REG,1);
//   #elif  EXTI2_SENSE_CONTROL  == EXTI_INT2_RISING_EDGE
//	   //MCUSCR_REG |= EXTI_INT2_RISING_EDGE
//	   SET_BIT(MCUSCR_REG,1);
//   #endif


	/* Enable states */
   #if    EXTI_INT0_STATE      ==  EXTI_DISABLE_STATE
	   CLR_BIT(GICR_REG,6);
   #elif  EXTI_INT0_STATE      ==  EXTI_ENABLE_STATE
       SET_BIT(GICR_REG,6);
   #endif


   #if    EXTI_INT1_State      ==  EXTI_DISABLE_STATE
       CLR_BIT(GICR_REG,7);
   #elif  EXI_INT1_State       ==  EXTI_ENABLE_STATE
       SET_BIT(GICR_REG,7);
   #endif


   #if    EXTI_INT2_State      ==  EXTI_DISABLE_STATE
       CLR_BIT(GICR_REG,5);
   #elif  EXI_INT2_State       ==  EXTI_ENABLE_STATE
       SET_BIT(GICR_REG,5);
   #endif

   /*Clear flags */
   SET_BIT(GIFR_REG,5);
   SET_BIT(GIFR_REG,6);
   SET_BIT(GIFR_REG,7);

}


void External_interrupt_Enable_G_EXI(void)
{
	SET_BIT(SREG_REG,7);
}


void External_interrupt_Disable_G_EXI(void)
{
	CLR_BIT(SREG_REG,7);
}

void External_interrupt_Enable_EXI(interrupt_pins EXTI_index , Modes Edge )
{
	/***************INT1***************/
        if( EXTI_index == INT0 )
        {
		switch(Edge)
		{
		case exti_low_level :
			CLR_BIT(MCUCR_REG,0);
			CLR_BIT(MCUCR_REG,1);
		break;

		case exti_any_logical_change :
			SET_BIT(MCUCR_REG,0);
			CLR_BIT(MCUCR_REG,1);
		break;

		case exti_falling_edge :
			CLR_BIT(MCUCR_REG,0);
			SET_BIT(MCUCR_REG,1);
		break;

		case exti_rising_edge :
			SET_BIT(MCUCR_REG,0);
			SET_BIT(MCUCR_REG,1);
		break;
		}
		/*enable INT0*/
		SET_BIT(GICR_REG,6);
        }
	/***************INT1***************/
        if (EXTI_index == INT1 )
        {
			switch(Edge)
			 {
		case exti_low_level :
			CLR_BIT(MCUCR_REG,2);
			CLR_BIT(MCUCR_REG,3);
		break;

		case exti_any_logical_change :
			SET_BIT(MCUCR_REG,2);
			CLR_BIT(MCUCR_REG,3);
		break;

		case exti_falling_edge:
			CLR_BIT(MCUCR_REG,2);
			SET_BIT(MCUCR_REG,3);
		break;

		case exti_rising_edge :
			SET_BIT(MCUCR_REG,2);
			SET_BIT(MCUCR_REG,3);
		break;
			 }
		/*enable INT1*/
		SET_BIT(GICR_REG,7);

        }
     /***************INT2***************/
     if (EXTI_index == INT2 )
     {
			switch(Edge)
			{
			case exti_falling_edge:
			CLR_BIT(MCUSCR_REG,6);
		    break;

			case exti_rising_edge :
			SET_BIT(MCUSCR_REG,6);
			break;
			}
			/*enable INT2*/
			SET_BIT(GICR_REG,5);
     }
}


void External_interrupt_Enable_INT0(void)
{
	SET_BIT(GICR_REG,6);
}

void External_interrupt_disable_INT0(void)
{
	CLR_BIT(GICR_REG,6);
}


void External_interrupt_Enable_INT1(void)
{
	SET_BIT(GICR_REG,7);
}

void External_interrupt_disable_INT1(void)
{
	CLR_BIT(GICR_REG,7);
}


void External_interrupt_Enable_INT2(void)
{
	SET_BIT(GICR_REG,5);
}


void External_interrupt_disable_INT2(void)
{
	CLR_BIT(GICR_REG,5);
}

/*function to take pointer of interrupting Function */
void Inttrupting_Function(void (*copyCall_Fun_Ptr)(void))
{
	Call_Fun_Ptr = copyCall_Fun_Ptr;
}

/*functions for ISR  */
/*called by hardware */

void __vector_1(void)     __attribute__((signal));
void __vector_1(void)

{
	if(Call_Fun_Ptr != NULL)
	{
		/*call Function want interrupt code */
		Call_Fun_Ptr();
	}

}










