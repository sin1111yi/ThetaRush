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

#include "impl/impl_platform.h"
#include "utils/utils.h"

// for platforms which IOs not defined in the way port with pin number
typedef uint32_t IOTag_t;

// for platform which IOs defined in the way port with pin number
typedef struct IODef_s
{
  void *gpiox;
  uint16_t pin;
} IODef_t;

// for platforms which IOs defined in their unique way
typedef void *IOExt_t;

typedef struct IO_s
{
  IODef_t ioDef;
  IOTag_t ioTag;
  IOExt_t extIO;
} IO_t;

typedef struct implIOInterface_s
{
  void (*pIOInit) (implRes_t res);
  bool (*pIORead) (implRes_t);
  void (*pIOWrite) (implRes_t res);
  void (*pIOHi) (implRes_t res);
  void (*pIOLo) (implRes_t res);
  void (*pIOToggle) (implRes_t res);
} implIOInterface_t;

void implIOInit (implRes_t res);
bool implIORead (implRes_t res);
void implIOWrite (implRes_t res);
void implIOHi (implRes_t res);
void implIOLo (implRes_t res);
void implIOToggle (implRes_t res);

void implIOInterfaceInit (void);
implIOInterface_t *implIOInterfaceHandle (void);
