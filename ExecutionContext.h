#ifndef EXECUTION_CONTEXT_HEADER_INCLUDED
#define EXECUTION_CONTEXT_HEADER_INCLUDED

typedef char LifeCycleState;

typedef char ReturnValue_t;

void EC_init();
LifeCycleState EC_get_component_state();
ReturnValue_t EC_activate_component();
ReturnValue_t EC_deactivate_component();
ReturnValue_t EC_execute();
ReturnValue_t EC_error();

extern void (*EC_start)();
extern void (*EC_suspend)();
extern void (*EC_resume)();

#endif // #ifndef EXECUTION_CONTEXT_HEADER_INCLDUED
