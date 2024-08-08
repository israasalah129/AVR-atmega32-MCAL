

#ifndef MCAL_ADC_HEADER_ADC_INTERFACE_H_
#define MCAL_ADC_HEADER_ADC_INTERFACE_H_

/************ADC Voltage Select *************/
#define  ADC_VOLTAGE_CLEAR_ADMUX_REG        0b00111111
#define  ADC_VOLTAGE_AVCC                   0b01000000
#define  ADC_VOLTAGE_AREF                   0b00000000
#define  ADC_VOLTAGE_2.56V                  0b11000000

/****************ADC_MODE_SELECTOR****************/
#define ADC_MODE_AUTO_TRIGGER                1
#define ADC_MODE_SINGLE_CONVERSION           0

/***********ADC_ADJUST_SELECT****************/
#define ADC_RIGHT_ADJUSTED                   0
#define ADC_LEFT_ADJUSTED                    1
/***********ADC_PRESCALAR_SELECT*************/
#define ADC_PRESCALAR_CLEAR_ADSRA            0b11111000
#define ADC_PRESCALAR_2                      0b11111001
#define ADC_PRESCALAR_4                      0b11111010
#define ADC_PRESCALAR_8                      0b11111011
#define ADC_PRESCALAR_16                     0b11111100
#define ADC_PRESCALAR_32                     0b11111101
#define ADC_PRESCALAR_64                     0b11111110
#define ADC_PRESCALAR_128                    0b11111111
/************ADC_AUTO_TRIGGER_SELECT**********/
#define ADC_AUTO_TRIGGER_CLEAR_SFIOR                         0b00011111
#define ADC_AUTO_TRIGGER_FREE_RUNNING                        0b00000000
#define ADC_AUTO_TRIGGER_Analog_Comparator                   0b00100000
#define ADC_AUTO_TRIGGER_External_Interrupt_Request_0        0b01000000
#define ADC_AUTO_TRIGGER_Timer/Counter0_Compare_Match        0b01100000
#define ADC_AUTO_TRIGGER_Timer/Counter0_Overflow             0b10000000
#define ADC_AUTO_TRIGGER_Timer/Counter_Compare_Match_B       0b10100000
#define ADC_AUTO_TRIGGER_Timer/Counter1_Overflow             0b11000000
#define ADC_AUTO_TRIGGER_Timer/Counter1_Capture_Event        0b11100000
/************ADC_CHANNEL_SELECTOR************/
#define ADC_CHANNEL_CLEAR_ADMUX    0b11100000
#define ADC_CHANNEL_ADC0_          0b00000000
#define ADC_CHANNEL_ADC1_          0b00000001
#define ADC_CHANNEL_ADC2_          0b00000010
#define ADC_CHANNEL_ADC3_          0b00000011
#define ADC_CHANNEL_ADC4_          0b00000100
#define ADC_CHANNEL_ADC5_          0b00000101
#define ADC_CHANNEL_ADC6_          0b00000110
#define ADC_CHANNEL_ADC7_          0b00000111

/************status****************************/
#define STD_TYPES_OK                1
#define STD_TYPES_NOK               0
/**********************************************/
#define NULL                        0
/************prototype of functions************/
void ADC_INIT(void);
u8 GET_ADC_RESULT(u16 * Copy_pu16DigitalValue);
u8 ADC_START_CONVERSION (u8 copy_u8Adc_Channel);
#endif /* MCAL_ADC_HEADER_ADC_INTERFACE_H_ */
