
#include "single_byte_command.h"

int32_t sbc_atoi(const uint16_t* param)
{
	uint8_t sign = 0;
	int32_t content = 0;

	if (*param == '-')
	{
		sign = 1;
		++param;
	}
	else if (*param == '+')
	{
		++param;
	}

	while (*param < '9' && *param>'0')
	{
		content *= 10;
		content += *param - '0';
	}
	if (sign)
		content *= -1;
	// ignore overflow
	return content;
}

uint32_t sbc_atoui(const uint16_t* param)
{
	uint32_t content = 0;

	while (*param < '9' && *param>'0')
	{
		content *= 10;
		content += *param - '0';
	}
	// ignore overflow
	return content;
}

float sbc_atof(const uint16_t* param)
{
	uint8_t sign = 0;
	float content = 0.0f;
	float decimal = 0.1f;

	if (*param == '-')
	{
		sign = 1;
		++param;
	}
	else if (*param == '+')
	{
		++param;
	}

	while (*param < '9' && *param>'0')
	{
		content *= 10.0f;
		content += *param - '0';
	}

	if (*param == '.')
		++param;

	while (*param < '9' && *param>'0')
	{
		content += (*param - '0') * decimal;
		decimal *= 0.1f;
	}

	if (sign)
		content *= -1.0f;
	// ignore overflow
	return content;
}

void sbc_reack_task(sbc_t* handle, sbc_mapping_t* task)
{
	if (task->state & SBC_MAP_ENABLE)
	{
		if (task->state & SBC_MAP_TRIGGERED)
		{
			// translate task params
			if (task->state & SBC_MAP_UINTPARAM)
				task->param.signed_param = sbc_atoi(&task->message_content[1]);
			else if (task->state & SBC_MAP_INTPARAM)
				task->param.unsigned_param = sbc_atoui(&task->message_content[1]);
			else if (task->state & SBC_MAP_FLOATPARAM)
				task->param.unsigned_param = sbc_atof(&task->message_content[1]);


			// if the message is an unknown message
			if (task->state & SBC_MAP_UNKNOWN)
			{
				if (handle->state & SBC_STATE_UNKNOWNACK)
					handle->unknown_command(task);

			}
			// For the normal message
			else
			{
				task->callback(task);
			}

			// Clear flags
			task->state &= ~SBC_MAP_TRIGGERED;
			handle->command_counter -= 1;

		}
	}
}

void sbc_main_callback(sbc_t* handle)
{
	static uint16_t round = 0;

	// react the trap command
	sbc_reack_task(handle, &handle->task_trap);

	// react the other commands
	sbc_reack_task(handle, &handle->mappings[round]);

	// deal with the counter
	round += 1;
	if (round == handle->ntasks)
		round = 0;

}


void sbc_task_init(sbc_mapping_t* handle)
{
	handle->callback = NULL;
	handle->command = 0;

	for (uint16_t i = 0; i < MAX_MESSAGE_LENGTH; ++i)
		handle->message_content[i] = 0;

	handle->message_len = 0;
	handle->state = 0;
}


#ifdef SBC_TASKS_POINTER
void sbc_init(sbc_t* handle, uint16_t ntasks, sbc_mapping_t* mappings)
{
	// init all the functions
	handle->trap = NULL;
	handle->unknown_command = NULL;
	handle->another_callback = NULL;

	handle->mappings = mappings;

	// init all the tasks
	for (int i = 0; i < ntasks; ++i)
	{
		sbc_task_init(&handle->mappings[i])
	}
	sbc_task_init(&handle->task_trap);
	handle->task_trap.state |= SBC_MAP_UNKNOWN;

	// single byte command reactor state machine
	handle->ntasks = 0;
	handle->state = 0;
	handle->target_num = 0;
}

#else
void sbc_init(sbc_t* handle)
{
	// init all the functions
	handle->trap = NULL;
	handle->unknown_command = NULL;
	handle->another_callback = NULL;
	
	// init all the tasks
	for (int i = 0; i < SBC_TASKS_NUM; ++i)
	{
		sbc_task_init(&handle->mappings[i]);
	}
	sbc_task_init(&handle->task_trap);
	handle->task_trap.state |= SBC_MAP_UNKNOWN;

	// single byte command reactor state machine
	handle->ntasks = 0;
	handle->state = 0;
	handle->target_num = 0;
}

uint16_t sbc_reg_task(sbc_t* handle, uint16_t command, sbc_task_fn callback)
{
	handle->mappings[handle->ntasks].callback = callback;
	handle->mappings[handle->ntasks].command = command;
	handle->mappings[handle->ntasks].state |= SBC_MAP_ENABLE;
	return handle->ntasks++;
}



#endif

