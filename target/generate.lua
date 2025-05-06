warn("@on")

if #arg == 0 then
    error("Empty input parameters are not allowed.")
elseif #arg > 1 then
    warn("Only the first input parameter will be accepted.")
end

local target = require(arg[1] .. "." .. "target")
local platfrom = require("platform")

for _, tbl in pairs(target.io) do
    print(string.format("#define %-20s P%s%d", tbl.name, tbl.io.port, tbl.io.pin))
end

for n = 1, platfrom.resources_max.bus_uart do
    local port = "uart" .. n
    if target.bus[port] ~= nil then
        print(string.format("#define %-20s %d", "USE_" .. target.bus[port].bus.port, 1))
        print(string.format("#define %-20s %d", "USE_" .. target.bus[port].bus.port .. "_DMA", target.bus[port].dma and 1 or 0))
        print(string.format("#define %-20s P%s%d", target.bus[port].tx.name, target.bus[port].tx.io.port, target.bus[port].tx.io.pin))
        print(string.format("#define %-20s P%s%d", target.bus[port].rx.name, target.bus[port].rx.io.port, target.bus[port].rx.io.pin))
    end
end

for n = 1, platfrom.resources_max.bus_spi do
    local port = "spi" .. n
    if target.bus[port] ~= nil then
        print(string.format("#define %-20s %d", "USE_" .. target.bus[port].bus.port, 1))
        print(string.format("#define %-20s %d", "USE_" .. target.bus[port].bus.port .. "DMA", target.bus[port].dma and 1 or 0))
        print(string.format("#define %-20s P%s%d", target.bus[port].mosi.name, target.bus[port].mosi.io.port, target.bus[port].mosi.io.pin))
        print(string.format("#define %-20s P%s%d", target.bus[port].miso.name, target.bus[port].miso.io.port, target.bus[port].miso.io.pin))
        print(string.format("#define %-20s P%s%d", target.bus[port].sclk.name, target.bus[port].sclk.io.port, target.bus[port].sclk.io.pin))
    end
end

for n = 1, platfrom.resources_max.bus_i2c do
    local port = "i2c" .. n
    if target.bus[port] ~= nil then
        print(string.format("#define %-20s %d", "USE_" .. target.bus[port].bus.port, 1))
        print(string.format("#define %-20s %d", "USE_" .. target.bus[port].bus.port .. "DMA", target.bus[port].dma and 1 or 0))
        print(string.format("#define %-20s P%s%d", target.bus[port].scl.name, target.bus[port].scl.io.port, target.bus[port].scl.io.pin))
        print(string.format("#define %-20s P%s%d", target.bus[port].sda.name, target.bus[port].sda.io.port, target.bus[port].sda.io.pin))
    end
end