#ifndef TIMER1_EXECUTION_CONTEXT
#define TIMER1_EXECUTION_CONTEXT

#include "ExecutionContext.h"

void Timer1EC_init(double microsecond);
void Timer1EC_start();
void Timer1EC_suspend();
void Timer1EC_resume();

#if 0
namespace RTC {
  class Timer1EC : public ExecutionContext {
  private:
    long m_Period;
  public:
    Timer1EC(double microsecond);
    virtual ~Timer1EC();
    byte m_ClockSetting;
    
  public:
    void start();
    
    void suspend();
    
    void resume();
    
  };
};
#endif

#endif
