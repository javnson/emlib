

// System headers


// Module headers
#include "single_byte_command_config.h"



#ifndef _HEADER_SBC_H_
#define _HEADER_SBC_H_

#ifdef __cplusplus
extern "C"
{
#endif


	//////////////////////////////////////////////////////////////////////////
	// Definition


	//////////////////////////////////////////////////////////////////////////
	// task for single byte command state definition

	// Enable the single byte command task
#define SBC_MAP_ENABLE		0x01
	// task triggered, this flag will be clear when the task complete.
	// if next command is coming but triggered is set,
	// a callback function named trap will triggered.
	// the old param will copy to the trap, you may see the task at last time.
#define SBC_MAP_TRIGGERED	0x02
	// task has been run successfully
//#define SBC_MAP_COMPLETE	0x04
	// task is the trap for SBC
#define SBC_MAP_UNKNOWN	    0x08
	// This param will convert format automatically
	// the task has only one param, which is a unsigned number less than 32 bits.
#define SBC_MAP_UINTPARAM	0x10
	// This param will convert format automatically
	// the task has only one param, which is a unsigned number less than 32 bits.
#define SBC_MAP_INTPARAM	0x20
	// This param will convert format automatically
	// the task has only one param, which is a float number.
#define SBC_MAP_FLOATPARAM	0x40
	// This param will convert format automatically
	// the task has only one param, which is a unsigned number less than 32 bits.
//#define SBC_MAP_UNKNOWN		0x80

	//////////////////////////////////////////////////////////////////////////
	// Single byte command state definition

	// Enable the single byte command module
#define SBC_STATE_ENABLE    0x01
	// Enable the trap function
#define SBC_STATE_MSGTRAP   0x02
	// Enable the trap function for unknown message
#define SBC_STATE_UNMSGTRAP 0x04
	//STATE MACHINE The command receiving process is on-line.
#define SBC_STATE_ONLINE    0x08
	//STATE MACHINE The first check character is received.
#define SBC_STATE_GETHEAD   0x10
	// Enable the link mode, when unknown character is coming call another_callback.
#define SBC_STATE_NEXTLINK  0x20
	// The message is unknown for tasks who has already registered.
#define SBC_STATE_UNKNOWMSG 0x40
	//STATE MACHINE The task_trap is running. in the following two cases, the flag is on
	//  + The unknown message is received
	//  + The last message who has same command has not been react.
#define SBC_STATE_TRAPING   0x80
	// The SBC_TASKS_NUM buffer is overflow.
	// The program will ignore the warning, just clear the message_len variable.
#define SBC_STATE_PARAMBUFO 0x100
	// The function unknown_command is well-defined.
#define SBC_STATE_UNKNOWNACK 0x200

	//////////////////////////////////////////////////////////////////////////
	// Type
	typedef union
	{
		uint32_t unsigned_param;
		int32_t signed_param;
		float float_param;
	}sbc_param_content;

	struct __tag_sbc_mapping;
	struct __tag_single_byte_command;

	typedef void (*sbc_task_fn)(struct __tag_sbc_mapping*);
	typedef void (*sbc_trap_fn)(struct __tag_single_byte_command*);
	typedef void (*sbc_unknown_char_fn)(char ch);

	// Define a mapping type
	// map a command to callback function
	typedef struct __tag_sbc_mapping
	{
		// select one of SBC_MAP_XXX macro
		uint8_t state;

		// specify the command
		uint16_t command;

		// digital param
		sbc_param_content param;
		// param source
		uint16_t message_content[MAX_MESSAGE_LENGTH];
		uint16_t message_len;

		sbc_task_fn callback;
	}sbc_mapping_t;

	// Define a single byte command object
	typedef struct __tag_single_byte_command
	{
		// select one of SBC_STATE_XXX macro
		uint16_t state;

		// when the same message are generate but the last message haven't been done, 
		// the last message will be copy to task trap,
		// and the trap function will be called.
		// Another case is when an unknown command is received, than the message would be sent to
		// the task_trap.
		sbc_trap_fn trap;
		sbc_mapping_t task_trap;

		// When unknown message is received, using this react function.
		sbc_task_fn unknown_command;

		// When any abnormal content is coming, call the function, pass it to the next routine.
		// So you want to connect more than one reactor, please use the function to link them.
		sbc_unknown_char_fn another_callback;

		// saving all the mappings or tasks.
#ifdef SBC_TASKS_POINTER
		sbc_mapping_t* mappings;
#else
		sbc_mapping_t mappings[SBC_TASKS_NUM];
#endif

		// How many tasks are stored in the array.
		// In the pointer case the variable may represent the capacitor of the pointer.
		// In the array case, the variable stores the meaningful task(mapping) array length.
		uint16_t ntasks;

		// Which target is on the front.
		// When the SBC_TOKEN_BEGIN is coming, the SBC_STATE_GETHEAD
		// than the next char coming will trigger the SBC_STATE_ONLINE flag,
		// and the character will used to find the corresponding task.
		// And when the SBC_TOKEN_END is coming, the flag will clear.
		uint16_t target_num;

		// This variable record how many tasks has not been react.
		uint16_t command_counter;

	}sbc_t;



	//////////////////////////////////////////////////////////////////////////
	// Global variable


	//////////////////////////////////////////////////////////////////////////
	// Inline function definition
	
	// This function should be called in the receive interrupt function.
	// The goal of this function is to receive the character, and put them in
	// correct position.
	// 
	// This is a tiny state machine in the function, 3 stages are
	// Free-run: waiting for a start token. 
	//  when receive the start token, change to get-head state
	//  otherwise, call another_callback() to deal with the char
	// get-head: Check the head of the message, which will decide which task will react.
	//  this state will read only one character, that is command, and change to next state
	// listening(on-line): Receive content till the end token is coming.
	// 
	static inline void sbc_post_char(sbc_t* handle, uint16_t ch)
	{
		// this variable only for state machine
		uint16_t state = handle->state;

		if (state & SBC_STATE_ENABLE)
		{
			// An task has on the front, keep receive or stop the message.
			if (state & SBC_STATE_ONLINE)
			{
				sbc_mapping_t* target = &handle->mappings[handle->target_num];

				// if this message is trapped, change the target.
				if (state & SBC_STATE_TRAPING)
				{
					target = &handle->task_trap;
					// sign the unknown message
					target->state |= SBC_MAP_UNKNOWN;
				}

				// reach the end of the message
				if (ch == (uint16_t)SBC_TOKEN_END)
				{
					// the end token will be discarded

					// set message flag
					target->state |= SBC_MAP_TRIGGERED;

					// call the trap routine, causing of unknown message is coming.
					if ((state & SBC_STATE_TRAPING) &&
						(state & SBC_STATE_MSGTRAP) &&
						(state & SBC_STATE_UNMSGTRAP))
						handle->trap(handle);

					// clear SBC module flag
					handle->state &= ~(SBC_STATE_GETHEAD | SBC_STATE_ONLINE | SBC_STATE_TRAPING);

					// record how many commands still.
					handle->command_counter += 1;
				}
				// keep receiving
				else
				{
					// receive and record the message
					target->message_content[target->message_len] = ch;
					target->message_len += 1;

					// call the trap routine, causing of message buffer overflow
					if (target->message_len == MAX_MESSAGE_LENGTH)
					{
						handle->state |= SBC_STATE_PARAMBUFO;

						if (state & SBC_STATE_MSGTRAP)
							handle->trap(handle);
						// just ignore the buffer overflow
						target->message_len = 0;
					}
				}
			}
			// The first check char is coming, find and set the front task.
			else if (state & SBC_STATE_GETHEAD)
			{
				// considering no tasks match the command.
				sbc_mapping_t* target = &handle->task_trap;
				handle->state |= SBC_STATE_UNKNOWMSG | SBC_STATE_TRAPING;

				// Looking for which command is called
				for (int i = 0; i < handle->ntasks; ++i)
				{
					if (handle->mappings[i].command == ch)
					{
						// clear the unknown flag
						handle->state &= ~SBC_STATE_UNKNOWMSG;

						if (!(handle->mappings[i].state & SBC_MAP_TRIGGERED))
						{
							handle->target_num = i;
							target = &handle->mappings[i];
							handle->state &= ~SBC_STATE_TRAPING;
						}

						break;
					}
				}

				// config the target
				target->message_content[0] = ch;
				target->message_len = 1;

				// Config SBC module state_machine
				handle->state |= SBC_STATE_ONLINE;

			}
			// Check if the begin token is coming.
			else
			{
				if (ch == (uint16_t)SBC_TOKEN_BEGIN)
				{
					// Config SBC module state_machine
					handle->state |= SBC_STATE_GETHEAD;
				}
				// Not the first character or common message, call another
				// routine to process.
				else
				{
					if (state & SBC_STATE_NEXTLINK)
					{
						handle->another_callback(ch);
					}
				}
			}
		}
	}

	// enable the specified task
	static inline void enable_task(sbc_t* handle, uint16_t index)
	{
		handle->mappings[index].state |= SBC_MAP_ENABLE;
	}

	// disable the specified task
	static inline void disable_task(sbc_t* handle, uint16_t index)
	{
		handle->mappings[index].state &= ~SBC_MAP_ENABLE;
	}

	// enable the SBC module
	static inline void enable_sbc(sbc_t* handle)
	{
		handle->state |= SBC_STATE_ENABLE;
	}

	// disable the SBC module
	static inline void disable_sbc(sbc_t* handle)
	{
		handle->state &= ~SBC_MAP_ENABLE;
	}

	// config the task param properties
	static inline void config_task_param(sbc_t* handle, uint16_t index, uint8_t param_state)
	{
		handle->mappings[index].state |= param_state & (SBC_MAP_UINTPARAM | SBC_MAP_INTPARAM | SBC_MAP_FLOATPARAM);
	}

	// config the trap task
	static inline void config_task_trap(sbc_t* handle, sbc_task_fn unknown_command)
	{
		handle->unknown_command = unknown_command;
		handle->state |= SBC_STATE_UNKNOWMSG;
	}

	//////////////////////////////////////////////////////////////////////////
	// Function prop-type

	// These functions will translate string to figures
	int32_t sbc_atoi(const uint16_t* param);
	uint32_t sbc_atoui(const uint16_t* param);
	float sbc_atof(const uint16_t* param);

	// This function will react only one function
	void sbc_reack_task(sbc_t* handle, sbc_mapping_t* task);

	// This function should be called in the main loop
	void sbc_main_callback(sbc_t* handle);

	// This function will init an mapping handle
	void sbc_task_init(sbc_mapping_t* handle);

	// init function
	//The object to be initialized.
#ifdef SBC_TASKS_POINTER
	// You should allocate tasks memory, and invoke the function.
	// handle: the SBC object to be initialized
	// ntasks: how many tasks are allocated
	// mappings: pass into the memory you allocated.
	void sbc_init(sbc_t* handle, uint16_t ntasks, sbc_mapping_t* mappings);
#else
	// You should allocate tasks memory, and invoke the function.
	// handle: the SBC object to be initialized
	void sbc_init(sbc_t* handle);

	// You may call the function to register function.
	// This function will create a new command link command to callback
	// return value: return the index of the task
	// handle: the SBC object to be initialized
	// command: the single byte command
	// callback: specify the callback function to the command
	uint16_t sbc_reg_task(sbc_t* handle, uint16_t command, sbc_task_fn callback);
#endif



#ifdef __cplusplus
}
#endif

#endif // macro _HEADER_SBC_H_
