

#include "task_trigger.h"


void task_null_rising_routine(uint32_t index)
{
	DBG_FRM_WARN("task_null_rising_routine has been called.\r\n");
}

void task_null_falling_routine(uint32_t index)
{
	DBG_FRM_WARN("task_null_falling_routine has been called.\r\n");
}

void task_trigger_default_routine(struct _tag_task_trigger* tt_obj, uint32_t index)
{
	DBG_FRM_WARN("task_trigger_default_routine has been called.\r\n");
}

void init_task_trigger_obj(task_trigger_t* tt_obj,
	task_trigger_routine task_complate_fn,
	task_trigger_routine all_task_complate_fn)
{
#if !defined DISABLE_DBG_FRM_MEMORY_VALID_CHECK_PTR
	if (is_variable_space_valid(tt_obj))
	{
		DBG_FRM_ERRO("function init_task_trigger_obj receive a invalid address.\r\n");
		while (1);
	}
#endif

	tt_obj->flag = 0;
	tt_obj->quantity = 0;
	tt_obj->quantity_compt = 0;

	tt_obj->task_complete_fn = task_complate_fn;
	tt_obj->all_task_complete_fn = all_task_complate_fn;

#ifdef TASK_TRIGER_FIXED_TASK_NUM
	for (int i = 0; i < TASK_TRIGER_TASK_QUANTITY; ++i)
		init_task_obj(&tt_obj->tasks[i]);

#endif
}

void init_period_task(tt_task_t* task, float frequency, float duration,
	float delay, float duty,
	void_routine rising_edge_fn,
	void_routine falling_edge_fn)
{
#if !defined DISABLE_DBG_FRM_MEMORY_VALID_CHECK_PTR
	if (is_variable_space_valid(task))
	{
		DBG_FRM_ERRO("function init_period_task receive a invalid address.\r\n");
		while (1);
	}
#endif

	task->flag = 0;
	task->frequency = TT_TASK_CONVERTION_TO_ISRC(1.0f /frequency);
	task->duration = TT_TASK_CONVERTION_TO_ISRC(duration);
	task->delay = TT_TASK_CONVERTION_TO_ISRC(delay);
	task->duty = TT_TASK_CONVERTION_TO_ISRC(duty);
	task->rising_edge_fn = rising_edge_fn;
	task->falling_edge_fn = falling_edge_fn;
	task->counter = 0;
	task->flag |= TT_TASK_FLAG_TIMER_INIT;

	if (task->rising_edge_fn == task_null_rising_routine)
	{
		task->flag |= TT_TASK_FLAG_DISABLE_RAISING;
	}

	if (task->falling_edge_fn == task_null_falling_routine)
	{
		task->flag |= TT_TASK_FLAG_DISABLE_FALLING;
	}
	task->flag |= TT_TASK_FLAG_ROUTINE_INIT | TT_TASK_FLAG_PERIOD;
}

void init_one_shot_task(tt_task_t* task, float duration, float delay,
	void_routine rising_edge_fn,
	void_routine falling_edge_fn)
{
#if !defined DISABLE_DBG_FRM_MEMORY_VALID_CHECK_PTR
	if (is_variable_space_valid(task))
	{
		DBG_FRM_ERRO("function init_one_shot_task receive a invalid address.\r\n");
		while (1);
	}
#endif

	task->flag = 0;
	task->frequency = 0;
	task->duration = TT_TASK_CONVERTION_TO_ISRC(duration);
	task->delay = TT_TASK_CONVERTION_TO_ISRC(delay);
	task->duty = 0;
	task->rising_edge_fn = rising_edge_fn;
	task->falling_edge_fn = falling_edge_fn;
	task->counter = 0;
	task->flag |= TT_TASK_FLAG_TIMER_INIT;

	if (task->rising_edge_fn == task_null_rising_routine)
	{
		task->flag |= TT_TASK_FLAG_DISABLE_RAISING;
	}

	if (task->falling_edge_fn == task_null_falling_routine)
	{
		task->flag |= TT_TASK_FLAG_DISABLE_FALLING;
	}
	task->flag |= TT_TASK_FLAG_ROUTINE_INIT | TT_TASK_FLAG_ONESHOT;
}

void config_period_task(tt_task_t* task, float frequency, float duration,
	float delay, float duty)
{
#if !defined DISABLE_DBG_FRM_MEMORY_VALID_CHECK_PTR
	if (is_variable_space_valid(task))
	{
		DBG_FRM_ERRO("function config_period_task receive a invalid address.\r\n");
		while (1);
	}
#endif
	// Clear flag
	task->flag = task->flag & TT_TASK_FLAG_ROUTINE_INIT; // keep task flag routine

	task->frequency = TT_TASK_CONVERTION_TO_ISRC(1.0f / frequency);
	task->duration = TT_TASK_CONVERTION_TO_ISRC(duration);
	task->delay = TT_TASK_CONVERTION_TO_ISRC(delay);
	task->duty = TT_TASK_CONVERTION_TO_ISRC(duty);
	task->counter = 0;
	task->flag |= TT_TASK_FLAG_TIMER_INIT;
	task->flag |= TT_TASK_FLAG_PERIOD;

}

