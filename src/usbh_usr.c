/**
  ******************************************************************************
  * @file    usbh_usr.c
  * @author  MCD Application Team and modified by Yuuichi Akagawa
  * @version V2.0.0
  * @date    22-July-2011, 2012/03/05
  * @brief   This file includes the user application layer
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

/* Includes ------------------------------------------------------------------*/
//#include "lcd_log.h"
#include "usbh_usr.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "xprintf.h"
/** @addtogroup USBH_USER
* @{
*/

/** @addtogroup USBH_HID_DEMO_USER_CALLBACKS
* @{
*/

/** @defgroup USBH_USR
* @brief This file is the Header file for usbh_usr.c
* @{
*/ 


/** @defgroup USBH_CORE_Exported_TypesDefinitions
* @{
*/ 

/**
* @}
*/ 
/** @addtogroup USER
* @{
*/

/** @defgroup USBH_USR 
* @brief    This file includes the user application layer
* @{
*/ 

/** @defgroup USBH_CORE_Exported_Types
* @{
*/ 



/** @defgroup USBH_USR_Private_Defines
* @{
*/ 
/**
* @}
*/ 


/** @defgroup USBH_USR_Private_Macros
* @{
*/ 
/**
* @}
*/ 

/** @defgroup USBH_USR_Private_Variables
* @{
*/
extern USB_OTG_CORE_HANDLE           USB_OTG_Core_dev;
/*  Points to the DEVICE_PROP structure of current device */
/*  The purpose of this register is to speed up the execution */

USBH_Usr_cb_TypeDef USR_Callbacks =
{
  USBH_USR_Init,							/* HostLibInitialized */
  USBH_USR_DeInit,							/* HostLibInitialized */  
  USBH_USR_DeviceAttached,					/* DeviceAttached */
  USBH_USR_ResetDevice,	
  USBH_USR_DeviceDisconnected,
  USBH_USR_OverCurrentDetected,
  USBH_USR_DeviceSpeedDetected,				/* DeviceSpeed */
  USBH_USR_Device_DescAvailable,			/* DeviceDescriptor is available */
  USBH_USR_DeviceAddressAssigned,			/* Address is assigned to USB Device */
  USBH_USR_Configuration_DescAvailable,		/* Configuration Descriptor available */
  USBH_USR_Manufacturer_String,				/* ManufacturerString*/
  USBH_USR_Product_String,					/* ProductString*/
  USBH_USR_SerialNum_String,				/* SerialNubString*/
  USBH_USR_EnumerationDone,					/* Enumeration finished */
  USBH_USR_UserInput,
  USBH_USR_ADK_Application,
  USBH_USR_DeviceNotSupported,				/* Device is not supported*/
  USBH_USR_UnrecoveredError
};

/**
* @}
*/

/** @defgroup USBH_USR_Private_Constants
* @{
*/ 

/**
* @}
*/



/** @defgroup USBH_USR_Private_FunctionPrototypes
* @{
*/ 
/**
* @}
*/ 


/** @defgroup USBH_USR_Private_Functions
* @{
*/ 

/**
* @brief  USBH_USR_Init 
* @param  None
* @retval None
*/
void USBH_USR_Init(void)
{
  static uint8_t startup = 0;  
  if(startup == 0 )
  {
    startup = 1;
#ifdef DEBUG
	xputs("> Host Library Initialized\n");
#endif
  }
}

/**
* @brief  USBH_USR_DeviceAttached 
* @param  None
* @retval None
*/
void USBH_USR_DeviceAttached(void)
{
#ifdef DEBUG
	xputs("> Device Attached\n");
#endif
}


/**
* @brief  USBH_USR_UnrecoveredError
* @param  None
* @retval None
*/
void USBH_USR_UnrecoveredError (void)
{
#ifdef DEBUG
	xputs("> UNRECOVERED ERROR STATE\n");
#endif
}


/**
* @brief  USBH_DisconnectEvent
*         Device disconnect event
* @param  None
* @retval None
*/
void USBH_USR_DeviceDisconnected (void)
{
#ifdef DEBUG
	xputs("> Device Disconnected\n");
#endif
}

/**
* @brief  USBH_USR_ResetUSBDevice 
*         Reset USB Device
* @param  None
* @retval None
*/
void USBH_USR_ResetDevice(void)
{
  /* Users can do their application actions here for the USB-Reset */
}


/**
* @brief  USBH_USR_DeviceSpeedDetected 
*         Displays the message on LCD for device speed
* @param  Devicespeed : Device Speed
* @retval None
*/
void USBH_USR_DeviceSpeedDetected(uint8_t DeviceSpeed)
{
  if(DeviceSpeed == HPRT0_PRTSPD_HIGH_SPEED)
  {
#ifdef DEBUG
	  xputs("> High speed device detected\n");
#endif
  }  
  else if(DeviceSpeed == HPRT0_PRTSPD_FULL_SPEED)
  {
#ifdef DEBUG
	  xputs("> Full speed device detected\n");
#endif
  }
  else if(DeviceSpeed == HPRT0_PRTSPD_LOW_SPEED)
  {
#ifdef DEBUG
	  xputs("> Low speed device detected\n");
#endif
  }
  else
  {
#ifdef DEBUG
	  xputs("> Device fault \n");
#endif
  }
}

