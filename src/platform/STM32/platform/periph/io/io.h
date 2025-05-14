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

#include "platform/periph/io/io_af.h"
#include "platform/periph/io/io.h"

#include "impl/impl_defs.h"
#include "impl/io/io_impl.h"

void stm32IOInit (ioRes_t ioRes);
bool stm32IORead (ioRes_t ioRes);
void stm32IOWrite (ioRes_t ioRes);
void stm32IOHi (ioRes_t ioRes);
void stm32IOLo (ioRes_t ioRes);
void stm32IOToggle (ioRes_t ioRes);
