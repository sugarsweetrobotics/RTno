#ifndef RTC_CONF_HEADER_INCLUDED
#define RTC_CONF_HEADER_INCLUDED


#ifdef USE_ETHERNET_CONNECTION
struct IPAddr {
  unsigned char value[4];

  IPAddr() {}

  IPAddr(unsigned char b1,
	 unsigned char b2,
	 unsigned char b3,
	 unsigned char b4) {
    value[0] = b1; value[1] = b2; value[2] = b3; value[3] = b4;
  }

  void operator=(const unsigned char var[]) {

  }

};

struct MacAddr {
  unsigned char value[6];

  MacAddr() {}

  MacAddr(unsigned char b1,
	     unsigned char b2,
	     unsigned char b3,
	     unsigned char b4,
	     unsigned char b5,
	     unsigned char b6) {
    value[0] = b1; value[1] = b2; value[2] = b3; value[3] = b4; value[4] = b5; value[5] = b6;
  }

  void operator=(const unsigned char var[]) {

  }
};

#endif

struct config_str {
  struct default_str {
    unsigned char connection_type;
    unsigned short port;

#ifdef USE_ETHERNET_CONNECTION
    MacAddr mac_address;
    IPAddr ip_address;
    IPAddr subnet_mask;
    IPAddr default_gateway;
#endif

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
#ifdef USE_ETHERNET_CONNECTION
#define ConnectionTypeEtherTcp 0x04
#endif

#define ProxySynchronousExecutionContext 0x21

#ifdef TIMER1_EXECUTION_CONTEXT
#define Timer1ExecutionContext 0x22
#endif

#define Timer2ExecutionContext 0x23

#endif
