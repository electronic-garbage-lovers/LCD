/**
  ******************************************************************************
  * @file    LIB_Config.h
  * @author  Waveshare Team
  * @version 
  * @date    13-October-2014
  * @brief     This file provides configurations for low layer hardware libraries.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WAVESHARE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _USE_LIB_CONFIG_H_
#define _USE_LIB_CONFIG_H_
//Macro Definition

/* Includes ------------------------------------------------------------------*/
#include "MacroAndConst.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

//Config
#include "Config.h"
/*------------------------------------------------------------------------------------------------------*/

//delay
#include "delay.h"

/*------------------------------------------------------------------------------------------------------*/
//SPI
#include "SPI.h"

/*------------------------------------------------------------------------------------------------------*/
//SSD1331
#include "SSD1331.h"
#include "Fonts.h"

#define SSD1331_RES_PIN         GPIO_Pin_2
#define SSD1331_DC_PIN          GPIO_Pin_6
#define SSD1331_CS_PIN          GPIO_Pin_12

#define SSD1331_RES_GPIO        GPIOC
#define SSD1331_DC_GPIO         GPIOC
#define SSD1331_CS_GPIO         GPIOB

#define __SSD1331_RES_SET()     GPIO_WriteBit(SSD1331_RES_GPIO, SSD1331_RES_PIN, Bit_SET)
#define __SSD1331_RES_CLR()     GPIO_WriteBit(SSD1331_RES_GPIO, SSD1331_RES_PIN, Bit_RESET)

#define __SSD1331_DC_SET()      GPIO_WriteBit(SSD1331_DC_GPIO, SSD1331_DC_PIN, Bit_SET)
#define __SSD1331_DC_CLR()      GPIO_WriteBit(SSD1331_DC_GPIO, SSD1331_DC_PIN, Bit_RESET)

#define __SSD1331_CS_SET()      GPIO_WriteBit(SSD1331_CS_GPIO, SSD1331_CS_PIN, Bit_SET)
#define __SSD1331_CS_CLR()      GPIO_WriteBit(SSD1331_CS_GPIO, SSD1331_CS_PIN, Bit_RESET)

#define SSD1331_SCLK_PIN        GPIO_Pin_13
#define SSD1331_SDIN_PIN        GPIO_Pin_15

#define SSD1331_SCLK_GPIO       GPIOB
#define SSD1331_SDIN_GPIO       GPIOB

#define __SSD1331_SCLK_SET()    GPIO_WriteBit(SSD1331_SCLK_GPIO, SSD1331_SCLK_PIN, Bit_SET)
#define __SSD1331_SCLK_CLR()    GPIO_WriteBit(SSD1331_SDIN_GPIO, SSD1331_SDIN_PIN, Bit_RESET)

#define __SSD1331_WRITE_BYTE(__DATA) spi_read_write_byte(SPI2, __DATA)

/*------------------------------------------------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */


#endif

/*-------------------------------END OF FILE-------------------------------*/

