
#ifndef MCAL_ADC_HEADER_ADC_PRIVATE_H_
#define MCAL_ADC_HEADER_ADC_PRIVATE_H_

/*********ADC_REG**************/

#define    ADMUX_REG                  *((volatile u8*)0x27)
#define    ADCSRA_REG                 *((volatile u8*)0x26)
#define    SFIOR_REG                  *((volatile u8*)0x50)
#define    ADCL_REG                   *((volatile u8*)0x24)
#define    ADCH_REG                   *((volatile u8*)0x25)
#define    ADCLH_REG                  *((volatile u16*)0x24)

#endif /* MCAL_ADC_HEADER_ADC_PRIVATE_H_ */
