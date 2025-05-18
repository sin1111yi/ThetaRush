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

#include <stdint.h>

#include "utils/utils.h"

#include "platform/resource.h"

#include "drivers/dev_defs.h"

#define IMPL_DISCARD_INTERFACE DEFAULT_NONE_INTERFACE
#define IMPL_MAP_PLATFORM_RES(impl, id) CONTACT3(impl, _##id, __MAP__PLATFORM_RES)
/**
 * @brief Every tr device need a driver
 *        Id of ThetaRush devices starts from 1
 *
 */

#define IMPL_RES(res, id) CONTACT3 (implResource__, res##_, id)
#define IMPL_RES_ID_BASE(res) IMPL_RES (res, set, 1),
#define IMPL_RES_NONE IMPL_RES (none, 0)
#define IMPL_RES_COUNT(res) (IMPL_RES (res, n) - IMPL_RES (res, 1))

enum __implRes_e
{
  IMPL_NONE,
  IMPL_OUTPUT_IO,
  IMPL_INPUT_IO,
  IMPL_RES_COUNT,
};

typedef enum __implResource_e
{
  IMPL_RES (IMPL_NONE, 0) = 0,

  IMPL_RES (IMPL_OUTPUT_IO, 1),
  IMPL_RES (IMPL_OUTPUT_IO, n),

  IMPL_RES (IMPL_INPUT_IO, 1),
  IMPL_RES (IMPL_INPUT_IO, n),

  IMPL_RES (IMPL_RES_COUNT, 0)

} implResource_t;

typedef struct __trArrow_s
{
  trDevice_t dev;          // device arrow
  implResource_t ires;     // impl resource
  platformResource_t pres; // platform resource
} trArrow_t;
