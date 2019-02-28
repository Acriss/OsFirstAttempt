#include "Tests_TimeSpec.hpp"

TEST(TimeSpecToMS, NullTimeSpec) {
    timespec time;
    time.tv_nsec = 0;
    time.tv_sec = 0;
    EXPECT_EQ(timespec_to_ms(time), 0);
}