/***********************************************************************************/
/*************   			  Name :    ISRAA SALAH 	    ************************/
/*************   			  Date : 	30/08/2022	  	    ************************/
/*************   		 	   SWC :	 GLOBAL_INT	    ************************/
/*************   		   Version :     1.0  			    ************************/
/***********************************************************************************/

/* include LIB */
#include "../../../LIB/STD_TYPES.h"
#include "../../../LIB/BIT_MATH.h"

/* HAL  */
#include "../Header/GLO_INTERRUPT_interface.h"
#include "../Header/GLO_INTERRUPT_private.h"


void Global_INT_Enable_(void)
{
	SET_BIT(SREG_REG,7);
}


void Global_INT_Disable_(void)
{
	CLR_BIT(SREG_REG,7);
}
