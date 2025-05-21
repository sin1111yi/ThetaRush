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

#define DRV_NUM_OF_CLOCK 1
#define DRV_NUM_OF_RUN_LED 3

enum __device_e
{
  devNone,
  devClock,
  devRunLed,
  devLed,
  devLedStrip,
  devKey,
  devImu,
  devCompass,
  devBarometer,
  devMotor,
  devCount,
};

/**
 * @brief Every tr device need a driver
 *        Id of ThetaRush devices starts from 1
 */

#define TR_DEVICE(dev, id) CONTACT3 (trDevice_, dev##_, id)

#define DRV_DEVICE_NONE TR_DEVICE (devNone, 1)
#define DRV_DEVICE_ID_BASE(dev) TR_DEVICE (dev, 1)
#define DRV_DEVICE_COUNT(dev) (TR_DEVICE (dev, n) - TR_DEVICE (dev, 1))

#define TR_PRIORITY(dev) CONTACT (trDevicePriority_, dev)

enum __trDevicePriority_e
{
  TR_PRIORITY (AMAZING_HIGH) = 0,

  TR_PRIORITY (VERY_HIGH) = 8,
  TR_PRIORITY (HIGH),
  TR_PRIORITY (NORMAL),
  TR_PRIORITY (LOW),
  TR_PRIORITY (VERY_LOW),
};

typedef enum __trDevice_e
{
  TR_DEVICE (devNone, 0) = 0,

  TR_DEVICE (devClock, 1),
  TR_DEVICE (devClock, n),

  TR_DEVICE (devRunLed, 1),
  TR_DEVICE (devRunLed, 2),
  TR_DEVICE (devRunLed, 3),
  TR_DEVICE (devRunLed, n),

  TR_DEVICE (devLed, 1),
  TR_DEVICE (devLed, n),

  TR_DEVICE (devKey, n),

  TR_DEVICE (devCount, 0)
} trDevice_t;
