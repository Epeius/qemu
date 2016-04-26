/*
 * WallTimer.cpp
 *
 *  Created on: 2016年4月22日
 *      Author: epeius
 */
extern "C" {
#include <sys/time.h>
}
#include "WallTimer.h"

using namespace std;

#define NULL 0
namespace fuzzyqemu {
WallTimer::WallTimer()
{
    struct timeval start_time;
    gettimeofday(&start_time, NULL);
    startSeconds = start_time.tv_sec;
    startMicroseconds = start_time.tv_usec;
}

uint64_t WallTimer::check()
{
    struct timeval cur_time;
    gettimeofday(&cur_time, NULL);
    return (cur_time.tv_sec - startSeconds) * 1000000 + cur_time.tv_usec
            - startMicroseconds;
}

} //namespace fuzzyqemu
