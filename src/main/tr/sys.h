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

typedef enum
{
  system_state_bootup = 0,
  system_state_drvs_init,
  system_state_drvs_init_done,
  system_state_selfchk,
  system_state_selfchk_failed,
  system_state_selfchk_passed,
  system_state_transponder_enabled,
  system_state_reday,
} systemState_e;

typedef struct __trSystemInitHandle_s
{
  systemState_e systemState;
  void (*pSystemInit) (void);
  void (*pSystemRun) (void);
} trSystemHandle_t;

trSystemHandle_t *trSystemHandle (void);
