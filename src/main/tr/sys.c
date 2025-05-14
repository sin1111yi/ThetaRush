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

#include "tr/sys.h"
#include "tr/init.h"

void
systemInit (void)
{
  trDrvInit ();
}

void
systemRun (void)
{
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
