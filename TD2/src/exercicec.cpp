#include <iostream>
#include <pthread.h>
#include <time.h>
#include "../../TD1/src/TimeSpec.hpp"

struct Data
{
    volatile double counter;
    unsigned int nLoops;
    bool has_protection;
    pthread_mutex_t mutex;
};

void incr(unsigned int nLoops, volatile double *pCounter)
{
    for (unsigned int i = 0; i < nLoops; i++)
    {
        *pCounter += 1;
    }
}

void incr_mutex(unsigned int nLoops, volatile double *pCounter, pthread_mutex_t *mutex)
{
    for (unsigned int i = 0; i < nLoops; i++)
    {
        pthread_mutex_lock(mutex);
        *pCounter += 1;
        pthread_mutex_unlock(mutex);
    }
}

void *call_incr(void *v_data)
{
    Data *data = (Data *)v_data;
    if (data->has_protection)
    {
        incr_mutex(data->nLoops, &(data->counter), &(data->mutex));
    }
    else
    {
        incr(data->nLoops, &(data->counter));
    }
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
    bool protected_bool = false;

    if (argc > 3)
    {
        std::string protection = std::string(argv[3]);
        if (protection == "protected")
        {
            protected_bool = true;
        }
    }

    Data data{0.0, nLoops, protected_bool};
    std::cout << data.has_protection << std::endl;
    if (protected_bool)
    {
        pthread_mutex_init(&data.mutex, NULL);
    }

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

    if (protected_bool)
    {
        pthread_mutex_destroy(&data.mutex);
    }

    timespec end = timespec_now();
    timespec duration = end - start;
    std::cout << nLoops << " " << nTasks << " " << duration.tv_sec << " " << duration.tv_nsec << std::endl;
    std::cout << "Compteur: " << (data.counter) << std::endl;
    return 0;
}