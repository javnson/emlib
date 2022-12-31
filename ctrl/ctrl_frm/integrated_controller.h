

#include "ctrl_frm.h"

typedef struct _tag_integrated_controller
{
	uint16_t num_ctrls;

	ctrl_frm_t** ctrls;


}integrated_controller;


static inline do_integrated_controller(integrated_controller* handle)
{
	int i = 0;

	// Check memory

	for (i = 0; i < handle->num_ctrls; ++i)
		do_ctrl_frm(ctrls[i]);


}

static inline ctrl_frm_t * get_controller_by_id(integrated_controller* handle, uint16_t index)
{
	// Check memory

	// Check index

	return handle->ctrls[index];
}
