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

void	sleep_think(t_philo *philo, long *current_time)
{
	*current_time = get_current_time(philo->start_time);
	printf("%ld %s %d %s\n", *current_time, "ms philo number", philo->index, "is sleeping");
	ft_sleep(philo->time_to_sleep);
	*current_time = get_current_time(philo->start_time);
	printf("%ld %s %d %s\n", *current_time, "ms philo number", philo->index, "is thinking");
}

void	*philo_action(void *philo_data)
{
	long	current_time;
	t_philo	*philo;

	philo = philo_data;
	if (philo->index % 2 == 0)
		usleep(200);
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		current_time = get_current_time(philo->start_time);
		printf("%ld %s %d %s\n", current_time, "ms philo number", philo->index, "has taken left fork");
		pthread_mutex_lock(philo->right_fork);
		current_time = get_current_time(philo->start_time);
		printf("%ld %s %d %s\n", current_time, "ms philo number", philo->index, "has taken right fork");
		philo->last_eating_time = get_current_time(philo->start_time);
		pthread_mutex_lock(&philo->eat);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->eat);
		pthread_mutex_lock(&philo->print);
		printf("%ld %s %d %s\n", current_time, "ms philo number", philo->index, "is eating");
		pthread_mutex_unlock(&philo->print);
		ft_sleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		sleep_think(philo, &current_time);
	}
}

int	is_died(t_philo philo)
{
	long	current_time;

	current_time = get_current_time(philo.start_time);
	if (current_time - philo.last_eating_time > philo.time_to_die)
	{
		pthread_mutex_lock(&philo.print);
		printf("%ld %s %d %s\n", current_time, "ms philo number", philo.index, "is died");
		return (1);
	}
	return (0);
}

int	is_finished(t_philo *philo)
{
	int	i;

	i = -1;
	if (philo->must_eat < 0)
		return (0);
	while (++i < philo->philo_num)
	{
		pthread_mutex_lock(&philo[i].eat);
		if (philo[i].eat_count < philo[i].must_eat)
		{
			pthread_mutex_unlock(&philo[i].eat);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].eat);
	}
	return (1);
}
