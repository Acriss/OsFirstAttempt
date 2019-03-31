#include "Timespec.hpp"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <signal.h>
#include <iostream>
using namespace std;

void incrHandler(int sig, siginfo_t *si, void *)
{
    int *pcompteur = (int *)(si->si_value).sival_ptr;
    cout << "Compteur: " << *pcompteur << endl;
    *pcompteur += 1;
}

int main(int argc, char const *argv[])
{
    int limit = 15;

    struct sigaction sigact;
    sigact.sa_flags = SA_SIGINFO;
    sigact.sa_sigaction = incrHandler;
    sigemptyset(&sigact.sa_mask);
    sigaction(SIGRTMIN, &sigact, NULL);

    struct sigevent sigeven;
    sigeven.sigev_notify = SIGEV_SIGNAL;
    sigeven.sigev_signo = SIGRTMIN;
    int pcompteur = 0;

    sigeven.sigev_value.sival_ptr = &pcompteur;

    timer_t timer;
    timer_create(CLOCK_REALTIME, &sigeven, &tid);
    itimerspec its;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 500000000;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 500000000;

    timer_settime(timer, 0, &its, NULL);
    while (pcompteur < limit)
    {
        // Wait for the compteur simply to reach limit
    }
    timer_delete(timer);
    cout << "Compteur: " << pcompteur << endl;

    return 0;
}
