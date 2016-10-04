/*
 * buffor_adc.c
 *
 *  Created on: 3 paź 2016
 *      Author: gwarchol
 */
#include "buffor_adc.h"


uint8_t buff_counterAD0;
uint8_t buff_counterAD1;


uint16_t adc_AD0Buff[ADC_BUFFOR_SIZE];														/* ADC GLOBAL variables */
uint16_t adc_AD1Buff[ADC_BUFFOR_SIZE];




void ADDToBufforAdc(uint16_t *buffor, uint16_t dana, uint8_t size)
{
	int i;
	for(i = size - 1; i > 0; i--){
		buffor[i] = buffor[i - 1];
	}
	buffor[0] = dana;
}
uint8_t GETFromBufforAdc(uint16_t *buffor, uint8_t *no)
{
	int i;
	uint8_t dana = buffor[0];
	for(i = 0; i < no; i++)
	{
		buffor[i] = buffor[i + 1];
	}
	*no--;
	return dana;
}
uint16_t SORTSamples(uint16_t *d, uint16_t x)
{
	uint16_t tab[ADC_BUFFOR_SIZE];
	int j, i;
	uint16_t temp;

	for(i = 0; i < x;i++){
		tab[i] = d[i]  &= 0xFFFC;
	}
	for(j = x - 1; j > 0; j--)
		for(i = 0; i < j; i++)
			if(tab[i] > tab[i + 1]){
				temp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = temp;
			}
	return tab[ADC_BUFFER_HALF];
}



uint16_t SIGNALCorrection(uint16_t *buff)
{
	return SORTSamples(buff, ADC_BUFFOR_SIZE);
}




