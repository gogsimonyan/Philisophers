#include "philo.h"

void ft_sleep(long time)
{
	struct timeval	start;
	struct timeval	now;
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
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000) - start_time);
}

void *philo(void *philo_data)
{
	long current_time;
	t_philo_data *philo = philo_data;
	if(philo->index % 2 == 0)
	{
		ft_sleep(10);
	}
	while(1)
	{	
		pthread_mutex_lock(&philo->left_fork);
		current_time = get_current_time(philo->start_time);
		printf("%s %d %s %ld %s\n","philo number", philo->index, "take left fork at", current_time, "ms");
		pthread_mutex_lock(&philo->right_fork);
		current_time = get_current_time(philo->start_time);
		printf("%s %d %s %ld %s\n","philo number", philo->index, "take right fork at", current_time, "ms");
		philo->last_eating_time = get_current_time(philo->start_time);
		philo->eat_count++;
		printf("%s %d %s %ld %s\n","philo number", philo->index, "is eating at", philo->last_eating_time, "ms");
		ft_sleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		current_time = get_current_time(philo->start_time);
		printf("%s %d %s %ld %s\n","philo number", philo->index, "is sleeping", current_time, "ms");
		ft_sleep(philo->time_to_sleep * 1000);
		current_time = get_current_time(philo->start_time);
		printf("%s %d %s %ld %s\n","philo number", philo->index, "is thinking", current_time, "ms");
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

int main(int argc, char **argv)
{
	t_philo_data *philo_list;
	struct timeval start;
	pthread_mutex_t *forks;
	int philo_numbers;
	int i = 0;
	int error_number;
	int must_eat = 0;

	if(argc == 5 || argc == 6)
	{
		gettimeofday(&start, NULL);
		philo_numbers = atoi(argv[1]);
		philo_list = malloc(sizeof(t_philo_data) * philo_numbers);
		forks = malloc(sizeof(pthread_mutex_t) * philo_numbers);
		if(argc == 6)
		{
			must_eat = atoi(argv[5]);
		}
		while(i < philo_numbers)
		{
			error_number = pthread_mutex_init(&forks[i], NULL);
			if(error_number)
			{
				printf("%s\n", "Error");
				return (0);
			}
			i++;
		}
		i = 0;
		while(i < philo_numbers)
		{
			philo_list[i].index = i;
			philo_list[i].time_to_die = atoi(argv[2]);
			philo_list[i].time_to_eat = atoi(argv[3]);
			philo_list[i].time_to_sleep = atoi(argv[4]);
			philo_list[i].left_fork = forks[i];
        	philo_list[i].right_fork = forks[(i + 1) % philo_numbers];
			philo_list[i].eat_count = 0;
			philo_list[i].start_time = start.tv_sec * 1000 + start.tv_usec / 1000;
			pthread_create(&philo_list[i].id, NULL, &philo, &philo_list[i]);
			pthread_detach(philo_list[i].id);
			i++;
		}
		while(1)
		{
			i = 0;
			while (i < philo_numbers)
			{
				if (is_died(philo_list[i]))
				{
					// clean();
					printf("%s\n", "Finish");
					return (0);
				}
    	}
    	return (0);
		}
	}
	else
	{
		printf("%s\n", "invalid argumnets");
	}
}