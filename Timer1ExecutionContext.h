#ifndef TIMER1_EXECUTION_CONTEXT
#define TIMER1_EXECUTION_CONTEXT

class Timer1EC {
 private:
  long m_Period;
 public:
  Timer1EC(long microsecond);
  virtual ~Timer1EC();

 public:
  void start();
  
  void suspend();
  
  void resume();
  
};

#endif
