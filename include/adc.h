
#include "stm32f4xx_hal.h"

typedef enum {
	READ_FROM_ADC_CHANNEL_5,
	READ_FROM_ADC_CHANNEL_13
} adc_channel_choose_flag_t;


#define MEASURE_TRUE 1
#define MEASURE_FALSE 0

#define ADC_READY 1
#define ADC_NOT_READY 0

void init_adc(void);

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle);


void addMeasurement(void);