/**
* @brief  USBH_USR_Device_DescAvailable 
*         Displays the message on LCD for device descriptor
* @param  DeviceDesc : device descriptor
* @retval None
*/
void USBH_USR_Device_DescAvailable(void *DeviceDesc)
{
#ifdef DEBUG
  uint8_t temp[20];    
  USBH_DevDesc_TypeDef *hs;
  hs = DeviceDesc;  

  xputs("Device Descriptor\n");
  sprintf((char *)temp , "Class : %02Xh\n" , (uint8_t)(*hs).bDeviceClass);
  xputs(temp);

  sprintf((char *)temp , "SubClass : %02Xh\n" , (uint8_t)(*hs).bDeviceSubClass);
  xputs(temp);

  sprintf((char *)temp , "Protocol : %02Xh\n" , (uint8_t)(*hs).bDeviceProtocol);
  xputs(temp);

  sprintf((char *)temp , "VID : %04Xh\n" , (uint32_t)(*hs).idVendor); 
  xputs(temp);

  sprintf((char *)temp , "PID : %04Xh\n" , (uint32_t)(*hs).idProduct); 
  xputs(temp);
#endif
}

/**
* @brief  USBH_USR_DeviceAddressAssigned 
*         USB device is successfully assigned the Address 
* @param  None
* @retval None
*/
void USBH_USR_DeviceAddressAssigned(void)
{
  
}


/**
* @brief  USBH_USR_Conf_Desc 
*         Displays the message on LCD for configuration descriptor
* @param  ConfDesc : Configuration descriptor
* @retval None
*/
void USBH_USR_Configuration_DescAvailable(USBH_CfgDesc_TypeDef * cfgDesc,
                                          USBH_InterfaceDesc_TypeDef *itfDesc,
                                          USBH_EpDesc_TypeDef *epDesc)
{
#ifdef DEBUG
  char temp[100];
  USBH_InterfaceDesc_TypeDef *id;
  id = itfDesc;  

  sprintf(temp, "Interface : %02X %02X\n", (uint8_t)(*id).bInterfaceClass, (uint8_t)(*id).bInterfaceSubClass);
  xputs(temp);
  sprintf((char *)temp , "Power info: bmAttributes:0x%02X, bMaxPower:%d\n",cfgDesc->bmAttributes, cfgDesc->bMaxPower );
  xputs(temp);

#endif
}

/**
* @brief  USBH_USR_Manufacturer_String 
*         Displays the message on LCD for Manufacturer String 
* @param  ManufacturerString : Manufacturer String of Device
* @retval None
*/
void USBH_USR_Manufacturer_String(void *ManufacturerString)
{
#ifdef DEBUG
  char temp[100];
  sprintf(temp, "Manufacturer : %s\n", (char *)ManufacturerString);
  xputs(temp);
#endif
}

/**
* @brief  USBH_USR_Product_String 
*         Displays the message on LCD for Product String
* @param  ProductString : Product String of Device
* @retval None
*/
void USBH_USR_Product_String(void *ProductString)
{
#ifdef DEBUG
  char temp[100];
  sprintf((char *)temp, "Product : %s\n", (char *)ProductString);  
  xputs(temp);
#endif
}

/**
* @brief  USBH_USR_SerialNum_String 
*         Displays the message on LCD for SerialNum_String 
* @param  SerialNumString : SerialNum_String of device
* @retval None
*/
void USBH_USR_SerialNum_String(void *SerialNumString)
{
#ifdef DEBUG
  uint8_t temp[100];
  sprintf((char *)temp, "Serial Number : %s\n", (char *)SerialNumString);    
  xputs(temp);
#endif
} 

/**
* @brief  EnumerationDone 
*         User response request is displayed to ask for
*         application jump to class
* @param  None
* @retval None
*/
void USBH_USR_EnumerationDone(void)
{
#ifdef DEBUG
	  xputs("> Enumeration completed\n");
#endif
} 

/**
* @brief  USBH_USR_DeviceNotSupported
*         Device is not supported
* @param  None
* @retval None
*/
void USBH_USR_DeviceNotSupported(void)
{
#ifdef DEBUG
	  xputs("> Device not supported.\n");
#endif
}  


/**
* @brief  USBH_USR_UserInput
*         User Action for application state entry
* @param  None
* @retval USBH_USR_Status : User response for key button
*/
USBH_USR_Status USBH_USR_UserInput(void)
{
  
  USBH_USR_Status usbh_usr_status;
  
//  usbh_usr_status = USBH_USR_NO_RESP;
    usbh_usr_status = USBH_USR_RESP_OK;
  
  /*Key B3 is in polling mode to detect user action */
//  if(STM_EVAL_PBGetState(Button_KEY) == RESET)
//  {
//
//    usbh_usr_status = USBH_USR_RESP_OK;
//
//  }
  
  
  return usbh_usr_status;
  
} 

/**
* @brief  USBH_USR_OverCurrentDetected
*         Device Overcurrent detection event
* @param  None
* @retval None
*/
void USBH_USR_OverCurrentDetected (void)
{
#ifdef DEBUG
	  xputs("Overcurrent detected.\n");
#endif
}


/**
* @brief  USBH_USR_DeInit
*         Deint User state and associated variables
* @param  None
* @retval None
*/
void USBH_USR_DeInit(void)
{
}

/**
* @brief  USBH_USR_ADK_Application
*         Application for ADK
* @param  None
* @retval Staus
*/
int USBH_USR_ADK_Application(void)
{
#ifdef DEBUG
	  xputs("> USBH_USR_ADK_Application\n");
#endif
  return(0);
}

/**
* @}
*/
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
