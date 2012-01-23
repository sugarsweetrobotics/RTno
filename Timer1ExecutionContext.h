#ifndef TIMER1_EXECUTION_CONTEXT
#define TIMER1_EXECUTION_CONTEXT

#include "ExecutionContext.h"


void Timer1EC_init(double microsecond);
void Timer1EC_start();
void Timer1EC_suspend();
void Timer1EC_resume();

#endif
