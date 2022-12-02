#include "philo.h"

void *philo_action(void *philo_data)
{
    long current_time;
    t_philo_data *philo = philo_data;
    if (philo->index % 2 == 0)
    {
        ft_sleep(10);
    }
    while (1)
    {
        pthread_mutex_lock(philo->left_fork);
        current_time = get_current_time(philo->start_time);
        printf("%s %d %s %ld %s\n", "philo number", philo->index, "take left fork at", current_time, "ms");
        pthread_mutex_lock(philo->right_fork);
        current_time = get_current_time(philo->start_time);
        printf("%s %d %s %ld %s\n", "philo number", philo->index, "take right fork at", current_time, "ms");
        philo->last_eating_time = get_current_time(philo->start_time);
        philo->eat_count++;
        printf("%s %d %s %ld %s\n", "philo number", philo->index, "is eating at", philo->last_eating_time, "ms");
        ft_sleep(philo->time_to_eat);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        current_time = get_current_time(philo->start_time);
        printf("%s %d %s %ld %s\n", "philo number", philo->index, "is sleeping", current_time, "ms");
        ft_sleep(philo->time_to_sleep);
        current_time = get_current_time(philo->start_time);
        printf("%s %d %s %ld %s\n", "philo number", philo->index, "is thinking", current_time, "ms");
    }
}

int is_died(t_philo_data philo)
{
    long current_time;
    long last_eating_time;
    current_time = get_current_time(philo.start_time);

    if (current_time - philo.last_eating_time > philo.time_to_die)
    {
        printf("%s %d %s\n", "philo number", philo.index, "is died");
        return (1);
    }
    else
        return (0);
}