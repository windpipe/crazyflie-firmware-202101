/**
 * ,---------,       ____  _ __
 * |  ,-^-,  |      / __ )(_) /_______________ _____  ___
 * | (  O  ) |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * | / ,--´  |    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *    +------`   /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie control firmware
 *
 * Copyright (C) 2019 Bitcraze AB
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, in version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * hello_world.c - App layer application of a simple hello world debug print every
 *   2 seconds.  
 */


#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "app.h"

#include "FreeRTOS.h"
#include "task.h"

#include "param.h"

#include "debug.h"

#define DEBUG_MODULE "DRONICLE"

static bool takeOffWhenReady = false;
static float goToInitialPositionWhenReady = -1.0f;
static bool terminateTrajectoryAndLand = false;

static float trajecory_center_offset_x = 0.0f;
static float trajecory_center_offset_y = 0.0f;
static float trajecory_center_offset_z = 0.0f;

void appMain()
{
  DEBUG_PRINT("Waiting for activation ...\n");

  while(1) {
    vTaskDelay(M2T(100));                   // 0.1 sec delay
    DEBUG_PRINT("Hello World!\n");
  }
}

PARAM_GROUP_START(dronicle)
  PARAM_ADD(PARAM_UINT8, takeoff, &takeOffWhenReady)
  PARAM_ADD(PARAM_FLOAT, start, &goToInitialPositionWhenReady)
  PARAM_ADD(PARAM_UINT8, stop, &terminateTrajectoryAndLand)
  PARAM_ADD(PARAM_FLOAT, offsx, &trajecory_center_offset_x)
  PARAM_ADD(PARAM_FLOAT, offsy, &trajecory_center_offset_y)
  PARAM_ADD(PARAM_FLOAT, offsz, &trajecory_center_offset_z)
  PARAM_ADD(PARAM_UINT8, dindex, &dronicle_index )          // windpipe.
  //PARAM_ADD(PARAM_UINT8, trajcount, &trajectoryCount)
PARAM_GROUP_STOP(dronicle)

LOG_GROUP_START(dronicle)
  LOG_ADD(LOG_UINT8, state, &state)
  LOG_ADD(LOG_FLOAT, prgr, &currentProgressInTrajectory)
  LOG_ADD(LOG_UINT32, uptime, &now)
  LOG_ADD(LOG_UINT32, flighttime, &flightTime)
LOG_GROUP_STOP(dronicle)