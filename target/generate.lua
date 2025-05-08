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
]]

warn("@on")

local debug = 0
local t

if debug == 1 then
    if #arg == 0 then
        error("Empty input parameters are not allowed.")
    elseif #arg > 1 then
        warn("Only the first input parameter will be accepted.")
    end

    t = arg[1]
else
    t = "stm32h750"
end

local licenses_declaration = {
    c_cpp = string.format(
        [[
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
]]),

    cmake = string.format(
        [=[
#[[
# This file is a part of ThetaRush.
#
# ThetaRush is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# ThetaRush is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.
#
# If not, see <https://www.gnu.org/licenses/>.
]]

]=])
}

local chead_file, err, cmake_file
local chead_file_name = t .. "/target.h"
local cmake_file_name = t .. "/target.cmake"
chead_file, err = io.open(chead_file_name, "w")
if not chead_file then
    print("Error when openning file, " .. err)
    return
end
cmake_file, err = io.open(cmake_file_name, "w")
if not cmake_file then
    print("Error when openning file, " .. err)
    return
end

local target = require(t .. "." .. "target")
local platform = require("platform")

local chead = {
    ---@param macro string
    ---@param val string | integer | boolean
    add_marco = function(macro, val)
        if type(val) == "string" then
            chead_file:write(string.format("#define %-20s %s\n", macro, val))
        elseif type(val) == "number" then
            chead_file:write(string.format("#define %-20s %d\n", macro, val))
        elseif type(val) == "boolean" then
            chead_file:write(string.format("#define %-20s %d\n", macro, val and 1 or 0))
        end
    end,

    ---@param snippet string
    add_snippet = function(snippet)
        chead_file:write(snippet .. "\n")
    end,

    ---@param marco string
    protect_empty_marco = function(marco)
        local m = string.format([[
#ifndef %-20s
#define %-20s
#endif /* %s */
]], marco, marco, marco)
        return m
    end,

    ---@param macro string
    ---@param val string | integer | boolean
    protect_marco = function(macro, val)
        local v
        if type(val) == "string" then
            v = val
        elseif type(val) == "number" then
            v = tostring(val)
        elseif type(val) == "boolean" then
            v = tostring(val and 1 or 0)
        end

        local m = string.format([[
#ifndef %-20s
#define %-20s %s
#endif /* %s */
]], macro, macro, v, macro)
        return m
    end,
}

---@param io table
local function io_to_str(io)
    return string.format("P%s%d", io.port, io.pin)
end

cmake_file:write(licenses_declaration.cmake)
cmake_file:write(string.format("set(%-20s %s)\n", "TARGET_MCU", target.info.mcu))
cmake_file:write(string.format("set(%-20s %s)\n", "TARGET_MCU_SERIES", target.info.mcu_series))
cmake_file:write(string.format("set(%-20s %s)\n", "TARGET_IDENTIFIER", target.info.identifier))
cmake_file:write(string.format("set(%-20s %s)\n", "TARGET_TOOLCHAIN", target.info.toolchain))

chead.add_snippet(licenses_declaration.c_cpp)
chead.add_snippet("#pragma once\n")
chead.add_snippet(chead.protect_empty_marco(target.info.mcu))
chead.add_snippet(chead.protect_empty_marco(target.info.mcu_series))
chead.add_snippet(chead.protect_marco("TARGET_IDENTIFIER", string.format("\"%s\"", target.info.identifier)))

for _, tbl in pairs(target.io) do
    chead.add_marco(tbl.name, io_to_str(tbl.io))
end

for n = 1, platform.resources_max.bus_uart do
    local port = "uart" .. n
    if target.bus[port] ~= nil then
        chead.add_snippet(string.format(
[[/**
 * Bus UART%d
 */]], n))
        chead.add_marco(string.format("%s", "USE_" .. target.bus[port].name), 1)
        chead.add_marco(string.format("%s", "USE_" .. target.bus[port].name .. "_DMA"), target.bus[port].dma)
        chead.add_marco(target.bus[port].tx.name, io_to_str(target.bus[port].tx.io))
        chead.add_marco(target.bus[port].rx.name, io_to_str(target.bus[port].rx.io))
    end
end

for n = 1, platform.resources_max.bus_spi do
    local port = "spi" .. n
    if target.bus[port] ~= nil then
        chead.add_snippet(string.format(
[[/**
 * Bus SPI%d
 */]], n))
        chead.add_marco(string.format("%s", "USE_" .. target.bus[port].name), 1)
        chead.add_marco(string.format("%s", "USE_" .. target.bus[port].name .. "_DMA"), target.bus[port].dma and 1 or 0)
        chead.add_marco(target.bus[port].mosi.name, io_to_str(target.bus[port].mosi.io))
        chead.add_marco(target.bus[port].miso.name, io_to_str(target.bus[port].miso.io))
        chead.add_marco(target.bus[port].sclk.name, io_to_str(target.bus[port].sclk.io))
    end
end

for n = 1, platform.resources_max.bus_i2c do
    local port = "i2c" .. n
    if target.bus[port] ~= nil then
        chead.add_snippet(string.format(
[[/**
 * Bus I2C%d
 */]], n))
        chead.add_marco(string.format("%s", "USE_" .. target.bus[port].name), 1)
        chead.add_marco(string.format("%s", "USE_" .. target.bus[port].name .. "_DMA"), target.bus[port].dma and 1 or 0)
        chead.add_marco(target.bus[port].sck.name, io_to_str(target.bus[port].sck.io))
        chead.add_marco(target.bus[port].sda.name, io_to_str(target.bus[port].sda.io))
    end
end

chead_file:close()
cmake_file:close()

local cmd_dump_chead_file = "cat " .. chead_file_name
local cmd_dump_cmake_file = "cat " .. cmake_file_name

print(t .. "/" .. "target.h\n")
os.execute(cmd_dump_chead_file)
print("\n" .. t .. "/" .. "target.cmake\n")
os.execute(cmd_dump_cmake_file)