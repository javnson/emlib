#include "constant_variables_config.h"

// Sometimes you may meet some constant variables to be defined as macro at first.
// But in the future, there's a chance that the the macro may need to be changed 
//  while running.
// So the constant_variable submodule gives you an option to change the state of these variables.
// In order to strength the submodule, you should follow the lead.
// before translate

#define MACRO (1.0)

// after translate


// if user need to disable the constant variable submodule
// user should do the following work
#define CVE_MACRO 0

#ifndef CVE_MACRO 
#define CVE_MACRO 1
#endif
#if CVE_MACRO == 1 // enable constant variable translate for MACRO
#define MACRO params.MACRO
#else
#define MACRO MACRO_INIT
#endif

typedef struct __tag_params
{
	float MACRO; // Generate this
}params_t;


// This function should be defined in .c file, and should be called at the beginning of the main function.
void init_params(params_t *handle)
{
#if CVE_MACRO == 1 // Generate for init
	MACRO = MACRO_INIT;
#endif
}
