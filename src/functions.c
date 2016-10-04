/*
 * functions.c
 *
 *  Created on: 20 wrz 2016
 *      Author: gwarchol
 */

#include "functions.h"
#include "adc.h"



ADC_HandleTypeDef hadc1;

UART_HandleTypeDef huart5;

UART_HandleTypeDef UartHandle;
DMA_HandleTypeDef hdma_uart5_tx;
__IO ITStatus UartReady = RESET;

unsigned char data_to_send[10] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char data_to_read[10] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

unsigned char irqRxBuff[512];
unsigned char dataFromPC[512];

int iRx = 0;

volatile communication_frame_t communication_frame_out;





void Error_Handler(void)
{

  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {}
}

void initJoyButton(void){

	GPIO_InitTypeDef GPIO_InitStruct;

	/* Peripheral clock enable */

	__GPIOA_CLK_ENABLE();

	  GPIO_InitStruct.Pin = GPIO_PIN_10;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

void scanJoyButtton(void *pvParameters){

	if(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_SET){
		 //setFrameCommand(0xFF);
		communication_frame_out.frame_command |= (1 < 8);
	}else {
		//setFrameCommand(0x00);
		communication_frame_out.frame_command &= ~(1 < 8);
	}

}


unsigned char sending_frames_couter = 0;

void setFrameCommand(const unsigned char command){
	communication_frame_out.frame_command = command;
}

void setFrameData(const unsigned char *data){
	strcpy(communication_frame_out.frame_data, data);
}


void sendDataFrame(void){


	data_to_send[0] =  0xC1; // head
	data_to_send[1] =  0x00; // to crc
	data_to_send[2] =  sending_frames_couter++;
	if(sending_frames_couter == 127)
		sending_frames_couter = 0;
	data_to_send[3] =  communication_frame_out.frame_command;
	data_to_send[4] =  communication_frame_out.frame_data[0];
	data_to_send[5] =  communication_frame_out.frame_data[1];
	data_to_send[6] =  communication_frame_out.frame_data[2];;
	data_to_send[7] =  communication_frame_out.frame_data[3];
	data_to_send[8] =  0x00;

	data_to_send[FRAME_SIZE -1] = FRAME_SIZE;
	frm_calcCrc(data_to_send, FRAME_SIZE, 1);

	HAL_UART_Transmit_IT(&huart5, data_to_send, FRAME_SIZE);

}

unsigned char frm_calcCrc(unsigned char *frame, unsigned int size, unsigned int setFlag){
    unsigned char sum = *frame + *(frame + size - 1);
    unsigned char n;
    for(n=2; n < (size-2); ++n)
    sum += *(frame+n);
    sum %= 256;
    if(setFlag){
        *(frame+1) = sum;
        *(frame+size-2) = sum;
    }
    return sum;
}

int parseData(const unsigned char data_in){

	unsigned char temp =  data_in;
	irqRxBuff[iRx] = temp;

	if((temp>(SERIAL_MIN_FRAME_SIZE -1)) && (temp<(iRx+2)) && (irqRxBuff[iRx-1]==irqRxBuff[iRx+2-temp]) && ((irqRxBuff[iRx+1-temp])==UH_HEADER_RX)){
		unsigned int iHead = iRx + 1 - temp;
		if(irqRxBuff[iRx-1] == frm_calcCrc(&irqRxBuff[iHead], temp, 0)){

			unsigned int n=0;
			for(; n<temp; ++n){
				dataFromPC[n] = irqRxBuff[iHead + n];
			}
			iRx = 0;
			return 1;
		}
	}
	if(++iRx == 512)
	iRx = 0;

	return 0;
}


void InitUART5(void){

	GPIO_InitTypeDef GPIO_InitStruct;

	/* Peripheral clock enable */
	__HAL_RCC_UART5_CLK_ENABLE();
	__GPIOD_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();

		/*
	  	UART5 GPIO Configuration
	    PC12     ------> UART5_TX
	    PD2     ------> UART5_RX
	    */

	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	huart5.Instance = UART5;
	huart5.Init.BaudRate = 115200;
	huart5.Init.WordLength = UART_WORDLENGTH_8B;
	huart5.Init.StopBits = UART_STOPBITS_1;
	huart5.Init.Parity = UART_PARITY_NONE;
	huart5.Init.Mode = UART_MODE_TX_RX;
	huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart5.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart5) != HAL_OK)
	{
		Error_Handler();
	}

	__HAL_UART_ENABLE_IT( &huart5,UART_IT_RXNE);
    HAL_NVIC_SetPriority(UART5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(UART5_IRQn);


    HAL_UART_Receive_IT(&huart5, data_to_read, 1);


}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart5)
{
  UartReady = SET;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart5)
{
	int i;

	__HAL_UART_ENABLE_IT(huart5,UART_IT_RXNE);
	HAL_UART_Receive_IT(huart5, data_to_read, 1);

	if(parseData(data_to_read[i]) == 1){

		strcpy(data_to_send, dataFromPC);
		//BSP_LED_Toggle(0);

	}

}

void UART5_IRQHandler(void)
{
   HAL_UART_IRQHandler(&huart5);
}











