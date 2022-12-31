// There's several methods to implement the debug console.
//  + One is to allocate a memory character buffer, and you can saving what you want to print.
//     This buffer will be treated as a robin buffer.
//     This method is useful, when you have a debugger, but don't have enough peripheral resources.
//  + Two is to allocate a communicate method, and you can say whatever you want to the BUS.
//     Generally, user may allocate a UART or SCI for spacial use.
//  + Three is to use a special record devices, such as UART recorder to record the UART stream,
//     scope to record what ADC saying, digital analyzer to record special communication protocol.
// All in all, debug console is something that can translate a character string to the monitor 
//  information. So that, the debug console has to provide a method to receive string.

#ifndef _HEADER_DEBUG_CONSOLE_PTR_H_
#define _HEADER_DEBUG_CONSOLE_PTR_H_

#ifdef __cplusplus
extern "C"
{
#endif

	//////////////////////////////////////////////////////////////////////////
	// Type


	//////////////////////////////////////////////////////////////////////////
	// Definition

#ifndef DBG_FRM_PRINT
#ifdef DISABLE_DEBUG_FRAMEWORK
#define DBG_FRM_PRINT(X) 
#else
#ifndef DISABLE_ALL_DEFAULT_NOTIFICATION
//#pragma message("DBG_FRM_PRINT function isn't defined clearly, printf function will use automatically.")
#endif //DISABLE_ALL_DEFAULT_NOTIFICATION
#define DBG_FRM_PRINT(message, ...) printf(message, ...)
#endif //DISABLE_DEBUG_FRAMEWORK
#endif //DBG_FRM_PRINT

#ifndef DBG_FRM_ASSERT
#ifdef DISABLE_DEBUG_FRAMEWORK
#define DBG_FRM_ASSERT(X)
#else
#ifndef DISABLE_ALL_DEFAULT_NOTIFICATION
//#pragma message("DBG_FRM_ASSERT function isn't defined clearly, default mode will use.")
#endif //DISABLE_ALL_DEFAULT_NOTIFICATION
#define DBG_FRM_ASSERT(coindition, msg, ...) \
			if(!(condition)) \
				DBG_FRM_PRINT("> [%s, %d, in function %s, Assert]:\n"msg,__FILE__,__LINE__,__func__,##__VA_ARGS__)
#endif //DISABLE_DEBUG_FRAMEWORK
#endif //DBG_FRM_PRINT

#ifndef DBG_FRM_ERRO
#ifdef DISABLE_DEBUG_FRAMEWORK
#define DBG_FRM_ERRO(X)
#else
#define DBG_FRM_ERRO(msg, ...) \
			DBG_FRM_PRINT("> [%s, %d, in function %s, ERRO]:\n"msg,__FILE__,__LINE__,__func__,##__VA_ARGS__)
#endif //DISABLE_DEBUG_FRAMEWORK
#endif //DBG_FRM_INFO

#ifndef DBG_FRM_WARN
#ifdef DISABLE_DEBUG_FRAMEWORK
#define DBG_FRM_WARN(X)
#else
#define DBG_FRM_WARN(msg, ...) \
			DBG_FRM_PRINT("> [%s, %d, in function %s, WARN]:\n"msg,__FILE__,__LINE__,__func__,##__VA_ARGS__)
#endif //DISABLE_DEBUG_FRAMEWORK
#endif //DBG_FRM_INFO

#ifndef DBG_FRM_INFO
#ifdef DISABLE_DEBUG_FRAMEWORK
#define DBG_FRM_INFO(X)
#else
#define DBG_FRM_INFO(msg, ...) \
			DBG_FRM_PRINT("> [%s, %d, in function %s, INFO]:\n"msg,__FILE__,__LINE__,__func__,##__VA_ARGS__)
#endif //DISABLE_DEBUG_FRAMEWORK
#endif //DBG_FRM_INFO
	//////////////////////////////////////////////////////////////////////////
	// Global variable


	//////////////////////////////////////////////////////////////////////////
	// Function prop-type


	//////////////////////////////////////////////////////////////////////////
	// Inline function definition


#ifdef __cplusplus
}
#endif

#endif // macro _HEADER_DEBUG_CONSOLE_PTR_H_

