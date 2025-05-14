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
#include "platform/platform.h"

static implIOInterface_t g_implIOInterface = { 0 };

void
implIOInit (clew_t clew)
{
  for (uint16_t i = 1; i < IMPL_RES_COUNT (IMPL_OUTPUT_IO); i++)
    {
      if (clew.ires == i)
        {
          P_RESIO(clew.pres, IMPL_MAP_PLATFORM_RES (IMPL_OUTPUT_IO, 1));
          P_RES (clew.pres, M_OutputIO, m_IO1);
          break;
        }
    }
  stm32IOInit (clew.pres);
}

bool
implIORead (clew_t clew)
{
  UNUSED (clew);

  return true;
}

void
implIOWrite (clew_t clew)
{
  UNUSED (clew);
}

void
implIOHi (clew_t clew)
{
  UNUSED (clew);
}

void
implIOLo (clew_t clew)
{
  UNUSED (clew);
}

void
implIOToggle (clew_t clew)
{
  UNUSED (clew);
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
