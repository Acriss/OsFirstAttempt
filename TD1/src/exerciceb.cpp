#include <iostream>
#include <string>
#include <time.h>

#include "TimeSpec.hpp"

void incr(unsigned int nLoops, double *pCounter)
{
    for (unsigned int i = 0; i < nLoops; i++) {
        *pCounter += 1;
    }
}

int exb(int argc, char const *argv[])
{
    unsigned int nLoops = 0;
    if (argc > 1)
    {
        nLoops = std::stoi(argv[1]);
    }
    else
    { // We find no argument, we go for default value
        nLoops = 15;
    }
    double counter = 0.0;
    timespec start = timespec_now();
    incr(nLoops, &counter);
    timespec end = timespec_now();
    timespec duration = end - start;
    std::cout << "Counter value: " << counter << std::endl;
    std::cout << "The execution lasted "
              << (double)duration.tv_sec + (double)duration.tv_nsec * 1e-9
              << " seconds." << std::endl;
    return 0;
}