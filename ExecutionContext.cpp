#define RTNO_SUBMODULE_DEFINE
#include "RTno.h"
#include "Packet.h"

#include "ExecutionContext.h"

static LifeCycleState m_Condition;

void EC_init() {
  m_Condition = RTC_STATE_INACTIVE;
}

LifeCycleState EC_get_component_state() {
  return m_Condition;
}

ReturnValue_t EC_activate_component() {
  if(m_Condition != RTC_STATE_INACTIVE) {
    return RTC_PRECONDITION_NOT_MET;
  }
  
  if(RTno::onActivated() == RTC_OK) {
    m_Condition = RTC_STATE_ACTIVE;
    return RTC_OK;
  }

  m_Condition = RTC_STATE_ERROR;
  return RTC_ERROR;
}


ReturnValue_t EC_deactivate_component() {
  if(m_Condition != RTC_STATE_ACTIVE) {
    return RTC_PRECONDITION_NOT_MET;
  }
  
  if(RTno::onDeactivated() == RTC_OK) {
    m_Condition = RTC_STATE_INACTIVE;
    return RTC_OK;
  } else {
    m_Condition = RTC_STATE_ERROR;
    return RTC_ERROR;
  }
}

ReturnValue_t EC_execute() {
  if(m_Condition != RTC_STATE_ACTIVE) {
    return RTC_PRECONDITION_NOT_MET;
  }
  
  if(RTno::onExecute() == RTC_OK) {
    return RTC_OK;
  } else {
    m_Condition = RTC_STATE_ERROR;
    return RTC_ERROR;
  }
}

ReturnValue_t EC_error() {
  if(m_Condition != RTC_STATE_ERROR) {
    return RTC_PRECONDITION_NOT_MET;
  }
  
  RTno::onError();
  return RTC_OK;
}

void (*EC_start)();
void (*EC_resume)();
void (*EC_suspend)();

