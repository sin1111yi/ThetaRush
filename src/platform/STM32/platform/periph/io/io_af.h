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

#include "platform/platform.h"

#ifdef __cplusplus
extern "C"
{
#endif

  typedef enum __IOAF_E
  {
    IO_AFx_NONE,
#if defined(STM32H7)
    /**
     * @brief   AF 0 selection
     */
    IO_AF0_RTC_50Hz, /* RTC_50Hz Alternate Function mapping */
    IO_AF0_MCO,      /* MCO (MCO1 and MCO2) Alternate Function mapping      */
    IO_AF0_SWJ,      /* SWJ (SWD and JTAG) Alternate Function mapping      */
    IO_AF0_LCDBIAS,  /* LCDBIAS Alternate Function mapping  */
    IO_AF0_TRACE,    /* TRACE Alternate Function mapping    */
#if defined(PWR_CPUCR_PDDS_D2) /* PWR D1 and D2 domains exists */
    IO_AF0_C1DSLEEP, /* Cortex-M7 Deep Sleep Alternate Function mapping :
                        available on STM32H7 Rev.B and above  */
    IO_AF0_C1SLEEP,  /* Cortex-M7 Sleep Alternate Function mapping : available
                        on STM32H7 Rev.B and above       */
    IO_AF0_D1PWREN,  /* Domain 1 PWR enable Alternate Function mapping :
                        available on STM32H7 Rev.B and above   */
    IO_AF0_D2PWREN,  /* Domain 2 PWR enable Alternate Function mapping :
                        available on STM32H7 Rev.B and above   */
#if defined(DUAL_CORE)
    IO_AF0_C2DSLEEP, /* Cortex-M4 Deep Sleep Alternate Function mapping :
                        available on STM32H7 Rev.B and above  */
    IO_AF0_C2SLEEP,  /* Cortex-M4 Sleep Alternate Function mapping : available
                        on STM32H7 Rev.B and above       */
#endif               /* DUAL_CORE */
#endif               /* PWR_CPUCR_PDDS_D2 */

    /**
     * @brief   AF 1 selection
     */
    IO_AF1_TIM1,   /* TIM1 Alternate Function mapping   */
    IO_AF1_TIM2,   /* TIM2 Alternate Function mapping   */
    IO_AF1_TIM16,  /* TIM16 Alternate Function mapping  */
    IO_AF1_TIM17,  /* TIM17 Alternate Function mapping  */
    IO_AF1_LPTIM1, /* LPTIM1 Alternate Function mapping */
#if defined(HRTIM1)
    IO_AF1_HRTIM1, /* HRTIM1 Alternate Function mapping */
#endif             /* HRTIM1 */
#if defined(SAI4)
    IO_AF1_SAI4, /* SAI4 Alternate Function mapping : available on
                    STM32H72xxx/STM32H73xxx */
#endif           /* SAI4 */
    IO_AF1_FMC,  /* FMC Alternate Function mapping : available on
                    STM32H72xxx/STM32H73xxx */

    /**
     * @brief   AF 2 selection
     */
    IO_AF2_TIM3,  /* TIM3 Alternate Function mapping   */
    IO_AF2_TIM4,  /* TIM4 Alternate Function mapping   */
    IO_AF2_TIM5,  /* TIM5 Alternate Function mapping   */
    IO_AF2_TIM12, /* TIM12 Alternate Function mapping  */
    IO_AF2_SAI1,  /* SAI1 Alternate Function mapping   */
#if defined(HRTIM1)
    IO_AF2_HRTIM1, /* HRTIM1 Alternate Function mapping */
#endif             /* HRTIM1 */
    IO_AF2_TIM15,  /* TIM15 Alternate Function mapping : available on
                      STM32H7A3xxx/STM32H7B3xxx/STM32H7B0xxx and
                      STM32H72xxx/STM32H73xxx */
#if defined(FDCAN3)
    IO_AF2_FDCAN3, /* FDCAN3 Alternate Function mapping */
#endif             /*FDCAN3*/

    /**
     * @brief   AF 3 selection
     */
    IO_AF3_TIM8,   /* TIM8 Alternate Function mapping   */
    IO_AF3_LPTIM2, /* LPTIM2 Alternate Function mapping */
    IO_AF3_DFSDM1, /* DFSDM Alternate Function mapping  */
    IO_AF3_LPTIM3, /* LPTIM3 Alternate Function mapping */
    IO_AF3_LPTIM4, /* LPTIM4 Alternate Function mapping */
    IO_AF3_LPTIM5, /* LPTIM5 Alternate Function mapping */
    IO_AF3_LPUART, /* LPUART Alternate Function mapping */
#if defined(OCTOSPIM)
    IO_AF3_OCTOSPIM_P1, /* OCTOSPI Manager Port 1 Alternate Function mapping */
    IO_AF3_OCTOSPIM_P2, /* OCTOSPI Manager Port 2 Alternate Function mapping */
#endif                  /* OCTOSPIM */
#if defined(HRTIM1)
    IO_AF3_HRTIM1, /* HRTIM1 Alternate Function mapping */
#endif             /* HRTIM1 */
    IO_AF3_LTDC,   /* LTDC Alternate Function mapping : available on
                      STM32H72xxx/STM32H73xxx */

    /**
     * @brief   AF 4 selection
     */
    IO_AF4_I2C1, /* I2C1 Alternate Function mapping   */
    IO_AF4_I2C2, /* I2C2 Alternate Function mapping   */
    IO_AF4_I2C3, /* I2C3 Alternate Function mapping   */
    IO_AF4_I2C4, /* I2C4 Alternate Function mapping   */
#if defined(I2C5)
    IO_AF4_I2C5,   /* I2C5 Alternate Function mapping   */
#endif             /* I2C5*/
    IO_AF4_TIM15,  /* TIM15 Alternate Function mapping  */
    IO_AF4_CEC,    /* CEC Alternate Function mapping    */
    IO_AF4_LPTIM2, /* LPTIM2 Alternate Function mapping */
    IO_AF4_USART1, /* USART1 Alternate Function mapping */
#if defined(USART10)
    IO_AF4_USART10, /* USART10 Alternate Function mapping : available on
                       STM32H72xxx/STM32H73xxx */
#endif              /*USART10*/
    IO_AF4_DFSDM1,  /* DFSDM  Alternate Function mapping */
#if defined(DFSDM2_BASE)
    IO_AF4_DFSDM2, /* DFSDM2 Alternate Function mapping */
#endif             /* DFSDM2_BASE */
    IO_AF4_DCMI,   /* DCMI Alternate Function mapping : available on
                      STM32H7A3xxx/STM32H7B3xxx/STM32H7B0xxx and
                      STM32H72xxx/STM32H73xxx */
#if defined(PSSI)
    IO_AF4_PSSI, /* PSSI Alternate Function mapping   */
#endif           /* PSSI */
#if defined(OCTOSPIM)
    IO_AF4_OCTOSPIM_P1, /* OCTOSPI Manager Port 1 Alternate Function mapping  :
                           available on STM32H72xxx/STM32H73xxx */
#endif                  /* OCTOSPIM */

    /**
     * @brief   AF 5 selection
     */
    IO_AF5_SPI1, /* SPI1 Alternate Function mapping   */
    IO_AF5_SPI2, /* SPI2 Alternate Function mapping   */
    IO_AF5_SPI3, /* SPI3 Alternate Function mapping   */
    IO_AF5_SPI4, /* SPI4 Alternate Function mapping   */
    IO_AF5_SPI5, /* SPI5 Alternate Function mapping   */
    IO_AF5_SPI6, /* SPI6 Alternate Function mapping   */
    IO_AF5_CEC,  /* CEC  Alternate Function mapping   */
#if defined(FDCAN3)
    IO_AF5_FDCAN3, /* FDCAN3 Alternate Function mapping */
#endif             /*FDCAN3*/

    /**
     * @brief   AF 6 selection
     */
    IO_AF6_SPI2, /* SPI2 Alternate Function mapping   */
    IO_AF6_SPI3, /* SPI3 Alternate Function mapping   */
    IO_AF6_SAI1, /* SAI1 Alternate Function mapping   */
    IO_AF6_I2C4, /* I2C4 Alternate Function mapping   */
#if defined(I2C5)
    IO_AF6_I2C5,   /* I2C5 Alternate Function mapping   */
#endif             /* I2C5*/
    IO_AF6_DFSDM1, /* DFSDM Alternate Function mapping  */
    IO_AF6_UART4,  /* UART4 Alternate Function mapping  */
#if defined(DFSDM2_BASE)
    IO_AF6_DFSDM2, /* DFSDM2 Alternate Function mapping */
#endif             /* DFSDM2_BASE */
#if defined(SAI3)
    IO_AF6_SAI3, /* SAI3 Alternate Function mapping   */
#endif           /* SAI3 */
#if defined(OCTOSPIM)
    IO_AF6_OCTOSPIM_P1, /* OCTOSPI Manager Port 1 Alternate Function mapping */
#endif                  /* OCTOSPIM */

    /**
     * @brief   AF 7 selection
     */
    IO_AF7_SPI2,   /* SPI2 Alternate Function mapping   */
    IO_AF7_SPI3,   /* SPI3 Alternate Function mapping   */
    IO_AF7_SPI6,   /* SPI6 Alternate Function mapping   */
    IO_AF7_USART1, /* USART1 Alternate Function mapping */
    IO_AF7_USART2, /* USART2 Alternate Function mapping */
    IO_AF7_USART3, /* USART3 Alternate Function mapping */
    IO_AF7_USART6, /* USART6 Alternate Function mapping */
    IO_AF7_UART7,  /* UART7 Alternate Function mapping  */
    IO_AF7_SDMMC1, /* SDMMC1 Alternate Function mapping */

    /**
     * @brief   AF 8 selection
     */
    IO_AF8_SPI6, /* SPI6 Alternate Function mapping   */
#if defined(SAI2)
    IO_AF8_SAI2,   /* SAI2 Alternate Function mapping   */
#endif             /*SAI2*/
    IO_AF8_UART4,  /* UART4 Alternate Function mapping  */
    IO_AF8_UART5,  /* UART5 Alternate Function mapping  */
    IO_AF8_UART8,  /* UART8 Alternate Function mapping  */
    IO_AF8_SPDIF,  /* SPDIF Alternate Function mapping  */
    IO_AF8_LPUART, /* LPUART Alternate Function mapping */
    IO_AF8_SDMMC1, /* SDMMC1 Alternate Function mapping */
#if defined(SAI4)
    IO_AF8_SAI4, /* SAI4 Alternate Function mapping   */
#endif           /* SAI4 */

    /**
     * @brief   AF 9 selection
     */
    IO_AF9_FDCAN1, /* FDCAN1 Alternate Function mapping   */
    IO_AF9_FDCAN2, /* FDCAN2 Alternate Function mapping   */
    IO_AF9_TIM13,  /* TIM13 Alternate Function mapping    */
    IO_AF9_TIM14,  /* TIM14 Alternate Function mapping    */
    IO_AF9_SDMMC2, /* SDMMC2 Alternate Function mapping   */
    IO_AF9_LTDC,   /* LTDC Alternate Function mapping     */
    IO_AF9_SPDIF,  /* SPDIF Alternate Function mapping    */
    IO_AF9_FMC,    /* FMC Alternate Function mapping      */
#if defined(QUADSPI)
    IO_AF9_QUADSPI, /* QUADSPI Alternate Function mapping  */
#endif              /* QUADSPI */
#if defined(SAI4)
    IO_AF9_SAI4, /* SAI4 Alternate Function mapping     */
#endif           /* SAI4 */
#if defined(OCTOSPIM)
    IO_AF9_OCTOSPIM_P1, /* OCTOSPI Manager Port 1 Alternate Function mapping */
    IO_AF9_OCTOSPIM_P2, /* OCTOSPI Manager Port 2 Alternate Function mapping */
#endif                  /* OCTOSPIM */

/**
 * @brief   AF 10 selection
 */
#if defined(SAI2)
    IO_AF10_SAI2,   /* SAI2 Alternate Function mapping   */
#endif              /*SAI2*/
    IO_AF10_SDMMC2, /* SDMMC2 Alternate Function mapping */
#if defined(USB2_OTG_FS)
    IO_AF10_OTG2_FS, /* OTG2_FS Alternate Function mapping */
#endif               /*USB2_OTG_FS*/
    IO_AF10_COMP1,   /* COMP1 Alternate Function mapping   */
    IO_AF10_COMP2,   /* COMP2 Alternate Function mapping   */
#if defined(LTDC)
    IO_AF10_LTDC,     /* LTDC Alternate Function mapping     */
#endif                /*LTDC*/
    IO_AF10_CRS_SYNC, /* CRS Sync Alternate Function mapping : available on
                         STM32H7 Rev.B and above  */
#if defined(QUADSPI)
    IO_AF10_QUADSPI, /* QUADSPI Alternate Function mapping */
#endif               /* QUADSPI */
#if defined(SAI4)
    IO_AF10_SAI4, /* SAI4 Alternate Function mapping */
#endif            /* SAI4 */
#if !defined(USB2_OTG_FS)
    IO_AF10_OTG1_FS, /* OTG1_FS Alternate Function mapping : available on
                        STM32H7A3xxx/STM32H7B3xxx/STM32H7B0xxx and
                        STM32H72xxx/STM32H73xxx */
#endif               /* !USB2_OTG_FS */
    IO_AF10_OTG1_HS, /* OTG1_HS Alternate Function mapping */
#if defined(OCTOSPIM)
    IO_AF10_OCTOSPIM_P1, /* OCTOSPI Manager Port 1 Alternate Function mapping
                          */
#endif                   /* OCTOSPIM */
    IO_AF10_TIM8,        /* TIM8 Alternate Function mapping        */
    IO_AF10_FMC,         /* FMC Alternate Function mapping : available on
                            STM32H7A3xxx/STM32H7B3xxx/STM32H7B0xxx and
                            STM32H72xxx/STM32H73xxx */

    /**
     * @brief   AF 11 selection
     */
    IO_AF11_SWP,    /* SWP Alternate Function mapping     */
    IO_AF11_MDIOS,  /* MDIOS Alternate Function mapping   */
    IO_AF11_UART7,  /* UART7 Alternate Function mapping   */
    IO_AF11_SDMMC2, /* SDMMC2 Alternate Function mapping  */
    IO_AF11_DFSDM1, /* DFSDM1 Alternate Function mapping  */
    IO_AF11_COMP1,  /* COMP1 Alternate Function mapping   */
    IO_AF11_COMP2,  /* COMP2 Alternate Function mapping   */
    IO_AF11_TIM1,   /* TIM1 Alternate Function mapping    */
    IO_AF11_TIM8,   /* TIM8 Alternate Function mapping    */
    IO_AF11_I2C4,   /* I2C4 Alternate Function mapping    */
#if defined(DFSDM2_BASE)
    IO_AF11_DFSDM2, /* DFSDM2 Alternate Function mapping  */
#endif              /* DFSDM2_BASE */
#if defined(USART10)
    IO_AF11_USART10, /* USART10 Alternate Function mapping */
#endif               /* USART10 */
#if defined(UART9)
    IO_AF11_UART9, /* UART9 Alternate Function mapping   */
#endif             /* UART9 */
#if defined(ETH)
    IO_AF11_ETH, /* ETH Alternate Function mapping     */
#endif           /* ETH */
#if defined(LTDC)
    IO_AF11_LTDC, /* LTDC Alternate Function mapping : available on
                     STM32H7A3xxx/STM32H7B3xxx/STM32H7B0xxx and
                     STM32H72xxx/STM32H73xxx */
#endif            /*LTDC*/
#if defined(OCTOSPIM)
    IO_AF11_OCTOSPIM_P1, /* OCTOSPI Manager Port 1 Alternate Function mapping
                          */
#endif                   /* OCTOSPIM */

    /**
     * @brief   AF 12 selection
     */
    IO_AF12_FMC,    /* FMC Alternate Function mapping     */
    IO_AF12_SDMMC1, /* SDMMC1 Alternate Function mapping  */
    IO_AF12_MDIOS,  /* MDIOS Alternate Function mapping   */
    IO_AF12_COMP1,  /* COMP1 Alternate Function mapping   */
    IO_AF12_COMP2,  /* COMP2 Alternate Function mapping   */
    IO_AF12_TIM1,   /* TIM1 Alternate Function mapping    */
    IO_AF12_TIM8,   /* TIM8 Alternate Function mapping    */
#if defined(LTDC)
    IO_AF12_LTDC, /* LTDC Alternate Function mapping    */
#endif            /*LTDC*/
#if defined(USB2_OTG_FS)
    IO_AF12_OTG1_FS, /* OTG1_FS Alternate Function mapping */
#endif               /* USB2_OTG_FS */
#if defined(OCTOSPIM)
    IO_AF12_OCTOSPIM_P1, /* OCTOSPI Manager Port 1 Alternate Function mapping
                          */
#endif                   /* OCTOSPIM */

    /**
     * @brief   AF 13 selection
     */
    IO_AF13_DCMI,  /* DCMI Alternate Function mapping  */
    IO_AF13_COMP1, /* COMP1 Alternate Function mapping */
    IO_AF13_COMP2, /* COMP2 Alternate Function mapping */
#if defined(LTDC)
    IO_AF13_LTDC, /* LTDC Alternate Function mapping  */
#endif            /*LTDC*/
#if defined(DSI)
    IO_AF13_DSI, /* DSI Alternate Function mapping   */
#endif           /* DSI */
#if defined(PSSI)
    IO_AF13_PSSI, /* PSSI Alternate Function mapping  */
#endif            /* PSSI */
    IO_AF13_TIM1, /* TIM1 Alternate Function mapping */
#if defined(TIM23)
    IO_AF13_TIM23, /* TIM23 Alternate Function mapping */
#endif             /*TIM23*/

    /**
     * @brief   AF 14 selection
     */
    IO_AF14_LTDC,  /* LTDC Alternate Function mapping  */
    IO_AF14_UART5, /* UART5 Alternate Function mapping */
#if defined(TIM24)
    IO_AF14_TIM24, /* TIM24 Alternate Function mapping */
#endif             /*TIM24*/

    /**
     * @brief   AF 15 selection
     */
    IO_AF15_EVENTOUT, /* EVENTOUT Alternate Function mapping */
#endif                /* STM32H7 */
  } IOAF_T;

#ifdef __cplusplus
}
#endif
