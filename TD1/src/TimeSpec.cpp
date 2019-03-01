#include "TimeSpec.hpp"

double timespec_to_ms(const timespec& time_ts) {
    time_t seconds = time_ts.tv_sec;
    long nano_seconds = time_ts.tv_nsec;
    return((seconds * 1000) + (nano_seconds/1000000.0));
}

timespec timespec_from_ms(double time_ms) {
    struct timespec timer;
    // Dividing by 1000 instead of 1000.0 will floor automatically
    timer.tv_sec = time_ms/1000;
    // amount of milli seconds left after whole seconds taken out
    double milli_seconds_left = time_ms - (timer.tv_sec * 1000);

    if (timer.tv_sec < 0) {
        timer.tv_sec += 1;
        timer.tv_nsec = 10e9 - milli_seconds_left * 10e6;
    } else {
        timer.tv_nsec = milli_seconds_left * 10e6;
    }
    return timer;
}

timespec timespec_now() {
    struct timespec timer;
    clock_gettime(CLOCK_REALTIME, &timer);
    return timer;
}

timespec timespec_negate(const timespec& time_ts) {
    struct timespec timer;
    if (time_ts.tv_nsec != 0) {
        timer.tv_sec = - time_ts.tv_sec -1;
        timer.tv_nsec = - (10e9 - time_ts.tv_nsec);
    
    } else {
        timer.tv_nsec = 0;
        timer.tv_sec = -timer.tv_sec;
    }
    
    return timer;
}

timespec timespec_add(const timespec &time1_ts, const timespec &time2_ts) {
    struct timespec timer;
    timer.tv_nsec = time1_ts.tv_nsec + time2_ts.tv_nsec;
    timer.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec;
    if (timer.tv_nsec > 10e9) {
        timer.tv_nsec -= 10e9;
        timer.tv_sec += 1;
    }
    return timer;
}

timespec timespec_subtract(const timespec &time1_ts, const timespec &time2_ts) {
    struct timespec timer;
    double ns = time1_ts.tv_nsec - time2_ts.tv_nsec;
    timer.tv_sec = time1_ts.tv_sec - time2_ts.tv_sec;
    if (ns < 0) {
        timer.tv_nsec = - ns + 10e9;
        timer.tv_sec -= 1;
    } else {
        timer.tv_nsec = ns;
    }
    return timer;
}