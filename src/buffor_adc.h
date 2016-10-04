/*
 * buffor_adc.h
 *
 *  Created on: 3 paź 2016
 *      Author: gwarchol
 */

#ifndef BUFFOR_ADC_H_
#define BUFFOR_ADC_H_

#define ADC_BUFFOR_SIZE 64
#define ADC_BUFFER_HALF  32



typedef unsigned  short uint16_t;
typedef unsigned  char uint8_t;




void ADDToBufforAdc(uint16_t *buffor, uint16_t dana, uint8_t size);
uint8_t GETFromBufforAdc(uint16_t *buffor, uint8_t *no);
uint16_t SORTSamples(uint16_t *d, uint16_t x);
uint16_t SIGNALCorrection(uint16_t *buff);


#endif /* BUFFOR_ADC_H_ */
