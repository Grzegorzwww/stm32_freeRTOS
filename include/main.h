#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include "diag/Trace.h"

// board
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_sdram.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_usart.h"


// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "functions.h"

void toggleLedWithTimer(void*);
void detectButtonPress(void*);
void toggleLedWithIpc(void*);
void dravText(void *);
void sendUartData(void *pvParameters);
void getDataFromAdc(void *);
void drawSmlLogo(void *);
void initializeHardware();
void createTask(TaskFunction_t code, const char * const name);
void delayMillis(uint32_t millis);

void SystemClock_Config(void);






#define logoElementsDelay() delayMillis(500);

#endif
