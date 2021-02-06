#ifndef __TIMER_H__
#define __TIMER_H__

#include<stdint.h>
#include<stdlib.h>
#include<time.h>

#define GHZ 3500000000

uint64_t tick(void);

float rand_time(int min, int max);

#endif
