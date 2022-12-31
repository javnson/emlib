// The function supplied in this file is called when the fucntion call happened.
// This file should be rewrite based on the chip memory architecture.

// System headers
#include <stdint.h>

// Module headers



#ifndef _HEADER_MEMOPRY_CUECK_H_
#define _HEADER_MEMOPRY_CUECK_H_

#ifdef __cplusplus
extern "C"
{
#endif

	//////////////////////////////////////////////////////////////////////////
	// Type
#ifndef addr_width_t
typedef uint32_t addr_width_t;
#endif

	//////////////////////////////////////////////////////////////////////////
	// Definition
#define MVC_ADDR_BETWEEN(addr, lower_bound, upeer_bound) \
	((((addr_width_t)addr) >= (lower_bound)) && (((addr_width_t)addr) <= (upeer_bound)))
	
#define MVC_ADDR_LESSTHN(addr, upper_bound) \
	(((addr_width_t)addr) <= (upper_bound))
	
	#ifdef DISABLE_DBG_FRM 	
	#define DISABLE_DBG_FRM_MEMORY_VALID_CHECK_PTR
	#endif

	//////////////////////////////////////////////////////////////////////////
	// Global variable


	//////////////////////////////////////////////////////////////////////////
	// Function prop-type


	//////////////////////////////////////////////////////////////////////////
	// Inline function definition
#if EMLIB_DEVICE_MODEL == STM32G030F6XX

	static inline dbg_frm_valid_t is_ram_area(void* addr)
	{
		if (MVC_ADDR_BETWEEN(addr, 0x20000000, 0x20001FFF) || // SRAM
			MVC_ADDR_BETWEEN(addr, 0x1FFF0000, 0x1FFF1FFF) || // system memory
			MVC_ADDR_LESSTHN(addr, 0x0000FFFF))   // SRAM depending on BOOT configuration
			return 0;
		return 1;
	}

	static inline dbg_frm_valid_t is_flash_area(void* addr)
	{
		if (MVC_ADDR_BETWEEN(addr, 0x1FFF7800, 0x1FFF787F) || // Option bytes
			MVC_ADDR_BETWEEN(addr, 0x1FFF7500, 0x1FFF77FF) || // Engineering bytes
			MVC_ADDR_BETWEEN(addr, 0x1FFF7000, 0x1FFF74FF) || // OTP
			MVC_ADDR_BETWEEN(addr, 0x08000000, 0x0800FFFF) || // Main Flash memory
			MVC_ADDR_LESSTHN(addr, 0x0000FFFF))   // Main Flash memory
			return 0;
		return 1;
	}

	static inline dbg_frm_valid_t is_variable_space_valid(void* addr)
	{
		if (is_flash_area(addr) || is_ram_area(addr))
			return 0;

		if (addr == NULL)
		{
#ifndef DISABLE_DBG_FRM_MEMORY_VALID_CHECK_PTR
			DBG_FRM_WARN("Valid variable space are invoked.\r\n");
#endif
			return 1;
		}

		return 0;
	}

	static inline dbg_frm_valid_t is_program_space_valid(void* addr)
	{
		if (is_flash_area(addr) || is_ram_area(addr))
			return 0;

		if (addr == NULL)
		{
#ifndef DISABLE_DBG_FRM_MEMORY_VALID_CHECK_PTR
			DBG_FRM_WARN("Valid program space are invoked.\r\n");
#endif
			return 1;
		}

		return 1;
	}

	static inline dbg_frm_valid_t is_register_space_valid(void* addr)
	{
		if (MVC_ADDR_BETWEEN(addr, 0x40020000, 0x400233FF) || // AHB
			MVC_ADDR_BETWEEN(addr, 0x40013400, 0x40015BFF) || // APB
			MVC_ADDR_BETWEEN(addr, 0x40007000, 0x400133FF) || // APB
			MVC_ADDR_BETWEEN(addr, 0x400003FF, 0x40005FFF)) // APB
			return 0;

		if (addr == NULL)
		{
#ifndef DISABLE_DBG_FRM_MEMORY_VALID_CHECK_PTR
			DBG_FRM_WARN("Valid register space are invoked.\r\n");
#endif
			return 1;
		}

		return 1;
	}

#else

	static inline dbg_frm_valid_t is_variable_space_valid(void* addr)
	{
		if (addr == NULL)
		{
#ifndef DISABLE_DBG_FRM_MEMORY_VALID_CHECK_PTR
			DBG_FRM_WARN("Valid variable space are invoked.\r\n");
#endif
			return 1;
		}

		return 0;
	}

	static inline dbg_frm_valid_t is_program_space_valid(void* addr)
	{
		if (addr == NULL)
		{
#ifndef DISABLE_DBG_FRM_MEMORY_VALID_CHECK_PTR
			DBG_FRM_WARN("Valid program space are invoked.\r\n");
#endif
			return 1;
		}

		return 0;
	}

	static inline dbg_frm_valid_t is_register_space_valid(void* addr)
	{
		if (addr == NULL)
		{
#ifndef DISABLE_DBG_FRM_MEMORY_VALID_CHECK_PTR
			DBG_FRM_WARN("Valid register space are invoked.\r\n");
#endif
			return 1;
		}

		return 0;
	}

#endif // DBG_MEMROY_MAP

#ifdef __cplusplus
}
#endif

#endif // macro _HEADER_NAME_H_



