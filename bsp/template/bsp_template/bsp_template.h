
#include <bsp_basic.h>


#ifndef _HEADER_DEVICE_BSP_
#define _HEADER_DEVICE_BSP_


// You need to specify the build environment you use,
// 
#define EMLIB_BUILD_ENV BUILD_KEIL

// You need to specify the device you use, 
// you may choose the device in "bsp_basic.h"
#define EMLIB_DEVICE_MODEL STM32G030F6XX

// You need to specify the board you use,
// you may choose the board in "bsp_basic.h"
// otherwise, you may set the macro to zero (0) 
// to specify the board is temporary
#define EMLIB_BOARD_MODEL (0)

// You need to specify the project version.
// I strongly suggest you give each scenario an unique project version.
// And use this project version to judge which module is uploaded.
#define EMLIB_PROJECT_VERSION (0)

#endif //_HEADER_DEVICE_BSP_
