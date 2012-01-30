#define RTNO_SUBMODULE_DEFINE

#include <stdint.h>
#include <Arduino.h>
#include "RTno.h"
#include "Packet.h"
#include "Timer1ExecutionContext.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static int32_t m_Period;
static uint8_t m_ClockSetting;


void Timer1EC_start();
void Timer1EC_suspend();
void Timer1EC_resume();

void Timer1EC_init(double rate)
{
  EC_init(0x22);
  TCCR1A = 0;
  TCCR1B = _BV(WGM13);

  // Initialize Period
  
  m_Period = (F_CPU / 2000000) * (int32_t)(1000000 / rate);
  const int32_t maxTimer = 65536;
  if(m_Period < maxTimer) {
    m_ClockSetting = _BV(CS10);
  } else if((m_Period /=   8) < maxTimer) {
    m_ClockSetting = _BV(CS11);
  } else if((m_Period /=  64) < maxTimer) {
    m_ClockSetting = _BV(CS11) | _BV(CS10);
  } else if((m_Period /= 256) < maxTimer) {
    m_ClockSetting = _BV(CS12);
  } else if((m_Period /=1024) < maxTimer) {
    m_ClockSetting = _BV(CS12) | _BV(CS10);;
  } else {
    m_Period = 0xFFFF, m_ClockSetting = _BV(CS12) | _BV(CS10);
  }

  //TIMSK1 = 0x01;
  //  m_pEC= this;
  EC_start = Timer1EC_start;
  EC_suspend = Timer1EC_suspend;
  EC_resume = Timer1EC_resume;
}

void Timer1EC_start()
{

  char SREG_buf = SREG;
  cli();
  ICR1 = m_Period;
  SREG = SREG_buf;

  TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));
  TCCR1B |= m_ClockSetting;
 
  TIMSK1 = _BV(TOIE1);
  TCCR1B |= m_ClockSetting;

}

void Timer1EC_suspend()
{
  TIMSK1 &= ~_BV(TOIE1);
}

void Timer1EC_resume()
{
  TIMSK1 = _BV(TOIE1);
  TCCR1B |= m_ClockSetting;
}


