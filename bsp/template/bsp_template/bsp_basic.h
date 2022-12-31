#ifndef _BSP_BASIC_H_
#define _BSP_BASIC_H_


//////////////////////////////////////////////////////////////////////////
// For EMLIB_BUILD_ENV macro
// Build Environment Select
#define BSP_BUILD_MSVC		(0x0001)
#define BSP_BUILD_GCC		(0x0002)
#define BSP_BUILD_KEIL		(0x0003)
#define BSP_BUILD_CCS		(0x0004)


//////////////////////////////////////////////////////////////////////////
// For EMLIB_DEVICE_MODEL macro
// This list defines all the supported devices,
// and all the supported boards

#define STM32G030F6XX		(0x0010) 

#define WINDOWS_GENERAL		(0x00FF)
#define LINUX_GENERAL		(0x000F)

//////////////////////////////////////////////////////////////////////////
// For EMLIB_BOARD_SELECT macro
#define BSP_BOARD_NULL		(0x0000)
#define BSP_BOARD_MINI		(0x0001)


// some other useful macro
#ifndef NULL
#define NULL ((0))
#endif

#endif
