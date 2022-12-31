
// System include files
#include <main.h>


#ifndef _HEADER_NAME_H_
#define _HEADER_NAME_H_

#ifdef __cplusplus
extern "C"
{
#endif

	
	//////////////////////////////////////////////////////////////////////////
	// Definition
	
// peripheral variable extern
extern I2C_HandleTypeDef hi2c2;
extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

// print module define
#define SHOW_BUFFER_LEN (512)
// Print function proptype
void dbg_print(const char* p_fmt, ...);
void comm_print(const char* p_fmt, ...);
// specify print output
#define DBG_FRM_PRINT dbg_print


	//////////////////////////////////////////////////////////////////////////
	// Select & Disable module

// debug framework, reference <debug_framwork/debug_framework_config.h>
// global emlib debug option
#define _EMLIB_DEBUG
#define DISABLE_DBG_FRM
//#define DISABLE_CMSIS_EXT
//#define DISABLE_GPCTRL
//#define DISABLE_COMM
//#define DISABLE_CTRL


	// For BLINK LED module, reference <blink_led/blink_led_config.h>
#define BLINK_LED_TICK HAL_GetTick()
#define BLINK_LED_ON HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET)
#define BLINK_LED_OFF HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET)
#define BLINK_LED_DUTY (80)
#define BLINK_LED_PWN_WIDTH (30)
#define BLINK_LED_TICK_FREQ (1000)



	//////////////////////////////////////////////////////////////////////////
	// Inline function definition
 

#ifdef __cplusplus
}
#endif

#endif // macro _HEADER_NAME_H_



//#include <bsp_basic.h>

// Module Headers
#include <dbg.h>
#include <cmsis_ext.h>
#include <gpctrl.h>
#include <comm.h>
#include <ctrl.h>



