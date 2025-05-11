--[[
-- This file is a part of ThetaRush.
--
-- ThetaRush is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- ThetaRush is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with this program.
--
-- If not, see <https://www.gnu.org/licenses/>.
--]]

local M = {}

local tr = require("tr_resources")

M.info = {
    mcu = "STM32H750xx",
    mcu_series = "STM32H7",
    identifier = "weact_stm32h750vbtx_core_board",
    toolchain = "arm-none-eabi",
}

M.io = {
    {
        source = "PE3",
        owner = tr.drv.led.run_led[1],
        set = tr.set.led,
    },

    {
        source = "PC13",
        owner = tr.drv.key.sys_key[1],
        set = tr.set.key,
    }
}

M.bus = {
    spi = {
        {
            source = "SPI1",
            set = tr.set.bus_spi.regular,
            sclk = "PA4",
            mosi = "PA5",
            miso = "PA6",
            ncs = {
                {
                    owner = tr.drv.imu.icm20689,
                    source = "PA7",
                },
                {
                    owner = tr.drv.imu.icm42688p,
                    source = "PA8",
                }
            },
            dma = true,
        }
    },

    uart = {
        {
            source = "UART1",
            set = tr.set.bus_uart.regular,
            tx = "PB14",
            rx = "PB15",
            owner = tr.drv.serial.serial_cli,
        }
    },

    i2c = {
        {
            source = "I2C1",
            sck = "PB7",
            sda = "PB8",
            owner = {
                tr.drv.baro.bmp180,
            }
        }
    }
}

return M
