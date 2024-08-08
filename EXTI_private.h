
/***********************************************************************************/
/*************   			  Name :    ISRAA SALAH 	    ************************/
/*************   			  Date : 	30/08/2022	  	    ************************/
/*************   		 	   SWC :	 EXternal_INT		 	    ************************/
/*************   		   Version :     1.0  			    ************************/
/***********************************************************************************/

#ifndef MCAL_EXTI_HEADER_EXTI_PRIVATE_H_
#define MCAL_EXTI_HEADER_EXTI_PRIVATE_H_

#define SREG_REG             (*(volatile u8 *)0x5f)
#define MCUCR_REG            (*(volatile u8 *)0x55)
#define MCUSCR_REG           (*(volatile u8 *)0x54)
#define GICR_REG             (*(volatile u8 *)0x5B)
#define GIFR_REG             (*(volatile u8 *)0x5A)

#endif /* MCAL_EXTI_HEADER_EXTI_PRIVATE_H_ */
