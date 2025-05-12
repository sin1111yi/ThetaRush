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

#include "drivers/light/led.h"
#include "drivers/drv_defs.h"

#include "impl/impl_defs.h"
#include "impl/io/io_impl.h"

static drvLightLed_t devRunLeds[DRV_NUM_OF_RUN_LED];

void
drvLedInit (trDevice_t dev)
{
  drvLightLed_t *instance
      = &devRunLeds[dev - DRV_DEVICE_ID_BASE (DEV_RUN_LED)];
  instance->dev = dev;
  if (dev == TR_DEVICE (DEV_RUN_LED, 1))
    {
#if defined(RUN_LED_1__PIN)
      instance->binder = implDevBindRes (dev, IMPL_RES_IO (RUN_LED_1__PIN));
      implIOInterfaceHandle ()->pIOInit (IMPL_RES_IO (RUN_LED_1__PIN));
#endif
    }
}

void
drvLedOn (trDevice_t dev)
{
}

void
drvLedOff (trDevice_t dev)
{
}

void
drvLedToggle (trDevice_t dev)
{
}
