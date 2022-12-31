#include <bsp_interface.h>



// This is the symbol for ending of a message.
#define SBC_TOKEN_END ';'
#define SBC_TOKEN_BEGIN ':'

	// If tasks are defined by pointer, user must pay attention to allocate
	// memory for tasks.
#ifndef SBC_TASKS_POINTER
#ifndef SBC_TASKS_NUM
#define SBC_TASKS_NUM 20
#endif
#else
#undef SBC_TASKS_NUM
#endif

	// Specify the maximum length of a message,
	// For pointer mode, the param buffer will be allocate using the length.
#ifndef MAX_MESSAGE_LENGTH
#define MAX_MESSAGE_LENGTH (32)
#endif

	// Specify the maximum length of the message buffer has.
	// For non-pointer mode the param buffer will be allocate using the length.
#ifndef MAX_PARAM_BUFFER
#define MAX_PARAM_BUFFER (512)
#endif