void config_one_shot_task(tt_task_t* task, float duration, float delay)
{
#if !defined DISABLE_DBG_FRM_MEMORY_VALID_CHECK_PTR
	if (is_variable_space_valid(task))
	{
		DBG_FRM_ERRO("function config_period_task receive a invalid address.\r\n");
		while (1);
	}
#endif
	// Clear flag
	task->flag = task->flag & TT_TASK_FLAG_ROUTINE_INIT; // keep task flag routine

	task->frequency = 0;
	task->duration = TT_TASK_CONVERTION_TO_ISRC(duration);
	task->delay = TT_TASK_CONVERTION_TO_ISRC(delay);
	task->duty = 0;
	task->counter = 0;
	task->flag |= TT_TASK_FLAG_TIMER_INIT;
	task->flag |= TT_TASK_FLAG_ONESHOT;
}

//config the edge routine
void config_edge_routine(tt_task_t* task,
	void_routine rising_edge_fn,
	void_routine falling_edge_fn)
{
#if !defined DISABLE_DBG_FRM_MEMORY_VALID_CHECK_PTR
	if (is_variable_space_valid(task))
	{
		DBG_FRM_ERRO("function config_period_task receive a invalid address.\r\n");
		while (1);
	}
#endif

	task->rising_edge_fn = rising_edge_fn;
	task->falling_edge_fn = falling_edge_fn;

	if (task->rising_edge_fn == task_null_rising_routine)
	{
		task->flag |= TT_TASK_FLAG_DISABLE_RAISING;
	}

	if (task->falling_edge_fn == task_null_falling_routine)
	{
		task->flag |= TT_TASK_FLAG_DISABLE_FALLING;
	}
	task->flag |= TT_TASK_FLAG_ROUTINE_INIT;
}

#ifdef TASK_TRIGER_FIXED_TASK_NUM

void init_period_task_by_id(task_trigger_t* tt_obj, uint8_t id,
	float frequency, float duration,
	float delay, float duty,
	void_routine rising_edge_fn,
	void_routine falling_edge_fn)
{
#if !defined DISABLE_DBG_FRM_MEMORY_VALID_CHECK_PTR
	if (is_variable_space_valid(tt_obj))
	{
		DBG_FRM_ERRO("function init_period_task_by_id receive a invalid address.\r\n");
		while (1);
	}
#endif

#if defined _DEBUG
	if (id >= TASK_TRIGER_TASK_QUANTITY)
	{
		DBG_FRM_ERRO("visit task by id, but array out of range.\r\n");
		while (1);
	}
#endif

	tt_task_t* task = &tt_obj->tasks[id];

	task->flag = 0;
	task->frequency = 0;
	task->duration = TT_TASK_CONVERTION_TO_ISRC(duration);
	task->delay = TT_TASK_CONVERTION_TO_ISRC(delay);
	task->duty = 0;
	task->rising_edge_fn = rising_edge_fn;
	task->falling_edge_fn = falling_edge_fn;
	task->counter = 0;
	task->flag |= TT_TASK_FLAG_TIMER_INIT;

	if (task->rising_edge_fn == task_null_rising_routine)
	{
		task->flag |= TT_TASK_FLAG_DISABLE_RAISING;
	}

	if (task->falling_edge_fn == task_null_falling_routine)
	{
		task->flag |= TT_TASK_FLAG_DISABLE_FALLING;
	}
	task->flag |= TT_TASK_FLAG_ROUTINE_INIT | TT_TASK_FLAG_ONESHOT;
}

void init_one_shot_task_by_id(tt_task_t* tt_obj, uint8_t id,
	float duration, float delay,
	void_routine rising_edge_fn,
	void_routine falling_edge_fn)
{
#if !defined DISABLE_DBG_FRM_MEMORY_VALID_CHECK_PTR
	if (is_variable_space_valid(tt_obj))
	{
		DBG_FRM_ERRO("function init_one_shot_task_by_id receive a invalid address.\r\n");
		while (1);
	}
#endif

#if defined _DEBUG
	if (id >= TASK_TRIGER_TASK_QUANTITY)
	{
		DBG_FRM_ERRO("visit task by id, but array out of range.\r\n");
		while (1);
	}
#endif

	tt_task_t* task = &tt_obj[id];

	task->flag = 0;
	task->frequency = 0;
	task->duration = TT_TASK_CONVERTION_TO_ISRC(duration);
	task->delay = TT_TASK_CONVERTION_TO_ISRC(delay);
	task->duty = 0;
	task->rising_edge_fn = rising_edge_fn;
	task->falling_edge_fn = falling_edge_fn;
	task->counter = 0;
	task->flag |= TT_TASK_FLAG_TIMER_INIT;

	if (task->rising_edge_fn == task_null_rising_routine)
	{
		task->flag |= TT_TASK_FLAG_DISABLE_RAISING;
	}

	if (task->falling_edge_fn == task_null_falling_routine)
	{
		task->flag |= TT_TASK_FLAG_DISABLE_FALLING;
	}
	task->flag |= TT_TASK_FLAG_ROUTINE_INIT | TT_TASK_FLAG_ONESHOT;
}


#endif

