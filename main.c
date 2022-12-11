/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gsimonya <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/12/04 17:40:53 by gsimonya		  #+#	#+#			 */
/*   Updated: 2022/12/04 17:59:00 by gsimonya         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

void clean(t_philo *philo_list, pthread_mutex_t	*forks)
{
	int i;

	i = 0;
	while(i < philo_list->philo_num)
	{
		pthread_mutex_destroy(philo_list[i].left_fork);
		pthread_mutex_destroy(philo_list[i].right_fork);
		pthread_mutex_destroy(&philo_list[i].print);
		i++;
	}
	free(philo_list);
	free(forks);
}

int	main(int argc, char **argv)
{
	t_philo			*philo_list;
	pthread_mutex_t	*forks;
	int				i;

	if ((argc == 5 || argc == 6) && check_args(argv))
	{
		philo_list = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
		forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
		init_mutex(forks, ft_atoi(argv[1]));
		init_philo(philo_list, forks, argv);
		while (1)
		{
			i = 0;
			while (i < philo_list->philo_num)
			{
				if (is_died(philo_list[i]) || is_finished(philo_list))
				{
					clean(philo_list, forks);
					printf("Finish\n"); 
					pthread_mutex_unlock(&philo_list[i].print);
					return 0;
				}
				i++;
			}
		}
	}
	printf("invalid argumnets\n");
}
