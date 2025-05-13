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

#include "impl/impl_defs.h"
#include "impl/impl_platform.h"
#include "impl/io/io_defs.h"
#include "impl/io/io_impl.h"
#include "utils/utils.h"

#include "platform/periph/io/io.h"

static implIOInterface_t g_implIOInterface = { 0 };

void
implIOInit (implClew_t clew)
{
#if defined(__PLATFORM_STM32__)

#else
  NOP;
#endif
}

bool
implIORead (implClew_t clew)
{
#if defined(__PLATFORM_STM32__)
#else
  NOP;
  return true;
#endif
}

void
implIOWrite (implClew_t clew)
{
#if defined(__PLATFORM_STM32__)
#else
  NOP;
#endif
}

void
implIOHi (implClew_t clew)
{
#if defined(__PLATFORM_STM32__)
#else
  NOP;
#endif
}

void
implIOLo (implClew_t clew)
{
#if defined(__PLATFORM_STM32__)
#else
  NOP;
#endif
}

void
implIOToggle (implClew_t clew)
{
#if defined(__PLATFORM_STM32__)
#else
  NOP;
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
