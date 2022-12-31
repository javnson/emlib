
#include <stdint.h>
#include "debug_framework_config.h"


#ifndef _FILE_DEBUG_FRAMEWORK_H_
#define _FILE_DEBUG_FRAMEWORK_H_




#ifdef __cplusplus
extern "C"
{
#endif


	//////////////////////////////////////////////////////////////////////////
	// Type
	// NOTE: The only one condition the value is nonzero is fatal error is happened.
	typedef uint8_t dbg_frm_valid_t;




	//////////////////////////////////////////////////////////////////////////
	// Global variable


	//////////////////////////////////////////////////////////////////////////
	// Function prop-type


	//////////////////////////////////////////////////////////////////////////
	// Inline function definition


#ifdef __cplusplus
}
#endif

#endif //_FILE_DEBUG_FRAMEWORK_H_

// invoke all the debug framework components
// Please DO NOT CHANGE THE ORDER of these components.
#include "debug_console_ptr.h"
#include "memory_valid_check.h"
