#include "ProxySyncEC.h"

void ProxySyncEC_start() {}
void ProxySyncEC_resume() {}
void ProxySyncEC_suspend() {}


void ProxySyncEC_init() {
  EC_init(0x21);
  
  EC_start = ProxySyncEC_start;
  EC_suspend = ProxySyncEC_suspend;
  EC_resume = ProxySyncEC_resume;
}
