/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    stm32h7xx_it.c
 * @brief   Interrupt Service Routines.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes
 * ------------------------------------------------------------------*/
#include "stm32_interrupt.h"
#include "platform/platform.h"
/* Private includes
 * ----------------------------------------------------------*/

/* Private typedef
 * -----------------------------------------------------------*/

/* Private define
 * ------------------------------------------------------------*/

/* Private macro
 * -------------------------------------------------------------*/

/* Private variables
 * ---------------------------------------------------------*/

/* Private function prototypes
 * -----------------------------------------------*/

/* Private user code
 * ---------------------------------------------------------*/

/* External variables
 * --------------------------------------------------------*/

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
 * @brief This function handles Non maskable interrupt.
 */
void
NMI_Handler (void)
{
  while (1)
    {
    }
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void
HardFault_Handler (void)
{
  while (1)
    {
    }
}

/**
 * @brief This function handles Memory management fault.
 */
void
MemManage_Handler (void)
{
  while (1)
    {
    }
}

/**
 * @brief This function handles Pre-fetch fault, memory access fault.
 */
void
BusFault_Handler (void)
{
  while (1)
    {
    }
}

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
void
UsageFault_Handler (void)
{
  while (1)
    {
    }
}

/**
 * @brief This function handles System service call via SWI instruction.
 */
void
SVC_Handler (void)
{
}

/**
 * @brief This function handles Debug monitor.
 */
void
DebugMon_Handler (void)
{
}

/**
 * @brief This function handles Pendable request for system service.
 */
void
PendSV_Handler (void)
{
}

/**
 * @brief This function handles System tick timer.
 */
void
SysTick_Handler (void)
{

#if defined(USE_HAL_DRIVER)
  HAL_IncTick ();
#endif
}

/******************************************************************************/
/* STM32H7xx Peripheral Interrupt Handlers */
/* Add here the Interrupt Handlers for the used peripherals. */
/* For the available peripheral interrupt handler names, */
/* please refer to the startup file (startup_stm32h7xx.s). */
/******************************************************************************/
