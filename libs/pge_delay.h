#ifndef PGE_DELAY_H
#define PGE_DELAY_H

#include <3ds.h>
#define PGE_Delay(x) svcSleepThread(x*1000000)

#endif // PGE_DELAY_H
