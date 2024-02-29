/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:19:57 by igenial           #+#    #+#             */
/*   Updated: 2024/02/26 13:27:44 by igenial          ###   ########.fr       */
/*                                                                            */
/* ****************************************************************************/

#include "philo.h"

int the_philo_die(t_main *dinner);
int the_philo_eat(t_main *dinner);

int	ig_philo_dead(t_philo *philo, long time_die)
{
	long dead;

	dead = get_time();
	if (dead - philo->last_eat_time > time_die)
	{
		dead = dead - philo->last_eat_time;
		philo->state = (t_philo_state) {DEAD, dead};
		return (1);
	}
	return (0);
}

int ig_philo_n_eat(t_philo *philo, int each_philos_eat)
{
	if (philo->eat_n == each_philos_eat)
		return (1);
	return (0);
}

int waiter(t_main *dinner)
{
	int philo;

	while (369)
	{
		philo = the_philo_die(dinner);
		if (philo > -1)
		{
			pthread_mutex_lock(&dinner->mx_dead_philo);
			dinner->dead_philo = philo;
			printf("\n%i\n", philo + 1);
			pthread_mutex_unlock(&dinner->mx_dead_philo);
			print_state(&dinner->philo[philo], DEAD);
			pthread_mutex_lock(&dinner->mx_print);
			break;
		}
		if (dinner->info->each_philos_eat
			&& the_philo_eat(dinner) == dinner->info->nu_philos - 1)
		{
			pthread_mutex_lock(&dinner->mx_print);
			pthread_mutex_lock(&dinner->mx_each_ate_enough);
			dinner->each_philos_eat = the_philo_eat(dinner);
			pthread_mutex_unlock(&dinner->mx_each_ate_enough);
//			print_state(&dinner->philo[dinner->each_philos_eat], DEAD);
			break;
		}
	}
	return (0);
}
 int the_philo_die(t_main *dinner)
 {
	 int i;

	 i = 0;
	 pthread_mutex_lock(&dinner->mx_phlio_state);
	 while (i < dinner->info->nu_philos)
	 {
		 if (ig_philo_dead(&dinner->philo[i], dinner->info->time_to_die))
		 {
			 pthread_mutex_unlock(&dinner->mx_phlio_state);
			 return (i);
		 }
		 i++;
	 }
	 pthread_mutex_unlock(&dinner->mx_phlio_state);
	 return (-1);
 }

int the_philo_eat(t_main *dinner)
{
	int i;
	int eat;

	i = 0;
	eat = 0;
	pthread_mutex_lock(&dinner->mx_phlio_state);
	while (i < dinner->info->nu_philos)
	{
		if (ig_philo_n_eat(&dinner->philo[i], dinner->info->each_philos_eat))
			eat++;
		i++;
	}
	pthread_mutex_unlock(&dinner->mx_phlio_state);
	return (eat);
}


long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int ig_the_check(t_main *dinner, int the_end)
{
	pthread_mutex_lock(&dinner->mx_each_ate_enough);
	pthread_mutex_lock(&dinner->mx_dead_philo);
	if(dinner->dead_philo != -1 || dinner->each_philos_eat != 0)
	{
		pthread_mutex_unlock(&dinner->mx_each_ate_enough);
		pthread_mutex_unlock(&dinner->mx_dead_philo);
		printf("check\n");
		if(the_end)
		{
			exit(0);
		}
		return (1);
	}
	pthread_mutex_unlock(&dinner->mx_each_ate_enough);
	pthread_mutex_unlock(&dinner->mx_dead_philo);
	return (0);
}