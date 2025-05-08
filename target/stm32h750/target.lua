local M = {}

local platform = require("platform")
local res = platform.resources

M.info = platform.config({
    mcu = "STM32H750xx",
    mcu_series = "STM32H7",
    identifier = "weact_stm32h750vbtx_core_board",
    toolchain = "arm-none-eabi"
})

M.io = {
    io1 = platform.setup(res.all.io, {
        name = "GPIO_OUTPUT1_PIN",
        io = res.io.PE3,
    }),
}

M.bus = {
    uart1 = platform.setup(res.all.bus_uart, {
        bus = res.bus_uart.UART1,
        type = res.type.bus_uart.TXRX,
        dma = true,
        tx = platform.setup(res.all.io, {
            name = res.bus_uart.UART1.tx,
            io = res.io.PB14,
        }),
        rx = platform.setup(res.all.io, {
            name = res.bus_uart.UART1.rx,
            io = res.io.PB15,
        }),
    }),

    spi1 = platform.setup(res.all.bus_spi, {
        bus = res.bus_spi.SPI1,
        type = res.type.bus_spi.TXRX,
        dma = true,
        ncs = {
            platform.setup(res.all.io, {
                name = res.bus_spi.SPI1.ncs(1),
                io = res.io.PA0,
            }),
            platform.setup(res.all.io, {
                name = res.bus_spi.SPI1.ncs(2),
                io = res.io.PA1,
            }),
        },

        mosi = platform.setup(res.all.io, {
            name = res.bus_spi.SPI1.mosi,
            io = res.io.PA5,
        }),

        miso = platform.setup(res.all.io, {
            name = res.bus_spi.SPI1.miso,
            io = res.io.PA6,
        }),

        sclk = platform.setup(res.all.io, {
            name = res.bus_spi.SPI1.sclk,
            io = res.io.PA7,
        }),
    }),

    i2c1 = platform.setup(res.all.bus_i2c, {
        bus = res.bus_i2c.I2C1,
        dma = true,

        sck = platform.setup(res.all.io, {
            name = res.bus_i2c.I2C1.sck,
            io = res.io.PB7,
        }),

        sda = platform.setup(res.all.io, {
            name = res.bus_i2c.I2C1.sda,
            io = res.io.PB8,
        }),
    }),
}

M.timer = {
    clock = platform.setup(res.all.timer, {
        name = "TIMER1",
        timer = res.timer.TIMER1,
        type = res.type.timer.clock,
        owner = nil
    })
}

return M
