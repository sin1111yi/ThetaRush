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

#include <stdbool.h>
#include <stdint.h>

#include "impl/impl_defs.h"
#include "impl/impl_platform.h"
#include "impl/io/io_impl.h"

#include "platform/periph/io/io_af.h"
#include "platform/platform.h"

typedef struct __periphIO_s
{
  IO_t IO;
  IOAF_T afio;
  implRes_t ioRes;
} periphIO_t;

bool stm32IOInit (IO_t IO);
void stm32IORead (IO_t IO);
void stm32IOWrite (IO_t IO);
void stm32IOHi (IO_t IO);
void stm32IOLo (IO_t IO);
void stm32IOToggle (IO_t IO);
