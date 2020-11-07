#ifndef PGE_DELAY_H
#define PGE_DELAY_H

#include <3ds.h>
#define PGE_Delay(x) svcSleepThread((uint64_t)x*1000000ull)

#endif // PGE_DELAY_H
