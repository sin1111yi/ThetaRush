# "How to Define a Target for ThetaRush?"

The `target.h` file is used for configuring the source code of ThetaRush, while `target.cmake` is utilized by CMake to configure the entire project automatically. Both of these files are automatically generated by `target.lua`, and manual editing should be strictly avoided to prevent unexpected errors.

To generate `target.h` and `target.cmake` through writing `target.lua`, a properly formatted target.lua should be declared as a `lua module` and follow the following structure:

```lua
local M = {}

M.info = { ... }
M.io = { ... }
M.bus = { ... }

return M
```

## 1."How to Define a Platform?"

To define the platform configuration by creating `M.info` in the specified format:

```lua
M.info = platform.config({
    mcu = "STM32H750xx",
    mcu_series = "STM32H7",
    identifier = "weact_stm32h750vbtx_core_board",
    toolchain = "arm-none-eabi"
})
```

Forced item(s)

- *`info.mcu`* is the mcu of current target
- *`info.mcu_series`* is the series of current mcu, for *STM32H750xx*, it's *STM32H7*
- *`info.identifier`* is the unique identifier of current target
- *`info.toolchain`* is the prefix of cross-compilation for current mcu, for *arm-none-eabi-gcc* is *arm-none-eabi*

Optional item(s)

- None
