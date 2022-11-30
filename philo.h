#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo_data 
{
	pthread_t id;
	int index;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	pthread_mutex_t left_fork;
	pthread_mutex_t right_fork;
	long last_eating_time;
	int eat_count;
	long start_time;
} t_philo_data;