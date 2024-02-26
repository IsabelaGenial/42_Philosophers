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

int	ig_philo_dead(t_philo *philo, int time_die)
{
	long dead;

	dead = get_time();
	if (dead - philo->last_eat_time >= time_die)
		return (1);
	return (0);
}

int ig_philo_n_eat(t_philo *philo, int each_philos_eat)
{
	if (philo->eat_n >= each_philos_eat)
		return (1);
	return (0);
}

int waiter(t_main *dinner)
{
	while (369)
	{
		if (the_philo_die(dinner))
		{
			printf("die");
			exit(1); //maybe return, because need exit of threads.
		}
		if (dinner->info->each_philos_eat && the_philo_eat(dinner) == dinner->info->nu_philos)
		{
			printf("all philos eating");
			exit(1);
		}
	}
	return (0);
}
 int the_philo_die(t_main *dinner)
 {
	 int i;

	 i=0;
	 while (i < dinner->info->nu_philos)
	 {
		 if (ig_philo_dead(&dinner->philo[i], dinner->info->time_to_die))
			 return (1);
		 i++;
	 }
	 return (0);
 }

int the_philo_eat(t_main *dinner)
{
	int i;
	int eat;

	i=0;
	eat = 0;
	while (i < dinner->info->nu_philos)
	{
		if (ig_philo_n_eat(&dinner->philo[i], dinner->info->each_philos_eat))
			eat++;
		i++;
	}
	return (eat);
}


long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000L) + (time.tv_usec / 1000L));
}