#ifndef TIMER2_EXECUTION_CONTEXT
#define TIMER2_EXECUTION_CONTEXT

#include "ExecutionContext.h"

void Timer2EC_init(double microsecond);
void Timer2EC_start();
void Timer2EC_suspend();
void Timer2EC_resume();


#endif
