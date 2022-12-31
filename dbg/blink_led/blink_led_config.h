
#include <bsp_interface.h>

#ifndef _FILE_BLINK_LED_CONFIG_H_
#define _FILE_BLINK_LED_CONFIG_H_

	//////////////////////////////////////////////////////////////////////////
	// Definition
// This macro defined the frequency of systick
#ifndef BLINK_LED_TICK_FREQ
#define BLINK_LED_TICK_FREQ (1000)
#endif
// This macro defined how many steps the process has
#ifndef BLINK_LED_DUTY
#define BLINK_LED_DUTY (80)
#endif
// This macro defined the frequency of the PWM
// This macro must ensure led's PWM is faster than 20ms
#ifndef BLINK_LED_PWN_WIDTH
#define BLINK_LED_PWN_WIDTH (20)
#endif

// This macro should point to a function which will return the systick
#ifndef BLINK_LED_TICK
#define BLINK_LED_TICK (0)
#endif
// This macro should point to a function which will light the LED
#ifndef BLINK_LED_ON
#define BLINK_LED_ON (0)
#endif
// This macro should point to a function which will close the LED
#ifndef BLINK_LED_OFF
#define BLINK_LED_OFF (0)
#endif



#endif

