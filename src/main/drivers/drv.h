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

#include "drivers/light/led.h"

typedef struct __drvInterface_s
{
  /* LED Interfaces */
  void (*pLedInit) (trDevice_t dev);
  void (*pLedOn) (trDevice_t dev);
  void (*pLedOff) (trDevice_t dev);
  void (*pLedToggle) (trDevice_t dev);
} drvInterface_t;

drvInterface_t *drvInterfaceHandle (void);
