#include "philo.h"

int main(int argc, char **argv)
{
	t_philo_data *philo_list;
	pthread_mutex_t *forks;
	int philo_numbers;
	int i = 0;
	int must_eat = 0;

	if(argc == 5 || argc == 6)
	{
		
		philo_numbers = atoi(argv[1]);
		philo_list = malloc(sizeof(t_philo_data) * philo_numbers);
		forks = malloc(sizeof(pthread_mutex_t) * philo_numbers);
		if(argc == 6)
		{
			must_eat = ft_atoi(argv[5]);
		}

		init_mutex(forks, philo_numbers);
		init_philo(philo_list, philo_numbers, forks, ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]));

		while (1)
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
				i++;
    		}
		}
	}
	else
	{
		printf("%s\n", "invalid argumnets");
	}
}
