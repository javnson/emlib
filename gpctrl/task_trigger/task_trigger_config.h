
#include <bsp_interface.h>
// System headers


// Module headers



#ifndef _HEADER_TASK_TRIGER_CONFIG_H_
#define _HEADER_TASK_TRIGER_CONFIG_H_

#ifdef __cplusplus
extern "C"
{
#endif

	//////////////////////////////////////////////////////////////////////////
	// Definition
	
#ifndef TASK_TRIGER_DISABLE_FIXED_TASK_NUM
	// You may specify a fixed task quantity, which you can't change it.
	// So the fixed quantity number of tasks will be stored in the struct by array.
	// This is the most simple mode.
#define TASK_TRIGER_FIXED_TASK_NUM 
#else
	// You may specify a address to the task queue, which you need to maintain manually
	// So the address will be saved in the struct by pointer.
	// I strongly suggest you, you should use the pointer mode, if you have a malloc().
	// It's your responsibility for paying attention to allocate and free the memory at time.
#define TASK_TRIGER_POINTER
#endif

	// You may change the following macro to specify the maximum tasks number.
#ifdef TASK_TRIGER_FIXED_TASK_NUM
#define TASK_TRIGER_TASK_QUANTITY (10)
#endif

	// The timer frequency of the ISR
	// We strongly suggest you set the frequency to 10k-100k Hz
	// All the unit will be transmit to the number of ISR, based on the macro 
	//  TASK_TRIGGER_TIMER_FREQUENCY
	// Please attention the accuracy and 
#ifndef TASK_TRIGGER_TIMER_FREQUENCY
#define TASK_TRIGGER_TIMER_FREQUENCY (200000)
#endif

	// If you won't let falling edge exist, when the duration is reached,
	// You may disable the macro.
#ifndef TASK_TRIGGER_DISABLE_AUTO_FALLING
#define TASK_TRIGGER_AUTO_FALLING
#endif



#ifdef __cplusplus
}
#endif

#endif // macro _HEADER_TASK_TRIGER_CONFIG_H_
