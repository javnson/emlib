
#include "pid_config.h"

// System headers


// Module headers




#ifndef _HEADER_NAME_H_
#define _HEADER_NAME_H_

#ifdef __cplusplus
extern "C"
{
#endif

	// Set up PID with discrete control system.
	// Maybe you need to set the discrete time.
	//#define DISABLE_PID_REGULAR_BASED_ON_DCS
#if !defined DISABLE_PID_REGULAR_BASED_ON_DCS && !defined _FILE_DISCRETE_CONTROL_SYSTEM_H_
#error "You should include discrete_control_system.h first."
#error "Or, you may use macro \"DISABLE_PID_REGULAR_BASED_ON_DCS\" to disable the connection with control system."
#endif

	//////////////////////////////////////////////////////////////////////////
	// Type
	/**
	 * @brief Describe an entity of PID regular.
	 */
	typedef struct _entity_pid_regular
	{
		/**
			* @brief This function specify the calculate function.
			*
			* @param reg: input the PID regular object. You must change the input param firstly.
			*
			* @retval None
			*
			* @note: this function variable will be called automatically.
			*/
		void(*fn_calc)(struct _entity_pid_regular* reg);

		/// <summary>
		/// PID input and output port
		/// </summary>
		dcs_param_t m_input;
		dcs_param_t m_output;

		/// <summary>
		/// PID regular basic param
		/// </summary>
		dcs_param_t m_proportional;
		dcs_param_t m_integral;
		dcs_param_t m_differential;

		/// <summary>
		/// calculate intermediate PID variables
		/// </summary>
		dcs_param_t p_integral_quantity;     ///< temp integral quantity
		dcs_param_t p_differential_quantity; ///< temp differential quantity

		/// <summary>
		/// integral param will not join in PID regular, unless input param within the limit.
		/// @warning PID regular is bipolar regular, so lower limit usually is negative
		/// @warning when limit is equals to zero, the input limit will be disable.
		/// </summary>
		dcs_param_t p_integral_input_upper_limit;
		dcs_param_t p_integral_input_lower_limit;

		/// <summary>
		/// integral output would be clamped, if output went beyond boundary.
		/// @warning you may disable this feature the time you set the limit to zero.
		/// </summary>
		dcs_param_t p_integral_output_upper_limit;
		dcs_param_t p_integral_output_lower_limit;

		/// <summary>
		/// differential output would be clamped, if output went beyond boundary.
		/// @warning you may disable this feature the time you set the limit to zero.
		/// </summary>
		dcs_param_t p_differential_output_upper_limit;
		dcs_param_t p_differential_output_lower_limit;

		dcs_param_t p_last_item;

#ifndef DISABLE_PID_REGULAR_BASED_ON_DCS
		struct _entity_discrete_control_system* m_dcs; ///< discrete control system object
#endif

		/**
			* @brief run the regular and get the next step.
			*
			* @param reg: input the PID regular object.
			*		 input_param: input the param, and get the result.
			*
			* @retval the result of the step
			*
			* @warning the function has been linked to function @see ::_pid_run_default.
			*          If necessary, user may cover the function if you need.
			*
			* @note   If you need to cover the function manually,
			* please follow the step(Make necessary optimization):
			*  + assign reg->m_input = input_param;
			*  + calculate the output param, and assign to reg->m_output
			*    this assembly will support you a set of algorithm.
			*  + return the reg->m_output.
			*/
		dcs_param_t(*fn_run)(struct _entity_pid_regular* reg, dcs_param_t input_param);

	}pid_regular, * ppid_regular;

	//////////////////////////////////////////////////////////////////////////
	// Definition


	//////////////////////////////////////////////////////////////////////////
	// Global variable


	//////////////////////////////////////////////////////////////////////////
	// Function prop-type
		/**
		* @brief set input param for the specified regular.
		*
		* @param reg: input the PID regular object.
		*        input_param: input the param, without calculate the result.s
		*
		* @retval None
		*
		* @warning You do not get the result after calling the function,
		*          unless you call the calc function. @see _pid_calc_default
		*/
	void _pid_input_default(struct _entity_pid_regular* reg, dcs_param_t input_param);

	/**
		* @brief get output result from the regular.
		*
		* @param reg: input the PID regular object.
		*
		* @retval the result of the step.
		*
		* @warning This function will do not calculate the result automatically,
		*	so you need to call calc function manually, @see _pid_calc_default.
		*/
	dcs_param_t _pid_output_defualt(struct _entity_pid_regular* reg);

	/**
		* @brief run the PID process, meanwhile update the input param.
		* The function will update the input param and then call calc function @see _pid_calc_default.
		*
		* @param reg: input the PID regular object.
		*		 input_param: input the param, and get the result.
		*
		* @retval the result of the step
		*
		*/
	dcs_param_t _pid_run_default(struct _entity_pid_regular* reg, dcs_param_t input_param);

	/**
		* @brief calculate PID param, this function is the default calculate function.
		*        You may call the function to run the process. And then you may get the result.
		*
		* @param reg: input the PID regular object. You must change the input param firstly.
		*
		* @retval None
		*
		*/
	void _pid_calc_default(struct _entity_pid_regular* reg);

	/**
		* @brief set PID regular param.
		*
		* @param reg: input the PID regular object.
		*        p  : input the proportional param
		*		 i  : input the integral param
		*        d  : input the differential param
		*
		* @retval None
		*
		*/
	void _pid_set_param(struct _entity_pid_regular* reg,
		dcs_param_t p, dcs_param_t i = (dcs_param_t)0, dcs_param_t d = (dcs_param_t)0);

	/**
		* @brief init the PID regular struct, this function will init the key variable, and the virtual function will be set to default function.
		*
		* @param reg: input the PID regular object to be init.
		*
		* @retval None
		*
		*/
	void init_pid_struct(struct _entity_pid_regular* reg);

	//////////////////////////////////////////////////////////////////////////
	// Inline function definition


#ifdef __cplusplus
}
#endif

#endif // macro _HEADER_NAME_H_
