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

#include "drivers/drv.h"

#include "tr/impl.h"
#include "tr/init.h"
#include "tr/sys.h"

#include "stm32h7xx.h"

void
systemInit (void)
{
  trImplInit ();
  trDrvInit ();
}

void
systemRun (void)
{
  while (1)
    {
      HAL_GPIO_TogglePin (GPIOE, GPIO_PIN_3);
      HAL_Delay (200);
    }
}

static trSystemHandle_t g_trSystemHandle = {
  .systemState = system_state_bootup,
  .pSystemInit = systemInit,
  .pSystemRun = systemRun,
};

trSystemHandle_t *
trSystemHandle (void)
{
  return &g_trSystemHandle;
}
