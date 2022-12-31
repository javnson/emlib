


#include <bsp_interface.h>




// uart transmit function
void dbg_print(const char* p_fmt, ...) 
{
	char str[SHOW_BUFFER_LEN];
	uint8_t len;

	va_list vArgs;
	va_start(vArgs, p_fmt);
	vsprintf((char*)str, (char const*)p_fmt, vArgs);
	va_end(vArgs);

	len = strlen(str);
	HAL_UART_Transmit(&huart2, (uint8_t*)str, len, 10);
	
	return ;
}

void comm_print(const char* p_fmt, ...) 
{
	char str[SHOW_BUFFER_LEN];
	uint8_t len;

	va_list vArgs;
	va_start(vArgs, p_fmt);
	vsprintf((char*)str, (char const*)p_fmt, vArgs);
	va_end(vArgs);

	len = strlen(str);
	HAL_UART_Transmit(&huart1, (uint8_t*)str, len, 10);
	
	return ;
}

