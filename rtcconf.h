#ifndef RTC_CONF_HEADER_INCLUDED
#define RTC_CONF_HEADER_INCLUDED



struct config_str {
  struct default_str {
    unsigned char connection_type;
    long baudrate;
  }_default;
};

struct exec_cxt_str {
  struct periodic_str {
    unsigned char type;
    double rate;
  }periodic;
};

#define ConnectionTypeSerial1 0x01
#define ConnectionTypeSerial2 0x02
#define ConnectionTypeSerial3 0x03

#define ProxySynchronousExecutionContext 0x21
#define Timer1ExecutionContext 0x22
#define Timer2ExecutionContext 0x23

#endif
