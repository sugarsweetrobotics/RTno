#ifndef PROXY_SYNC_EXECUTION_CONTEXT
#define PROXY_SYNC_EXECUTION_CONTEXT


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

#endif //#ifndef PROXY_SYNC_EXECUTION_CONTEXT
