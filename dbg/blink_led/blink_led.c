

#include "blink_led.h"


void init_blink_led_handle(blink_led_t* handle,
	blink_led_prescale_t pwm_width,
	blink_led_prescale_t pwm_duty)
{

// Check memory
	

}


void do_blink_led(void)
{
	static blink_led_prescale_t pwmset;
	static blink_led_tick_t time;
	static blink_led_prescale_t timecount;
	static blink_led_tick_t tick;
	static blink_led_flag_t timeflag;

	if ((BLINK_LED_TICK - tick >= 1))
	{
		tick = BLINK_LED_TICK;

		if (timeflag == 0)
		{
			time++;
			if (time >= BLINK_LED_DUTY * BLINK_LED_PWN_WIDTH) timeflag = 1;
		}
		else
		{
			time--;
			if (time == 0) timeflag = 0;
		}

		// duty
		pwmset = time / BLINK_LED_DUTY ;

		// generate PWM which width is 20ms
		if (timecount > BLINK_LED_PWN_WIDTH) timecount = 0;
		else timecount++;

		if (timecount >= pwmset) 
			BLINK_LED_ON;
		else 
			BLINK_LED_OFF;
	}
}

void do_blink_led_by_handle(blink_led_t* handle)
{
	if ((handle->get_tick() - handle->tick >= 1))
	{
		handle->tick = handle->get_tick();

		if (handle->timeflag == 0)
		{
			handle->time++;
			if (handle->time >= BLINK_LED_PWN_WIDTH * BLINK_LED_DUTY) handle->timeflag = 1;
		}
		else
		{
			handle->time--;
			if (handle->time == 0) handle->timeflag = 0;
		}

		// duty
		handle->pwmset = handle->time / BLINK_LED_DUTY;

		// generate PWM which width is BLINK_LED_PWN_WIDTH ms
		if (handle->timecount > BLINK_LED_PWN_WIDTH) handle->timecount = 0;
		else handle->timecount++;

		if (handle->timecount >= handle->pwmset)
			handle->led_on();
		else
			handle->led_off();
	}
}

