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

#include "utils/utils.h"

#include "platform/periph/io/io_defs.h"

#define DEFIO_TAG__(pinid) CONTACT (DEFIO_TAG_E__, pinid)
#define DEFIO_TAG(port, pin) ((uint16_t)((DEF_GPIO##port) << 4 | pin))

/**
 * @brief for platformResource_t
 *        [0:3] GPIO Pin Number
 *              e.g. PC13 has pin number 13 -> 0b 00 1101
 *        [4:7] GPIO Port Index
 *              e.g. PC13 has GPIOC -> 0b 00 1100
 *        [8:11] Platform Source Minor Part
 *              e.g. PE3 is output IO 1 -> 0xb0001 for 1
 *                   PE9 is timer1 Channel 1 -> 0b0001 for channel 1
 *        [12:15] Platform Source Major Part
 *              e.g. PE9 is timer1 Channel 1 -> M_resTIM
 *
 *
 */
typedef uint32_t platformResource_t;

typedef platformResource_t ioRes_t;

#define PLATFORM_RES_MAJOR(source) CONTACT (platformRes_Major_, source)
#define PLATFORM_RES_MINOR(source) CONTACT (platformRes_Minor_, source)

#define PG_RES(pres, major, minor)                                             \
  do                                                                          \
    {                                                                         \
      pres = (pres & 0xffff0fff) | (PLATFORM_RES_MAJOR (major) << 12);        \
      pres = (pres & 0xfffff0ff) | (PLATFORM_RES_MINOR (minor) << 8);         \
    }                                                                         \
  while (0)

#define PG_RESIO(pres, map)                                                    \
  do                                                                          \
    {                                                                         \
      pres = (pres & 0xffffff00) | DEFIO_TAG__ (map);                         \
    }                                                                         \
  while (0)

enum __majorPlatfromRes_e
{
  M_OutputIO,
  M_InputIO,

  M_UART1,

  M_TIMER1,

  M_resCount,
};

/* this enum must has the same order as the __majorPlatfromRes_e */
enum __platformResourceMajor_e
{
  PLATFORM_RES_MAJOR (M_OutputIO),
  PLATFORM_RES_MAJOR (M_InputIO),
  PLATFORM_RES_MAJOR (M_UART1),

  PLATFORM_RES_MAJOR (M_resCount),
};

enum __minorPlatfromRes_e
{
  m_None,
  m_IO1 = 1,
  m_IO2,
  m_IO3,
  m_IO4,
  m_IO5,
  m_IO6,
  m_IO7,
  m_IO8,
  m_IO9,
  m_IO10,
  m_IO11,
  m_IO12,
  m_IO13,
  m_IO14,
  m_IO15,
  m_IO16, // The maximum number of input/output IO is 16, total 32

  m_CH1,
  m_CH2,
  m_CH3,
  m_CH4,
  m_CH5,
  m_CH6, // The maximum number of TIM channel is 6

  m_Tx,
  m_Rx, // UART Tx and Rx

  m_resCount,
};

/* this enum must has the same order as the __minorPlatfromRes_e */
enum __platformResourceMinor_e
{
  
  PLATFORM_RES_MINOR (m_None),
  PLATFORM_RES_MINOR (m_IO1) = 1,
  PLATFORM_RES_MINOR (m_IO2),
  PLATFORM_RES_MINOR (m_IO3),
  PLATFORM_RES_MINOR (m_IO4),
  PLATFORM_RES_MINOR (m_IO5),
  PLATFORM_RES_MINOR (m_IO6),
  PLATFORM_RES_MINOR (m_IO7),
  PLATFORM_RES_MINOR (m_IO8),
  PLATFORM_RES_MINOR (m_IO9),
  PLATFORM_RES_MINOR (m_IO10),
  PLATFORM_RES_MINOR (m_IO11),
  PLATFORM_RES_MINOR (m_IO12),
  PLATFORM_RES_MINOR (m_IO13),
  PLATFORM_RES_MINOR (m_IO14),
  PLATFORM_RES_MINOR (m_IO15),
  PLATFORM_RES_MINOR (m_IO16),

  PLATFORM_RES_MINOR (m_CH1),
  PLATFORM_RES_MINOR (m_CH2),
  PLATFORM_RES_MINOR (m_CH3),
  PLATFORM_RES_MINOR (m_CH4),
  PLATFORM_RES_MINOR (m_CH5),
  PLATFORM_RES_MINOR (m_CH6),

  PLATFORM_RES_MINOR (m_Tx),
  PLATFORM_RES_MINOR (m_Rx),

  PLATFORM_RES_MINOR (m_resCount),
};

static inline uint8_t
platformGetGpioPin (platformResource_t res)
{
  return (uint8_t)(res & 0x0000000f);
}

static inline uint8_t
platformGetGpioPort (platformResource_t res)
{
  return (uint8_t)((res & 0x000000f0) >> 4);
}

static inline uint8_t
platformGetMinorRes (platformResource_t res)
{
  return (uint8_t)((res & 0x00000f00) >> 8);
}

static inline uint8_t
platformGetMajorRes (platformResource_t res)
{
  return (uint8_t)((res & 0x0000f000) >> 12);
}
