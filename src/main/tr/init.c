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

#include "drivers/drv.h"

#include "tr/ds/init.h"

#include "tr/init.h"

void
trDrvInit (void)
{
  trDsInit ();

#if defined(USING_RUN_LED_1)
  drvInterfaceHandle ()->pLedInit (TR_DEVICE (devRunLed, 1));
#endif
}
