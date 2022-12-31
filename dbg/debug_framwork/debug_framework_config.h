
#include <bsp_interface.h>
// System headers


// Module headers



#ifndef _HEADER_NAME_H_
#define _HEADER_NAME_H_

#ifdef __cplusplus
extern "C"
{
#endif


	//////////////////////////////////////////////////////////////////////////
	// Definition
	
	// Submodule config
	// The debug framework enable flag, you may define the disable flag, if you
	//  want to escape from the debug information, and meanwhile the application
	//  performance will relatively improve.
#define DISABLE_DEBUG_FRAMEWORK

	// If you need to show all the compiler notification please	comment the following macro
#define DISABLE_ALL_DEFAULT_NOTIFICATION

	// If you need to disable output of memory check function.
#define DISABLE_DBG_FRM_MEMORY_VALID_CHECK_PTR

	// If you need to disable the memory valid check, please define this macro
#define DISABLE_DBG_FRM_MEMORY_VALID_CHECK



	//////////////////////////////////////////////////////////////////////////
	// Type



	//////////////////////////////////////////////////////////////////////////
	// Global variable


	//////////////////////////////////////////////////////////////////////////
	// Function prop-type


	//////////////////////////////////////////////////////////////////////////
	// Inline function definition


#ifdef __cplusplus
}
#endif

#endif // macro _HEADER_NAME_H_


