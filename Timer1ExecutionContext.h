#ifndef TIMER1_EXECUTION_CONTEXT
#define TIMER1_EXECUTION_CONTEXT

#include "ExecutionContext.h"

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
