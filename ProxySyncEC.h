#ifndef PROXY_SYNC_EXECUTION_CONTEXT
#define PROXY_SYNC_EXECUTION_CONTEXT
#include "ExecutionContext.h"
void ProxySyncEC_init();

#if 0

namespace RTC {
  class ProxySyncEC : public ExecutionContext {
  private:
    
  public:
  ProxySyncEC() : ExecutionContext() {};
    virtual ~ProxySyncEC(){};
    
    void start(){};
    void suspend(){};
    void resume(){};
  };
};
#endif

#endif //#ifndef PROXY_SYNC_EXECUTION_CONTEXT
