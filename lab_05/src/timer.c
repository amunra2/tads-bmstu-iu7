#include<stdint.h>
#include<inttypes.h>
#include"../inc/timer.h"

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}


float rand_time(int min, int max)
{
    //srand(time(NULL));

    return (max - min) * (float)(rand()) / (float)RAND_MAX + min;
}
