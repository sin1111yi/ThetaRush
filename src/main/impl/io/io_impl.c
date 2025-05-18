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

static implIOInterface_t g_implIOInterface = { 0 };

void
implIOInit (trArrow_t arrow)
{
  for (uint16_t i = IMPL_RES (IMPL_OUTPUT_IO, 1); i < IMPL_RES (IMPL_OUTPUT_IO, n); i++)
    {
      if (arrow.ires == i)
        {
          P_RESIO(arrow.pres, IMPL_MAP_PLATFORM_RES (IMPL_OUTPUT_IO, 1));
          P_RES (arrow.pres, M_OutputIO, m_IO1);
          break;
        }
    }
  stm32IOInit (arrow.pres);
}

bool
implIORead (trArrow_t arrow)
{
  UNUSED (arrow);

  return true;
}

void
implIOWrite (trArrow_t arrow)
{
  UNUSED (arrow);
}

void
implIOHi (trArrow_t arrow)
{
  UNUSED (arrow);
}

void
implIOLo (trArrow_t arrow)
{
  UNUSED (arrow);
}

void
implIOToggle (trArrow_t arrow)
{
  UNUSED (arrow);
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
