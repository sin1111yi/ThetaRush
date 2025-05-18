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

warn("@on")

local config = {
	target = nil,
	verbose = false,
	clean = nil,
}

local function show_info(opt)
	if opt == "help" then
		print([[
Usage:
  lua target_config_gen.lua [options] [parameters]

Generate target config files for ThetaRush according to "<target_name>/target_config.lua"

Options:
  --help, -h             Show help information
  --target <target>, -t  Specify target name (required when generating files)
  --dump-result, -d      Dump the content of generated files
  --clean <target>, -c   Clean generated files

Parameters:
  Can accept additional configuration parameters in key=value format

Examples:
  Generate config:        lua generate.lua -t <target>
  Clean specific target:  lua generate.lua -c <target>
  Show file contents:     lua generate.lua -t <target> -d
]])
	end
end

local function parse_input_parameters(args)
	for k, arg in ipairs(args) do
		if arg == "-h" or arg == "--help" then
			show_info("help")
			os.exit(0)
		elseif arg == "-t" or arg == "--target" then
			config.target = args[k + 1]
			k = k + 1 -- skip next argrument
		elseif arg == "-d" or arg == "--dump-result" then
			config.verbose = true
		elseif arg == "-c" or arg == "--clean" then
			if args[k + 1] ~= nil then
				config.clean = args[k + 1]
				k = k + 1
			else
				print("target_config_gen.lua: Unknown input paratemer for option clean.\r\n")
				show_info("help")
				os.exit(1)
			end
		end
	end
end

parse_input_parameters(arg)

if config.clean ~= nil then
	os.remove(config.clean .. "/target.h")
	os.remove(config.clean .. "/target.cmake")
	os.exit(0)
end

local chead_file, err, cmake_file
local chead_file_name = config.target .. "/target.h"
local cmake_file_name = config.target .. "/target.cmake"
chead_file, err = io.open(chead_file_name, "w")
if not chead_file then
	print("Error when openning file, " .. err)
	os.exit(2)
end
cmake_file, err = io.open(cmake_file_name, "w")
if not cmake_file then
	print("Error when openning file, " .. err)
	os.exit(2)
end

local target = require(config.target .. "." .. "target")
local tr = require("tr_resources")

local licenses_declaration = {
	c_cpp = string.format([[
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

	cmake = string.format([=[
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

]=]),
}

local chead = {
	---@param macro string
	---@param val string | integer | boolean
	add_marco = function(macro, val)
		if type(val) == "string" then
			chead_file:write(string.format("#define %-30s %s\n", macro, val))
		elseif type(val) == "number" then
			chead_file:write(string.format("#define %-30s %d\n", macro, val))
		elseif type(val) == "boolean" then
			chead_file:write(string.format("#define %-30s %d\n", macro, val and 1 or 0))
		end
	end,

	---@param snippet string
	add_snippet = function(snippet)
		chead_file:write(snippet .. "\n")
	end,

	---@param marco string
	protect_empty_marco = function(marco)
		local m = string.format(
			[[
#ifndef %-20s
#define %-20s
#endif /* %s */]],
			marco,
			marco,
			marco
		)
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

		local m = string.format(
			[[
#ifndef %-20s
#define %-20s %s
#endif /* %s */]],
			macro,
			macro,
			v,
			macro
		)
		return m
	end,
}

cmake_file:write(licenses_declaration.cmake)
cmake_file:write(string.format('set(%s %s CACHE INTERNAL "Target MCU")\n', "TARGET_MCU", target.info.mcu))
cmake_file:write(
	string.format('set(%s %s CACHE INTERNAL "Target MCU Series")\n', "TARGET_MCU_SERIES", target.info.mcu_series)
)
cmake_file:write(
	string.format('set(%s "%s" CACHE INTERNAL "Target Identifier")\n', "TARGET_IDENTIFIER", target.info.identifier)
)
cmake_file:write(
	string.format(
		'set(%s %s CACHE INTERNAL "Target Build Toolchain")\n',
		"TARGET_BUILD_TOOLCHAIN",
		target.info.toolchain
	)
)

chead.add_snippet(licenses_declaration.c_cpp)
chead.add_snippet("#pragma once\n")
chead.add_snippet(chead.protect_empty_marco(target.info.mcu))
chead.add_snippet(chead.protect_empty_marco(target.info.mcu_series))
chead.add_snippet(chead.protect_marco("TARGET_IDENTIFIER", string.format('"%s"', target.info.identifier)))
chead.add_snippet(chead.protect_marco("PROJECT_BUILD_TIME", string.format('"%s"', os.date("%d-%m-%Y %H:%M:%S"))))

if target.info.debug == true then
	chead_file:write([[
// WARN: In this case, trace and debug interface will be disabled!
//       Please ensure GPIOs of the SWD interface are not occupied!
]])
	chead.add_snippet(chead.protect_empty_marco("__HARDWARE_DEBUG_ENABLED__"))
elseif target.info.debug == false or target.info.debug == nil then
	chead_file:write([[
// WARN: In this case, trace and debug interface will be disabled!
]])
	chead.add_snippet(chead.protect_empty_marco("__HARDWARE_DEBUG_DISABLED__"))
end

local outputIoNum = 0
local inputIoNum = 0

for k, io in ipairs(target.io) do
	local ioArrow = {
		device = nil,
		implResource = nil,
		platformResource = nil
	}
	if io.set == tr.set.led then
		outputIoNum = outputIoNum + 1
		ioArrow.device = io.owner
		ioArrow.impl = "IMPL_RES" .. "(" .. tr.impl.output_io .. ", " .. outputIoNum .. ")"
		ioArrow.platformResource = tr.impl.output_io .. "_" .. outputIoNum .. "__MAP__" .. "PLATFORM_RES"
	elseif io.set == tr.set.key then
		inputIoNum = inputIoNum + 1
		ioArrow.device = io.owner
		ioArrow.impl = "IMPL_RES" .. "(" .. tr.impl.input_io .. ", " ..  inputIoNum .. ")"
		ioArrow.platformResource = tr.impl.input_io .. "_" .. inputIoNum .. "__MAP__" .. "PLATFORM_RES"
	end
	chead.add_marco("USING_" .. ioArrow.device, true)
	chead.add_marco(io.owner .. "_" .. "DRV_IMPL", ioArrow.impl)
	chead.add_marco(ioArrow.platformResource, io.source)
end

print(string.format(
	[[
target_config_gen.lua finished, file generated at %s.]],
	config.target
))
