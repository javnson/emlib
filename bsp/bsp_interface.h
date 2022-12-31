
// System headers
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>


// Module headers

#ifndef _HEADER_BSP_INTERFACE_H_
#define _HEADER_BSP_INTERFACE_H_

#ifdef __cplusplus
extern "C"
{
#endif


	//////////////////////////////////////////////////////////////////////////
	// Definition
#ifndef NULL
#define NULL 0
#endif

	//////////////////////////////////////////////////////////////////////////
	// Select device
#if defined BSP_DEVICE_STM32G030
	#include <board/stm32g030/bsp_stm32g030.h>
#endif

#ifdef __cplusplus
}
#endif

#endif // macro _HEADER_BSP_INTERFACE_H_
