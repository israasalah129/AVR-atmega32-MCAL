
/* include LIB */
#include "../../../LIB/STD_TYPES.h"
#include "../../../LIB/BIT_MATH.h"

#define F_CPU  8000000UL
#include <util/delay.h>

/* MCAL  */
#include "SPI_private.h"
#include "SPI_interface.h"
#include "SPI_config.h"

void SPI_INIT (void)
{
#if SPI_MODE == SPI_MASTER
	/*MASTR MODE */
	SET_BIT(SPCR_REG,4);

	/*FREQ*/
	SET_BIT(SPCR_REG,1);
	SET_BIT(SPCR_REG,0);

	/*SPI ENABLE */
	SET_BIT(SPCR_REG,6);

#elif  SPI_MODE == SPI_SLAVE
	    /*MASTR MODE */
		CLR_BIT(SPCR_REG,4);
#endif
		/*MSB*/
		CLR_BIT(SPCR_REG,5);
		/*CLK PHA*/
		SET_BIT(SPCR_REG,2);
		/*CLK PIO*/
		SET_BIT(SPCR_REG,3);

}

void SPI_SEND_REC (u8 Local_u8Data , u8 * Local_u8RECData)

{
	SPDR_REG = Local_u8Data;

	/*check flag*/
	while(! GET_BIT(SPSR_REG,7));
	*Local_u8RECData = SPDR_REG;
}
