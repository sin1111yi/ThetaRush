/**
 ******************************************************************************
 * @file    system_stm32h7xx.c
 * @author  MCD Application Team
 * @brief   CMSIS Cortex-Mx Device Peripheral Access Layer System Source File.
 *
 *   This file provides two functions and one global variable to be called from
 *   user application:
 *      - ExitRun0Mode(): Specifies the Power Supply source. This function is
 *                        called at startup just after reset and before the
 *call of SystemInit(). This call is made inside the "startup_stm32h7xx.s"
 *file.
 *
 *      - SystemInit(): This function is called at startup just after reset and
 *                      before branch to main program. This call is made inside
 *                      the "startup_stm32h7xx.s" file.
 *
 *      - SystemCoreClock variable: Contains the core clock, it can be used
 *                                  by the user application to setup the
 *SysTick timer or configure other parameters.
 *
 *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and
 *must be called whenever the core clock is changed during program execution.
 *
 *
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2017 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/** @addtogroup CMSIS
 * @{
 */

/** @addtogroup stm32h7xx_system
 * @{
 */

/** @addtogroup STM32H7xx_System_Private_Includes
 * @{
 */

#include <math.h>

#include "target.h"

#include "stm32h7xx.h"

#include "platform/memprot.h"

#if defined(STM32H750xx)

#if defined(__SYSTEM_STM32__)
#error "Compiling conflict system_stm32xx.c is not allowed."
#else
#define __SYSTEM_STM32__
#endif /* __SYSTEM_STM32__ */

#if !defined(HSE_VALUE)
#define HSE_VALUE                                                             \
  ((uint32_t)25000000) /*!< Value of the External oscillator in Hz */
#endif                 /* HSE_VALUE */

#if !defined(CSI_VALUE)
#define CSI_VALUE                                                             \
  ((uint32_t)4000000) /*!< Value of the Internal oscillator in Hz*/
#endif                /* CSI_VALUE */

#if !defined(HSI_VALUE)
#define HSI_VALUE                                                             \
  ((uint32_t)64000000) /*!< Value of the Internal oscillator in Hz*/
#endif                 /* HSI_VALUE */

/**
 * @}
 */

/** @addtogroup STM32H7xx_System_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup STM32H7xx_System_Private_Defines
 * @{
 */

/************************* Miscellaneous Configuration
 * ************************/
/*!< Uncomment the following line if you need to use initialized data in D2
 * domain SRAM (AHB SRAM) */
/* #define DATA_IN_D2_SRAM */

/* Note: Following vector table addresses must be defined in line with linker
         configuration. */
/*!< Uncomment the following line if you need to relocate the vector table
     anywhere in FLASH BANK1 or AXI SRAM, else the vector table is kept at the
   automatic remap of boot address selected */
/* #define USER_VECT_TAB_ADDRESS */

#if defined(USER_VECT_TAB_ADDRESS)
#if defined(DUAL_CORE) && defined(CORE_CM4)
/*!< Uncomment the following line if you need to relocate your vector Table
     in D2 AXI SRAM else user remap will be done in FLASH BANK2. */
/* #define VECT_TAB_SRAM */
#if defined(VECT_TAB_SRAM)
#define VECT_TAB_BASE_ADDRESS                                                 \
  D2_AXISRAM_BASE /*!< Vector Table base address field.                       \
                       This value must be a multiple of 0x400. */
#define VECT_TAB_OFFSET                                                       \
  0x00000000U /*!< Vector Table base offset field.                            \
                   This value must be a multiple of 0x400. */
#else
#define VECT_TAB_BASE_ADDRESS                                                 \
  FLASH_BANK2_BASE /*!< Vector Table base address field.                      \
                        This value must be a multiple of 0x400. */
#define VECT_TAB_OFFSET                                                       \
  0x00000000U /*!< Vector Table base offset field.                            \
                   This value must be a multiple of 0x400. */
#endif        /* VECT_TAB_SRAM */
#else
/*!< Uncomment the following line if you need to relocate your vector Table
     in D1 AXI SRAM else user remap will be done in FLASH BANK1. */
/* #define VECT_TAB_SRAM */
#if defined(VECT_TAB_SRAM)
#define VECT_TAB_BASE_ADDRESS                                                 \
  D1_AXISRAM_BASE /*!< Vector Table base address field.                       \
                       This value must be a multiple of 0x400. */
