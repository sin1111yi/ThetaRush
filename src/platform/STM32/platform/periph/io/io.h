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

#include "stm32h7xx.h"

#include "impl/resource.h"
#include "impl/io/io_impl.h"

#include "platform/periph/io/io_af.h"

#ifdef STM32H7
#define __GPIO_BASE D3_AHB1PERIPH_BASE
#endif
#define __STM32_GPIOX(x) ((uint32_t)(__GPIO_BASE + ((x) << 10)))
#define __STM32_PIN(x) ((uint16_t)(1 << x))

void stm32IOInit (ioRes_t ioRes);
bool stm32IORead (ioRes_t ioRes);
void stm32IOWrite (ioRes_t ioRes, implIOStat_t sta);
void stm32IOHi (ioRes_t ioRes);
void stm32IOLo (ioRes_t ioRes);
void stm32IOToggle (ioRes_t ioRes);

void stm32IOInitExti (ioRes_t ioRes, void (*callback) (void));
