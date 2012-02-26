#define RTNO_SUBMODULE_DEFINE

#include <stdint.h>
#include "RTno.h"
#include "Packet.h"

#include "ExecutionContext.h"

static int8_t m_Type;
static LifeCycleState m_Condition;

void EC_init(int8_t Type) {
  m_Type = Type;
  m_Condition = RTC_STATE_INACTIVE;
}

int8_t EC_get_type() {
  return m_Type;
}

LifeCycleState EC_get_component_state() {
  return m_Condition;
}

ReturnValue_t EC_activate_component() {
  if(m_Condition != RTC_STATE_INACTIVE) {
    return RTNO_RTC_PRECONDITION_NOT_MET;
  }
  
  if(RTno::onActivated() == RTC_OK) {
    m_Condition = RTC_STATE_ACTIVE;
    return RTNO_RTC_OK;
  }

  m_Condition = RTC_STATE_ERROR;
  return RTNO_RTC_ERROR;
}


ReturnValue_t EC_deactivate_component() {
  if(m_Condition != RTC_STATE_ACTIVE) {
    return RTNO_RTC_PRECONDITION_NOT_MET;
  }
  
  if(RTno::onDeactivated() == RTC_OK) {
    m_Condition = RTC_STATE_INACTIVE;
    return RTNO_RTC_OK;
  } else {
    m_Condition = RTC_STATE_ERROR;
    return RTNO_RTC_ERROR;
  }
}

ReturnValue_t EC_execute() {
  if(m_Condition != RTC_STATE_ACTIVE) {
    return RTNO_RTC_PRECONDITION_NOT_MET;
  }
  
  if(RTno::onExecute() == RTNO_RTC_OK) {
    return RTNO_RTC_OK;
  } else {
    m_Condition = RTC_STATE_ERROR;
    return RTNO_RTC_ERROR;
  }
}

ReturnValue_t EC_reset_component() {
  if(m_Condition != RTC_STATE_ERROR) {
    return RTNO_RTC_PRECONDITION_NOT_MET;
  }
  if(RTno::onReset() == RTNO_RTC_OK) {
    m_Condition = RTC_STATE_INACTIVE;
    return RTNO_RTC_OK;
  } 
  return RTNO_RTC_ERROR;
}

ReturnValue_t EC_error() {
  if(m_Condition != RTC_STATE_ERROR) {
    return RTNO_RTC_PRECONDITION_NOT_MET;
  }
  
  RTno::onError();
  return RTNO_RTC_OK;
}


#ifdef __cplusplus
extern "C" {
#endif

void (*EC_start)();
void (*EC_resume)();
void (*EC_suspend)();

#ifdef __cplusplus
}
#endif
