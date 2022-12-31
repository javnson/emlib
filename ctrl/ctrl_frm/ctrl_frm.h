

// System headers


// Module headers
#include <ctrl_frm_config.h>


#ifndef _HEADER_CTRL_FRM_H_
#define _HEADER_CTRL_FRM_H_

#ifdef __cplusplus
extern "C"
{
#endif


	//////////////////////////////////////////////////////////////////////////
	// Definition


	//////////////////////////////////////////////////////////////////////////
	// Type
	typedef void (*ctrl_frm_calc_fn)(ctrl_frm_t* ctrl_handle);
	typedef void* ctrl_frm_pointer_t;

	typedef struct __tag_ctrl_frm
	{
		ctrl_frm_calc_fn do_ctrl;
		ctrl_frm_pointer_t input_ptr;
		ctrl_frm_pointer_t outpu_ptr;

		bool enable;
		uint16_t counter;
		uint16_t ctrl_cycle_per_isr;

	}ctrl_frm_t;


	//////////////////////////////////////////////////////////////////////////
	// Global variable


	//////////////////////////////////////////////////////////////////////////
	// Function prop-type


	//////////////////////////////////////////////////////////////////////////
	// Inline function definition
	inline static void do_ctrl_frm(ctrl_frm_t* handle)
	{
		// Check Memory 

		if (handle->enable)
		{
			if (++handle->counter >= handle->ctrl_cycle_per_isr)
			{
				handle->counter = 0;
				handle->do_ctrl(handle);
			}
		}
	}

	inline static void init_ctrl_frm(ctrl_frm_t* handle)
	{
		// Check Memory

		handle->enable = false;
		handle->counter = 0;
		handle->ctrl_cycle_per_isr = 0;
	}

	inline static void regist_ctrl_frm(ctrl_frm_t* handle,
		ctrl_frm_calc_fn ctrl_fn,
		ctrl_frm_pointer_t input_ptr,
		ctrl_frm_pointer_t outpu_ptr
	)
	{
		// Check Memory

		handle->do_ctrl = ctrl_fn;
		handle->input_ptr = input_ptr;
		handle->output_ptr = outpu_ptr;
	}


#ifdef __cplusplus
}
#endif

#endif // macro _HEADER_CTRL_FRM_H_












