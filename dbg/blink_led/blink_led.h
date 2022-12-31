
// System headers
#include <stdint.h>

// Module headers
#include "blink_led_config.h"

#ifndef _HEADER_BLINK_LED_H_
#define _HEADER_BLINK_LED_H_



#ifdef __cplusplus
extern "C"
{
#endif

	//////////////////////////////////////////////////////////////////////////
	// Type

	typedef uint8_t blink_led_prescale_t;
	typedef uint16_t blink_led_counter_t;
	typedef uint32_t blink_led_tick_t;
	typedef uint8_t blink_led_flag_t;

	typedef struct _tag_blink_led
	{
		void (*led_on)(void);
		void (*led_off)(void);

		blink_led_tick_t(*get_tick)(void);

		blink_led_tick_t tick;
		blink_led_prescale_t pwmset;
		blink_led_tick_t time;
		blink_led_prescale_t timecount;

		blink_led_flag_t timeflag;

		blink_led_prescale_t pwm_width;
		blink_led_prescale_t pwm_duty;
	}blink_led_t;

	//////////////////////////////////////////////////////////////////////////
	// Global variable

	//////////////////////////////////////////////////////////////////////////
	// Function prop-type
	void init_blink_led_handle(blink_led_t* handle,
		blink_led_prescale_t pwm_width
#ifdef __cplusplus
	= BLINK_LED_PWN_WIDTH
#endif
	,
		blink_led_prescale_t pwm_duty 
#ifdef __cplusplus
	= BLINK_LED_DUTY
#endif
	);
	void do_blink_led_by_handle(blink_led_t* handle);

	void do_blink_led(void);

	//////////////////////////////////////////////////////////////////////////
	// Inline function definition



#ifdef __cplusplus
}
#endif

#endif // macro _HEADER_BLINK_LED_H_

