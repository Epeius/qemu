/*
 * WallTimerWrapper.h
 *
 *  Created on: 2016年4月22日
 *      Author: epeius
 */

#ifndef WALLTIMERWRAPPER_H_
#define WALLTIMERWRAPPER_H_

#include <inttypes.h>

struct WallTimerWrapper;

#ifdef __cplusplus
extern "C" {
#endif
struct WallTimerWrapper *WallTimer_GetInstance(void);
void WallTimer_ReleaseInstance(struct WallTimerWrapper **ppInstance);
extern uint64_t WallTimer_check(struct WallTimerWrapper *pApple);
extern uint64_t WallTimer_GetSeconds(struct WallTimerWrapper *pApple);
extern uint64_t WallTimer_GetUSeconds(struct WallTimerWrapper *pApple);
#ifdef __cplusplus
}
;
#endif


#endif /* WALLTIMERWRAPPER_H_ */
