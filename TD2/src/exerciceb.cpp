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

void *call_incr(void *vector_data)
{
    Data *data = (Data *)vector_data;
    incr(data->nLoops, &(data->counter));
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Pas assez d'arguments !" << std::endl;
        return 1;
    }
    unsigned int nLoops = std::stoi(argv[1]);
    unsigned int nTasks = std::stoi(argv[2]);
    std::string order = "OTHER";
    if (argc > 3)
    {
        order = std::string(argv[3]);
        if (order != "RR" && order != "FIFO" && order != "OTHER")
        {
            order = "OTHER";
        }
    }
    if (order != "OTHER")
    {
        struct sched_param scheduleParam;
        unsigned int scheduleType = SCHED_OTHER;
        if (order == "RR")
            scheduleType = SCHED_RR;
        else if (order == "FIFO")
            scheduleType = SCHED_FIFO;
        scheduleParam.sched_priority = sched_get_priority_max(scheduleType);
        pthread_setschedparam(pthread_self(), scheduleType, &scheduleParam);
    }

    Data data{0.0, nLoops};

    pthread_attr_t attributes;
    pthread_attr_init(&attributes);

    struct sched_param schedParam;
    schedParam.sched_priority = 9;

    pthread_attr_setschedparam(&attributes, &schedParam);

    pthread_t tasks[nTasks];
    timespec start = timespec_now();
    for (unsigned int t = 0; t < nTasks; t++)
    {
        pthread_create(&tasks[t], &attributes, call_incr, &data);
    }
    for (unsigned int t = 0; t < nTasks; t++)
    {
        pthread_join(tasks[t], NULL);
    }
    timespec end = timespec_now();
    timespec duration = end - start;

    std::cout << nLoops << " " << nTasks << " " << duration.tv_sec << " " << duration.tv_nsec << std::endl;
    pthread_attr_destroy(&attributes);
    return 0;
}