local M = {}

M.resources_max = {
    io = 16,
    bus_uart = 10,
    bus_spi = 6,
    bus_i2c = 5,
    timer = 16,
}

M.resources = {
    ---@enum all all configurable resources
    all = {
        io = 1,
        bus_uart = 2,
        bus_spi = 3,
        bus_i2c = 4,
    },

    io = (function()
        local tbl_io = {}
        for _, port in ipairs({ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" }) do
            for pin_num = 0, 15 do
                local pin_name = "P" .. port .. pin_num
                tbl_io[pin_name] = {
                    port = port,
                    pin = pin_num,
                }
            end
        end
        return tbl_io
    end)(),

    bus_uart = (function()
        local tbl_bus_uart = {}
        for uart_num = 1, M.resources_max.io do
            local uart_name = "UART" .. uart_num
            tbl_bus_uart[uart_name] = {
                port = "BUS_" .. uart_name,
            }
        end
        return tbl_bus_uart
    end)(),

    bus_spi = (function()
        local tbl_bus_spi = {}
        for spi_num = 1, M.resources_max.bus_spi do
            local spi_name = "SPI" .. spi_num
            tbl_bus_spi[spi_name] = {
                port = "BUS_" .. spi_name,
            }
        end
        return tbl_bus_spi
    end)(),

    bus_i2c = (function()
        local tbl_bus_i2c = {}
        for i2c_num = 1, M.resources_max.bus_i2c do
            local i2c_name = "I2C" .. i2c_num
            tbl_bus_i2c[i2c_name] = {
                port = "BUS_" .. i2c_name,
            }
        end
        return tbl_bus_i2c
    end)(),

    timer = (function()
        local tbl_timer = {}
        for timer_num = 1, M.resources_max.timer do
            local timer_name = "TIMER" .. timer_num
            tbl_timer[timer_name] = {
                timer = timer_name,
            }
        end
        return tbl_timer
    end)(),
}

local definer = {
    field_property = { "forced", "optional", "uncertain" },
}
---@brief add a field to table
---@param tbl table
---@param field string
---@param opt string
function definer:addf(tbl, field, opt)
    for _, v in pairs(self.field_property) do
        if opt == v then
            if not tbl[v] then
                tbl[v] = {}
            end
            tbl[v][field] = true
        end
    end
end

---@brief delete field from table
---@param tbl table
function definer:delf(tbl, field)
    for _, v in pairs(self.field_property) do
        if tbl[v][field] then
            table.remove(tbl[v], field)
        end
    end
end

---@brief get field from table
---@param tbl table
function definer:getf(tbl, field)
    if tbl[field] == nil then
        return false
    else
        return true
    end
end

function definer:io(opts)
    local strict_tbl = {}
    local fields = {}

    definer:addf(fields, "name", "forced")
    definer:addf(fields, "io", "forced")
    definer:addf(fields, "owner", "optional")

    setmetatable(strict_tbl, {
        __newindex = function(_, k, v)
            if not fields.forced[k] and not fields.optional[k] then
                error(string.format('"%s" is an illegal members for io defination.', k))
            end
            rawset(strict_tbl, k, v)
        end,
    })

    for k, v in pairs(opts) do
        strict_tbl[k] = v
    end

    for k in pairs(fields.forced) do
        if strict_tbl[k] == nil then
            error(string.format('Missing necessary member "%s" for io defination.', k))
        end
    end

    return strict_tbl
end

function definer:bus_uart(opts)
    local strict_tbl = {}
    local fields = {}
    local uart_type = { "TX", "RX", "TXRX" }

    definer:addf(fields, "name", "forced")
    definer:addf(fields, "bus", "forced")
    definer:addf(fields, "type", "forced")
    definer:addf(fields, "dma", "forced")

    definer:addf(fields, "owner", "optional")

    for k, v in pairs(opts) do
        if k == "type" then
            local valid = false

            for _, type in ipairs(uart_type) do
                if v == type then
                    valid = true
                    break
                end
            end

            if not valid then
                error(string.format('"type" must be one of "TX", "RX", "TXRX"'))
            else
                if v == "TX" then
                    definer:addf(fields, "tx", "forced")
                    definer:addf(fields, "rx", "optional")
                elseif v == "RX" then
                    definer:addf(fields, "tx", "optional")
                    definer:addf(fields, "rx", "forced")
                elseif v == "TXRX" then
                    definer:addf(fields, "tx", "forced")
                    definer:addf(fields, "rx", "forced")
                end
            end
        end
    end

    setmetatable(strict_tbl, {
        __newindex = function(_, k, v)
            if fields.forced[k] == nil and fields.optional[k] == nil then
                error(string.format('"%s" is an illegal members for uart bus defination.', k))
            end

            rawset(strict_tbl, k, v)
        end,
    })

    for k, v in pairs(opts) do
        strict_tbl[k] = v
    end

    for k in pairs(fields.forced) do
        if strict_tbl[k] == nil then
            error(string.format('Missing necessary member "%s" for uart bus defination.', k))
        end
    end

    return strict_tbl
end

function definer:bus_spi(opts)
    local strict_tbl = {}
    local fields = {}
    local spi_type = { "TX", "RX", "TXRX" }

    definer:addf(fields, "name", "forced")
    definer:addf(fields, "bus", "forced")
    definer:addf(fields, "type", "forced")
    definer:addf(fields, "ncs", "forced")
    definer:addf(fields, "sclk", "forced")
    definer:addf(fields, "dma", "forced")

    definer:addf(fields, "owner", "optional")

    for k, v in pairs(opts) do
        if k == "type" then
            local valid = false

            for _, type in ipairs(spi_type) do
                if v == type then
                    valid = true
                    break
                end
            end

            if not valid then
                error(string.format('"type" must be one of "TX", "RX", "TXRX"'))
            else
                if v == "TX" then
                    definer:addf(fields, "miso", "optional")
                    definer:addf(fields, "mosi", "forced")
                elseif v == "RX" then
                    definer:addf(fields, "miso", "forced")
                    definer:addf(fields, "mosi", "optional")
                elseif v == "TXRX" then
                    definer:addf(fields, "miso", "forced")
                    definer:addf(fields, "mosi", "forced")
                end
            end
        elseif k == "ncs" then
            if v[1] == nil then
                error('BUS_SPIx "ncs" must be set to at least one io.')
            else
                for i, io in pairs(v) do
                    if
                        pcall(function(p)
                            if p.name ~= nil then
                                p.name = p.name
                            end
                        end, io) == false
                    then
                        error(string.format("BUS_SPIx ncs[%d] must be setup by platform.setup.io", i))
                    end
                end
            end
        end
    end

    setmetatable(strict_tbl, {
        __newindex = function(_, k, v)
            if fields.forced[k] == nil and fields.optional[k] == nil then
                error(string.format('"%s" is an illegal members for spi bus defination.', k))
            end

            rawset(strict_tbl, k, v)
        end,
    })

    for k, v in pairs(opts) do
        strict_tbl[k] = v
    end

    for k in pairs(fields.forced) do
        if strict_tbl[k] == nil then
            error(string.format('Missing necessary member "%s" for spi bus defination.', k))
        end
    end

    return strict_tbl
end

function definer:bus_i2c(opts)
    local strict_tbl = {}
    local fields = {}

    definer:addf(fields, "name", "forced")
    definer:addf(fields, "bus", "forced")
    definer:addf(fields, "scl", "forced")
    definer:addf(fields, "sda", "forced")
    definer:addf(fields, "dma", "forced")

    definer:addf(fields, "owner", "optional")

    setmetatable(strict_tbl, {
        __newindex = function(_, k, v)
            if fields.forced[k] == nil and fields.optional[k] == nil then
                error(string.format('"%s" is an illegal members for i2c bus defination.', k))
            end

            rawset(strict_tbl, k, v)
        end,
    })

    for k, v in pairs(opts) do
        strict_tbl[k] = v
    end

    for k in pairs(fields.forced) do
        if strict_tbl[k] == nil then
            error(string.format('Missing necessary member "%s" for i2c bus defination.', k))
        end
    end

    return strict_tbl
end

M.config = function(tbl)
    local strict_tbl = {}
    local fields = {}
    definer:addf(fields, "series", "forced")
    definer:addf(fields, "mcu", "forced")
    definer:addf(fields, "identifier", "forced")
    definer:addf(fields, "toolchain", "forced")

    setmetatable(strict_tbl, {
        __newindex = function(_, k, v)
            if fields.forced[k] == nil and fields.optional[k] == nil then
                error(string.format('"%s" is an illegal members for io defination.', k))
            end
            rawset(strict_tbl, k, v)
        end,
    })

    for k, v in pairs(tbl) do
        strict_tbl[k] = v
    end

    for k in pairs(fields.forced) do
        if strict_tbl[k] == nil then
            error(string.format('Missing necessary member "%s" for io defination.', k))
        end
    end

    return strict_tbl
end

M.setup = function(dev, opts)
    if dev == M.resources.all.io then
        return definer:io(opts)
    elseif dev == M.resources.all.bus_uart then
        return definer:bus_uart(opts)
    elseif dev == M.resources.all.bus_spi then
        return definer:bus_spi(opts)
    elseif dev == M.resources.all.bus_i2c then
        return definer:bus_i2c(opts)
    end
end

return M
