#ifndef PGE_DELAY_H
#define PGE_DELAY_H

#include <3ds.h>
#define PGE_Delay(x) svcSleepThread((int64_t)x*1000000l)

#endif // PGE_DELAY_H
