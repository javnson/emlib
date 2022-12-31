
// This sub-module provide a timer based tiny task runner.
// You can specify the running frequency and duration, even duty.

// System headers


// Module headers
#include "task_trigger_config.h"
#include <debug_framwork/debug_framwork.h>


#ifndef _HEADER_TASK_TRIGGER_H_
#define _HEADER_TASK_TRIGGER_H_

#ifdef __cplusplus
extern "C"
{
#endif

	//////////////////////////////////////////////////////////////////////////
	// Definition
#define TT_TASK_FLAG_TIMER_INIT      (0x01)
#define TT_TASK_FLAG_ROUTINE_INIT    (0x02)
#define TT_TASK_FLAG_ONESHOT         (0x04)
#define TT_TASK_FLAG_PERIOD          (0x08)
#define TT_TASK_FLAG_DISABLE_RAISING (0x0C)
#define TT_TASK_FLAG_DISABLE_FALLING (0x10)
#define TT_TASK_FLAG_RAISING_COMPT   (0x20)
#define TT_TASK_FLAG_FALLING_COMPT   (0x40)
#define TT_TASK_FLAG_ENABLE          (0x80)
#define TT_TASK_FLAG_COMPT           (0xC0)


#define TT_TASKQ_FLAG_ENABLE         (0x01)
#define TT_TASKQ_FLAG_COMPT          (0x02)
#define TT_TASKQ_FLAG_COMPT_CB       (0x04)
#define TT_TASKQ_FLAG_ALL_COMPT_CB   (0X08)

	// This macro is for unit conversion form ms to timer interrupt cycle
#define TT_TASK_TRANSFER_FACTOR      ((TASK_TRIGGER_TIMER_FREQUENCY)/1000)
#define TT_TASK_CONVERTION_TO_ISRC(x) ((uint32_t)((x) * TT_TASK_TRANSFER_FACTOR))

	//////////////////////////////////////////////////////////////////////////
	// Type
	struct _tag_task_trigger;
	typedef void (*void_routine)(uint32_t);
	typedef void (*task_trigger_routine)(struct _tag_task_trigger*, uint32_t);

	typedef struct _tag_task_triger_task
	{
		// 0x01: task timer has been init
		// 0x02: task routine has been init
		// 0x04: task is one-shot task
		// 0x08: task is a period task
		// 0x0C: disable raising edge
		// 0x10: disable falling edge
		// 0x20: raising edge routine has completed
		// 0x40: falling edge routine has completed
		// 0x80: task has been enable
		// 0xC0: the task has been complete
		uint8_t flag;

		// How often the task will be triggered, unit timer interrupt cycle
		uint32_t frequency;
		// How long the high_level keep, unit: timer interrupt cycle
		uint32_t duty;
		// Specify how long the operating time will keep, unit: timer interrupt cycle
		uint32_t duration;
		// Counter will auto increment, every timer interrupt cycle
		uint32_t counter;
		// The task will setup after the specified delay, unit: timer interrupt cycle
		uint32_t delay;

		// This function would be called when rising edge coming
		void_routine rising_edge_fn;
		// This function would be called when falling edge coming
		void_routine falling_edge_fn;
	}tt_task_t;

	typedef struct _tag_task_trigger
	{
		// Flags
		// 0x01: enable the task trigger
		// 0x02: all the tasks has been complete
		// 0x04: setup each task complete callback
		// 0x08: setup all tasks complete callback
		uint8_t flag;

		// How many tasks are in the task queue.
		uint8_t quantity;
		// How many tasks are completed.
		uint8_t quantity_compt;

		// task queue
#if defined TASK_TRIGER_FIXED_TASK_NUM
		tt_task_t tasks[TASK_TRIGER_TASK_QUANTITY];
#elif defined TASK_TRIGER_POINTER
		tt_task_t* tasks;
#endif

		// This function would be called when any task of the task queue has completed.
		task_trigger_routine task_complete_fn;
		// This function would be called when all the tasks of the task queue were completed.
		// At the time, the second param is useless, and this param will always set to 0.
		task_trigger_routine all_task_complete_fn;

	}task_trigger_t;



	//////////////////////////////////////////////////////////////////////////
	// Global variable


	//////////////////////////////////////////////////////////////////////////
	// Function prop-type

	void task_null_rising_routine(uint32_t index);
	void task_null_falling_routine(uint32_t index);
	// This function would be called, every task has completed
	void task_trigger_default_routine(struct _tag_task_trigger* tt_obj, uint32_t index);

	// initialize the task trigger object
	void init_task_trigger_obj(task_trigger_t* tt_obj,
		task_trigger_routine task_complate_fn
	#ifdef __cplusplus
	= task_trigger_default_routine
	#endif
	,
		task_trigger_routine all_task_complate_fn
	#ifdef __cplusplus
	= task_trigger_default_routine
	#endif
	);


	// initialize the task object
	// task: the task to be initialized
	// frequency: the task trigger frequency, unit Hz
	// duty: the task trigger duty, unit 1
	// duration: the task length, unit ms
	// delay: the first trigger delay, unit ms
	void init_period_task(tt_task_t* task, float frequency, float duration,
		float delay, float duty 
		#ifdef __cpluplus	
		= 0.5f
		#endif
		,
		void_routine rising_edge_fn
		#ifdef __cplusplus
		= task_null_rising_routine
		#endif
		,
		void_routine falling_edge_fn
		#ifdef __cplusplus
		= task_null_falling_routine
		#endif
		);

	// initialize the task object
	// task: the task object to be set
	// duration: the interval between rising edge and falling edge
	void init_one_shot_task(tt_task_t* task, float duration, float delay,
		void_routine rising_edge_fn 
	#ifdef __cplusplus
	= task_null_rising_routine
	#endif
	,
		void_routine falling_edge_fn
	#ifdef __cplusplus
	= task_null_falling_routine
	#endif
	);

	// config the period task 
	void config_period_task(tt_task_t* task, float frequency, float duration,
		float delay, float duty
			#ifdef __cplusplus
			= 0.5f
		#endif
		);

	// config the one-shot task
	void config_one_shot_task(tt_task_t* task, float duration, float delay);

	//config the edge routine
	void config_edge_routine(tt_task_t* task,
		void_routine rising_edge_fn 
	#ifdef __cplusplus
	= task_null_rising_routine
	#endif
	,
		void_routine falling_edge_fn
	#ifdef __cplusplus
	= task_null_falling_routine
	#endif
	);

#ifdef TASK_TRIGER_FIXED_TASK_NUM
	// initialize the task object, which was specified by task id
	// the id will be the index for a array, so it start from 0
	// frequency: the task trigger frequency, unit Hz
	// duty: the task trigger duty, unit 1
	// duration: the task length, unit ms
	// delay: the first trigger delay, unit ms
	void init_period_task_by_id(task_trigger_t *tt_obj, uint8_t id,
		float frequency, float duration,
		float delay, float duty 
		#ifdef __cpluplus	
		= 0.5f
		#endif
		,
		void_routine rising_edge_fn
		#ifdef __cplusplus
		= task_null_rising_routine
		#endif
		,
		void_routine falling_edge_fn
		#ifdef __cplusplus
		= task_null_falling_routine
		#endif	
		);

	// initialize the task object
	// task: the task object to be set
	// duration: the interval between rising edge and falling edge
	void init_one_shot_task_by_id(tt_task_t* task, uint8_t id,
		float duration, float delay,
		void_routine rising_edge_fn,
		void_routine falling_edge_fn);

#endif

	//////////////////////////////////////////////////////////////////////////
	// Inline function definition

	// 
	static inline void init_task_obj(tt_task_t* task)
	{
		task->flag = 0;
		task->counter = 0;

		task->delay = 0;
		task->duration = 0;
		task->duty = 0;
		task->frequency = 0;

		task->falling_edge_fn = task_null_falling_routine;
		task->rising_edge_fn = task_null_rising_routine;
		
		return;
		
	}

	// This function should be called in the Timer ISR
	static inline void task_trigger_isr(task_trigger_t* tt_obj)
	{
#if !defined DISABLE_DBG_FRM_MEMORY_VALID_CHECK_PTR
		if (is_variable_space_valid(tt_obj))
		{
			DBG_FRM_ERRO("task trigger ISR param error, invalid param has been ");

			while (1);
		}
#endif

		if ((tt_obj->flag & TT_TASKQ_FLAG_ENABLE) &&
			(tt_obj->flag & TT_TASKQ_FLAG_COMPT))
		{
			tt_task_t* ptask = tt_obj->tasks;
			for (int i = 0; i < tt_obj->quantity; ++i)
			{
				if ((ptask[i].flag & TT_TASK_FLAG_ENABLE) &&
					(!ptask[i].flag & TT_TASK_FLAG_COMPT)
					)
				{
					// Frequent generate mode
					if (ptask[i].flag & TT_TASK_FLAG_PERIOD)
					{
						// judge if rising edge is coming
						if ((!ptask[i].flag & TT_TASK_FLAG_DISABLE_RAISING) &&
							(!ptask[i].flag & TT_TASK_FLAG_RAISING_COMPT) &&
							(ptask[i].counter % ptask[i].frequency <= ptask[i].duty)
							)
						{
							ptask[i].rising_edge_fn(i);
							ptask[i].flag |= TT_TASK_FLAG_RAISING_COMPT;
							ptask[i].flag &= ~TT_TASK_FLAG_FALLING_COMPT;
						}

						// judge if falling edge is coming
						if ((!ptask[i].flag & TT_TASK_FLAG_DISABLE_FALLING) &&
							(!ptask[i].flag & TT_TASK_FLAG_FALLING_COMPT) &&
							(ptask[i].counter % ptask[i].frequency >= ptask[i].duty)
							)
						{
							ptask[i].falling_edge_fn(i);
							ptask[i].flag |= TT_TASK_FLAG_FALLING_COMPT;
							ptask[i].flag &= ~TT_TASK_FLAG_RAISING_COMPT;
						}

						// judge if all the process is complete
						if ((ptask[i].counter >= ptask[i].duration))
						{
#ifdef TASK_TRIGGER_AUTO_FALLING 
							// if falling edge hasn't meet, just do it
							if ((!ptask[i].flag & TT_TASK_FLAG_DISABLE_FALLING) &&
								(!ptask[i].flag & TT_TASK_FLAG_FALLING_COMPT)
								)
							{
								ptask[i].falling_edge_fn(i);
								ptask[i].flag |= TT_TASK_FLAG_FALLING_COMPT;
							}
#endif

							// complete the task
							ptask[i].flag |= TT_TASK_FLAG_COMPT;
							tt_obj->quantity_compt += 1;

							// judge if complete routine should be called
							if (tt_obj->flag & TT_TASKQ_FLAG_COMPT_CB)
								tt_obj->task_complete_fn(tt_obj, i);
						}
					}
					// One shot mode
					else if (ptask[i].flag & TT_TASK_FLAG_ONESHOT)
					{
						// judge if rising edge is coming
						if ((!ptask[i].flag & TT_TASK_FLAG_DISABLE_RAISING) &&
							(!ptask[i].flag & TT_TASK_FLAG_RAISING_COMPT)
							)
						{
							ptask[i].rising_edge_fn(i);
							ptask[i].flag |= TT_TASK_FLAG_RAISING_COMPT;
						}

						// judge if falling edge is coming
						if (ptask[i].counter >= ptask[i].duration &&
							(!ptask[i].flag & TT_TASK_FLAG_DISABLE_FALLING) &&
							(!ptask[i].flag & TT_TASK_FLAG_FALLING_COMPT)
							)
						{
							ptask[i].falling_edge_fn(i);

							// complete the task
							ptask[i].flag |= TT_TASK_FLAG_FALLING_COMPT |
								TT_TASK_FLAG_COMPT;
							tt_obj->quantity_compt += 1;
							// judge if complete routine should be called
							if (tt_obj->flag & TT_TASKQ_FLAG_COMPT_CB)
								tt_obj->task_complete_fn(tt_obj, i);
						}

					}

					ptask[i].counter += 1;
				}
				else
				{
					// whatever the task is complete or the task is disable
					// the counter of quantity_compt should increase.
					tt_obj->quantity_compt += 1;
				}
			}

			// deal with the task_trigger complete routine.
			if ((tt_obj->quantity == tt_obj->quantity_compt) &&
				(tt_obj->flag & TT_TASKQ_FLAG_ALL_COMPT_CB))
			{
				tt_obj->flag |= TT_TASKQ_FLAG_COMPT;
				tt_obj->all_task_complete_fn(tt_obj, 0);
			}

		}
	}




#ifdef __cplusplus
}
#endif

#endif // macro _HEADER_TASK_TRIGGER_H_
