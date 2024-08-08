/*
 * SPI_private.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ÇáÝÇãÕÑ
 */

#ifndef MCAL_SPI_SPI_PRIVATE_H_
#define MCAL_SPI_SPI_PRIVATE_H_

/*********SPI_REG**************/

#define    SPDR_REG                  *((volatile u8*)0x2F)
#define    SPSR_REG                  *((volatile u8*)0x2E)
#define    SPCR_REG                  *((volatile u8*)0x2D)

#define    SPI_MASTER           0
#define    SPI_SLAVE            1

#endif /* MCAL_SPI_SPI_PRIVATE_H_ */
