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

#include "target.h"

#include "drivers/light/led.h"

#include "impl/impl_defs.h"
#include "impl/io/io_impl.h"

static drvLightLed_t devRunLeds[DRV_NUM_OF_RUN_LED];

static drvLightLed_t *
__drvLedGetInstance (trDevice_t dev)
{
  drvLightLed_t *instance = &devRunLeds[dev - DRV_DEVICE_COUNT (devRunLed)];
  instance->arrow.dev = dev;

  switch (dev)
    {
#if defined(USING_RUN_LED_1)
    case TR_DEVICE (devRunLed, 1):
      instance->arrow.ires = RUN_LED_1_DRV_IMPL;
      break;
#endif
#if defined(USING_RUN_LED_2)
    case TR_DEVICE (devRunLed, 2):
      instance->arrow.ires = RUN_LED_2_DRV_IMPL;
      break;
#endif
#if defined(USING_RUN_LED_3)
    case TR_DEVICE (devRunLed, 3):
      instance->arrow.ires = RUN_LED_3_DRV_IMPL;
      break;
#endif
    default:
      break;
    }

  return instance;
}

void
drvLedInit (trDevice_t dev)
{
  drvLightLed_t *instance = __drvLedGetInstance (dev);
  implIOInterfaceHandle ()->pIOInit (instance->arrow);
}

void
drvLedOn (trDevice_t dev)
{
  drvLightLed_t *instance = __drvLedGetInstance (dev);
#if (!defined(LED_DRIVER_MODE) || LED_DRIVER_MODE == 0)
  implIOInterfaceHandle ()->pIOWrite (instance->arrow, IMPL_IO_STAT_LOW);
#else
  implIOInterfaceHandle ()->pIOWrite (instance->arrow, IMPL_IO_STAT_HIGH);
#endif
}

void
drvLedOff (trDevice_t dev)
{
  drvLightLed_t *instance = __drvLedGetInstance (dev);
#if (!defined(LED_DRIVER_MODE) || LED_DRIVER_MODE == 0)
  implIOInterfaceHandle ()->pIOWrite (instance->arrow, IMPL_IO_STAT_HIGH);
#else
  implIOInterfaceHandle ()->pIOWrite (instance->arrow, IMPL_IO_STAT_LOW);
#endif
}

void
drvLedToggle (trDevice_t dev)
{
  drvLightLed_t *instance = __drvLedGetInstance (dev);
  implIOInterfaceHandle ()->pIOToggle (instance->arrow);
}