#define VECT_TAB_OFFSET                                                       \
  0x00000000U /*!< Vector Table base offset field.                            \
                   This value must be a multiple of 0x400. */
#else
#define VECT_TAB_BASE_ADDRESS                                                 \
  FLASH_BANK1_BASE /*!< Vector Table base address field.                      \
                        This value must be a multiple of 0x400. */
#define VECT_TAB_OFFSET                                                       \
  0x00000000U /*!< Vector Table base offset field.                            \
                   This value must be a multiple of 0x400. */
#endif        /* VECT_TAB_SRAM */
#endif        /* DUAL_CORE && CORE_CM4 */
#endif        /* USER_VECT_TAB_ADDRESS */
/******************************************************************************/

/**
 * @}
 */

/** @addtogroup STM32H7xx_System_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup STM32H7xx_System_Private_Variables
 * @{
 */
/* This variable is updated in three ways:
    1) by calling CMSIS function SystemCoreClockUpdate()
    2) by calling HAL API function HAL_RCC_GetHCLKFreq()
    3) each time HAL_RCC_ClockConfig() is called to configure the system clock
   frequency Note: If you use this function to configure the system clock; then
   there is no need to call the 2 first functions listed above, since
   SystemCoreClock variable is updated automatically.
*/
uint32_t SystemCoreClock = 64000000;
uint32_t SystemD2Clock = 64000000;
const uint8_t D1CorePrescTable[16]
    = { 0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9 };

/**
 * @}
 */

/** @addtogroup STM32H7xx_System_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup STM32H7xx_System_Private_Functions
 * @{
 */

