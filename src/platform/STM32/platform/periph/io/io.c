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

#include "platform/periph/io/io.h"
#include "platform/periph/io/io_af.h"
#include "platform/platform.h"

#define GPIO_BASE GPIOA_BASE
#define GPIOX(x) ((uint32_t)(GPIO_BASE + ((x) << 10)))
#define PIN(x) ((uint16_t)(1 << x))

void
stm32IOInit (ioRes_t ioRes)
{
  GPIO_TypeDef *gpiox = (GPIO_TypeDef *)(GPIOX (platformGetGpioPort (ioRes)));
  uint16_t pin = PIN (platformGetGpioPin (ioRes));

  GPIO_InitTypeDef GPIO_InitStruct = { 0 };

  GPIO_InitStruct.Pin = pin;

  __HAL_RCC_GPIOE_CLK_ENABLE ();
  __HAL_RCC_GPIOC_CLK_ENABLE ();
  __HAL_RCC_GPIOH_CLK_ENABLE ();
  __HAL_RCC_GPIOB_CLK_ENABLE ();
  __HAL_RCC_GPIOA_CLK_ENABLE ();

  if (platformGetMajorRes (ioRes) == PLATFORM_RES_MAJOR (M_OutputIO))
    {
      HAL_GPIO_WritePin (gpiox, pin, GPIO_PIN_RESET);
      GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    }

    HAL_GPIO_Init(gpiox, &GPIO_InitStruct);
}

bool
stm32IORead (ioRes_t ioRes)
{
  UNUSED (ioRes);

  return true;
}

void
stm32IOWrite (ioRes_t ioRes)
{
  UNUSED (ioRes);
}

void
stm32IOHi (ioRes_t ioRes)
{
  UNUSED (ioRes);
}

void
stm32IOLo (ioRes_t ioRes)
{
  UNUSED (ioRes);
}

void
stm32IOToggle (ioRes_t ioRes)
{
  UNUSED (ioRes);
}
