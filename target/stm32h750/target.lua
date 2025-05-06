local M = {}

local platform = require("platform")
local res = platform.resources

M.platform = platform.config({
    series = "STM32H7",
    mcu = "STM32H750xx",
    identifier = "weact_stm32h750vbtx_core_board",
    toolchain = "arm-none-eabi"
})

M.io = {
    io1 = platform.setup(res.all.io, {
        name = "GPIO_OUTPUT_PIN1",
        io = res.io.PE3,
        owner = nil,
    }),
}

M.bus = {
    uart1 = platform.setup(res.all.bus_uart, {
        name = "BUS_UART1",
        bus = res.bus_uart.UART1,
        type = "TXRX",
        dma = true,
        tx = platform.setup(res.all.io, {
            name = "BUS_UART1_TX_PIN",
            io = res.io.PB14,
            owner = nil
        }),
        rx = platform.setup(res.all.io, {
            name = "BUS_UART1_RX_PIN",
            io = res.io.PB15,
            owner = nil
        }),
        owner = nil,
    }),

    spi1 = platform.setup(res.all.bus_spi, {
        name = "BUS_SPI1",
        bus = res.bus_spi.SPI1,
        type = "TXRX",
        dma = true,
        ncs = {
            platform.setup(res.all.io, {
                name = "BUS_SPI1_NCS1_PIN",
                io = res.io.PA0,
            }),
            platform.setup(res.all.io, {
                name = "BUS_SPI1_NCS2_PIN",
                io = res.io.PA1,
            }),
        },

        mosi = platform.setup(res.all.io, {
            name = "BUS_SPI1_MOSI_PIN",
            io = res.io.PA5,
            owner = nil,
        }),

        miso = platform.setup(res.all.io, {
            name = "BUS_SPI1_MISO_PIN",
            io = res.io.PA6,
            owner = nil,
        }),

        sclk = platform.setup(res.all.io, {
            name = "BUS_SPI1_SCLK_PIN",
            io = res.io.PA7,
            owner = nil,
        }),
        owner = nil,
    }),

    i2c1 = platform.setup(res.all.bus_i2c, {
        name = "BUS_I2C1",
        bus = res.bus_i2c.I2C1,
        dma = true,

        scl = platform.setup(res.all.io, {
            name = "BUS_I2C1_SCL_PIN",
            io = res.io.PB7,
            owner = nil,
        }),

        sda = platform.setup(res.all.io, {
            name = "BUS_I2C1_SDA_PIN",
            io = res.io.PB8,
            owner = nil
        }),

        owner = nil
    })
}

return M
