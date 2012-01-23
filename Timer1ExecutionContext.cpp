#define RTNO_SUBMODULE_DEFINE

#include <Arduino.h>
#include "RTno.h"
#include "Packet.h"
#include "Timer1ExecutionContext.h"
#include <avr/io.h>
#include <avr/interrupt.h>

//using namespace RTC;

static long m_Period;
static byte m_ClockSetting;

//static RTC::Timer1EC *m_pEC;

ISR(TIMER1_OVF_vect)
{
  //  m_pEC->execute();
  EC_execute();
}


void Timer1EC_init(double rate)
{
  EC_init();
  TCCR1A = 0;
  TCCR1B = 0x10;

  // Initialize Period
  m_Period = (F_CPU / 2000000) * (long)(1000000 / rate);
  long maxTimer = 0x10000;
  if(m_Period < maxTimer) {
    m_ClockSetting = 0x01;
  } else if((m_Period /   8) < maxTimer) {
    m_ClockSetting = 0x02;
  } else if((m_Period /  64) < maxTimer) {
    m_ClockSetting = 0x03;
  } else if((m_Period / 256) < maxTimer) {
    m_ClockSetting = 0x04;
  } else if((m_Period /1024) < maxTimer) {
    m_ClockSetting = 0x05;
  } else {
    m_Period = 0xFFFF, m_ClockSetting = 0x05; // maxSetting;
  }
  
  char SREG_buf = SREG;
  cli();
  ICR1 = m_Period;
  SREG = SREG_buf;

  
  TCCR1B &= 0xF8;
  //  TCCR1B |= m_ClockSetting;

  //TIMSK1 = 0x01;

  //  m_pEC= this;
  EC_start = Timer1EC_start;
  EC_suspend = Timer1EC_suspend;
  EC_resume = Timer1EC_resume;
}
/*
Timer1EC::~Timer1EC()
{
}
*/
void Timer1EC_start()
{
  TIMSK1 = 0x01;
  TCCR1B |= m_ClockSetting;
}

void Timer1EC_suspend()
{
  TIMSK1 &= 0xFE;
}

void Timer1EC_resume()
{
  TIMSK1 |= 0x01;
}


