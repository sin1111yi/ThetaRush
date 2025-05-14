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

#include "target.h"

#if !defined(__PLATFORM_STM32__)
#define __PLATFORM_STM32__
#endif

#if defined(STM32H7)
#include "stm32h7xx.h"

#if defined(STM32H750xx)
#define MAX_MPU_REGIONS 16

#endif /* STM32H750xx */

#endif /* STM32H7 */
