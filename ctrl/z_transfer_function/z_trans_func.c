

#include <memory.h>

#include <ctrl.h>

void _z_func_calc_default(pz_function obj)
{
	cs_assert_error(obj->cm_num_param, "num_param must be a array and not point to nullptr");
	cs_assert_error(obj->cm_den_param, "den_param must be a array and not point to nullptr");
	cs_assert_error(obj->cm_den_param[0] != (dcs_param_t)0, "den_param[0] must be an nonzero value.");

	dcs_param_t r_n = obj->cm_num_param[0] * obj->m_input;

	// this switch ensure the judgment will not happen usually.
	switch (obj->m_buffer_state)
	{
	case BUFFER_POINTER_FIXED:
		for (dcs_difference_t i = 1; i <= obj->cm_num_order; ++i)
			//r_n += obj->cm_num_param[i] * obj->p_input_buffer[obj->cm_num_order - i];
			r_n += *(obj->cm_num_param + i) * (*(obj->p_input_buffer + obj->cm_num_order - i));
		for (dcs_difference_t i = 1; i <= obj->cm_den_order; ++i)
			//r_n -= obj->cm_den_param[i] * obj->p_output_buffer[obj->cm_den_order - i];
			r_n -= *(obj->cm_den_param + i) * (*(obj->p_output_buffer + obj->cm_den_order - i));

		// get the result.
		obj->m_output = r_n / obj->cm_den_param[0];

		// memory move.
		for (dcs_difference_t i = 1; i < obj->cm_num_order; ++i)
			obj->p_input_buffer[i - 1] = obj->p_input_buffer[i];
		if (obj->cm_num_order) obj->p_input_buffer[obj->cm_num_order - 1] = obj->m_input;

		for (dcs_difference_t i = 1; i < obj->cm_den_order; ++i)
			obj->p_output_buffer[i - 1] = obj->p_output_buffer[i];
		if (obj->cm_den_order) obj->p_output_buffer[obj->cm_den_order - 1] = obj->m_output;

		return;
	case BUFFER_POINTER_CIRCLE:
		for (dcs_difference_t i = 1; i <= obj->cm_num_order; ++i)
			//r_n += obj->cm_num_param[i] * obj->p_input_buffer[(obj->cm_num_order - i + obj->p_cir_pos) % obj->cm_num_order];
			r_n += *(obj->cm_num_param + i) * (*(obj->p_input_buffer + (obj->cm_num_order - i + obj->p_cir_pos) % obj->cm_num_order));

		for (dcs_difference_t i = 1; i <= obj->cm_den_order; ++i)
			//r_n -= obj->cm_den_param[i] * obj->p_output_buffer[(obj->cm_den_order - i + obj->p_cir_pos) % obj->cm_den_order];
			r_n -= *(obj->cm_den_param + i) * (*(obj->p_output_buffer + (obj->cm_den_order - i + obj->p_cir_pos) % obj->cm_den_order));

		// get the result.
		obj->m_output = r_n / obj->cm_den_param[0];

		// replace the oldest data
		if (obj->cm_num_order) obj->p_input_buffer[obj->p_cir_pos % obj->cm_num_order] = obj->m_input;
		if (obj->cm_den_order) obj->p_output_buffer[obj->p_cir_pos % obj->cm_den_order] = obj->m_output;

		// Keep good circulation
		if (++obj->p_cir_pos == obj->cm_den_order * obj->cm_num_order)
			obj->p_cir_pos = 0;

		return;
	case BUFFER_POINTER_ENDLESS:
		for (dcs_difference_t i = 1; i <= obj->cm_num_order; ++i)
			//r_n += obj->cm_num_param[i] * obj->p_input_buffer[obj->cm_num_order - i];
			r_n += *(obj->cm_num_param + i) * (*(obj->p_input_buffer + obj->cm_num_order - i));
		for (dcs_difference_t i = 1; i <= obj->cm_den_order; ++i)
			//r_n -= obj->cm_den_param[i] * obj->p_output_buffer[obj->cm_den_order - i];
			r_n -= *(obj->cm_den_param + i) * (*(obj->p_output_buffer + obj->cm_den_order - i));

		// get the result.
		obj->m_output = r_n / obj->cm_den_param[0];

		// Move to net position.
		*(++obj->p_input_buffer + obj->cm_num_order - 1) = obj->m_input;
		*(++obj->p_output_buffer + obj->cm_den_order - 1) = obj->m_output;

		return;
	default:
		cs_assert_error(0, "Unknown buffer style.");

	}
	return;
}

void init_z_function_struct(struct _entity_z_transfer_function* obj, struct _entity_discrete_control_system* dcs)
{
	cs_assert_error(obj, "You must pass an obj pointer to the z_function struct.\n");

	cs_assert_error(obj->cm_den_param, "You must specify the denominator param firstly.\n");
	cs_assert_error(obj->cm_num_param, "You must specify the numerator param firstly.\n");

	cs_assert_error(obj->cm_num_order == 0 || obj->p_input_buffer, "You must specify the input buffer.\n");
	cs_assert_error(obj->cm_den_order == 0 || obj->p_output_buffer, "You must specifu the output buffer.\n");

	cs_assert_error(dcs, "The z_function module is based on discrete control system, you must define and pass a dcs object,\n");
	obj->m_dcs = dcs;

	for (dcs_difference_t i = 0; i < obj->cm_num_order; ++i)
		obj->p_input_buffer[i] = obj->m_dcs->m_zero;

	for (dcs_difference_t i = 0; i < obj->cm_den_order; ++i)
		obj->p_output_buffer[i] = obj->m_dcs->m_zero;

	obj->fn_calc = _z_func_calc_default;
	obj->p_cir_pos = 0;

}

void init_z_function_struct_mm(struct _entity_z_transfer_function* obj, struct _entity_discrete_control_system* dcs)
{
	obj->p_input_buffer = obj->cm_num_order == 0 ? 0 : (dcs_param_t*)malloc(sizeof(dcs_param_t) * obj->cm_num_order);
	obj->p_output_buffer = obj->cm_den_order == 0 ? 0 : (dcs_param_t*)malloc(sizeof(dcs_param_t) * obj->cm_den_order);
	init_z_function_struct(obj, dcs);
}

void deinit_z_function_struct_mm(struct _entity_z_transfer_function* obj)
{
	if (obj->cm_num_order != 0) free(obj->p_input_buffer);
	if (obj->cm_den_order != 0) free(obj->p_output_buffer);
}
