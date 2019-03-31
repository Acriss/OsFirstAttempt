#include <iostream>
#include <pthread.h>
#include <time.h>
#include "../../TD1/src/TimeSpec.hpp"

struct Data
{
    volatile double counter;
    unsigned int nLoops;
};

void incr(unsigned int nLoops, volatile double *pCounter)
{
    for (unsigned int i = 0; i < nLoops; i++)
        *pCounter += 1;
}

void *call_incr(void *v_data)
{
    Data *data = (Data *)v_data;
    incr(data->nLoops, &(data->counter));
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Pas assez d'arguments fournis" << std::endl;
        return 1;
    }
    unsigned int nLoops = std::stoi(argv[1]);
    unsigned int nTasks = std::stoi(argv[2]);

    Data data{0.0, nLoops};

    pthread_t tasks[nTasks];
    timespec start = timespec_now();
    for (unsigned int t = 0; t < nTasks; t++)
    {
        pthread_create(&tasks[t], NULL, call_incr, &data);
    }
    for (unsigned int t = 0; t < nTasks; t++)
    {
        pthread_join(tasks[t], NULL);
    }
    timespec end = timespec_now();
    timespec duration = end - start;
    std::cout << nLoops << " " << nTasks << " " << duration.tv_sec << " " << duration.tv_nsec << std::endl;

    std::cout << "Counter: " << (data.counter) << std::endl;
    return 0;
}