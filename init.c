/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gsimonya <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/12/04 17:40:53 by gsimonya		  #+#	#+#			 */
/*   Updated: 2022/12/04 17:40:54 by gsimonya		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo_list, pthread_mutex_t *forks, char **argv)
{
	int				i;
	struct timeval	start;

	i = -1;
	gettimeofday(&start, NULL);
	while (++i < ft_atoi(argv[1]))
	{
		philo_list[i].index = i;
		philo_list[i].philo_num = ft_atoi(argv[1]);
		philo_list[i].time_to_die = ft_atoi(argv[2]);
		philo_list[i].time_to_eat = ft_atoi(argv[3]);
		philo_list[i].time_to_sleep = ft_atoi(argv[4]);
		philo_list[i].left_fork = &forks[i];
		philo_list[i].right_fork = &forks[(i + 1) % philo_list[i].philo_num];
		philo_list[i].must_eat = -1;
		philo_list[i].eat_count = 0;
		if (argv[5])
			philo_list[i].must_eat = ft_atoi(argv[5]);
		philo_list[i].start_time = start.tv_sec * 1000 + start.tv_usec / 1000;
		pthread_create(&philo_list[i].id, NULL, &philo_action, &philo_list[i]);
		pthread_detach(philo_list[i].id);
	}
}

void	init_mutex(pthread_mutex_t *forks, int forks_number)
{
	int	i;
	int	error_number;

	i = 0;
	error_number = 0;
	while (i < forks_number)
	{
		error_number = pthread_mutex_init(&forks[i], NULL);
		if (error_number)
		{
			printf("Error when initializing mutex number %d\n", error_number);
		}
		i++;
	}
}
