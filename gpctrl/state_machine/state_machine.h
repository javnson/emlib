

// System headers


// Module headers



#ifndef _HEADER_STATE_MACHINE_H_
#define _HEADER_STATE_MACHINE_H_

#ifdef __cplusplus
extern "C"
{
#endif


	//////////////////////////////////////////////////////////////////////////
	// Definition


	//////////////////////////////////////////////////////////////////////////
	// Type
	typedef void (*state_callback_t)(struct _tag_state*);

	typedef struct _tag_state
	{
		// 0x01 Enable the state
		// 0x02 Enable the entry callback: the other state turn to the state
		// 0x03 Enable the state callback: the state keep running callback
		// 0x04 Enable the leave callback: the state need to change to another
		uint16_t state;

		state_callback_t entry_fn;
		state_callback_t keep_fn;
		state_callback_t leave_fn;
	};

	typedef struct _tag_state_machine
	{
		uint16_t state;

		uint16_t current_state;

	}state_machine_t;


	//////////////////////////////////////////////////////////////////////////
	// Global variable


	//////////////////////////////////////////////////////////////////////////
	// Function prop-type


	//////////////////////////////////////////////////////////////////////////
	// Inline function definition


#ifdef __cplusplus
}
#endif

#endif // macro _HEADER_STATE_MACHINE_H_

