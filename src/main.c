/**
  ******************************************************************************
  * @file    main.c
  * @author  Yuuichi Akagawa
  * @version V1.0.0
  * @date    2012/01/22
  * @brief   Android Open Accessory implementation
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
#include "usb_bsp.h"
#include "usbh_core.h"
#include "usbh_usr.h"
#include "usbh_adk_core.h"
#include "uart_debug.h"

/* Private macro */
/* Private variables */
__IO uint32_t TimingDelay;

/* Private function prototypes */
void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
/** @defgroup USBH_USR_MAIN_Private_Variables
* @{
*/
#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN USB_OTG_CORE_HANDLE           USB_OTG_Core_dev __ALIGN_END ;

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN USBH_HOST                     USB_Host __ALIGN_END ;
/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
  int i = 0;
  uint8_t msg[2];
  uint16_t len;
  RCC_ClocksTypeDef RCC_Clocks;

  /* Initialize LEDs and User_Button on STM32F4-Discovery --------------------*/
  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);

  /* SysTick end of count event each 1ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

  uart_debug_init();

  /* Init Host Library */
  USBH_Init(&USB_OTG_Core_dev,
            USB_OTG_FS_CORE_ID,
            &USB_Host,
            &USBH_ADK_cb,
            &USR_Callbacks);
  USBH_ADK_Init("ammlab.org", "HelloADK", "DemoKit", "1.0", "http://www.ammlab.org",  "1234567");

  while (1)
  {
    /* Host Task handler */
    USBH_Process(&USB_OTG_Core_dev , &USB_Host);

    /* Accessory Mode enabled */
    if( USBH_ADK_getStatus() == ADK_IDLE) {
    	// in
    	len = USBH_ADK_read(&USB_OTG_Core_dev, msg, sizeof(msg));
    	if( len > 0 ){
    		if( msg[0] == 0x1){
    			if( msg[1] == 0x1) {
    				STM_EVAL_LEDOn(LED5);
    			}else{
    				STM_EVAL_LEDOff(LED5);
    			}
    		}
    	}

    	// out
    	if( STM_EVAL_PBGetState(BUTTON_USER) ){
    		msg[0] = 1;
    		msg[1] = 1;
			STM_EVAL_LEDOn(LED6);
    	}else{
    		msg[0] = 1;
    		msg[1] = 0;
			STM_EVAL_LEDOff(LED6);
    	}
    	USBH_ADK_write(&USB_OTG_Core_dev, msg, 2);
    }
    Delay(5);

    if (i++ == 100)
    {
      STM_EVAL_LEDToggle(LED3);
      i = 0;
    }
  }
}


#ifdef USE_FULL_ASSERT
/**
* @brief  assert_failed
*         Reports the name of the source file and the source line number
*         where the assert_param error has occurred.
* @param  File: pointer to the source file name
* @param  Line: assert_param error line source number
* @retval None
*/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line
  number,ex: printf("Wrong parameters value: file %s on line %d\r\n",
  file, line) */

  /* Infinite loop */
  while (1)
  {}
}

#endif

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 1 ms.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}


