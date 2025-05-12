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

#include <stdint.h>

#define TR_DEVICE(dev, id) DEVICE_##dev##_##id

#define DRV_DEVICE_ID_BASE(dev) TR_DEVICE (dev, 1)

#define DRV_NUM_OF_CLOCK 1
#define DRV_NUM_OF_RUN_LED 3

enum __device_e
{
  DEV_NONE,
  DEV_CLOCK,
  DEV_RUN_LED,
  DEV_LED,
  DEV_LED_STRIP,
  DEV_IMU,
  DEV_MAGN,
  DEV_BARO,
  DEV_MOTOR,
  DEV_END,
};

/**
 * @brief Id of ThetaRush devices starts from 1
 *
 */
typedef enum __trDevice_e
{
  TR_DEVICE (DEV_NONE, 1) = 0,

  TR_DEVICE (DEV_CLOCK, 1),

  TR_DEVICE (DEV_RUN_LED, 1),
  TR_DEVICE (DEV_RUN_LED, 2),
  TR_DEVICE (DEV_RUN_LED, 3),

  TR_DEVICE (DEV_LED, 1),

  TR_DEVICE (DEV_END, 1)
} trDevice_t;

typedef uint32_t trDev_t;