#include <iostream>
#include <string>
#include <time.h>


void incr(unsigned int nLoops, double *pCounter) {
    for (unsigned int i = 0; i < nLoops; i++) {
        *pCounter += 1;
    }
}

int exb(int argc, char const *argv[])
{
    unsigned int nLoops = std::stoi(argv[1]);
    double counter = 0.0;
    incr(nLoops, &counter);
    std::cout << counter << std::endl;
    return 0;
}