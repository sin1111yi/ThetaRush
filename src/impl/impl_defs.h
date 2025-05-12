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

#include "impl/impl_platform.h"
#include "impl/io/io_defs.h"

#include "drivers/drv_defs.h"

#define IMPL_DISCARD_INTERFACE DEFAULT_NONE_INTERFACE

#define DEV_BIND_RES(dev, res) ((uint32_t)(((dev) << 24) | (res)))
#define BIND_GET_DEV(bind) ((uint32_t)((bind) & 0xff000000) >> 24)
#define BIND_GET_RES(bind) ((uint32_t)((bind) & 0x00ffffff))

#define IMPL_RES_IO(io) DEFIO_RES (io)
#define IMPL_RES_IO_NONE DEFIO_RES__NONE

typedef struct __implBinder_s
{
  trDev_t dev;
  implRes_t res;
} implBinder_t;

static inline implBinder_t
implDevBindRes (trDev_t dev, implRes_t res)
{
  implBinder_t binder = {
    .dev = dev,
    .res = res,
  };

  return binder;
}

static inline trDev_t
implBindGetDev (implBinder_t binder)
{
  return binder.dev;
}

static inline implRes_t
implBindGetRes (implBinder_t binder)
{
  return binder.res;
}
