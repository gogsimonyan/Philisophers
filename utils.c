#include "philo.h"

void ft_sleep(long time)
{
    struct timeval start;
    struct timeval now;
    long present;

    gettimeofday(&now, NULL);
    present = 0;
    while (present < time)
    {
        usleep(100);
        gettimeofday(&start, NULL);
        present = (start.tv_sec * 1000 + start.tv_usec / 1000) - (now.tv_sec * 1000 + now.tv_usec / 1000);
    }
}

long get_current_time(long start_time)
{
    struct timeval current_time;

    gettimeofday(&current_time, NULL);
    return ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000) - start_time);
}

int check_args(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

int ft_atoi(char *str)
{
    int result = 0;

    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-' || *str == '+')
        str++;
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + *str - '0';
        str++;
    }
    return (result);
}