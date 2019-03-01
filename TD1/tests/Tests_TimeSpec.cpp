#include "Tests_TimeSpec.hpp"

// timespec_to_ms
TEST(TimeSpecToMS, NullTimeSpec) {
    timespec time;
    time.tv_nsec = 0;
    time.tv_sec = 0;
    EXPECT_EQ(timespec_to_ms(time), 0);
}
TEST(TimeSpecToMS, AllPositiveTimeSpec) {
    timespec time;
    time.tv_sec = 1;
    time.tv_nsec = 900000;
    EXPECT_EQ(timespec_to_ms(time), 1000.9);
}
TEST(TimeSpecToMS, NegativeNSTimespec) {
    timespec time;
    time.tv_sec = -1;
    time.tv_nsec = 900000;
    EXPECT_EQ(timespec_to_ms(time), -0.1);
}

// timespec_from_ms
TEST(TimeSpecFromMS, NullTimeSpec) {
    timespec time;
    time.tv_nsec = 0;
    time.tv_sec = 0;
    EXPECT_EQ(timespec_from_ms(0), time);
}
TEST(TimeSpecFromMS, AllPositiveTimeSpec) {
    timespec time;
    time.tv_sec = 1;
    time.tv_nsec = 900000;
    EXPECT_EQ(timespec_from_ms(1000.9), time);
}
TEST(TimeSpecFromMS, NegativeNSTimespec) {
    timespec time;
    time.tv_sec = -1;
    time.tv_nsec = 900000;
    EXPECT_EQ(timespec_from_ms(-0.1), time);
}

// test timespec_negate
TEST(TimeSpecNegate, NullTimeSpec) {
    timespec time, compared;
    time.tv_sec = 0;
    time.tv_nsec = 0;
    compared.tv_sec = 0;
    compared.tv_nsec = 0;
    EXPECT_EQ(compared, timespec_negate(time));
}
TEST(TimeSpecNegate, AllPositiveTimeSpec) {
    timespec time, compared;
    time.tv_sec = 1;
    time.tv_nsec = 10e8;
    compared.tv_sec = -2;
    compared.tv_nsec = 9*10e8;
    EXPECT_EQ(compared, timespec_negate(time));
}
TEST(TimeSpecNegate, NullS_PositiveNS_TimeSpec) {
    timespec time, compared;
    time.tv_sec = 0;
    time.tv_nsec = 10e8;
    compared.tv_sec = -1;
    compared.tv_nsec = 9*10e8;
    EXPECT_EQ(compared, timespec_negate(time));
}
TEST(TimeSpecNegate, PositiveS_NullNS_TimeSpec) {
    timespec time, compared;
    time.tv_sec = 1;
    time.tv_nsec = 0;
    compared.tv_sec = -1;
    compared.tv_nsec = 0;
    EXPECT_EQ(compared, timespec_negate(time));
}
TEST(TimeSpecNegate, NegativeS_NullNS_TimeSpec) {
    timespec time, compared;
    time.tv_sec = -1;
    time.tv_nsec = 0;
    compared.tv_sec = 1;
    compared.tv_nsec = 0;
    EXPECT_EQ(compared, timespec_negate(time));
}
TEST(TimeSpecNegate, NegativeS_PositiveNS_TimeSpec) {
    timespec time, compared;
    time.tv_sec = -1;
    time.tv_nsec = 10e8;
    compared.tv_sec = 0;
    compared.tv_nsec = 9*10e8;
    EXPECT_EQ(compared, timespec_negate(time));
}

// Test timespec_add
