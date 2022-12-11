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

#ifndef PHILO_H

# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo_data
{
	pthread_t		id;
	int				index;
	int				philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	print;
	pthread_mutex_t	eat;
	long			last_eating_time;
	int				eat_count;
	int				must_eat;
	long			start_time;
}	t_philo;

void	ft_sleep(long time);
long	get_current_time(long start_time);
void	*philo_action(void *philo_data);
int		is_died(t_philo philo);
int		check_args(char **str);
int		ft_atoi(char *str);
void	init_philo(t_philo *philo_list, pthread_mutex_t *forks, char **argv);
void	init_mutex(pthread_mutex_t *forks, int forks_number);
int		is_finished(t_philo *philo);

#endif