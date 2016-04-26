/*
 * WallTimerWrapper.cpp
 *
 *  Created on: 2016年4月22日
 *      Author: epeius
 */

#include "WallTimerWrapper.h"
#include "WallTimer.h"

#ifdef __cplusplus
namespace fuzzyqemu {
extern "C" {
#endif

struct WallTimerWrapper
{
    WallTimer WallTimer;
};

struct WallTimerWrapper *WallTimer_GetInstance(void)
{
    return new struct WallTimerWrapper;
}

void WallTimer_ReleaseInstance(struct WallTimerWrapper **ppInstance)
{
    delete *ppInstance;
    *ppInstance = 0;
}

uint64_t WallTimercheck(struct WallTimerWrapper *wt)
{
    return wt->WallTimer.check();
}

uint64_t  WallTimer_GetSeconds(struct WallTimerWrapper *wt)
{
    return wt->WallTimer.startSeconds;
}

uint64_t  WallTimer_GetUSeconds(struct WallTimerWrapper *wt)
{
    return wt->WallTimer.startMicroseconds;
}

#ifdef __cplusplus
};
}
#endif
