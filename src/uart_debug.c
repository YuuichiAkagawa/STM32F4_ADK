/**
  ******************************************************************************
  * @file    uart_debug.c
  * @author  Yuuichi Akagawa
  * @version V1.0.0
  * @date    2012/02/27
  * @brief   UART debug out utility
  ******************************************************************************
  * @attention
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *      http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  * <h2><center>&copy; COPYRIGHT (C)2012 Yuuichi Akagawa</center></h2>
  *
  ******************************************************************************
  */

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "uart_debug.h"

//USART2
USART_TypeDef* COM_USART        = USART2;
GPIO_TypeDef*  COM_TX_PORT      = GPIOA;
GPIO_TypeDef*  COM_RX_PORT      = GPIOA;
const uint32_t COM_USART_CLK    = RCC_APB1Periph_USART2;
const uint32_t COM_TX_PORT_CLK  = RCC_AHB1Periph_GPIOA;
const uint32_t COM_RX_PORT_CLK  = RCC_AHB1Periph_GPIOA;
const uint16_t COM_TX_PIN       = GPIO_Pin_2;
const uint16_t COM_RX_PIN       = GPIO_Pin_3;
const uint16_t COM_TX_PIN_SOURCE= GPIO_PinSource2;
const uint16_t COM_RX_PIN_SOURCE= GPIO_PinSource3;
const uint16_t COM_TX_AF        = GPIO_AF_USART2;
const uint16_t COM_RX_AF        = GPIO_AF_USART2;

void uart_debug_init()
{
	  USART_InitTypeDef USART_InitStructure;
	  GPIO_InitTypeDef GPIO_InitStructure;
	  /* USARTx configured as follow:
	        - BaudRate = 230400 baud
	        - Word Length = 8 Bits
	        - One Stop Bit
	        - No parity
	        - Hardware flow control disabled (RTS and CTS signals)
	        - Receive and transmit enabled
	  */
	  USART_InitStructure.USART_BaudRate = 230400;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	  /* Enable GPIO clock */
	  RCC_AHB1PeriphClockCmd(COM_TX_PORT_CLK | COM_RX_PORT_CLK, ENABLE);
	  /* Enable UART clock */
	  RCC_APB1PeriphClockCmd(COM_USART_CLK, ENABLE);

	  /* Connect PXx to USARTx_Tx*/
	  GPIO_PinAFConfig(COM_TX_PORT, COM_TX_PIN_SOURCE, COM_TX_AF);

	  /* Connect PXx to USARTx_Rx*/
	  GPIO_PinAFConfig(COM_RX_PORT, COM_RX_PIN_SOURCE, COM_RX_AF);

	  /* Configure USART Tx as alternate function  */
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

	  GPIO_InitStructure.GPIO_Pin = COM_TX_PIN;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(COM_TX_PORT, &GPIO_InitStructure);

	  /* Configure USART Rx as alternate function  */
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Pin = COM_RX_PIN;
	  GPIO_Init(COM_RX_PORT, &GPIO_InitStructure);

	  /* USART configuration */
	  USART_Init(COM_USART, &USART_InitStructure);

	  /* Enable USART */
	  USART_Cmd(COM_USART, ENABLE);
	  USART_SendData(USART2, (uint8_t) 'o');

	  /* Attach ChaN's xprintf interface */
	  xdev_out(uart_debug_putc);
}

void uart_debug_putc( unsigned char c)
{
	USART_SendData(USART2, (uint8_t) c);
	  /* Loop until the end of transmission */
	  while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
	  {}
}

