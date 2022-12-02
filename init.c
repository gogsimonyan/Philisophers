#include "philo.h"

void init_philo(t_philo_data *philo_list, int philo_numbers, pthread_mutex_t *forks, long time_to_die, long time_to_eat, long time_to_sleep)
{
    int i = 0;
    struct timeval start;

    gettimeofday(&start, NULL);

    while (i < philo_numbers)
    {
        philo_list[i].index = i;
        philo_list[i].time_to_die = time_to_die;
        philo_list[i].time_to_eat = time_to_eat;
        philo_list[i].time_to_sleep = time_to_sleep;
        philo_list[i].left_fork = &forks[i];
        philo_list[i].right_fork = &forks[(i + 1) % philo_numbers];
        philo_list[i].eat_count = 0;
        philo_list[i].start_time = start.tv_sec * 1000 + start.tv_usec / 1000;
        pthread_create(&philo_list[i].id, NULL, &philo_action, &philo_list[i]);
        pthread_detach(philo_list[i].id);
        i++;
    }
}

void init_mutex(pthread_mutex_t *forks, int forks_number)
{
    int i = 0;
    int error_number = 0;

    while (i < forks_number)
    {
        error_number = pthread_mutex_init(&forks[i], NULL);
        if (error_number)
        {
            printf("Error when initializing mutex number %d\n", error_number);
            // clean();
        }
        i++;
    }
}