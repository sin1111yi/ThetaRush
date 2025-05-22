/**
 * This file is part of Cleanflight, Betaflight and ThetaRush.
 *
 * Cleanflight, Betaflight and ThetaRush are free software. You can
 * redistribute this software and/or modify this software under the
 * terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight, Betaflight and ThetaRush are distributed in the hope that
 * they will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdint.h>

#include "utils/utils.h"

#include "platform/platform.h"

typedef uint16_t platformRccPeriph_t;

enum platfromRccReg_t
{
  RCC_EMPTY = 0,
#if defined (STM32H7)
  RCC_AHB,
  RCC_APB2,
  RCC_APB1L,
  RCC_APB1H,
  RCC_AHB1,
  RCC_AHB2,
  RCC_AHB3,
  RCC_APB3,
  RCC_AHB4,
  RCC_APB4,
#endif
};

#define RCC_ENCODE(reg, mask) (((reg) << 5) | LOG2_32BIT (mask))

#if defined(STM32H7)
#define RCC_AHB(periph) RCC_ENCODE (RCC_AHB, RCC_AHBENR_##periph##EN)
#define RCC_APB2(periph) RCC_ENCODE (RCC_APB2, RCC_APB2ENR_##periph##EN)
#define RCC_AHB1(periph) RCC_ENCODE (RCC_AHB1, RCC_AHB1ENR_##periph##EN)
#define RCC_AHB2(periph) RCC_ENCODE (RCC_AHB2, RCC_AHB2ENR_##periph##EN)
#define RCC_AHB3(periph) RCC_ENCODE (RCC_AHB3, RCC_AHB3ENR_##periph##EN)
#define RCC_APB3(periph) RCC_ENCODE (RCC_APB3, RCC_APB3ENR_##periph##EN)
#define RCC_AHB4(periph) RCC_ENCODE (RCC_AHB4, RCC_AHB4ENR_##periph##EN)
#define RCC_APB4(periph) RCC_ENCODE (RCC_APB4, RCC_APB4ENR_##periph##EN)
#define RCC_APB1L(periph) RCC_ENCODE (RCC_APB1L, RCC_APB1LENR_##periph##EN)
#define RCC_APB1H(periph) RCC_ENCODE (RCC_APB1H, RCC_APB1HENR_##periph##EN)
#endif

void stm32RccClockCmd (platformRccPeriph_t platformRccPeriph,
                       FunctionalState newState);
void stm32RccResetCmd (platformRccPeriph_t platformRccPeriph,
                       FunctionalState newState);
