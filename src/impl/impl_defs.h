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

#include "drivers/dev_defs.h"
#include "platform/pfm_defs.h"
#include "utils/utils.h"

#define IMPL_DISCARD_INTERFACE DEFAULT_NONE_INTERFACE

enum __implRes_e
{
  none,
  outputIO,
  inputIO,
  resCount,
};

/**
 * @brief Every tr device need a driver
 *        Id of ThetaRush devices starts from 1
 *
 */

#define IMPL_RES(res, id) CONTACT3 (resource__, res##_, id)
#define IMPL_RES_ID_BASE(res) IMPL_RES (res, set, 1),
#define IMPL_RES_NONE IMPL_RES (none, 0)
#define IMPL_RES_COUNT(res) (IMPL_RES (res, n) - IMPL_RES (res, 1))

#define IMPL_RES_IS(implRes, res)                                             \
  ((implRes >= IMPL_RES (res, 1) && implRes <= IMPL_RES (res, n)) ? 1 : 0)

typedef enum __implResource_e
{
  IMPL_RES (none, 0) = 0,

  IMPL_RES (outputIO, 1),
  IMPL_RES (outputIO, n),

  IMPL_RES (inputIO, 1),
  IMPL_RES (inputIO, n),

  IMPL_RES (resCount, 0)

} implResource_t;

typedef struct __implClew_s
{
  trDevice_t dev;          // device clew
  implResource_t ires;     // impl resource
  platfromResource_t pres; // platform resource
} implClew_t;
