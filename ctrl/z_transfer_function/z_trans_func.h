
#include "z_trnas_func_config.h"
// System headers


// Module headers

/* Application Notes
* Application Note: 3/27/2022
* when you use BUFFER_POINTER_ENDLESS mode to ask the `fn_clac` routine to move pointer. you must pay
* attention to the origin for the array. The first `cm_num_order` items of `p_input_buffer` are occupied
* due to calculation needs.so as `cm_den_order` items of `p_output_buffer`.
* You can also give the Z transfer function the initial condition after init routine, by set the
* `z_function::p_input_buffer` and `z_function::p_output_buffer`.
*
* Application Note: 3/28/2022
* Please notice that the order of the denominator and numerator must be carefully confirm!
* If you don't set the correct coefficient or order, the result may be divergent or shaking.
*/

/* Demo routine
* Demo 1 Trinomial mean filter
* transfer function: $T(z)=\frac{1+z^{-1}+z^{-2}}{3}$
	discrete_control_system dcs;
	z_function z1;

	dcs.m_discrete_time = 0.001; // 10 kHz
	dcs.m_zero = 0.0f;

	z1.cm_num_order = 2;
	z1.cm_den_order = 0;

	float num[3] = { 1.0f, 1.0f, 1.0f };
	float den[1] = { 3.0f };

	z1.cm_num_param = num;
	z1.cm_den_param = den;

	float* input_array = new float[2 << 13];
	float* output_array = new float[2 << 13];

	z1.p_input_buffer = input_array;
	z1.p_output_buffer = output_array;

	z1.m_buffer_state = z1.BUFFER_POINTER_ENDLESS;

	init_z_function_struct(&z1, &dcs);

	for (size_t i = 0; i < 10000; i++)
	{
		z1.m_input = i;
		z1.fn_calc(&z1);
	} // set break point here.
* You may notice the mean filter's result at the break point.
*/



#ifndef _HEADER_NAME_H_
#define _HEADER_NAME_H_

