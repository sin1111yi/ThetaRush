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

#include "stm32h7xx.h"

#include "impl/resource.h"

#include "platform/periph/io/io.h"
#include "platform/periph/io/io_af.h"
#include "platform/periph/rcc/rcc.h"

#ifdef STM32H7
#define __GPIO_BASE ((uint32_t)(D3_AHB1PERIPH_BASE))
#endif
#define __STM32_GPIOX(x) ((uint32_t)(__GPIO_BASE + ((x) << 10)))
#define __STM32_PIN(x) ((uint16_t)(1 << x))

struct ioGpioxRcc_s
{
  platformRccPeriph_t rcc;
};

const struct ioGpioxRcc_s ioGpioxRcc[] = {
  { RCC_AHB4 (GPIOA) }, { RCC_AHB4 (GPIOB) }, { RCC_AHB4 (GPIOC) },
  { RCC_AHB4 (GPIOD) }, { RCC_AHB4 (GPIOE) }, { RCC_AHB4 (GPIOF) },
  { RCC_AHB4 (GPIOG) }, { RCC_AHB4 (GPIOH) },
#if !(defined(STM32H723xx) || defined(SYM32H725xx) || defined(STM32H730xx))
  { RCC_AHB4 (GPIOI) },
#endif
};

void
stm32IOInit (ioRes_t ioRes)
{
  GPIO_TypeDef *gpiox
      = (GPIO_TypeDef *)(__STM32_GPIOX (platformGetGpioPort (ioRes)));
  uint16_t pin = __STM32_PIN (platformGetGpioPin (ioRes));

  GPIO_InitTypeDef GPIO_InitStruct = { 0 };

  uint32_t idx = ((uint32_t)gpiox - __GPIO_BASE) >> 10;
  platformRccPeriph_t rccPeriph = ioGpioxRcc[idx].rcc;
  stm32RccClockCmd (rccPeriph, ENABLE);

  GPIO_InitStruct.Pin = pin;

  if (platformGetMajorRes (ioRes) == PLATFORM_RES_MAJOR (M_OutputIO))
    {
      HAL_GPIO_WritePin (gpiox, pin, GPIO_PIN_RESET);
      GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    }

  HAL_GPIO_Init (gpiox, &GPIO_InitStruct);
}

bool
stm32IORead (ioRes_t ioRes)
{
  GPIO_TypeDef *gpiox
      = (GPIO_TypeDef *)(__STM32_GPIOX (platformGetGpioPort (ioRes)));
  uint16_t pin = __STM32_PIN (platformGetGpioPin (ioRes));

#if defined(USE_HAL_DRIVER)
  return HAL_GPIO_ReadPin (gpiox, pin);
#elif defined(USE_FULL_LL_DRIVER)
  return LL_GPIO_ReadInputPort (gpiox, pin);
#else
  return (gpiox->IDR & pin);
#endif

  return true;
}

void
stm32IOWrite (ioRes_t ioRes, implIOStat_t sta)
{
  GPIO_TypeDef *gpiox
      = (GPIO_TypeDef *)(__STM32_GPIOX (platformGetGpioPort (ioRes)));
  uint16_t pin = __STM32_PIN (platformGetGpioPin (ioRes));

#if defined(USE_HAL_DRIVER)
  HAL_GPIO_WritePin (gpiox, pin, (sta ? GPIO_PIN_SET : GPIO_PIN_RESET));
#elif defined(USE_FULL_LL_DRIVER)
  LL_GPIO_SetOutputPin (gpiox, pin << (sta ? 0 : 16));
#else
  gpio->BSRR = pin << (sta ? 0 : 16);
#endif
}

void
stm32IOHi (ioRes_t ioRes)
{
  GPIO_TypeDef *gpiox
      = (GPIO_TypeDef *)(__STM32_GPIOX (platformGetGpioPort (ioRes)));
  uint16_t pin = __STM32_PIN (platformGetGpioPin (ioRes));

#if defined(USE_HAL_DRIVER)
  HAL_GPIO_WritePin (gpiox, pin, GPIO_PIN_SET);
#elif defined(USE_FULL_LL_DRIVER)
  LL_GPIO_SetOutputPin (gpiox, pin);
#else
  gpio->BSRR = pin;
#endif
}

void
stm32IOLo (ioRes_t ioRes)
{
  GPIO_TypeDef *gpiox
      = (GPIO_TypeDef *)(__STM32_GPIOX (platformGetGpioPort (ioRes)));
  uint16_t pin = __STM32_PIN (platformGetGpioPin (ioRes));

#if defined(USE_HAL_DRIVER)
  HAL_GPIO_WritePin (gpiox, pin, GPIO_PIN_RESET);
#elif defined(USE_FULL_LL_DRIVER)
  LL_GPIO_ResetOutputPin (gpiox, pin);
#else
  gpio->BSRR = pin;
#endif
}

void
stm32IOToggle (ioRes_t ioRes)
{
  GPIO_TypeDef *gpiox
      = (GPIO_TypeDef *)(__STM32_GPIOX (platformGetGpioPort (ioRes)));
  uint16_t pin = __STM32_PIN (platformGetGpioPin (ioRes));

#if defined(USE_HAL_DRIVER)
  HAL_GPIO_TogglePin (gpiox, pin);
#elif defined(USE_FULL_LL_DRIVER)
  if (LL_GPIO_ReadOutputPort (gpiox) & pin)
    pin <<= 16;

  LL_GPIO_SetOutputPin (gpiox, pin);
#else
  if (gpiox->ODR & pin)
    pin <<= 16;

  gpiox->BSRR = pin;
#endif
}
