/*
* This is a program sheet copy from motor ware from TI, 
* This is a pack of PID submodule, this ctrl module 
* let user use easily.
* Param set Set Kp, set min max
* ctrl param, increment counter, reset counter, do ctrl
* 
* 
					if (CTRL_doPositionCtrl(handle))
					{
						_iq refValue = gMotorVars.postion_target;
						_iq fbackValue = getposition();
						_iq outMax = -0.3; // Speed limit
						_iq outMin = 0.3;

						//      PID handle         reference, feedback,   return_value
						PID_run(obj->pidHandle_pos, refValue, fbackValue, &speed);
					}
* NONONO! I think the module should be implement by a more general ctrl module.
*/



// System headers


// Module headers
#include "pid.h"


#ifndef _HEADER_PID_CTRL_H_
#define _HEADER_PID_CTRL_H_

#ifdef __cplusplus
extern "C"
{
#endif


	//////////////////////////////////////////////////////////////////////////
	// Definition


	//////////////////////////////////////////////////////////////////////////
	// Type



	//////////////////////////////////////////////////////////////////////////
	// Global variable


	//////////////////////////////////////////////////////////////////////////
	// Function prop-type


	//////////////////////////////////////////////////////////////////////////
	// Inline function definition


#ifdef __cplusplus
}
#endif

#endif // macro _HEADER_PID_CTRL_H_
