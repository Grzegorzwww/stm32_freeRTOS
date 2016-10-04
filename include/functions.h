/*
 * functions.h
 *
 *  Created on: 20 wrz 2016
 *      Author: gwarchol
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "stm32f4xx_hal.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"


#define RXBUFFERSIZE 512
#define TXBUFFERSIZE 512

#define SERIAL_MIN_FRAME_SIZE 6
#define UH_HEADER_RX 0xC1
#define FRAME_SIZE 10

typedef struct communication_frame_s {


	unsigned char frame_command;
	unsigned char frame_data[4];

}communication_frame_t;


void InitUART5(void);

void Error_Handler(void);


void sendDataFrame(void);
unsigned char frm_calcCrc(unsigned char *frame, unsigned int size, unsigned int setFlag);
int parseData(const unsigned char data_in);

void setFrameData(const unsigned char *data);
void setFrameCommand(const unsigned char command);

void initJoyButton(void);
void scanJoyButtton(void *pvParameters);

/*void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart5);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart5);*/

//static uint16_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

#endif /* FUNCTIONS_H_ */
