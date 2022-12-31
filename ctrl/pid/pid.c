

#include <ctrl.h>

void _pid_input_default(struct _entity_pid_regular* reg, dcs_param_t input_param)
{
	cs_assert_error(!reg, "Input param reg must be the pointer to the pid_regular struct.\n");
	reg->m_input = input_param;

	return;
}

dcs_param_t _pid_output_defualt(struct _entity_pid_regular* reg)
{
	cs_assert_error(!reg, "Input param reg must be the pointer to the pid_regular struct.\n");

	return reg->m_output;
}

dcs_param_t _pid_run_default(struct _entity_pid_regular* reg, dcs_param_t input_param)
{
	cs_assert_error(!reg, "Input param reg must be the pointer to the pid_regular struct.\n");

	reg->m_input = input_param;
	reg->fn_calc();

	return reg->m_output;
}

void _pid_calc_default(struct _entity_pid_regular* reg)
{
	cs_assert_error(!reg, "Input param reg must be the pointer to the pid_regular struct.\n");

	// Differential param calc.
	reg->p_differential_quantity = reg->m_differential == (dcs_param_t)0
		? (dcs_param_t)0
		: (reg->m_input - reg->p_last_item) /
#ifndef DISABLE_PID_REGULAR_BASED_ON_DCS
		(reg->dcs == NULL) ?
		(dcs_param_t)1 : reg->dcs->m_discrete_time
#else //DISABLE_PID_REGULAR_BASED_ON_DCS
		(pid_param)1
#endif //DISABLE_PID_REGULAR_BASED_ON_DCS	
		;

	// Differential param range limit.
	reg->p_differential_quantity = (
		(reg->p_differential_output_upper_limit != (dcs_param_t)0) ? reg->p_differential_quantity > reg->p_differential_output_upper_limit : (dcs_param_t)0 ||
		(reg->p_differential_output_lower_limit != (dcs_param_t)0) ? reg->p_differential_quantity < reg->p_differential_output_lower_limit : (dcs_param_t)0) ?
		0 : reg->p_differential_quantity;

	// Integral param calc
	reg->p_integral_quantity += (
		(reg->p_integral_input_lower_limit != (dcs_param_t)0) ? reg->m_input < reg->p_integral_input_lower_limit : (dcs_param_t)0 ||
		(reg->p_integral_input_upper_limit != (dcs_param_t)0) ? reg->m_input > reg->p_integral_input_upper_limit : (dcs_param_t)0) ?
		0 : reg->m_input
		*
#ifndef DISABLE_PID_REGULAR_BASED_ON_DCS
		(reg->m_dcs == NULL) ?
		(dcs_param_t)1 : reg->m_dcs->m_discrete_time
#else //DISABLE_PID_REGULAR_BASED_ON_DCS
		(pid_param)1
#endif //DISABLE_PID_REGULAR_BASED_ON_DCS
		;

	// Integral param range limit
	// 	@NOTE: You may choose from these cases, by removing/adding the comment. 
	// case I: Cut out if out of range
	//reg->p_integral_quantity = (
	//	reg->p_integral_output_upper_limit != 0 ? reg->p_integral_quantity > reg->p_integral_output_upper_limit : 0 || 
	//	reg->p_integral_output_lower_limit != 0 ? reg->p_integral_quantity < reg->p_integral_output_lower_limit : 0 ) ?
	//	0 : reg->p_integral_quantity;
	// case II: limit if out of range
	reg->p_integral_quantity = (
		reg->p_integral_output_upper_limit != 0 ? reg->p_integral_quantity > reg->p_integral_output_upper_limit : 0)
		? reg->p_integral_output_upper_limit : reg->p_integral_quantity;
	reg->p_integral_quantity = (
		reg->p_integral_output_lower_limit != 0 ? reg->p_integral_quantity < reg->p_integral_output_lower_limit : 0)
		? reg->p_integral_output_lower_limit : reg->p_integral_quantity;


	// update output item
	reg->m_output = reg->m_proportional * reg->m_input +
		reg->m_integral * reg->p_integral_quantity +
		reg->m_differential * reg->p_differential_quantity;

	// update last item
	reg->p_last_item = reg->m_input;

	return;
}

void _pid_set_param(struct _entity_pid_regular* reg, dcs_param_t p, dcs_param_t i, dcs_param_t d)
{
	cs_assert_error(!reg, "Input param reg must be the pointer to the pid_regular struct.\n");

	reg->m_proportional = p;
	reg->m_integral = i;
	reg->m_differential = d;

	return;
}


void init_pid_struct(struct _entity_pid_regular* reg)
{
	cs_assert_error(!reg, "Input param reg must be the pointer to the pid_regular struct.\n");

	reg->fn_calc = _pid_calc_default;
	reg->fn_run = _pid_run_default;

	reg->m_proportional = (dcs_param_t)1;
	reg->m_integral = (dcs_param_t)0;
	reg->m_differential = (dcs_param_t)0;

	if (reg->m_dcs)
	{
		reg->m_input = (dcs_param_t)reg->m_dcs->m_zero;
		reg->m_output = (dcs_param_t)reg->m_dcs->m_zero;

		reg->p_integral_input_lower_limit = (dcs_param_t)reg->m_dcs->m_zero;
		reg->p_integral_input_upper_limit = (dcs_param_t)reg->m_dcs->m_zero;
		reg->p_integral_output_upper_limit = (dcs_param_t)reg->m_dcs->m_zero;
		reg->p_integral_output_lower_limit = (dcs_param_t)reg->m_dcs->m_zero;

		reg->p_differential_output_lower_limit = (dcs_param_t)reg->m_dcs->m_zero;
		reg->p_differential_output_upper_limit = (dcs_param_t)reg->m_dcs->m_zero;

		reg->p_integral_quantity = (dcs_param_t)reg->m_dcs->m_zero;
		reg->p_differential_quantity = (dcs_param_t)reg->m_dcs->m_zero;
	}
	else
	{
		reg->m_input = (dcs_param_t)0;
		reg->m_output = (dcs_param_t)0;

		reg->p_integral_input_lower_limit = (dcs_param_t)0;
		reg->p_integral_input_upper_limit = (dcs_param_t)0;
		reg->p_integral_output_upper_limit = (dcs_param_t)0;
		reg->p_integral_output_lower_limit = (dcs_param_t)0;

		reg->p_differential_output_lower_limit = (dcs_param_t)0;
		reg->p_differential_output_upper_limit = (dcs_param_t)0;

		reg->p_integral_quantity = (dcs_param_t)0;
		reg->p_differential_quantity = (dcs_param_t)0;
	}

	return;
}

