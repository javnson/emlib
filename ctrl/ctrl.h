

// System headers
#include <bsp_interface.h>

// Module headers



#ifndef _HEADER_CTRL_H_
#define _HEADER_CTRL_H_

#ifdef __cplusplus
extern "C"
{
#endif

	//////////////////////////////////////////////////////////////////////////
	// Type
	// specific parameter type for the whole discrete control system.
#if defined DCS_PARAM_USE_FLOAT
	typedef float dcs_param_t;
#elif defined DCS_PARAM_USE_UINT8
	typedef uint8_t dcs_param_t;
#elif defined DCS_PARAM_USE_UINT16
	typedef uint16_t dcs_param_t;
#elif defined DCS_PARAM_USE_UINT32
	typedef uint32_t dcs_param_t;
#elif defined DCS_PARAM_USE_INT8
	typedef int8_t dcs_param_t;
#elif defined DCS_PARAM_USE_INT16
	typedef int16_t dcs_param_t;
#elif defined DCS_PARAM_USE_INT32
	typedef int32_t dcs_param_t;
#elif defined DCS_PARAM_USE_DOUBLE
	typedef double dcs_param_t;
#elif defined DCS_PARAM_USE_MANUAL
	typedef PID_PARAM_USE_MANUAL dcs_param_t;
#else
//#pragma message ("Now the dcs_param_t type is default which is float type, please use macro \"DCS_PARAM_USE_MANUAL\" to define a manual type for yourself.")
	typedef float dcs_param_t;
#endif

	// specify parameter type for the unit
#if defined DCS_UNIT_USE_FLOAT
	typedef float dcs_unit_t;
#elif defined DCS_PARAM_USE_UINT8
	typedef uint8_t dcs_unit_t;
#elif defined DCS_UNIT_USE_UIINT16
	typedef uint16_t dcs_uint_t;
#elif defined DCS_UNIT_USE_UIINT32
	typedef uint32_t dcs_uint_t;
#elif defined DCS_UINT_USE_INT8
	typedef int8_t dcs_uint_t;
#elif defined DCS_UINT_USE_INT16
	typedef int16_t dcs_uint_t;
#elif defined DCS_UINT_USE_INT32
	typedef int32_t dcs_param_t;
#elif defined DCS_UNIT_USE_DOUBLE
	typedef double dcs_param_t;
#elif defined DCS_UNIT_USE_MANUAL
	typedef DCS_UNIT_USE_MANUAL dcs_uint_t;
#else
//#pragma message ("Now the dcs_unit_t type is default type, which is float type. You may use macro \"DCS_UNIT_USE_MANUAL\" to specify the unit type clearly.\n")
	typedef float dcs_uint_t;
#endif

	// specify Measurement type of memory length
#if defined DCS_DIFFERENCE_USE_UINT16
	typedef uint16_t dcs_difference_t;
#elif defined DCS_DIFFERENCE_USE_UINT32
	typedef uint32_t dcs_difference_t;
#elif defined DCS_DIFFERENCE_USE_UINT64
	typedef uint64_t dcs_difference_t;
#elif defined DCS_DIFFERENCE_USE_MANUAL
	typedef DCS_DIFFERENCE_USE_MANUAL dcs_difference_t;
#else
//#pragma message ("Now the dcs_difference type is default type, which is uint32_t. You may use maccro\"DCS_DIFFERENCE_USE_MANUAL\" to specify the difference type.\n")
	typedef uint32_t dcs_difference_t;
#endif

	/**
	 * @brief Describe a discrete control system.
	 */
	typedef struct _entity_discrete_control_system
	{
		/**
			* @brief This function will prepare whole discrete control system. You may cover the function if necessary. Or you may just cover only transactional function.
			*
			* @param obj: the handle of the discrete control system
			*
			* @retval None
			*
			*/
		void (*fn_calc)(struct _entity_discrete_control_system* obj);

		dcs_param_t m_discrete_time;  ///< The discrete time for the system.
									  /// @note you may set the param to 1, if you need a pure discrete system.

		dcs_param_t m_zero; ///< The zero point for the discrete system.

		uint8_t enable;
		uint32_t counter;

		dcs_param_t *input;		// pointer to the target
		dcs_param_t *output;    // pointer to the target



	}discrete_control_system, * pdiscrete_control_system;


	//////////////////////////////////////////////////////////////////////////
	// Definition


	//////////////////////////////////////////////////////////////////////////
	// Global variable


	//////////////////////////////////////////////////////////////////////////
	// Function prop-type


	//////////////////////////////////////////////////////////////////////////
	// Inline function definition


#ifdef __cplusplus
}
#endif

#endif // macro _HEADER_CTRL_H_

// invoke all the sub modules