#ifdef __cplusplus
extern "C"
{
#endif

	//////////////////////////////////////////////////////////////////////////
	// Type
	/**
	 * @brief This object implements a physically realizable z-domain function.
	 *  You may call the fn_calc to calculate the result for the Z domain.
	 *  In general you have to design the Z function firstly, and simplify the equation to the following basic form.
	 $$
	  \begin{aligned}
		H(z) &= \frac{R(z)}{X(z)}=\frac{a_0+\Sigma_{p=1}^{m}{a_pz^{-p}}}{1+\Sigma_{q=1}^n{b_qz^{-q}}} \\
		r_n &= a_0x_n+\Sigma_{p=1}^{m}{a_px_{n-p}}-\Sigma_{q=1}^n{b_qr_{n-q}}
	  \end{aligned}
	 $$
	 * You may read it by LaTex compiler, if necessary.
	 * Than, based on the equation, the user must pass two vectors as the numerator
	 *  and the denominator.
	 * the entity provide a calculate function, named @fn_calc user may call the function, at the right time.
	 *
	 */
	typedef struct _entity_z_transfer_function
	{
		/**
		* @brief This function specify the calculate function.
		*        You may provide the input param and call the function to get the result.
		*
		* @param obj: input the Z-domain function object.
		*
		* @retval None
		*
		*/
		void(*fn_calc)(struct _entity_z_transfer_function* obj);//Ðéº¯Êý

		dcs_param_t m_input;
		dcs_param_t m_output;

		dcs_difference_t cm_num_order; // const member numerator order, refer to p, this value may be set to 0, if none history information are needed.
		dcs_difference_t cm_den_order; // const member denominator order, refer to q, this value may be set to 0, if none history information are needed.

		// these params are stored in decreasing order
		dcs_param_t* cm_num_param; // const member numerator
								   // The pointer point to an array that contain more than `cm_num_order + 1` items, as the numerator param.
								   // In general, the first param should be 1, in order to match the equation.
		dcs_param_t* cm_den_param; // const member denominator
								   // The pointer point to an array that contain more than `cm_den_order + 1` items.

		dcs_param_t* p_input_buffer;  // The buffer must point to an array that contain more than `cm_num_order` items, 
									  // and only cm_num_order element will be used.
		dcs_param_t* p_output_buffer; // The buffer must point to an array that contain more than `cm_den_order` items,
									  // and only cm_den_order element will be used.
									  // 
		// An example for 3-order system fixed system mode or endless system mode.
		// index : [-1]      [0]       [1]       [2]
		//         x_(-4)    x_(-3)    x_(-2)    x_(-1)  
		//         r_(-4)    r_(-3)    r_(-2)    r_(-1)  
		// warning: the run function won't check the boundary conditions. User must ensure the boundary condition is reasonable.
		// An example for 3-order system circle mode. Every oldest data will be replaced by the newest data.
		// index : [0]       [1]       [2]       [3]
		//   1st   x_(-4)    x_(-3)    x_(-2)    x_(-1)  
		//         r_(-4)    r_(-3)    r_(-2)    r_(-1)  
		// index : [0]       [1]       [2]       [3]
		//   2nd   x_(0)     x_(-3)    x_(-2)    x_(-1)  
		//         r_(0)     r_(-3)    r_(-2)    r_(-1)  
		// index : [0]       [1]       [2]       [3]
		//   3rd   x_(0)     x_(1)     x_(-2)    x_(-1)  
		//         r_(0)     r_(1)     r_(-2)    r_(-1)  
		enum {
			BUFFER_POINTER_FIXED = 1,  // The buffer label is fixed, buffer[0] is the last item(previous item for output), 
									   //  buffer[1] is the previous item for buffer[0].
									   // That is, a circular copy is executed every time calculation (@fn_calc) is completed.
									   BUFFER_POINTER_CIRCLE,     // The calculation results will be stored in the buffer in a circular manner.
																 //  The last input param will replace the earliest stored data.
																 //  And the function will automatically match the label and index.
																 BUFFER_POINTER_ENDLESS     // The calculation result will stored in an endless array.
																							//  The pointer will move to next item every time calculation is completed, 
																							//  and user must ensure the buffer has enough length, or move the pointer address manually.
		} m_buffer_state;

		dcs_difference_t p_cir_pos; // This variable record the position of the oldest item.
		struct _entity_discrete_control_system* m_dcs;

	}z_function, * pz_function;

	//////////////////////////////////////////////////////////////////////////
	// Definition


	//////////////////////////////////////////////////////////////////////////
	// Global variable


	//////////////////////////////////////////////////////////////////////////
	// Function prop-type
	/**
	 * @brief init the z transfer function entity struct.
	 *
	 * @param obj: the struct to be init.
	 *		 dcs: the discrete control system the z_function module based on.
	 *
	 * @retval None
	 * @note The function mast be call after all pointer was set.
	 *
	 */
	void init_z_function_struct(struct _entity_z_transfer_function* obj, struct _entity_discrete_control_system* dcs);

	/**
	 * @brief init z transfer function entity struct and alloc memory automatically.
	 *
	 * @param obj: the struct to be init.
	 *		 dcs: the discrete control system the z_function module based on.
	 *
	 * @retval None
	 * @note	This function will call @malloc. you must ensure the function is enable in your production environment.
	 *  Otherwise, you have no choice to use @init_z_function_struct and alloc memory manually.
	 *  This function will only allocate memory for p_input_buffer and p_output_buffer in minimum size.
	 * @warning The time you use this function to construct a z_function entity. You need to call
	 */
	void init_z_function_struct_mm(struct _entity_z_transfer_function* obj, struct _entity_discrete_control_system* dcs);

	/**
	 * @brief init z transfer function entity struct and alloc memory automatically.
	 *
	 * @param obj: the struct to be init.
	 *		 dcs: the discrete control system the z_function module based on.
	 *
	 * @retval None
	 * @note	This function will call @malloc. you must ensure the function is enable in your production environment.
	 *  Otherwise, you have no choice to use @init_z_function_struct and alloc memory manually.
	 *  This function will only allocate memory for p_input_buffer and p_output_buffer in minimum size.
	 * @warning The time you use this function to construct a z_function entity. You need to call
	 */
	void deinit_z_function_struct_mm(struct _entity_z_transfer_function* obj);

	/**
		* @brief This function is default function for the z transfer.
		*
		* @param obj: the z_transfer_function object.
		*
		* @retval None
		*
		*/
	void _z_func_calc_default(struct _entity_z_transfer_function* obj);

	//////////////////////////////////////////////////////////////////////////
	// Inline function definition


#ifdef __cplusplus
}
#endif

#endif // macro _HEADER_NAME_H_
