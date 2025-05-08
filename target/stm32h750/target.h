/**
 * This file is a part of ThetaRush.
 *
 * ThetaRush is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ThetaRush is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.
 *
 * If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#ifndef STM32H750xx         
#define STM32H750xx         
#endif /* STM32H750xx */

#ifndef STM32H7             
#define STM32H7             
#endif /* STM32H7 */

#ifndef TARGET_IDENTIFIER   
#define TARGET_IDENTIFIER    "weact_stm32h750vbtx_core_board"
#endif /* TARGET_IDENTIFIER */

#define GPIO_OUTPUT1_PIN     PE3
/**
 * Bus UART1
 */
#define USE_BUS_UART1        1
#define USE_BUS_UART1_DMA    1
#define BUS_UART1_TX_PIN     PB14
#define BUS_UART1_RX_PIN     PB15
/**
 * Bus SPI1
 */
#define USE_BUS_SPI1         1
#define USE_BUS_SPI1_DMA     1
#define BUS_SPI1_MOSI_PIN    PA5
#define BUS_SPI1_MISO_PIN    PA6
#define BUS_SPI1_SCLK_PIN    PA7
/**
 * Bus I2C1
 */
#define USE_BUS_I2C1         1
#define USE_BUS_I2C1_DMA     1
#define BUS_I2C1_SCK_PIN     PB7
#define BUS_I2C1_SDA_PIN     PB8
