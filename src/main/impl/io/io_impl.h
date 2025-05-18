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
  void (*pIOInit) (trArrow_t arrow);
  bool (*pIORead) (trArrow_t arrow);
  void (*pIOWrite) (trArrow_t arrow);
  void (*pIOHi) (trArrow_t arrow);
  void (*pIOLo) (trArrow_t arrow);
  void (*pIOToggle) (trArrow_t arrow);
} implIOInterface_t;

void implIOInit (trArrow_t arrow);
bool implIORead (trArrow_t arrow);
void implIOWrite (trArrow_t arrow);
void implIOHi (trArrow_t arrow);
void implIOLo (trArrow_t arrow);
void implIOToggle (trArrow_t arrow);

void implIOInterfaceInit (void);
implIOInterface_t *implIOInterfaceHandle (void);
