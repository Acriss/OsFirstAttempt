#ifndef TimeSpec
#define TimeSpec

#include <stdio.h>
#include <time.h>
#include <math.h>

double timespec_to_ms(const timespec& time_ts);
timespec timespec_from_ms(double time_ms);
timespec timespec_now();
timespec timespec_negate(const timespec& time_ts);
timespec timespec_add(const timespec &time1_ts, const timespec &time2_ts);
timespec timespec_subtract(const timespec &time1_ts, const timespec &time2_ts);

#endif