/**
  ******************************************************************************
  * @file    usbh_usr.h
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    22-July-2011
  * @brief   This file is the header file for usb usr file
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USH_USR_H__
#define __USH_USR_H__


/* Includes ------------------------------------------------------------------*/
#include "usbh_core.h"
#include "stm32f4_discovery.h"
#include <stdio.h>

/** @addtogroup USBH_USER
* @{
*/

/** @addtogroup USBH_HID_DEMO_USER_CALLBACKS
* @{
*/
  
/** @defgroup USBH_USR 
  * @brief This file is the header file for user action
  * @{
  */ 


/** @defgroup USBH_CORE_Exported_Variables
  * @{
  */ 


extern  USBH_Usr_cb_TypeDef USR_Callbacks;


/**
  * @}
  */ 


/** @defgroup USBH_CORE_Exported_FunctionsPrototype
  * @{
  */ 

void USBH_USR_ApplicationSelected(void);
void USBH_USR_Init(void);
void USBH_USR_DeInit(void);
void USBH_USR_DeviceAttached(void);
void USBH_USR_ResetDevice(void);
void USBH_USR_DeviceDisconnected (void);
void USBH_USR_OverCurrentDetected (void);
void USBH_USR_DeviceSpeedDetected(uint8_t DeviceSpeed); 
void USBH_USR_Device_DescAvailable(void *);
void USBH_USR_DeviceAddressAssigned(void);
void USBH_USR_Configuration_DescAvailable(USBH_CfgDesc_TypeDef * cfgDesc,
                                          USBH_InterfaceDesc_TypeDef *itfDesc,
                                          USBH_EpDesc_TypeDef *epDesc);
void USBH_USR_Manufacturer_String(void *);
void USBH_USR_Product_String(void *);
void USBH_USR_SerialNum_String(void *);
void USBH_USR_EnumerationDone(void);
void USBH_USR_DeInit(void);
void USBH_USR_DeviceNotSupported(void);
void USBH_USR_UnrecoveredError(void);

USBH_USR_Status USBH_USR_UserInput(void);
int USBH_USR_ADK_Application(void);

/**
  * @}
  */ 

#endif /* __USBH_USR_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
