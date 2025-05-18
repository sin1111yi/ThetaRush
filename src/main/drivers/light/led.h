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

#include "impl/impl_defs.h"

#include "drivers/dev_defs.h"

typedef enum __drvLightLedState_e
{
  lightLedSta_On,
  lightLedSta_Off,
} drvLightLedState_t;

typedef struct __drvLightLed_s
{
  trArrow_t arrow;
  drvLightLedState_t sta;
} drvLightLed_t;

void drvLedInit (trDevice_t dev);
void drvLedOn (trDevice_t dev);
void drvLedOff (trDevice_t dev);
void drvLedToggle (trDevice_t dev);
