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

#include "utils/utils.h"

#include "impl/impl_defs.h"

typedef struct implIOInterface_s
{
  void (*pIOInit) (clew_t clew);
  bool (*pIORead) (clew_t clew);
  void (*pIOWrite) (clew_t clew);
  void (*pIOHi) (clew_t clew);
  void (*pIOLo) (clew_t clew);
  void (*pIOToggle) (clew_t clew);
} implIOInterface_t;

void implIOInit (clew_t clew);
bool implIORead (clew_t clew);
void implIOWrite (clew_t clew);
void implIOHi (clew_t clew);
void implIOLo (clew_t clew);
void implIOToggle (clew_t clew);

void implIOInterfaceInit (void);
implIOInterface_t *implIOInterfaceHandle (void);
