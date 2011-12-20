#ifndef EXECUTION_CONTEXT_HEADER_INCLUDED
#define EXECUTION_CONTEXT_HEADER_INCLUDED


namespace RTC {
  typedef char LifeCycleState;

  class ExecutionContext {
    
    
  private:
    LifeCycleState m_Condition;
    
  public:
    ExecutionContext() {m_Condition = RTC_STATE_INACTIVE;};
    virtual ~ExecutionContext() {};
    
    
    LifeCycleState get_component_state() {
      return m_Condition;
    }
    
    char activate_component() {
      if(m_Condition != RTC_STATE_INACTIVE) {
	return RTC_PRECONDITION_NOT_MET;
      }
      
      if(RTno::onActivated() == RTC_OK) {
	m_Condition = RTC_STATE_ACTIVE;
	return RTC_OK;
      } else {
	m_Condition = RTC_STATE_ERROR;
	return RTC_ERROR;
      }
    }
    
    char deactivate_component() {
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
    
    char execute() {
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

    char error() {
      if(m_Condition != RTC_STATE_ERROR) {
	return RTC_PRECONDITION_NOT_MET;
      }

      RTno::onError();
      return RTC_OK;
    }
    
    virtual void start() = 0;
    //  virtual void stop() = 0;
    virtual void resume() = 0;
    virtual void suspend() = 0;
    
  };
  
};
#endif // #ifndef EXECUTION_CONTEXT_HEADER_INCLDUED
