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

M.set = {
    debug = {
        enable = true,
        disbale = false,
    },

    led = "OUTPUT",
    key = "INPUT",
    bus_spi = {
        disable_miso = "DISABLE_MISO",
        regular = "REGULAR",
    },
    bus_uart = {
        disable_tx = "DISABLE_TX",
        disable_rx = "DISABLE_RX",
        regular = "REGULAR"
    }
}

M.drv = {
    led = {
        run_led = {
            "RUN_LED_1",
            "RUN_LED_2",
            "RUN_LED_3"
        },

        strip = {
            "LED_STRIP_1",
            "LED_STRIP_2",
            "LED_STRIP_3",
            "LED_STRIP_4",
            "LED_STRIP_5",
            "LED_STRIP_6",
            "LED_STRIP_7",
            "LED_STRIP_8",
        }
    },

    key = {
        sys_key = {
            "SYS_KEY_1",
            "SYS_KEY_2",
        }
    },

    serial = {
        serial_cli = "SERIAL_CLI",
        sbus_input = "SBUS_INPUT"
    },

    imu = {
        icm20689 = "ICM20689",
        icm42688p ="ICM42688P"
    },

    magn = {
        qmc5883l = "QMC5883L"
    },

    baro = {
        bmp180 = "BMP180",
    },

    flash = {
        w25qxx = "W25QXX"
    }
}

return M
