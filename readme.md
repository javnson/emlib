# Embedded library Manual

At the present time, the project is still improving, this is only a test version, 0.0.1. If you want to enjoy some modules which doesn't exist, please contact me.

This is a general purpose library for embedded devices, which will help you develop your portable flexible embedded applications. All the tools supplied by the tool-kit will allow you to run, or more precisely simulate, in you computer whatever Windows or Linux even a bare machine.

Generally and firstly, you may copy the necessary files to your project. Then you need to tell your compiler the existence of the library. Again you need to write a little code to  tell the library what you boards is, or you may copy and invoke BSP(board support package) which is suitable to your devices. And last but not least, enjoy!

## 1. Know the library

This library contains a lot of modules that you would use in different scenarios. They are

### 1.1 control suite

This control suite module is the first module for the library, and once upon  a time these code help me a lot. All the files are stored in the `./ctrl` path.

The module, control suite, provide you a lot of tools for building a embedded control devices. Basically, this module will allow you to implement your own transfer function easily. Which only need a little but reasonable RAM area. And also some basic controller module will be supplied, such as, PID, ramp generator, and digital filters.

Right now the developer aim at cooperation between your MCU or DSP with FPGA, we would supplied you a tool kits for communication with FPGA, and solutions for team up.

### 1.2 general purpose real-time controller

This module, general purpose real-time controller, provided you a serials of flexible tools helping you build your own general purpose real-time controller. All the files are stored in the `./gpctrl` directory.

This module prepare a tool for real-time general purpose input / output tasks. The original intention is to arm your devices by the software, so that you can focus on logic or specific routine, without be distracted by scheduling, and meanwhile you have no necessary to invoke a operating system or interrupted based task scheduler. In most case, the real-time device has no need to run a OS, a cumbersome scheduler, for the tiny processer. In another words, you can treats this module as a round-robin scheduler.

All the module needs only a general purpose timer.

### 1.3 CMSIS extension

This module, CMSIS extension, is provided you a lot of extension and using demo, which helps you use CMSIS library more easily. All the files are stored in the `./cmsis_ext` directory.

### 1.4 communication suite

This module, communication suite, provided you a lot of framework, which is object-oriented, to simplify the communication routine. Meanwhile, based on the communication, we provide a lot of packages to dispatch the peripheral electronic-modules quickly, and extract the core function, which makes you keep your eye on the right things. All the files are stored in the `./comm`directory.

### 1.5 debug suite

This module, debug suite, provided you a useful tool to debug your embedded devices. Sometimes these debug method would be treated as backdoor. All the files are stored in the `./dbg` directory.

### 1.6 unit test

This module will provide all the unit test and examples which help you quick start. All the files are stored in each module's root directory. In each module, you will see the unit test in `./<module>/unit_test` directory.

### 1.7 BSP

The BSP module provided the specified hardware support package. Each folder contains a device usage case, each case defines which module is setup and the interface for device and library. All the supported device is stored in the `./bsp` folder.

If you need to use the BSP, you need to copy the specified BSP files in the BSP folders.

## 2. Quick start

The following manual will help you setup your compile environment.

### 2.1 Copy module to your project

Firstly, you need to copy the `emlib` module to your project directory. Each module is dependent only when the manual tell you. User don't need to delete any file of the submodule you don't need, and the only thing user need to do is to change the config header file, which owns the same name with the module name. The detail will descript in the later.

### 2.2 configure your compiler

Secondly, you need to edit your compiler config. There're lot's of things to do, as follows

+ Add header (scan) path

Each module owns a header path to added to the compile header path. You should add the root directory of the module to the "include scan path".

The submodule's header file is added based on the module root path.

+ Add macro config

An important macro `_EMLIB_DEBUG` is necessary, if you need to use debug mode of the library. And you need a log function, which will output all the information, warning and errors.

It's recommended that you define the `_EMLIB_DEBUG` macro to `_DEBUG`. 

Each module define the debug information output for debugging, and there's no doubt that performance consumption is necessary.

+ Configure each module

In the end, you need to config the submodule of each module, the specified manual is stored in the `readme.md` in the module root directory. This file will give suggestions to config the module headers.

### 2.3 prepare a BSP file

The main target of a BSP file is to config all the modules. The easiest method is to copy one BSP file in the `./bsp` folder.

If you need to customize a BSP, you need to have a glance of the BSP file prepare part, or imitate existing BSP headers.

### 2.4 Enjoy modules

The final thing you need to do is to add the BSP header to your source file. And now you can invoke the library routines, or call the frameworks.





 

