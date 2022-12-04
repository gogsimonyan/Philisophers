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
	printf("%s %d %s %ld %s\n", "philo number",
		philo->index, "is sleeping", *current_time, "ms");
	ft_sleep(philo->time_to_sleep);
	*current_time = get_current_time(philo->start_time);
	printf("%s %d %s %ld %s\n", "philo number",
		philo->index, "is thinking", *current_time, "ms");
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
		printf("%s %d %s %ld %s\n", "philo number",
			philo->index, "take left fork at", current_time, "ms");
		pthread_mutex_lock(philo->right_fork);
		current_time = get_current_time(philo->start_time);
		printf("%s %d %s %ld %s\n", "philo number",
			philo->index, "take right fork at", current_time, "ms");
		philo->last_eating_time = get_current_time(philo->start_time);
		philo->eat_count++;
		printf("%s %d %s %ld %s\n", "philo number",
			philo->index, "is eating at", philo->last_eating_time, "ms");
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
		printf("%s %d %s\n", "philo number", philo.index, "is died");
		return (1);
	}
	return (0);
}
