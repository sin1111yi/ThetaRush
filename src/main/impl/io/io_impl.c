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

#include <stdbool.h>
#include <stdlib.h>

#include "utils/utils.h"

#include "impl/impl_defs.h"
#include "impl/io/io_impl.h"

#include "platform/periph/io/io.h"

#include "tr/ds/ll.h"

static implIOInterface_t g_implIOInterface = { 0 };

static void
__implIOConfigPlatformTag (trArrow_t *arrow)
{
  switch (arrow->ires)
    {
#define _implIoCaseOutputIO(k)                                                \
  case IMPL_RES (IMPL_OUTPUT_IO, k):                                          \
    PG_RESIO (arrow->pres, IMPL_MAP_PLATFORM_RES (IMPL_OUTPUT_IO, k));        \
    PG_RES (arrow->pres, M_OutputIO, m_IO##k);                                \
    break;

      _implIoCaseOutputIO (1);

    default:
      break;
    }
}

void
implIOInit (trArrow_t arrow)
{
  bool isInputIO = 0;

  __implIOConfigPlatformTag (&arrow);

  if (platformGetMajorRes (arrow.pres) == PLATFORM_RES_MAJOR (M_InputIO))
    isInputIO = true;
  else
    isInputIO = false;

#if defined(RUNNING_PLATFORM_IS_STM32)
  if (!isInputIO)
    stm32IOInit (arrow.pres);
  else
    stm32IOInitExti (arrow.pres, NULL);
#endif
}

bool
implIORead (trArrow_t arrow)
{
  __implIOConfigPlatformTag (&arrow);

#if defined(RUNNING_PLATFORM_IS_STM32)
    return stm32IORead (arrow.pres);
#endif
}

void
implIOWrite (trArrow_t arrow, implIOStat_t sta)
{
  __implIOConfigPlatformTag (&arrow);

#if defined(RUNNING_PLATFORM_IS_STM32)
    stm32IOWrite (arrow.pres, sta);
#endif
}

void
implIOHi (trArrow_t arrow)
{
  __implIOConfigPlatformTag (&arrow);

#if defined(RUNNING_PLATFORM_IS_STM32)
    stm32IOHi (arrow.pres);
#endif
}

void
implIOLo (trArrow_t arrow)
{
  __implIOConfigPlatformTag (&arrow);

#if defined(RUNNING_PLATFORM_IS_STM32)
    stm32IOLo (arrow.pres);
#endif
}

void
implIOToggle (trArrow_t arrow)
{
  __implIOConfigPlatformTag (&arrow);

#if defined(RUNNING_PLATFORM_IS_STM32)
    stm32IOToggle (arrow.pres);
#endif
}

void
implIOInterfaceInit (void)
{
  implIOInterface_t *pInterface = &g_implIOInterface;

  pInterface->pIOInit = implIOInit;
  pInterface->pIORead = implIORead;
  pInterface->pIOWrite = implIOWrite;
  pInterface->pIOHi = implIOHi;
  pInterface->pIOLo = implIOLo;
  pInterface->pIOToggle = implIOToggle;
}

implIOInterface_t *
implIOInterfaceHandle (void)
{
  return &g_implIOInterface;
}
