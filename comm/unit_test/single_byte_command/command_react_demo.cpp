#include <single_byte_command.h>


sbc_t sbc;

void task_for_a(struct __tag_sbc_mapping*)
{
	cout << "This is task A has been run.";
}

int main(int argc, char* argv[])
{
	sbc_init(&sbc);
	uint16_t sbc_task_handle = sbc_reg_task(&sbc, 'a', task_for_a);
}

