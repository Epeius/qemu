/*
 * WallTimer.h
 *
 *  Created on: 2016年4月22日
 *      Author: epeius
 */

#ifndef WALLTIMER_H_
#define WALLTIMER_H_

#include <inttypes.h>

namespace fuzzyqemu {

class WallTimer
{
public:
    uint64_t startSeconds;
    uint64_t startMicroseconds;

public:
    WallTimer();

    /// check - Return the delta since the timer was created, in microseconds.
    uint64_t check();
};

} //namespace fuzzyqemu
#endif /* WALLTIMER_H_ */
