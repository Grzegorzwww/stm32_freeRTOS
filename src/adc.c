/*
 * adc.c
 *
 *  Created on: 27 wrz 2016
 *      Author: gwarchol
 */

#include "adc.h"
#include "functions.h"
#include "buffor_adc.h"

__IO ADC_HandleTypeDef hadc1;
__IO uint16_t uhADCxConvertedValue = 0;

DMA_HandleTypeDef hdma_adc1;
volatile ADC_ChannelConfTypeDef sConfig;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle);

extern volatile communication_frame_t communication_frame_out;
volatile adc_channel_choose_flag_t adc_channel_choose_flag = READ_FROM_ADC_CHANNEL_5;

unsigned char measure_flag = MEASURE_TRUE;
volatile unsigned char adc_5_ready = ADC_NOT_READY;
volatile unsigned char adc_13_ready = ADC_NOT_READY;

volatile unsigned short ADC_5_TEMP_VALUE = 0x0000;
volatile unsigned short ADC_13_TEMP_VALUE = 0x0000;

unsigned short ADC_5_BUFFER[ADC_BUFFOR_SIZE];
unsigned short ADC_13_BUFFER[ADC_BUFFOR_SIZE];


void init_adc(void){




	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_ADC1_CLK_ENABLE();
	 __HAL_RCC_GPIOC_CLK_ENABLE();
	 __HAL_RCC_GPIOA_CLK_ENABLE();

	/**ADC1 GPIO Configuration
    PC3     ------> ADC1_IN13
    PA5     ------> ADC1_IN5
	 */
	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);





	    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	    */
	  hadc1.Instance = ADC1;
	  hadc1.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
	  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	  hadc1.Init.ScanConvMode = ENABLE;
	  hadc1.Init.ContinuousConvMode = ENABLE;
	  hadc1.Init.DiscontinuousConvMode = DISABLE;
	  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	  hadc1.Init.NbrOfConversion = 1;
	  hadc1.Init.DMAContinuousRequests = DISABLE;
	  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	  if (HAL_ADC_Init(&hadc1) != HAL_OK)
	  {
	    Error_Handler();
	  }

	    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	    */
	  sConfig.Channel = ADC_CHANNEL_5;
	  sConfig.Rank = 1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  sConfig.Channel = ADC_CHANNEL_13;
	  sConfig.Rank = 2;
	  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
		   Error_Handler();
	  }

	    /* Peripheral interrupt init */
	    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
	    HAL_NVIC_EnableIRQ(ADC_IRQn);


	  HAL_ADC_Start_IT(&hadc1);

}





void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
{
	/* Turn LED3 on: Transfer process is correct */




	switch(adc_channel_choose_flag){
	case READ_FROM_ADC_CHANNEL_5:

		ADC_5_TEMP_VALUE = HAL_ADC_GetValue(&hadc1);
		adc_5_ready = ADC_READY;


		sConfig.Channel = ADC_CHANNEL_13;
		sConfig.Rank = 1;
		sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
		if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
		{
			Error_Handler();
		}
		adc_channel_choose_flag = READ_FROM_ADC_CHANNEL_13;


		break;

	case READ_FROM_ADC_CHANNEL_13:
		ADC_13_TEMP_VALUE = HAL_ADC_GetValue(&hadc1);
		adc_13_ready = ADC_READY;

		sConfig.Channel = ADC_CHANNEL_5;
		sConfig.Rank = 1;
		sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
		if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
		{
			Error_Handler();
		}

		adc_channel_choose_flag = READ_FROM_ADC_CHANNEL_5;

		break;

	}
}


void ADC_IRQHandler(void){
	HAL_ADC_IRQHandler(&hadc1);
	HAL_ADC_Start_IT(&hadc1);
}

void addMeasurement(void ){

	if(adc_5_ready == ADC_READY){
		ADDToBufforAdc(ADC_5_BUFFER, ADC_5_TEMP_VALUE, ADC_BUFFOR_SIZE);
		ADC_5_TEMP_VALUE = SIGNALCorrection(ADC_5_BUFFER);
		communication_frame_out.frame_data[0] = ADC_5_TEMP_VALUE >> 8;
		communication_frame_out.frame_data[1] = ADC_5_TEMP_VALUE;
		adc_5_ready = ADC_NOT_READY;
		//ADC_5_TEMP_VALUE = 0;


	} else if(adc_13_ready == ADC_READY){
		ADDToBufforAdc(ADC_13_BUFFER, ADC_13_TEMP_VALUE, ADC_BUFFOR_SIZE);

		ADC_13_TEMP_VALUE= SIGNALCorrection(ADC_13_BUFFER);
		communication_frame_out.frame_data[2] = ADC_13_TEMP_VALUE >> 8;
		communication_frame_out.frame_data[3] = ADC_13_TEMP_VALUE;

		adc_13_ready = ADC_NOT_READY;
		//ADC_13_TEMP_VALUE = 0;

	}



}





