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

#include "platform/periph/rcc/rcc.h"

void
stm32RccClockCmd (platformRccPeriph_t platformRccPeriph,
                  FunctionalState newState)
{
  int tag = platformRccPeriph >> 5;
  uint32_t mask = 1 << (platformRccPeriph & 0x1f);

#if defined(USE_HAL_DRIVER)

  // Note on "suffix" macro parameter:
  // ENR and RSTR naming conventions for buses with multiple registers per bus
  // differs among MCU types. ST decided to use AxBn{L,H}ENR convention for H7
  // which can be handled with simple "ENR" (or "RSTR") contatenation, while
  // use AxBnENR{1,2} convention for G4 which requires extra "suffix" to be
  // concatenated. Here, we use "suffix" for all MCU types and leave it as
  // empty where not applicable.

#define NOSUFFIX // Empty

#define __HAL_RCC_CLK_ENABLE(bus, suffix, enbit)                              \
  do                                                                          \
    {                                                                         \
      __IO uint32_t tmpreg;                                                   \
      SET_BIT (RCC->bus##ENR##suffix, enbit);                                 \
      /* Delay after an RCC peripheral clock enabling */                      \
      tmpreg = READ_BIT (RCC->bus##ENR##suffix, enbit);                       \
      UNUSED (tmpreg);                                                        \
    }                                                                         \
  while (0)

#define __HAL_RCC_CLK_DISABLE(bus, suffix, enbit)                             \
  (RCC->bus##ENR##suffix &= ~(enbit))

#define __HAL_RCC_CLK(bus, suffix, enbit, newState)                           \
  if (newState == ENABLE)                                                     \
    {                                                                         \
      __HAL_RCC_CLK_ENABLE (bus, suffix, enbit);                              \
    }                                                                         \
  else                                                                        \
    {                                                                         \
      __HAL_RCC_CLK_DISABLE (bus, suffix, enbit);                             \
    }

  switch (tag)
    {
    case RCC_AHB1:
      __HAL_RCC_CLK (AHB1, NOSUFFIX, mask, newState);
      break;

    case RCC_AHB2:
      __HAL_RCC_CLK (AHB2, NOSUFFIX, mask, newState);
      break;

#if !(defined(STM32H7))
    case RCC_APB1:
      __HAL_RCC_CLK (APB1, NOSUFFIX, mask, newState);
      break;
#endif

    case RCC_APB2:
      __HAL_RCC_CLK (APB2, NOSUFFIX, mask, newState);
      break;

#ifdef STM32H7

    case RCC_AHB3:
      __HAL_RCC_CLK (AHB3, NOSUFFIX, mask, newState);
      break;

    case RCC_AHB4:
      __HAL_RCC_CLK (AHB4, NOSUFFIX, mask, newState);
      break;

    case RCC_APB1L:
      __HAL_RCC_CLK (APB1L, NOSUFFIX, mask, newState);
      break;

    case RCC_APB1H:
      __HAL_RCC_CLK (APB1H, NOSUFFIX, mask, newState);
      break;

    case RCC_APB3:
      __HAL_RCC_CLK (APB3, NOSUFFIX, mask, newState);
      break;

    case RCC_APB4:
      __HAL_RCC_CLK (APB4, NOSUFFIX, mask, newState);
      break;
#endif
    }
#endif
}

void
stm32RccResetCmd (platformRccPeriph_t platformRccPeriph,
                  FunctionalState newState)
{
  int tag = platformRccPeriph >> 5;
  uint32_t mask = 1 << (platformRccPeriph & 0x1f);

  // Peripheral reset control relies on RSTR bits are identical to ENR bits
  // where applicable

#define __HAL_RCC_FORCE_RESET(bus, suffix, enbit)                             \
  (RCC->bus##RSTR##suffix |= (enbit))
#define __HAL_RCC_RELEASE_RESET(bus, suffix, enbit)                           \
  (RCC->bus##RSTR##suffix &= ~(enbit))
#define __HAL_RCC_RESET(bus, suffix, enbit, NewState)                         \
  if (NewState == ENABLE)                                                     \
    {                                                                         \
      __HAL_RCC_RELEASE_RESET (bus, suffix, enbit);                           \
    }                                                                         \
  else                                                                        \
    {                                                                         \
      __HAL_RCC_FORCE_RESET (bus, suffix, enbit);                             \
    }
#if defined(USE_HAL_DRIVER)

  switch (tag)
    {
    case RCC_AHB1:
      __HAL_RCC_RESET (AHB1, NOSUFFIX, mask, newState);
      break;

    case RCC_AHB2:
      __HAL_RCC_RESET (AHB2, NOSUFFIX, mask, newState);
      break;

#if !defined(STM32H7)
    case RCC_APB1:
      __HAL_RCC_RESET (APB1, NOSUFFIX, mask, NewState);
      break;
#endif

    case RCC_APB2:
      __HAL_RCC_RESET (APB2, NOSUFFIX, mask, newState);
      break;

#ifdef STM32H7

    case RCC_AHB3:
      __HAL_RCC_RESET (AHB3, NOSUFFIX, mask, newState);
      break;

    case RCC_AHB4:
      __HAL_RCC_RESET (AHB4, NOSUFFIX, mask, newState);
      break;

    case RCC_APB1L:
      __HAL_RCC_RESET (APB1L, NOSUFFIX, mask, newState);
      break;

    case RCC_APB1H:
      __HAL_RCC_RESET (APB1H, NOSUFFIX, mask, newState);
      break;

    case RCC_APB3:
      __HAL_RCC_RESET (APB3, NOSUFFIX, mask, newState);
      break;

    case RCC_APB4:
      __HAL_RCC_RESET (APB4, NOSUFFIX, mask, newState);
      break;
#endif
    }
#endif
}
