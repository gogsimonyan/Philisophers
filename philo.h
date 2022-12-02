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
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	long last_eating_time;
	int eat_count;
	long start_time;
} t_philo_data;

void ft_sleep(long time);
long get_current_time(long start_time);
void *philo_action(void *philo_data);
int is_died(t_philo_data philo);
int check_args(char *str);
int ft_atoi(char *str);
void init_philo(t_philo_data *philo_list, int philo_numbers, pthread_mutex_t *forks, long time_to_die, long time_to_eat, long time_to_sleep);
void init_mutex(pthread_mutex_t *forks, int forks_number);