static void
Error_Handler (void)
{
  __disable_irq ();
  while (1)
    {
    }
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void
SystemClock_Config (void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
  RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

  /** Supply configuration update enable
   */
  HAL_PWREx_ConfigSupply (PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
   */
  __HAL_PWR_VOLTAGESCALING_CONFIG (PWR_REGULATOR_VOLTAGE_SCALE0);

  while (!__HAL_PWR_GET_FLAG (PWR_FLAG_VOSRDY))
    {
    }

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig (&RCC_OscInitStruct) != HAL_OK)
    {
      Error_Handler ();
    }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType
      = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1
        | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig (&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    {
      Error_Handler ();
    }
}

/**
 * @brief  Update SystemCoreClock variable according to Clock Register Values.
 *         The SystemCoreClock variable contains the core clock , it can
 *         be used by the user application to setup the SysTick timer or
 * configure other parameters.
 *
 * @note   Each time the core clock changes, this function must be called
 *         to update SystemCoreClock variable value. Otherwise, any
 * configuration based on this variable will be incorrect.
 *
 * @note   - The system frequency computed by this function is not the real
 *           frequency in the chip. It is calculated based on the predefined
 *           constant and the selected clock source:
 *
 *           - If SYSCLK source is CSI, SystemCoreClock will contain the
 * CSI_VALUE(*)
 *           - If SYSCLK source is HSI, SystemCoreClock will contain the
 * HSI_VALUE(**)
 *           - If SYSCLK source is HSE, SystemCoreClock will contain the
 * HSE_VALUE(***)
 *           - If SYSCLK source is PLL, SystemCoreClock will contain the
 * CSI_VALUE(*), HSI_VALUE(**) or HSE_VALUE(***) multiplied/divided by the PLL
 * factors.
 *
 *         (*) CSI_VALUE is a constant defined in stm32h7xx_hal.h file (default
 * value 4 MHz) but the real value may vary depending on the variations in
 * voltage and temperature.
 *         (**) HSI_VALUE is a constant defined in stm32h7xx_hal.h file
 * (default value 64 MHz) but the real value may vary depending on the
 * variations in voltage and temperature.
 *
 *         (***)HSE_VALUE is a constant defined in stm32h7xx_hal.h file
 * (default value 25 MHz), user has to ensure that HSE_VALUE is same as the
 * real frequency of the crystal used. Otherwise, this function may have wrong
 * result.
 *
 *         - The result of this function could be not correct when using
 * fractional value for HSE crystal.
 * @param  None
 * @retval None
 */
void
SystemCoreClockUpdate (void)
{
  uint32_t pllp, pllsource, pllm, pllfracen, hsivalue, tmp;
  uint32_t common_system_clock;
  float_t fracn1, pllvco;

  /* Get SYSCLK source
   * -------------------------------------------------------*/

  switch (RCC->CFGR & RCC_CFGR_SWS)
    {
    case RCC_CFGR_SWS_HSI: /* HSI used as system clock source */
      common_system_clock
          = (uint32_t)(HSI_VALUE >> ((RCC->CR & RCC_CR_HSIDIV) >> 3));
      break;

    case RCC_CFGR_SWS_CSI: /* CSI used as system clock  source */
      common_system_clock = CSI_VALUE;
      break;

    case RCC_CFGR_SWS_HSE: /* HSE used as system clock  source */
      common_system_clock = HSE_VALUE;
      break;

    case RCC_CFGR_SWS_PLL1: /* PLL1 used as system clock  source */

      /* PLL_VCO = (HSE_VALUE or HSI_VALUE or CSI_VALUE/ PLLM) * PLLN
      SYSCLK = PLL_VCO / PLLR
      */
      pllsource = (RCC->PLLCKSELR & RCC_PLLCKSELR_PLLSRC);
      pllm = ((RCC->PLLCKSELR & RCC_PLLCKSELR_DIVM1) >> 4);
      pllfracen = ((RCC->PLLCFGR & RCC_PLLCFGR_PLL1FRACEN)
                   >> RCC_PLLCFGR_PLL1FRACEN_Pos);
      fracn1 = (float_t)(uint32_t)(pllfracen
                                   * ((RCC->PLL1FRACR & RCC_PLL1FRACR_FRACN1)
                                      >> 3));

      if (pllm != 0U)
        {
          switch (pllsource)
            {
            case RCC_PLLCKSELR_PLLSRC_HSI: /* HSI used as PLL clock source */

              hsivalue = (HSI_VALUE >> ((RCC->CR & RCC_CR_HSIDIV) >> 3));
              pllvco = ((float_t)hsivalue / (float_t)pllm)
                       * ((float_t)(uint32_t)(RCC->PLL1DIVR & RCC_PLL1DIVR_N1)
                          + (fracn1 / (float_t)0x2000) + (float_t)1);

              break;

            case RCC_PLLCKSELR_PLLSRC_CSI: /* CSI used as PLL clock source */
              pllvco = ((float_t)CSI_VALUE / (float_t)pllm)
                       * ((float_t)(uint32_t)(RCC->PLL1DIVR & RCC_PLL1DIVR_N1)
                          + (fracn1 / (float_t)0x2000) + (float_t)1);
              break;

            case RCC_PLLCKSELR_PLLSRC_HSE: /* HSE used as PLL clock source */
              pllvco = ((float_t)HSE_VALUE / (float_t)pllm)
                       * ((float_t)(uint32_t)(RCC->PLL1DIVR & RCC_PLL1DIVR_N1)
                          + (fracn1 / (float_t)0x2000) + (float_t)1);
              break;

            default:
              hsivalue = (HSI_VALUE >> ((RCC->CR & RCC_CR_HSIDIV) >> 3));
              pllvco = ((float_t)hsivalue / (float_t)pllm)
                       * ((float_t)(uint32_t)(RCC->PLL1DIVR & RCC_PLL1DIVR_N1)
                          + (fracn1 / (float_t)0x2000) + (float_t)1);
              break;
            }
          pllp = (((RCC->PLL1DIVR & RCC_PLL1DIVR_P1) >> 9) + 1U);
          common_system_clock = (uint32_t)(float_t)(pllvco / (float_t)pllp);
        }
      else
        {
          common_system_clock = 0U;
        }
      break;

    default:
      common_system_clock
          = (uint32_t)(HSI_VALUE >> ((RCC->CR & RCC_CR_HSIDIV) >> 3));
      break;
    }

    /* Compute SystemClock frequency
     * --------------------------------------------------*/
#if defined(RCC_D1CFGR_D1CPRE)
  tmp = D1CorePrescTable[(RCC->D1CFGR & RCC_D1CFGR_D1CPRE)
                         >> RCC_D1CFGR_D1CPRE_Pos];

  /* common_system_clock frequency : CM7 CPU frequency  */
  common_system_clock >>= tmp;

  /* SystemD2Clock frequency : CM4 CPU, AXI and AHBs Clock frequency  */
  SystemD2Clock = (common_system_clock
                   >> ((D1CorePrescTable[(RCC->D1CFGR & RCC_D1CFGR_HPRE)
                                         >> RCC_D1CFGR_HPRE_Pos])
                       & 0x1FU));

#else
  tmp = D1CorePrescTable[(RCC->CDCFGR1 & RCC_CDCFGR1_CDCPRE)
                         >> RCC_CDCFGR1_CDCPRE_Pos];

  /* common_system_clock frequency : CM7 CPU frequency  */
  common_system_clock >>= tmp;

  /* SystemD2Clock frequency : AXI and AHBs Clock frequency  */
  SystemD2Clock = (common_system_clock
                   >> ((D1CorePrescTable[(RCC->CDCFGR1 & RCC_CDCFGR1_HPRE)
                                         >> RCC_CDCFGR1_HPRE_Pos])
                       & 0x1FU));

#endif

#if defined(DUAL_CORE) && defined(CORE_CM4)
  SystemCoreClock = SystemD2Clock;
#else
  SystemCoreClock = common_system_clock;
#endif /* DUAL_CORE && CORE_CM4 */
}

/**
 * @brief  Setup the microcontroller system
 *         Initialize the FPU setting and  vector table location
 *         configuration.
 * @param  None
 * @retval None
 */
void
SystemInit (void)
{
#if defined(DATA_IN_D2_SRAM)
  __IO uint32_t tmpreg;
#endif /* DATA_IN_D2_SRAM */

/* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB->CPACR |= ((3UL << (10 * 2))
                 | (3UL << (11 * 2))); /* set CP10 and CP11 Full Access */
#endif
  /* Reset the RCC clock configuration to the default reset state
   * ------------*/

  /* Increasing the CPU frequency */
  if (FLASH_LATENCY_DEFAULT > (READ_BIT ((FLASH->ACR), FLASH_ACR_LATENCY)))
    {
      /* Program the new number of wait states to the LATENCY bits in the
       * FLASH_ACR register */
      MODIFY_REG (FLASH->ACR, FLASH_ACR_LATENCY,
                  (uint32_t)(FLASH_LATENCY_DEFAULT));
    }

  /* Set HSION bit */
  RCC->CR |= RCC_CR_HSION;

  /* Reset CFGR register */
  RCC->CFGR = 0x00000000;

  /* Reset HSEON, HSECSSON, CSION, HSI48ON, CSIKERON, PLL1ON, PLL2ON and PLL3ON
   * bits */
  RCC->CR &= 0xEAF6ED7FU;

  /* Decreasing the number of wait states because of lower CPU frequency */
  if (FLASH_LATENCY_DEFAULT < (READ_BIT ((FLASH->ACR), FLASH_ACR_LATENCY)))
    {
      /* Program the new number of wait states to the LATENCY bits in the
       * FLASH_ACR register */
      MODIFY_REG (FLASH->ACR, FLASH_ACR_LATENCY,
                  (uint32_t)(FLASH_LATENCY_DEFAULT));
    }

#if defined(D3_SRAM_BASE)
  /* Reset D1CFGR register */
  RCC->D1CFGR = 0x00000000;

  /* Reset D2CFGR register */
  RCC->D2CFGR = 0x00000000;

  /* Reset D3CFGR register */
  RCC->D3CFGR = 0x00000000;
#else
  /* Reset CDCFGR1 register */
  RCC->CDCFGR1 = 0x00000000;

  /* Reset CDCFGR2 register */
  RCC->CDCFGR2 = 0x00000000;

  /* Reset SRDCFGR register */
  RCC->SRDCFGR = 0x00000000;
#endif
  /* Reset PLLCKSELR register */
  RCC->PLLCKSELR = 0x02020200;

  /* Reset PLLCFGR register */
  RCC->PLLCFGR = 0x01FF0000;
  /* Reset PLL1DIVR register */
  RCC->PLL1DIVR = 0x01010280;
  /* Reset PLL1FRACR register */
  RCC->PLL1FRACR = 0x00000000;

  /* Reset PLL2DIVR register */
  RCC->PLL2DIVR = 0x01010280;

  /* Reset PLL2FRACR register */

  RCC->PLL2FRACR = 0x00000000;
  /* Reset PLL3DIVR register */
  RCC->PLL3DIVR = 0x01010280;

  /* Reset PLL3FRACR register */
  RCC->PLL3FRACR = 0x00000000;

  /* Reset HSEBYP bit */
  RCC->CR &= 0xFFFBFFFFU;

  /* Disable all interrupts */
  RCC->CIER = 0x00000000;

#if (STM32H7_DEV_ID == 0x450UL)
  /* dual core CM7 or single core line */
  if ((DBGMCU->IDCODE & 0xFFFF0000U) < 0x20000000U)
    {
      /* if stm32h7 revY*/
      /* Change  the switch matrix read issuing capability to 1 for the AXI
       * SRAM target (Target 7) */
      *((__IO uint32_t *)0x51008108) = 0x000000001U;
    }
#endif /* STM32H7_DEV_ID */

#if defined(DATA_IN_D2_SRAM)
    /* in case of initialized data in D2 SRAM (AHB SRAM), enable the D2 SRAM
     * clock (AHB SRAM clock) */
#if defined(RCC_AHB2ENR_D2SRAM3EN)
  RCC->AHB2ENR |= (RCC_AHB2ENR_D2SRAM1EN | RCC_AHB2ENR_D2SRAM2EN
                   | RCC_AHB2ENR_D2SRAM3EN);
#elif defined(RCC_AHB2ENR_D2SRAM2EN)
  RCC->AHB2ENR |= (RCC_AHB2ENR_D2SRAM1EN | RCC_AHB2ENR_D2SRAM2EN);
#else
  RCC->AHB2ENR |= (RCC_AHB2ENR_AHBSRAM1EN | RCC_AHB2ENR_AHBSRAM2EN);
#endif /* RCC_AHB2ENR_D2SRAM3EN */

  tmpreg = RCC->AHB2ENR;
  (void)tmpreg;
#endif /* DATA_IN_D2_SRAM */

#if defined(DUAL_CORE) && defined(CORE_CM4)
  /* Configure the Vector Table location add offset address for cortex-M4
   * ------------------*/
#if defined(USER_VECT_TAB_ADDRESS)
  SCB->VTOR = VECT_TAB_BASE_ADDRESS
              | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal D2
                                    AXI-RAM or in Internal FLASH */
#endif                           /* USER_VECT_TAB_ADDRESS */

#else
  if (READ_BIT (RCC->AHB3ENR, RCC_AHB3ENR_FMCEN) == 0U)
    {
      /* Enable the FMC interface clock */
      SET_BIT (RCC->AHB3ENR, RCC_AHB3ENR_FMCEN);

      /*
       * Disable the FMC bank1 (enabled after reset).
       * This, prevents CPU speculation access on this bank which blocks the
       * use of FMC during 24us. During this time the others FMC master (such
       * as LTDC) cannot use it!
       */
      FMC_Bank1_R->BTCR[0] = 0x000030D2;

      /* Disable the FMC interface clock */
      CLEAR_BIT (RCC->AHB3ENR, RCC_AHB3ENR_FMCEN);
    }

    /* Configure the Vector Table location
     * -------------------------------------*/
#if defined(USER_VECT_TAB_ADDRESS)
  SCB->VTOR = VECT_TAB_BASE_ADDRESS
              | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal D1
                                    AXI-RAM or in Internal FLASH */
#endif /* USER_VECT_TAB_ADDRESS */

#ifdef USE_HAL_DRIVER
  HAL_Init ();
#endif

  SystemClock_Config ();
  SystemCoreClockUpdate ();

#if 0
  // Configure MPU

  memProtConfigure(mpuRegions, mpuRegionCount);
#endif

  // Enable CPU L1-Cache
  SCB_EnableICache ();
  SCB_EnableDCache ();

#endif /*DUAL_CORE && CORE_CM4*/
}

/**
 * @brief  Exit Run* mode and Configure the system Power Supply
 *
 * @note   This function exits the Run* mode and configures the system power
 * supply according to the definition to be used at compilation preprocessing
 * level. The application shall set one of the following configuration option:
 *           - PWR_LDO_SUPPLY
 *           - PWR_DIRECT_SMPS_SUPPLY
 *           - PWR_EXTERNAL_SOURCE_SUPPLY
 *           - PWR_SMPS_1V8_SUPPLIES_LDO
 *           - PWR_SMPS_2V5_SUPPLIES_LDO
 *           - PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO
 *           - PWR_SMPS_2V5_SUPPLIES_EXT_AND_LDO
 *           - PWR_SMPS_1V8_SUPPLIES_EXT
 *           - PWR_SMPS_2V5_SUPPLIES_EXT
 *
 * @note   The function modifies the PWR->CR3 register to enable or disable
 * specific power supply modes and waits until the voltage level flag is set,
 * indicating that the power supply configuration is stable.
 *
 * @param  None
 * @retval None
 */
void
ExitRun0Mode (void)
{
#if defined(USE_PWR_LDO_SUPPLY)
#if defined(SMPS)
  /* Exit Run* mode by disabling SMPS and enabling LDO */
  PWR->CR3 = (PWR->CR3 & ~PWR_CR3_SMPSEN) | PWR_CR3_LDOEN;
#else
  /* Enable LDO mode */
  PWR->CR3 |= PWR_CR3_LDOEN;
#endif /* SMPS */
  /* Wait till voltage level flag is set */
  while ((PWR->CSR1 & PWR_CSR1_ACTVOSRDY) == 0U)
    {
    }
#elif defined(USE_PWR_EXTERNAL_SOURCE_SUPPLY)
#if defined(SMPS)
  /* Exit Run* mode */
  PWR->CR3 = (PWR->CR3 & ~(PWR_CR3_SMPSEN | PWR_CR3_LDOEN)) | PWR_CR3_BYPASS;
#else
  PWR->CR3 = (PWR->CR3 & ~(PWR_CR3_LDOEN)) | PWR_CR3_BYPASS;
#endif /* SMPS */
  /* Wait till voltage level flag is set */
  while ((PWR->CSR1 & PWR_CSR1_ACTVOSRDY) == 0U)
    {
    }
#elif defined(USE_PWR_DIRECT_SMPS_SUPPLY) && defined(SMPS)
  /* Exit Run* mode */
  PWR->CR3 &= ~(PWR_CR3_LDOEN);
  /* Wait till voltage level flag is set */
  while ((PWR->CSR1 & PWR_CSR1_ACTVOSRDY) == 0U)
    {
    }
#elif defined(USE_PWR_SMPS_1V8_SUPPLIES_LDO) && defined(SMPS)
  /* Exit Run* mode */
  PWR->CR3 |= PWR_CR3_SMPSLEVEL_0 | PWR_CR3_SMPSEN | PWR_CR3_LDOEN;
  /* Wait till voltage level flag is set */
  while ((PWR->CSR1 & PWR_CSR1_ACTVOSRDY) == 0U)
    {
    }
#elif defined(USE_PWR_SMPS_2V5_SUPPLIES_LDO) && defined(SMPS)
  /* Exit Run* mode */
  PWR->CR3 |= PWR_CR3_SMPSLEVEL_1 | PWR_CR3_SMPSEN | PWR_CR3_LDOEN;
  /* Wait till voltage level flag is set */
  while ((PWR->CSR1 & PWR_CSR1_ACTVOSRDY) == 0U)
    {
    }
#elif defined(USE_PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO) && defined(SMPS)
  /* Exit Run* mode */
  PWR->CR3 |= PWR_CR3_SMPSLEVEL_0 | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN
              | PWR_CR3_LDOEN;
  /* Wait till voltage level flag is set */
  while ((PWR->CSR1 & PWR_CSR1_ACTVOSRDY) == 0U)
    {
    }
#elif defined(USE_PWR_SMPS_2V5_SUPPLIES_EXT_AND_LDO) && defined(SMPS)
  /* Exit Run* mode */
  PWR->CR3 |= PWR_CR3_SMPSLEVEL_1 | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN
              | PWR_CR3_LDOEN;
  /* Wait till voltage level flag is set */
  while ((PWR->CSR1 & PWR_CSR1_ACTVOSRDY) == 0U)
    {
    }
#elif defined(USE_PWR_SMPS_1V8_SUPPLIES_EXT) && defined(SMPS)
  /* Exit Run* mode */
  PWR->CR3 = (PWR->CR3 & ~(PWR_CR3_LDOEN)) | PWR_CR3_SMPSLEVEL_0
             | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_BYPASS;
  /* Wait till voltage level flag is set */
  while ((PWR->CSR1 & PWR_CSR1_ACTVOSRDY) == 0U)
    {
    }
#elif defined(USE_PWR_SMPS_2V5_SUPPLIES_EXT) && defined(SMPS)
  /* Exit Run* mode */
  PWR->CR3 = (PWR->CR3 & ~(PWR_CR3_LDOEN)) | PWR_CR3_SMPSLEVEL_1
             | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_BYPASS;
  /* Wait till voltage level flag is set */
  while ((PWR->CSR1 & PWR_CSR1_ACTVOSRDY) == 0U)
    {
    }
#else
  /* No system power supply configuration is selected at exit Run* mode */
#endif /* USE_PWR_LDO_SUPPLY */
}

#endif /* STM32H750xx */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
