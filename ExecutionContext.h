#ifndef EXECUTION_CONTEXT_HEADER_INCLUDED
#define EXECUTION_CONTEXT_HEADER_INCLUDED

#include <stdint.h>

extern "C" {
  typedef int8_t LifeCycleState;
  typedef int8_t ReturnValue_t;
  
  void EC_init(int8_t);
  LifeCycleState EC_get_component_state();
  ReturnValue_t EC_activate_component();
  ReturnValue_t EC_deactivate_component();
  ReturnValue_t EC_reset_component();
  ReturnValue_t EC_execute();
  ReturnValue_t EC_error();
  int8_t EC_get_type();
  
  extern void (*EC_start)();
  extern void (*EC_suspend)();
  extern void (*EC_resume)();
}

#endif // #ifndef EXECUTION_CONTEXT_HEADER_INCLDUED
