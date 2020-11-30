#include <3ds.h>
#include <cstdio>

uint64_t timer_start = 0;

void PS_StartTimer()
{
    timer_start = svcGetSystemTick();
}

void PS_SleepTill(uint64_t ms)
{
    uint64_t ms_elapsed = (svcGetSystemTick() - timer_start) / 268000;
    // printf("Want %llu, already %llu ms\n", ms, ms_elapsed);
    if (ms_elapsed >= ms) return;
    svcSleepThread((ms-ms_elapsed)*1000000);
}
