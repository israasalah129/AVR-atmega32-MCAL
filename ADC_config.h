
#ifndef MCAL_ADC_HEADER_ADC_CONFIG_H_
#define MCAL_ADC_HEADER_ADC_CONFIG_H_

#include "ADC_interface.h"
/************ADC Voltage Select *************/

/*
1-ADC_VOLTAGE_AVCC
2-ADC_VOLTAGE_AREF
3-ADC_VOLTAGE_2_56V                        */

#define ADC_VOLTAGE       ADC_VOLTAGE_AVCC

/****************ADC_MODE_SELECTOR***********/

/*1-ADC_MODE_AUTO_TRIGGER
  2-ADC_MODE_SINGLE_CONVERSION              */

#define ADC_MODE          ADC_MODE_SINGLE_CONVERSION

/***********ADC_ADJUST_SELECT****************/
/*1-ADC_RIGHT_ADJUSTED
  2-ADC_LEFT_ADJUSTED                      */

#define ADC_RESULT_MODE   ADC_RIGHT_ADJUSTED

/***********ADC_PRESCALAR_SELECT*************/

 /*1-ADC_PRESCALAR_2
   2-ADC_PRESCALAR_4
   3-ADC_PRESCALAR_8
   4-ADC_PRESCALAR_16
   5-ADC_PRESCALAR_32
   6-ADC_PRESCALAR_64
   7-ADC_PRESCALAR_128                      */

#define ADC_PRESCALAR     ADC_PRESCALAR_64

/************ADC_AUTO_TRIGGER_SELECT**********/

  /*1-ADC_AUTO_TRIGGER_FREE_RUNNING
    2-ADC_AUTO_TRIGGER_
    3-ADC_AUTO_TRIGGER_
    4-ADC_AUTO_TRIGGER_
    5-ADC_AUTO_TRIGGER_                     */

#define ADC_AUTO_TRIGGER_MODE  ADC_AUTO_TRIGGER_FREE_RUNNING

/************ADC_CHANNEL_SELECTOR************/

/*0- ADC_CHANNEL_ADC0_
  1- ADC_CHANNEL_ADC1_
  2- ADC_CHANNEL_ADC2_
  3- ADC_CHANNEL_ADC3_
  4- ADC_CHANNEL_ADC4_
  5- ADC_CHANNEL_ADC5_
  6- ADC_CHANNEL_ADC6_
  7- ADC_CHANNEL_ADC7_
                                            */

#define ADC_CHANNEL        ADC_CHANNEL_ADC0_

/****************ADC pin ********************/
#define ADC_PIN_PORT       DIO_u8_PORTA
#define ADC_PIN            DIO_u8_PIN0


#endif /* MCAL_ADC_HEADER_ADC_CONFIG_H_ */
